%option     outfile="scanner.cxx"
%option header-file="scanner.hxx"

%option yylineno
%option c++
%option 8bit warn nodefault
%option noyywrap
%option debug

%x incl

%{
    #include <string>
    #include <iostream>
    #include <stdexcept>
    #include <cstdlib>
    #include <fstream>

    #include "parser.hxx"
    #include "scanner.hpp"
    #include "parsemanager.h"

    using namespace std;

    ParseManager* pmr = ParseManager::instance()->instance();

    #define YIELD_TOKEN(tok, val, type)     yylval->build<type>(val); \
                                            cout << "val: " << val << endl; \
                                            return yy::parser::token::T_##tok;

    #define YY_TXT                  std::string(yytext, yyleng)
    #define YY_NUM                  std::atof(yytext)

    #define INT_TOKEN(tok, val)     cout << "int token" << endl; YIELD_TOKEN(tok, val, int)
    #define NUM_TOKEN(tok)          YIELD_TOKEN(tok, YY_NUM, double)
    #define STR_TOKEN(tok)          cout << "str_tok " << YY_TXT << endl; YIELD_TOKEN(tok, YY_TXT, std::string)
    #define LITERAL                 cout << "Literal: " << yytext[0] << endl; return yytext[0];

    // before executing an action, set the length of the location from
    // the length of the matched pattern:
    #define YY_USER_ACTION          yylloc->columns(yyleng);
%}

CMDFILENAMECHAR   [_a-zA-Z0-9\/\.\\_\+\$\:\[\]\\\,\=\&\!\<\>\-\~]
CMDFILENAMECHAR1  [_a-zA-Z0-9\/\.\\_\+\$\:\[\]\\\,\=\&\!\<\>\~]
FILENAMECHAR1     [_a-zA-Z\/\.\\\$\_\~]
SYMBOLCHARN       [_a-zA-Z\/\.\\\$\_\~0-9]
FILENAMECHAR	  [_a-zA-Z0-9\/\.\-\_\+\=\$\:\[\]\\\,\~]
NOCFILENAMECHAR	  [_a-zA-Z0-9\/\.\-\_\+\$\:\[\]\\\~]

WILDCHAR	  ["*"]

V_TAG           [.$_a-zA-Z][._a-zA-Z0-9]*
V_IDENTIFIER    [*?.$_a-zA-Z\[\]\-\!\^\\]([*?.$_a-zA-Z0-9\[\]\-\!\^\\]|::)*

%%

%{
    yylloc->step();
%}

"<<="                       INT_TOKEN(LSHIFTEQ, ast::LSHIFTEQ)
">>="                       INT_TOKEN(RSHIFTEQ, ast::RSHIFTEQ)
"||"                        INT_TOKEN(OROR, ast::OROR)
"=="                        INT_TOKEN(EQ, ast::EQ)
"!="                        INT_TOKEN(NE, ast::NE)
">="                        INT_TOKEN(GE, ast::GE)
"<="                        INT_TOKEN(LE, ast::LE)
"<<"                        INT_TOKEN(LSHIFT, ast::LSHIFT)
">>"                        INT_TOKEN(RSHIFT, ast::RSHIFT)
"+="                        INT_TOKEN(PLUSEQ, ast::PLUSEQ)
"-="                        INT_TOKEN(MINUSEQ, ast::MINUSEQ)
"*="                        INT_TOKEN(MULTEQ, ast::MULTEQ)
"/="                        INT_TOKEN(DIVEQ, ast::DIVEQ)
"&="                        INT_TOKEN(ANDEQ, ast::ANDEQ)
"|="                        INT_TOKEN(OREQ, ast::OREQ)
"&&"                        INT_TOKEN(ANDAND, ast::ANDAND)

"INCLUDE"                   BEGIN(incl);
"MEMORY"                    INT_TOKEN(MEMORY, ast::MEMORY)

