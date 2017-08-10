%output  "parser.cxx"
%defines "parser.hxx"

%skeleton "lalr1.cc" // C++ parser interface
%require  "3" // require bison version
%parse-param  { yy::scanner* scanner } { ParserCallback* cb } // add parser members
%locations // call yylex with a location

%define parse.error verbose // increase usefulness of error messages
%define parse.assert // assert correct cleanup of semantic value objects

%define api.value.type variant
%define api.token.prefix {T_}

%define parse.trace
%right UNARY

%token                  END     0   "end of file"

%token <std::string>    NAME
%token <std::string>    LNAME
%type  <std::string>    filename
%token <double>         NUM
%token <int>            SIGN
                        REL
                        INCLUDE
                        MEMORY
                        ORIGIN
                        LENGTH
                        AT
                        ALIGN_K
                        SUBALIGN
                        ALIGN_WITH_INPUT
                        OUTPUT
                        OUTPUT_ARCH
                        OUTPUT_FORMAT
                        SEARCH_DIR
                        EXTERN
                        TARGET_K
                        REGION_ALIAS
                        REGION_MAP
                        LD_FEATURE
                        FLOAT
                        NOFLOAT
                        STARTUP
                        SIZEOF_HEADERS
                        ABSOLUTE_
                        ADDR
                        ALIGNOF
                        ASSERT_K
                        BLOCK
                        CONSTANT
                        DATA_SEGMENT_ALIGN
                        DATA_SEGMENT_END
                        DATA_SEGMENT_RELRO_END
                        DEFINED
                        INT
                        LOADADDR
                        LOG2CEIL
                        MAX_K
                        MIN_K
                        NEXT
                        SEGMENT_START
                        SIZEOF
                        LSHIFTEQ
                        RSHIFTEQ
                        OROR
                        EQ
                        NE
                        GE
                        LE
                        LSHIFT
                        RSHIFT
                        PLUSEQ
                        MINUSEQ
                        MULTEQ
                        DIVEQ
                        ANDEQ
                        OREQ
                        ANDAND
                        VERSIONK
                        BIND
                        ENTRY
                        MAP
                        INPUT
                        AS_NEEDED
                        CREATE_OBJECT_SYMBOLS
                        CONSTRUCTORS
                        FORCE_COMMON_ALLOCATION
                        INHIBIT_COMMON_ALLOCATION
                        SECTIONS
                        INSERT_K
                        AFTER
                        BEFORE
                        FILL
                        HLL
                        SYSLIB
                        QUAD
                        SQUAD
                        LONG
                        SHORT
                        BYTE
                        NOCROSSREFS
                        NOCROSSREFS_TO
                        OVERLAY
                        SORT_BY_NAME
                        SORT_BY_ALIGNMENT
                        SORT_NONE
                        NOLOAD
                        DSECT
                        COPY
                        INFO
                        ONLY_IF_RO
                        ONLY_IF_RW
                        SPECIAL
                        INPUT_SECTION_FLAGS
                        PHDRS
                        HIDDEN
                        PROVIDE
                        PROVIDE_HIDDEN
                        KEEP
                        EXCLUDE_FILE
                        GROUP
                        VERS_TAG
                        VERS_IDENTIFIER
                        GLOBAL
                        LOCAL
                        SORT_BY_INIT_PRIORITY
                        CORE_SYM
                        FLAGS

%type <ast::Includes>       includes

%type <ast::Region>         memory_spec
%type <ast::Regions>        memory_spec_list
%type <std::string>         length_spec
%type <uint64_t>            origin_spec
%type <std::string>         attributes_opt

%code requires 
{
  #include <iostream>
  #include <stdexcept>
  #include <string>

  #include "ast.hpp"
  #include "location.hh"

  using namespace std;

  namespace yy
  {
    class scanner;
  };

  // results
  struct ParserCallback 
  {
    virtual void memInit(ast::Regions) = 0;
    virtual void includeFiles(ast::Includes) = 0;
    virtual void secInit(ast::Sections) = 0;
  };
}

