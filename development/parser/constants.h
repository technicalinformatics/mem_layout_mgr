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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// just for debugging
#define  HERE() { printf("here at Line %d, in fct %s \n", __LINE__, __FUNCTION__); };

// ====================== Parser ======================
#define getBit    &
#define setBit    |=
#define unsetBit  &= ~
#define toggleBit ^=
#define bit(number) (1 << number)

const std::string TEST_BENCHES = "../testbenches/";
const std::string TEST_HEADER = "test_header/";
const std::string TEST_COMBINATION = "test_combination/";
const std::string TEST_INCLUDE = "test_include/";
const std::string TEST_MEMORY = "test_memory/";
const std::string TEST_SECTION = "test_section/";
const std::string TEST_OTHERS = "test_others/";

// copied from binutils/ld/bfd.h
#define SEC_NO_FLAGS   0x000

/* Tells the OS to allocate space for this section when loading.
   This is clear for a section containing debug information only.  */
#define SEC_ALLOC      0x001

/* Tells the OS to load the section from the file when loading.
   This is clear for a .bss section.  */
#define SEC_LOAD       0x002

/* The section contains data still to be relocated, so there is
   some relocation information too.  */
#define SEC_RELOC      0x004

/* A signal to the OS that the section contains read only data.  */
#define SEC_READONLY   0x008

/* The section contains code only.  */
#define SEC_CODE       0x010

/* The section contains data only.  */
#define SEC_DATA       0x020

/* The section will reside in ROM.  */
#define SEC_ROM        0x040

// ======== ORIGIN, LENGTH
const unsigned long KILO = 1024UL;
const unsigned long MEGA = 1024UL * 1024UL;
const unsigned long GIGA = 1024UL * 1024UL * 1024UL;
const unsigned long TERA = 1024UL * 1024UL * 1024UL * 1024UL;
const unsigned long PETA = 1024UL * 1024UL * 1024UL * 1024UL * 1024UL;

// ======== Bitmap
const size_t RECT_X = 50;
const size_t RECT_Y = 40;
const size_t RECT_W = 200;
const size_t RECT_H = 300;
const size_t NR_PIXELS = 1;
const size_t TO_KBYTES = 4096;
const std::pair<size_t, size_t> BITMAP_SIZE(500, 400); // width height

#endif /* CONSTANTS_H */