"REGION_ALIAS"              INT_TOKEN(REGION_ALIAS, ast::REGION_ALIAS)
"REGION_MAP"                INT_TOKEN(REGION_MAP, ast::REGION_MAP)
"LD_FEATURE"                INT_TOKEN(LD_FEATURE, ast::LD_FEATURE)
"ORIGIN"                    INT_TOKEN(ORIGIN, ast::ORIGIN)
"org"                       INT_TOKEN(ORIGIN, ast::ORIGIN)
"VERSION"                   INT_TOKEN(VERSIONK, ast::VERSIONK)
"BLOCK"                     INT_TOKEN(BLOCK, ast::BLOCK)
"BIND"                      INT_TOKEN(BIND, ast::BIND)
"LENGTH"                    INT_TOKEN(LENGTH, ast::LENGTH)
"len"                       INT_TOKEN(LENGTH, ast::LENGTH)
"l"                         INT_TOKEN(LENGTH, ast::LENGTH)
"ALIGN"                     INT_TOKEN(ALIGN_K, ast::ALIGN_K)
"DATA_SEGMENT_ALIGN"        INT_TOKEN(DATA_SEGMENT_ALIGN, ast::DATA_SEGMENT_ALIGN)
"DATA_SEGMENT_RELRO_END"    INT_TOKEN(DATA_SEGMENT_RELRO_END, ast::DATA_SEGMENT_RELRO_END)
"DATA_SEGMENT_END"          INT_TOKEN(DATA_SEGMENT_END, ast::DATA_SEGMENT_END)
"ADDR"                      INT_TOKEN(ADDR, ast::ADDR)
"LOADADDR"                  INT_TOKEN(LOADADDR, ast::LOADADDR)
"ALIGNOF"                   INT_TOKEN(ALIGNOF, ast::ALIGNOF)
"MAX"                       INT_TOKEN(MAX_K, ast::MAX_K)
"MIN"                       INT_TOKEN(MIN_K, ast::MIN_K)
"LOG2CEIL"                  INT_TOKEN(LOG2CEIL, ast::LOG2CEIL)
"ASSERT"                    INT_TOKEN(ASSERT_K, ast::ASSERT_K)
"ENTRY"                     INT_TOKEN(ENTRY, ast::ENTRY)
"EXTERN"                    INT_TOKEN(EXTERN, ast::EXTERN)
"NEXT"                      INT_TOKEN(NEXT, ast::NEXT)
"SIZEOF_HEADERS"            INT_TOKEN(SIZEOF_HEADERS, ast::SIZEOF_HEADERS)
"sizeof_headers"            INT_TOKEN(SIZEOF_HEADERS, ast::SIZEOF_HEADERS)
"SEGMENT_START"             INT_TOKEN(SEGMENT_START, ast::SEGMENT_START)
"MAP"                       INT_TOKEN(MAP, ast::MAP)
"SIZEOF"                    INT_TOKEN(SIZEOF, ast::SIZEOF)
"TARGET"                    INT_TOKEN(TARGET_K, ast::TARGET_K)
"SEARCH_DIR"                INT_TOKEN(SEARCH_DIR, ast::SEARCH_DIR)
"OUTPUT"                    INT_TOKEN(OUTPUT, ast::OUTPUT)
"INPUT"                     INT_TOKEN(INPUT, ast::INPUT)
"GROUP"                     INT_TOKEN(GROUP, ast::GROUP)
"AS_NEEDED"                 INT_TOKEN(AS_NEEDED, ast::AS_NEEDED)
"DEFINED"                   INT_TOKEN(DEFINED, ast::DEFINED)
"CREATE_OBJECT_SYMBOLS"     INT_TOKEN(CREATE_OBJECT_SYMBOLS, ast::CREATE_OBJECT_SYMBOLS)
"CONSTRUCTORS"              INT_TOKEN(CONSTRUCTORS, ast::CONSTRUCTORS)
"FORCE_COMMON_ALLOCATION"   INT_TOKEN(FORCE_COMMON_ALLOCATION, ast::FORCE_COMMON_ALLOCATION)
"INHIBIT_COMMON_ALLOCATION" INT_TOKEN(INHIBIT_COMMON_ALLOCATION, ast::INHIBIT_COMMON_ALLOCATION)
"SECTIONS"                  INT_TOKEN(SECTIONS, ast::SECTIONS)
"INSERT"                    INT_TOKEN(INSERT_K, ast::INSERT_K)
"AFTER"                     INT_TOKEN(AFTER, ast::AFTER)
"BEFORE"                    INT_TOKEN(BEFORE, ast::BEFORE)
"FILL"                      INT_TOKEN(FILL, ast::FILL)
"STARTUP"                   INT_TOKEN(STARTUP, ast::STARTUP)
"OUTPUT_FORMAT"             INT_TOKEN(OUTPUT_FORMAT, ast::OUTPUT_FORMAT)
"OUTPUT_ARCH"               INT_TOKEN(OUTPUT_ARCH, ast::OUTPUT_ARCH)
"HLL"                       INT_TOKEN(HLL, ast::HLL)
"SYSLIB"                    INT_TOKEN(SYSLIB, ast::SYSLIB)
"FLOAT"                     INT_TOKEN(FLOAT, ast::FLOAT)
"NOFLOAT"                   INT_TOKEN(NOFLOAT, ast::NOFLOAT)
"QUAD"                      INT_TOKEN(QUAD, ast::QUAD)
"SQUAD"                     INT_TOKEN(SQUAD, ast::SQUAD)
"LONG"                      INT_TOKEN(LONG, ast::LONG)
"SHORT"                     INT_TOKEN(SHORT, ast::SHORT)
"BYTE"                      INT_TOKEN(BYTE, ast::BYTE)
"NOCROSSREFS"               INT_TOKEN(NOCROSSREFS, ast::NOCROSSREFS)
"NOCROSSREFS_TO"            INT_TOKEN(NOCROSSREFS_TO, ast::NOCROSSREFS_TO)
"OVERLAY"                   INT_TOKEN(OVERLAY, ast::OVERLAY)
"SORT_BY_NAME"              INT_TOKEN(SORT_BY_NAME, ast::SORT_BY_NAME)
"SORT_BY_ALIGNMENT"         INT_TOKEN(SORT_BY_ALIGNMENT, ast::SORT_BY_ALIGNMENT)
"SORT"                      INT_TOKEN(SORT_BY_NAME, ast::SORT_BY_NAME)
"SORT_NONE"                 INT_TOKEN(SORT_NONE, ast::SORT_NONE)
"NOLOAD"                    INT_TOKEN(NOLOAD, ast::NOLOAD)
"DSECT"                     INT_TOKEN(DSECT, ast::DSECT)
"COPY"                      INT_TOKEN(COPY, ast::COPY)
"INFO"                      INT_TOKEN(INFO, ast::INFO)
"ONLY_IF_RO"                INT_TOKEN(ONLY_IF_RO, ast::ONLY_IF_RO)
"ONLY_IF_RW"                INT_TOKEN(ONLY_IF_RW, ast::ONLY_IF_RW)
"SPECIAL"                   INT_TOKEN(SPECIAL, ast::SPECIAL)
"INPUT_SECTION_FLAGS"       INT_TOKEN(INPUT_SECTION_FLAGS, ast::INPUT_SECTION_FLAGS)
"PHDRS"                     INT_TOKEN(PHDRS, ast::PHDRS)
"@"                         INT_TOKEN(AT, ast::AT)
"AT"                        INT_TOKEN(AT, ast::AT)
"ALIGN_WITH_INPUT"          INT_TOKEN(ALIGN_WITH_INPUT, ast::ALIGN_WITH_INPUT)
"SUBALIGN"                  INT_TOKEN(SUBALIGN, ast::SUBALIGN)
"HIDDEN"                    INT_TOKEN(HIDDEN, ast::HIDDEN)
"PROVIDE"                   INT_TOKEN(PROVIDE, ast::PROVIDE)
"PROVIDE_HIDDEN"            INT_TOKEN(PROVIDE_HIDDEN, ast::PROVIDE_HIDDEN)
"KEEP"                      INT_TOKEN(KEEP, ast::KEEP)
"EXCLUDE_FILE"              INT_TOKEN(EXCLUDE_FILE, ast::EXCLUDE_FILE)
"CONSTANT"                  INT_TOKEN(CONSTANT, ast::CONSTANT)