%code
{
  #include <iostream>
  #include <utility> // move
  #include <string>
  #include <sstream>

  #include "parsemanager.h"
  #include "scanner.hpp"

  using std::move;

  #undef yylex
  #define yylex scanner->lex

  ParseManager* pm = ParseManager::instance()->instance();

  template <class T, class V>
  T&& enlist(T& t, V& v)
  {
    t.push_back(move(v));
    return move(t);
  }
}

%%

script_file : ifile_list 
            ;

ifile_list  :  ifile_p1 /*ifile_list*/
            ;

/* ------------------------ intro ------------------------ */ 
ifile_p1   : includes { cb->includeFiles(move($1)); } ifile_p1
            | MEMORY '{' memory_spec_list region_map '}' { cb->memInit(move($3)); } ifile_p1
            | SECTIONS '{' sec_or_group_p1 '}' ifile_p1
            | phdrs ifile_p1 ifile_p1
            | startup ifile_p1 
            | high_level_library ifile_p1
            | low_level_library ifile_p1
            | floating_point_support ifile_p1
            | statement_anywhere ifile_p1
            | version ifile_p1
            | ';' ifile_p1
            | TARGET_K '(' NAME ')' { pm->target_k_ = move($3); } ifile_p1
            | SEARCH_DIR '(' NAME ')' { pm->search_dir_ = move($3); } ifile_p1
            | OUTPUT '(' NAME ')' { pm->output_ = move($3); } ifile_p1
            | OUTPUT_FORMAT '(' NAME ')' { pm->output_format_ = new OutputFormat(move($3), "", ""); } ifile_p1
            | OUTPUT_FORMAT '(' NAME ',' NAME ',' NAME ')'{ pm->output_format_ = new OutputFormat(move($3), move($5), move($7)); } ifile_p1
            | OUTPUT_ARCH '(' NAME ')' { pm->output_arch_ = move($3); } ifile_p1
            | FORCE_COMMON_ALLOCATION ifile_p1
            | INHIBIT_COMMON_ALLOCATION ifile_p1
            | INPUT '(' input_list ')'
            | GROUP '(' input_list ')'
            | MAP '(' filename ')' ifile_p1
            | NOCROSSREFS '(' nocrossref_list ')' ifile_p1
            | NOCROSSREFS_TO '(' nocrossref_list ')' ifile_p1
            | EXTERN '(' extern_name_list ')' ifile_p1
            | INSERT_K AFTER NAME ifile_p1
            | INSERT_K BEFORE NAME ifile_p1
            | REGION_ALIAS '(' NAME ',' NAME ')' { pm->addRegionAlias(move($5) , move($3)); } ifile_p1
            | LD_FEATURE '(' NAME ')' {} ifile_p1
            | core_sym '=' exp ';' ifile_p1
            |
            ;

core_sym : CORE_SYM '(' NAME ')'
         ;
    
filename : NAME
         ;

input_list: input_list1
          ;

input_list1:    NAME
                | input_list1 ',' NAME
                | input_list1 NAME
                | LNAME
                | input_list1 ',' LNAME
                | input_list1 LNAME
                | AS_NEEDED '('input_list1 ')'
                | input_list1 ',' AS_NEEDED '('input_list1 ')'
                | input_list1 AS_NEEDED '('input_list1 ')'
                ;

/* Parsed as expressions so that commas separate entries */
extern_name_list: extern_name_list_body
extern_name_list_body : NAME 
                      | extern_name_list_body NAME
                      | extern_name_list_body ',' NAME
                      ;

floating_point_support : FLOAT
                       | NOFLOAT
                       ;

/* ------------------------ include ------------------------ */ 
includes    : includes INCLUDE NAME { $$ = enlist($1, $3); }
            |
            ;
            
/* ------------------------ memory ------------------------ */ 
region_map : REGION_MAP '(' NAME ',' ORIGIN '(' NAME ')' ',' LENGTH '(' NAME ')' ',' ORIGIN '(' NAME ')' ')'
           |
           ;

