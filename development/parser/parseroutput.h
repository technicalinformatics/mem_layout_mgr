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

#ifndef PARSEROUTPUT_H
#define PARSEROUTPUT_H

#include <map>
#include <string>
#include <vector>

#include "ast.hpp"
#include "parser.hxx"

#include "parsemanager.h"

class ParseCallback;

class ParserOutput : public ParserCallback
{
  ParseManager* pm = ParseManager::instance()->instance();  
public:
  // parser callback

  /**
   * Callback function. Makes a new memory section
   * @param mem specifies a memory area of a file
   */
  void memInit(ast::Regions mem);

  /**
   * Callback function. Gets a tree of includes
   * @param in
   */
  void includeFiles(ast::Includes in);

  /**
   * Callback function. Ought to be for catching the tree of sections.
   * @param sec
   */
  void secInit(ast::Sections sec);
};

#endif /* PARSEROUTPUT_H */
