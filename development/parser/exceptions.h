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

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>
#include <stdio.h>

class Exceptions : public std::exception
{
public:
  virtual ~Exceptions() {}

  /**
   * This enum represents a list of Error Messages.
   */
  enum ErrorMsg
  {
    UNKNOWN_EXCEPTION,
    OPEN_FILE,
    WARNING_GCC_VERSION,
    UNKNOWN_PARSING_ER,
    UNKNOWN_CONVERSION,
    OUT_OF_BOUNDARY,
    CORE_NOT_FOUND,
    UNKNOWN_FLAG,
    UNKNONW_INPUT,
    EXIT,
  };

  static const std::string MESSAGES[];

  /**
   * Ctor
   * @param msg 
   */
  Exceptions(ErrorMsg msg);

  /**
   * Overrides the what function.
   * @return the error message.
   */
  virtual const char* what() const noexcept;
    
  // getter for the type
  ErrorMsg getErrorType() const;

private:
  std::string error_full_msg_;
  ErrorMsg error_msg_;
};
#endif /* EXCEPTIONS_H_ */
