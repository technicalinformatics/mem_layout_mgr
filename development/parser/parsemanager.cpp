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

#include <cstdlib>
#include <strstream>
#include <fstream>
#include <basetsd.h>
#include "constants.h"
#include "parsemanager.h"
#include "parseroutput.h"

ParseManager* ParseManager::instance_ = 0;

ParseManager::ParseManager()
{
  std::cout << "ctor: ParseManager" << std::endl;
}

void
ParseManager::addRegionAlias(std::string mem, std::string alias)
{
  auto found = region_alias_.find(mem);
  if (found == region_alias_.end()) 
  {
    // add new memory region as key and value pair. 
    region_alias_.insert({mem, {alias}});
    return;
  }

  for (auto iter_alias : found->second)
  {
    // if memory exists as key and it is also as prominent as alias. s
    if (iter_alias == alias)
      return;
  }
  
  // if memory exists and the alias is NOT prominent, then add alias. 
  found->second.push_back(alias);
}

void
ParseManager::printMap()
{
  std::cout << "------ Region Aliases ------" << std::endl;
  for (auto item_reg : region_alias_)
  {
    std::cout << "Region " << item_reg.first << std::endl;
    for (auto items : item_reg.second)
      std::cout << "\t" << items << std::endl;
  }
}

std::string
ParseManager::findRegionAlias(std::string mem)
{
  auto found = region_alias_.find(mem);
  if (found == region_alias_.end())
  {
    // if no memory region is found as key return an empty string
    return "";
  }

  std::string aliases;
  for (uint32_t i = 0; i < found->second.size(); i++)
  {
    if (i == 0)
    {
      // Otherwise, mem region found. alias append without comma. 
      aliases.append(found->second.at(i));
    }
    else
    {
      // every following alias gets a comma. 
      aliases.append(", " + found->second.at(i));
    }
  }
  return aliases;
}

void
ParseManager::addRegion(ast::Regions& regions)
{
  regions_list_.push_back(regions);
}

void
ParseManager::printRegionList()
{
  std::cout << "------ MEMORY ------ " << std::endl;
  for (auto item_reg_list : regions_list_)
  {
    for (auto r : item_reg_list)
    {
      std::cout << r.name_ << " (" << r.attributes_ << ") "
          << " org = " << r.origin_
          << ", l = " << r.length_ << std::endl;
    }
  }
}

void
ParseManager::resetIncludes()
{
  includes_.clear();
  includes_list_.clear();
}

void
ParseManager::addIncludes(ast::Includes in)
{
  includes_.push_back(in);
}

void
ParseManager::printIncludes()
{
  std::cout << "------ INCLUDE ------" << std::endl;
  for (auto include : includes_)
  {
    for (auto item_include : include)
    {
      cout << "include: " << item_include << endl;
    }
  }
}

void
ParseManager::addIncludeTovector(std::string include)
{
  includes_list_.push_back(include);
}

void
ParseManager::resetValues()
{
  output_arch_ = "";
  delete output_format_;
  output_format_ = nullptr;
  entry_ = "";
  target_k_ = "";
  search_dir_ = "";
  output_ = "";
  region_alias_.clear();
  regions_list_.clear();
  includes_.clear();
}

int
ParseManager::parse(const std::vector<std::string>& input_file, ParserOutput* out)
{
  for (unsigned row = 0; row < input_file.size(); ++row)
  {
    // initialize scanner and parser
    std::cout << " ---- start with file " << row << " ----" << std::endl;
    const std::string& main_file = input_file[row];
    std::istringstream in(main_file);
    yy::scanner scanner(&in);
    yy::parser parser(&scanner, out);
    
    try
    {
      // execute parser
      int result = parser.parse();
      if (result != 0)
      {
        throw std::runtime_error(Exceptions::MESSAGES[Exceptions::UNKNOWN_PARSING_ER]);
      }
    }
    catch (yy::parser::syntax_error& e) // if error happens stop parsing and print error.
    {
      std::ostringstream msg;
      msg << e.what() << std::endl;
      std::cout << main_file << std::endl;
      
      std::string tmp = msg.str();
      while (tmp.find("NAME") != string::npos)
        tmp.replace(tmp.find("NAME"), 4, "IDENTIFIER");

      while (tmp.find("NUM") != string::npos)
        tmp.replace(tmp.find("NUM"), 3, "NUMBER");
      
      std::cout << ">>>>>>>>>>>>> Parse Error >>>>>>>>>>>>>" << std::endl
          << tmp << std::endl;
     
      std::cout << "Line: " << e.location << std::endl;
      std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
      
      return -1;
    }
    catch (...) // all other errors
    {
      std::cout << Exceptions::UNKNOWN_EXCEPTION << std::endl;
      
      return -1;
    }
  }
  return 0;
}