memory_spec_list : memory_spec_list opt_comma memory_spec { $$ = enlist($1, $3); }
                 | 
                 ;
             
memory_spec : NAME attributes_opt ':' origin_spec opt_comma length_spec { $$ = {$1, 
                                                                                $2, 
                                                                                $4, 
                                                                                pm->calculateNumber(move($6))};
                                                                        }            
            ;

opt_comma : ','
          |
          ;

origin_spec : ORIGIN '=' NAME { $$ = { pm->calculateNumber(move($3)) }; }
            ;

length_spec : LENGTH '=' NAME { $$ = {$3}; }
            ;

attributes_opt : /* empty */ {/* dummy action to avoid bison 1.25 error message */}
               | '(' NAME ')' { $$ = $2; pm->checkFlags(move($2)); }
               | '(' '!' NAME ')' { $$ = "!"+$3; pm->checkFlags(move("!"+$3)); }
               | '(' NAME '!' NAME ')' { $$ = $2+"!"+$4; pm->checkFlags(move($2+"!"+$4));}
               ;

startup : STARTUP '(' filename ')' 
        ;

high_level_library  : HLL '(' high_level_library_NAME_list ')'
                    | HLL '(' ')' 
                    ;

high_level_library_NAME_list    : high_level_library_NAME_list opt_comma filename 
                                | filename 
                                ;

low_level_library   : SYSLIB '(' low_level_library_NAME_list ')'
                    ;

low_level_library_NAME_list : low_level_library_NAME_list opt_comma filename 
                            |
                            ;

/* ------------------------ include ------------------------ */ 
sec_or_group_p1 : sec_or_group_p1 section 
                | sec_or_group_p1 statement_anywhere
                |
                ;

nocrossref_list : /* empty */{ /* $$ = NULL; */ }
                | NAME nocrossref_list
                | NAME ',' nocrossref_list
                ;

mustbe_exp: exp 
          ;
                  
exp : '-' exp %prec UNARY 
    | '(' exp ')'
    | NEXT '(' exp ')' %prec UNARY
    | '!' exp %prec UNARY
    | '+' exp %prec UNARY 
    | '~' exp %prec UNARY
    | exp '*' exp
    | exp '/' exp 
    | exp '%' exp 
    | exp '+' exp 
    | exp '-' exp 
    | exp LSHIFT exp 
    | exp RSHIFT exp
    | exp EQ exp 
    | exp NE exp 
    | exp LE exp 
    | exp GE exp 
    | exp '<' exp
    | exp '>' exp
    | exp '&' exp 
    | exp '^' exp
    | exp '|' exp 
    | exp '?' exp ':' exp 
    | exp ANDAND exp 
    | exp OROR exp 
    | DEFINED '(' NAME ')' 
    | INT
    | SIZEOF_HEADERS 
    | ALIGNOF '(' NAME ')' 
    | SIZEOF '(' NAME ')' 
    | ADDR '(' NAME ')' 
    | LOADADDR '(' NAME ')' 
    | CONSTANT '(' NAME ')' 
    | ABSOLUTE_ '(' exp ')' 
    | ALIGN_K '(' exp ')' 
    | ALIGN_K '(' exp ',' exp ')' 
    | DATA_SEGMENT_ALIGN '(' exp ',' exp ')' 
    | DATA_SEGMENT_RELRO_END '(' exp ',' exp ')' 
    | DATA_SEGMENT_END '(' exp ')' 
    | SEGMENT_START '(' NAME ',' exp ')'
    | BLOCK '(' exp ')'
    | core_sym
    | NAME 
    | MAX_K '(' exp ',' exp ')'
    | MIN_K '(' exp ',' exp ')'
    | ASSERT_K '(' exp ',' NAME ')'
    | ORIGIN '(' NAME ')' 
    | LENGTH '(' NAME ')' 
    | LOG2CEIL '(' exp ')' 
    | DEFINED '(' core_sym ')'
    ;

memspec_at_opt: AT '>' NAME 
              |
              ;

opt_at : AT '(' exp ')' 
       |
       ;

