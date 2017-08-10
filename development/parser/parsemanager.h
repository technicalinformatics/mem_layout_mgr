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
 * # Peter Lorenz, peter.lorenz@student.tugraz.at
 */

#ifndef PARSEMANAGER_H
#define PARSEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <iostream> 

#include "exceptions.h"
#include "parser.hxx"
#include "scanner.hpp"
#include "ast.hpp"

class ParserOutput;

namespace patch
{
  // converts number to string
  template < typename T > std::string
  to_string(const T& n)
  {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
  
  // converts long to hex string
  template< typename T >
  std::string long_to_hex(T i)
  {
    std::stringstream stream;
    stream << "0x" << std::hex << i;
    return stream.str();
  }
}

class OutputFormat
{
  std::string output_1_ = "";
  std::string output_2_ = "";
  std::string output_3_ = "";
public:

  OutputFormat(std::string one, std::string two, std::string three) :
  output_1_(one), output_2_(two), output_3_(three)
  {
  }
  
  
  ~OutputFormat()
  {
    std::cout << "DTOR OutputFormat " << std::endl;
  }
  
  void printOutputFormat() 
  {
    std::cout << "Output Format \t" << output_1_ << ", " << output_2_ << ", " <<
        output_3_ << std::endl;
  }
};

class ParseManager
{
  static ParseManager* instance_;

  /**
   * CTOR of the Singleton Pattern
   */
  ParseManager();
     
public:
  /**
   * Singleton Instance Check. Only one parsemanager class should exist!
   * @return the single object
   */
  static ParseManager *instance()
  {
    if (not instance_)
        instance_ = new ParseManager;
    return instance_;
  }

  // data structure, where the parsed information is saved.
  std::string output_arch_ = "";
  OutputFormat* output_format_ = nullptr;
  std::string entry_ = "";
  std::string target_k_ = "";
  std::string search_dir_ = "";
  std::string output_ = "";
  std::map<std::string, std::vector<std::string> > region_alias_;
  ast::RegionsList regions_list_;
  ast::Includes includes_list_;
  std::vector<ast::Includes> includes_;
  
  // Lexer
  yyFlexLexer lexer_;

  // Methods
  
  /**
   * One region can have different alias. This stored into a map
   * @param mem is the key in the map
   * @param alias is the value in a map. One key can have several aliases
   */
  void addRegionAlias(std::string mem, std::string alias);
  
  /**
   * print all regions with their aliases
   */
  void printMap();
  
  /**
   * principle a getter to save code multiplications
   * @param mem is the key in a map
   * @return a string of aliases
   */
  std::string findRegionAlias(std::string mem);

  /**
   * Add a region to a vector, which collects all regions.
   * @param regions
   */
  void addRegion(ast::Regions& regions);
  
  /**
   * just for debugging
   */
  void printRegionList();
  
  /**
   * reset list of includes 
   */
  void resetIncludes();
  
  /**
   * add a include to the collector of incudes
   * @param in the include, which will be added.
   */
  void addIncludes(ast::Includes in);
  
  /**
   * just for debugging
   */
  void printIncludes();
  
  /**
   * one step underneath than <addIncludes> 
   * @param include just the pure string 
   */
  void addIncludeTovector(std::string include);
  
  /**
   * all values will be set to the initial value, if the user presses the 
   * "Run" button
   */
  void resetValues();

  /**
   * Most important function in the universe. 
   * Gives also back in which row the file is not compiling.
   * @param exprs what should we parse. can be files as one element...
   * @param out is the output of the parser
   * @return -1 if exception is thrown
   */
  int parse(const std::vector<std::string>& exprs, ParserOutput* out);
  
  /**
   * Helper function
   * @param s to verify if it is a hex number
   * @return true if it is a hex number
   */
  bool
  is_hex_notation(std::string const& s);
  
  /**
   * Checks if, i.e. 800K or 800  and calculates the value
   * @param number, e.g. 8K or 8M
   * @return number if only number else calculate number by multiplying
   */
  unsigned long long calculateNumber(string number);

  /**
   * For Debugging Purpose. Especially, the read/write access.
   * @param value gets covnerted to binary 
   */
  void printBitMask(uint8_t value);

  /**
   * Get a string, e.g. Memory Region.
   * binutils/ld/ldlang.c: lang_set_flags
   * @param flags  'r', 'rx', 'w', '!w', ...
   * @param invert if a '!' is written then invert the flags.
   * @return a bitmap of flags
   */
  void checkFlags(string flags);
  
  /**
   * check which flages are set  in method setFlags
   * @param flag prepared from method setFlags above
   * @return the flags which are set alphabetically.
   */
  std::string mapFlags(uint64_t flag);

  /**
   * copied and adapted from binutils. 
   * origin expects a hex number 0x*****, so we need to 
   * convert the string to dec
   * @param hex_number
   * @return dec number
   */
  uint64_t convertHexToDec(string hex_number);
  
  /**
   * convert str to hex
   * @param number which should be converted to a string
   * @return decimal value
   */
  uint64_t convertStrToDec(std::string number);
  
  /**
   * opens a file for the parse stack
   * good example: http://www.cs.princeton.edu/~appel/modern/c/software/flex/flex.html
   * @param name is the filename of an 'INCLUDE example.ld'
   */
  void open_command_file(const char* name);

};

#endif /* PARSEMANAGER_H */
