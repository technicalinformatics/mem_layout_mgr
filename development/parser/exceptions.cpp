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

#include "exceptions.h"
#include <string>

const std::string Exceptions::MESSAGES[] =
{
    "Err: Unknown Exception!",
    "Err: Could not open main linker script!",
    "Err: It is required to have GCC 6.",
    "Err: Unknown Parsing Error!",
    "Err: Cannot write conversion of Number",
    "Err: Out of boundary in flags!",
    "Err: Core not found!",
    "Err: Unknown Flag!",
    "Err: Unknown Input!",
    "Good bye :)",
};

Exceptions::Exceptions(Exceptions::ErrorMsg msg) : error_msg_(msg)
{
  //store the error message for the what() call
  std::string str = MESSAGES[static_cast<int> (error_msg_)];
  error_full_msg_ = str;
}

const char* Exceptions::what() const noexcept
{
  return error_full_msg_.c_str();
}

Exceptions::ErrorMsg
Exceptions::getErrorType() const
{
  return error_msg_;
}