opt_align : ALIGN_K '(' exp ')' 
          |
          ;

opt_flag : FLAGS '(' NAME ')' 
         | 
         ;

sect_constraint : ONLY_IF_RO
                | ONLY_IF_RW
                | SPECIAL 
                |
                ;
          
opt_align_with_input: ALIGN_WITH_INPUT 
                    | 
                    ;

opt_subalign: SUBALIGN '(' exp ')'
            | 
            ;
            
opt_exp_without_type: exp ':'
                    | ':' 
                    ;
                      
section :   NAME 
            opt_exp_with_type 
            opt_at 
            opt_align 
            opt_flag
            opt_align_with_input 
            opt_subalign 
            sect_constraint 
            '{' statement_list_opt '}'
            memspec_opt memspec_at_opt phdr_opt fill_opt opt_comma 
            | OVERLAY opt_exp_without_type opt_nocrossrefs opt_at opt_subalign
            '{' overlay_section '}'
            memspec_opt memspec_at_opt phdr_opt fill_opt opt_comma
            | /* The GROUP case is just enough to support the gcc
                   svr3.ifile script.  It is not intended to be full
                   support.  I'm not even sure what GROUP is supposed
                   to mean.  */
            GROUP opt_exp_with_type '{' sec_or_group_p1 '}'
            | INCLUDE filename sec_or_group_p1 END 
            ;
            
type  : NOLOAD 
      | DSECT
      | COPY
      | INFO
      | OVERLAY
      ;

atype: '(' type ')'
       | /* EMPTY */
       | '(' ')'
       ;

// todo ldgram.y line 1149
opt_exp_with_type : exp atype ':'
                  |  exp atype NAME ':' 
                  | atype ':' 
                   /* The BIND cases are to support the gcc svr3.ifile
		   script.  They aren't intended to implement full
		   support for the BIND keyword.  I'm not even sure
		   what BIND is supposed to mean.  */
                  | BIND '(' exp ')' atype ':'
                  | BIND '(' exp ')' BLOCK '(' exp ')' atype ':' 
                  ;

opt_nocrossrefs : /* empty */ 
                | NOCROSSREFS 
                ;

memspec_opt : '>' NAME 
            | { /*$$ = DEFAULT_MEMORY_REGION;*/ }
            | '>' core_sym 
            ;

phdr_opt  : /* empty */
          | phdr_opt ':' NAME 
          ;
            
overlay_section:  /* empty */
                  | overlay_section NAME '{' statement_list_opt '}'
                  phdr_opt fill_opt
                  opt_comma
                  ;
                  
phdrs : PHDRS '{' phdr_list '}'
      ;

phdr_list   : /* empty */
            | phdr_list phdr
            ;

phdr :  NAME phdr_type phdr_qualifiers ';'
     ;

phdr_type : exp 
          ;

phdr_qualifiers : /* empty */
                | NAME phdr_val phdr_qualifiers 
                | AT '(' exp ')' phdr_qualifiers 
                ;

phdr_val    : /* empty */
            | '(' exp ')' 
            ;

/* This is used within a normal linker script file.  */
version : VERSIONK '{' vers_nodes '}'
        ;

vers_nodes  : vers_node
            | vers_nodes vers_node
            ;

vers_node   : '{' vers_tag '}' ';' 
            | VERS_TAG '{' vers_tag '}' ';' 
            | VERS_TAG '{' vers_tag '}' verdep ';' 
            ;

verdep  : VERS_TAG
        | verdep VERS_TAG
        ;

vers_tag    : /* empty */
            | vers_defns ';' 
            | GLOBAL ':' vers_defns ';'
            | LOCAL ':' vers_defns ';'
            | GLOBAL ':' vers_defns ';' LOCAL ':' vers_defns ';'
            ;

vers_defns  : VERS_IDENTIFIER 
            | NAME
            | vers_defns ';' VERS_IDENTIFIER 
            | vers_defns ';' NAME 
            | vers_defns ';' EXTERN NAME '{' vers_defns opt_semicolon '}' 
            | EXTERN NAME '{' vers_defns opt_semicolon '}'
            | GLOBAL
            | vers_defns ';' GLOBAL
            | LOCAL 
            | vers_defns ';' LOCAL 
            | EXTERN
            | vers_defns ';' EXTERN
            ;