bool
ParseManager::is_hex_notation(std::string const& s)
{
  // first two signs are '0x' and the size must be bigger than 2 and it should
  // contain one of the follwing signs "0123456789abcdefABCDEF"
  return s.compare(0, 2, "0x") == 0
      && s.size() > 2
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

unsigned long long
ParseManager::calculateNumber(string number)
{
  string appendix;
  string num;
  uint64_t multiplier = 1;
  uint64_t to_multiply = 1;
  
  // check of any letter of the set {K, M, G, P, T} 
  unsigned not_found = static_cast<unsigned> (-1);
  if (number.find('K') != not_found or
      number.find('M') != not_found or
      number.find('G') != not_found or
      number.find('P') != not_found or
      number.find('T') != not_found)
  {
    // appendix found and saved  temporary
    appendix = number.at(number.length() - 1);
    
    // remove the appendix from original string
    number.pop_back();
  }

  if (is_hex_notation(number))
  {
    std::cout << "found hex notation " << __func__ << std::endl;
    to_multiply = convertHexToDec(number);
  }
  else
  {
    // iterate to every character, because at this point, it must be a decimal
    // number.
    unsigned i = 0;
    for (const auto character : number)
    {
      if (i <= number.length() - 1 and not isdigit(character))
      {
        // return 0 if it is no digit. 
        std::cout << Exceptions::MESSAGES[Exceptions::UNKNOWN_CONVERSION] + ": " + number 
            << std::endl;
        return 0;
      }
      
      // add number to final string. 
      num.append(1, character);
      i++;
    }
    
    // if there is no appendix return immediatly.
    if (appendix.empty())
      return convertStrToDec(number);
    
    to_multiply = convertStrToDec(number);
  }
  
  // The appendix is getting multiplied with the original number.
  switch (appendix.c_str()[0])
  {
  case 'K':
    multiplier = KILO;
    break;
  case 'M':
    multiplier = MEGA;
    break;
  case 'G':
    multiplier = GIGA;
    break;
  case 'T':
    multiplier = TERA;
    break;
  case 'P':
    multiplier = PETA;
    break;

  default:
    break;
  }

  return to_multiply * multiplier;
}

void
ParseManager::printBitMask(uint8_t value)
{
  uint8_t bitMask = bit(7);

  printf("%d as bit: 0b", value);
  while (bitMask != 0)
  {
    char bitValue;
    if ((value getBit bitMask) != 0)
    {
      bitValue = '1';
    }
    else
    {
      bitValue = '0';
    }
    printf("%c", bitValue);
    bitMask >>= 1;
  }
  printf("\n");
}

void
ParseManager::checkFlags(std::string flags)
{
  for (unsigned c = 0; c < flags.length(); c++)
  {
    switch (flags.at(c))
    {
    case '!':
      break;

    case 'A':
    case 'a':
      break;

    case 'R':
    case 'r':
      break;

    case 'W':
    case 'w':
      break;

    case 'X':
    case 'x':
      break;

    case 'L':
    case 'l':
    case 'I':
    case 'i':
      break;

    case 'C':
    case 'c':
    {
      if (c + 1 > flags.length())
      {
        std::cout << Exceptions::MESSAGES[Exceptions::OUT_OF_BOUNDARY] << std::endl;
        break;
      }
      if (flags.at(c + 1) == '1') {}
      else if (flags.at(c + 1) == '2') {}
      else if (flags.at(c + 1) == '3') {}
      else if (flags.at(c + 1) == '4') {}
      else if (flags.at(c + 1) == '5') {}
      else if (flags.at(c + 1) == '6') {}
      else
      {
        std::cout << Exceptions::MESSAGES[Exceptions::CORE_NOT_FOUND] << std::endl;
        std::cout << "Flag: " << flags.at(c) << flags.at(c + 1) << std::endl;
      }
      break;
    }
    case 'P':
    case 'p':
      break;

    default:
    {
      std::cout << Exceptions::MESSAGES[Exceptions::UNKNOWN_FLAG] << std::endl;
      std::cout << "Flag: " << flags << " " << flags.at(c) << std::endl;
      break;
    }
    }
  }
}

uint64_t
ParseManager::convertHexToDec(std::string hex_number)
{
  return strtoul(hex_number.c_str(), nullptr, 16); // 16 is hex
}

uint64_t 
ParseManager::convertStrToDec(std::string number)
{
  return strtoul(number.c_str(), nullptr, 0); // 0 means automatic detection
}