"ABSOLUTE"                  INT_TOKEN(ABSOLUTE_, ast::ABSOLUTE_)
"absolute"                  INT_TOKEN(ABSOLUTE_, ast::ABSOLUTE_)

V_TAG                       INT_TOKEN(VERS_TAG, ast::VERS_TAG)
V_IDENTIFIER                INT_TOKEN(VERS_IDENTIFIER, ast::VERS_IDENTIFIER)
"GLOBAL"                    INT_TOKEN(GLOBAL, ast::GLOBAL)
"LOCAL"                     INT_TOKEN(LOCAL, ast::LOCAL)

"SORT_BY_INIT_PRIORITY"     INT_TOKEN(SORT_BY_INIT_PRIORITY, ast::SORT_BY_INIT_PRIORITY)
"CORE_SYM"                  INT_TOKEN(CORE_SYM, ast::CORE_SYM)
"FLAGS"                     INT_TOKEN(FLAGS, ast::FLAGS)

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]                     {/* ignore multiline comment */}
{WILDCHAR}{FILENAMECHAR1}+{WILDCHAR}+{FILENAMECHAR1}*   STR_TOKEN(NAME)
[[:alpha:]][[:alnum:]_.]*         STR_TOKEN(NAME)
[[:digit:]]+[[:alnum:]_]*         STR_TOKEN(NAME)
\"(\\.|[^"])*\"                   STR_TOKEN(NAME)
{FILENAMECHAR1}{FILENAMECHAR}*    STR_TOKEN(NAME)
"="{FILENAMECHAR1}{FILENAMECHAR}* STR_TOKEN(NAME)
"-l"{FILENAMECHAR}+               STR_TOKEN(LNAME)
{FILENAMECHAR1}{NOCFILENAMECHAR}* STR_TOKEN(LNAME)
"-l"{NOCFILENAMECHAR}+            STR_TOKEN(LNAME)