opt_semicolon   : /* empty */
                | ';'
                ;

fill_exp: mustbe_exp 
        ;

fill_opt  : '=' fill_exp
          | /* empty */
          ;

assign_op : PLUSEQ 
          | MINUSEQ 
          | MULTEQ 
          | DIVEQ 
          | LSHIFTEQ 
          | RSHIFTEQ 
          | ANDEQ 
          | OREQ 
          ;

end : ';' | ','
    ;

assignment  : NAME '=' mustbe_exp
            | NAME assign_op mustbe_exp
            | HIDDEN '(' NAME '=' mustbe_exp ')'
            | PROVIDE '(' NAME '=' mustbe_exp ')'
            | PROVIDE_HIDDEN '(' NAME '=' mustbe_exp ')'
            ;

statement_anywhere  : ENTRY '(' NAME ')' { pm->entry_ = move($3); }
                    | assignment end
                    | ASSERT_K '(' exp ',' NAME ')'
                    ;

/* The '*' and '?' cases are there because the lexer returns them as
separate tokens rather than as NAME.  */
wildcard_name: NAME
             | NAME '*'
             | '*' 
             | '?'
             ;

wildcard_spec   : wildcard_name
                | EXCLUDE_FILE '(' exclude_name_list ')' wildcard_name 
                | SORT_BY_NAME '(' wildcard_name ')' 
                | SORT_BY_ALIGNMENT '(' wildcard_name ')' 
                | SORT_NONE '(' wildcard_name ')'
                | SORT_BY_NAME '(' SORT_BY_ALIGNMENT '(' wildcard_name ')' ')'
                | SORT_BY_NAME '(' SORT_BY_NAME '(' wildcard_name ')' ')'
                | SORT_BY_ALIGNMENT '(' SORT_BY_NAME '(' wildcard_name ')' ')'
                | SORT_BY_ALIGNMENT '(' SORT_BY_ALIGNMENT '(' wildcard_name ')' ')' 
                | SORT_BY_NAME '(' EXCLUDE_FILE '(' exclude_name_list ')' wildcard_name ')'
                | SORT_BY_INIT_PRIORITY '(' wildcard_name ')'
                ;

sect_flag_list: NAME 
              | sect_flag_list '&' NAME 
              ;

sect_flags: INPUT_SECTION_FLAGS '(' sect_flag_list ')'
          ;

exclude_name_list: exclude_name_list wildcard_name 
                 | wildcard_name
                 ;

file_NAME_list: file_NAME_list opt_comma wildcard_spec
              | wildcard_spec 
              ;
                    
input_section_spec_no_keep: NAME 
                            | sect_flags NAME 
                            | '[' file_NAME_list ']'
                            | sect_flags '[' file_NAME_list ']'
                            | wildcard_spec '(' file_NAME_list ')'
                            | sect_flags wildcard_spec '(' file_NAME_list ')'
                            ;
                    
input_section_spec: input_section_spec_no_keep
                    | KEEP '(' input_section_spec_no_keep ')'
                    ;
                   
statement:  assignment end
            | CREATE_OBJECT_SYMBOLS
            | ';'
            | CONSTRUCTORS
            | SORT_BY_NAME '(' CONSTRUCTORS ')'
            | input_section_spec
            | length '(' mustbe_exp ')'
            | FILL '(' fill_exp ')'
            | ASSERT_K '(' exp ',' NAME ')' end
            | INCLUDE filename statement_list_opt END
            ;

statement_list: statement_list statement
              | statement
              ;

statement_list_opt: /* empty */
                  | statement_list
                  ;

length: QUAD 
        | SQUAD 
        | LONG 
        | SHORT 
        | BYTE
        ;
%%

void yy::parser::error(const parser::location_type& l, const std::string& m)
{
  throw yy::parser::syntax_error(l, m);
}
