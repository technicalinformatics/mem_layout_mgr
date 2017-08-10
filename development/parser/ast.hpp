/*
 * #############################################################################
 * Copyright Notice and Disclaimer for the mosartMCU Project.
 * Copyright (C) 2016 EAS Group. All rights reserved.
 *
 * This file was released for educational use within the
 * Embedded Automotive Systems Group,
 * Institute of Technical Informatics,
 * Graz University of Technology, Austria
 * This copyright may not be removed, modified or relocated within this file.
 * #############################################################################
 */

#ifndef AST_HPP
#define AST_HPP

# include <string>
# include <vector>

using namespace std;

namespace ast
{
  // ======================== keywords ========================
  enum
  {
    INCLUDE,
    MEMORY,
    SECTION,
    ORIGIN,
    LENGTH,
    AT,
    ALIGN_K,
    SUBALIGN,
    ALIGN_WITH_INPUT,
    OUTPUT,
    OUTPUT_FORMAT,
    OUTPUT_ARCH,
    SEARCH_DIR,
    EXTERN,
    TARGET_K,
    REGION_ALIAS,
    REGION_MAP, 
    LD_FEATURE,
    FLOAT,
    NOFLOAT,
    STARTUP,
    SIZEOF_HEADERS,
    ABSOLUTE_,
    ADDR,
    ALIGNOF,
    ASSERT_K,
    BLOCK,
    CONSTANT,
    DATA_SEGMENT_ALIGN,
    DATA_SEGMENT_END,
    DATA_SEGMENT_RELRO_END,
    DEFINED,
    INT,
    LOADADDR,
    LOG2CEIL,
    MAX_K,
    MIN_K,
    NEXT,
    SEGMENT_START,
    SIZEOF,
    LSHIFTEQ,
    RSHIFTEQ,
    OROR,
    EQ,
    NE,
    GE,
    LE,
    LSHIFT,
    RSHIFT,
    PLUSEQ,
    MINUSEQ,
    MULTEQ,
    DIVEQ,
    ANDEQ,
    OREQ,
    ANDAND,
    VERSIONK,
    BIND,
    ENTRY,
    MAP,
    INPUT,
    GROUP,
    AS_NEEDED,
    CREATE_OBJECT_SYMBOLS,
    CONSTRUCTORS,
    FORCE_COMMON_ALLOCATION,
    INHIBIT_COMMON_ALLOCATION,
    SECTIONS,
    INSERT_K,
    AFTER,
    BEFORE,
    FILL,
    HLL,
    SYSLIB,
    QUAD,
    SQUAD,
    LONG,
    SHORT,
    BYTE,
    NOCROSSREFS,
    NOCROSSREFS_TO,
    SORT_BY_NAME,
    SORT_BY_ALIGNMENT,
    SORT_NONE,
    NOLOAD,
    DSECT,
    COPY,
    INFO,
    OVERLAY,
    ONLY_IF_RO,
    ONLY_IF_RW,
    SPECIAL,
    INPUT_SECTION_FLAGS,
    PHDRS,
    HIDDEN,
    PROVIDE,
    PROVIDE_HIDDEN,
    KEEP,
    EXCLUDE_FILE,
    VERS_TAG,
    VERS_IDENTIFIER,
    GLOBAL,
    LOCAL,
    SORT_BY_INIT_PRIORITY,
    CORE_SYM,
    FLAGS
  };
    
    // ========================= memory =========================
    struct Region
    {
      string name_;
      string attributes_;
      uint64_t origin_;
      uint64_t length_;
    };

    typedef vector<Region> Regions;
    typedef vector<Regions> RegionsList;

    // ========================= include =========================
    typedef vector<string> IncludeList;
    typedef IncludeList Includes;

    // ========================= section =========================
    // https://www.math.utah.edu/docs/info/ld_3.html#SEC14
    struct SectionVal
    {
      string name_;
      string absolute_;
      string addr_;
      string opt_align_;
      string define_;
      string next_;
      string sizeof_;
    };

    typedef std::vector<SectionVal> Sections;

    // ========================= phdr =========================
    // todo if you want to read out phdr output drint parsing
}

#endif /* AST_HPP */