{FILENAMECHAR1}{SYMBOLCHARN}*     STR_TOKEN(NAME)

[[:digit:]]+                      NUM_TOKEN(NUM)
[[:digit:]]*\.[[:digit:]]+        NUM_TOKEN(NUM)

\/\/.*                            {/* ignore comments */}
[ \t\r\n]                         {/* ignore whitespace */ }



<incl>[ \t]*                       /* eat the whitespace */
<incl>[^ \t\n]+ {                  /* got the include file name */
        std::cout << yytext << std::endl;
        ifstream* tmp = new std::ifstream( yytext, ios::in );
        pmr->addIncludeTovector(patch::to_string(yytext));
        
        if (not tmp->is_open())
            cout << " yyin is empty by include "  << endl;
         
        yyin = tmp;

        yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ) );
        //yy_switch_to_buffer(yy_create_buffer( yyin, YY_BUF_SIZE ));
        BEGIN(INITIAL);
        }

<<EOF>>    {
                std::cout << "pop state" << std::endl;
                yypop_buffer_state();
                if ( !YY_CURRENT_BUFFER )
                {
                    yyterminate();
                }
            }

.                                 LITERAL
%%

yy::scanner::scanner(std::istream* in, std::ostream* out) : yyFlexLexer(in, out)
{
  cout << "scanner(std::istream* in, std::ostream* out)" << endl;
  cout << "input stream " << in << endl;
  cout << "output stream " << out << endl;
}

int
yyFlexLexer::yylex()
{
  throw std::logic_error(
      "The yylex() exists for technical reasons and must not be used.");
}
