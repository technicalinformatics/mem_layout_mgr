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

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "exceptions.h"

using namespace std;

class FileManager
{
    static FileManager* instance_;
    
    /**
     * CTOR of the Singleton Pattern
     */
    FileManager();
    vector<string> test_cases_; // fill vector with testcases

public:
    /**
     * Singleton Instance Check. Only one filemanager class should exist!
     * @return the single object
     */
    static FileManager *instance()
    {
      if (not instance_)
          instance_ = new FileManager;
      return instance_;
    }
    
    /**
     * Getter for testcases
     * @return vector of test cases, whereas each file is a std::string
     */
    vector<string>
    getTestCases()
    {
      return test_cases_;
    }
    
    /**
     * saves all filenames in a vector 
     * @param filenames a vector in the end of the 
     * @param directory where the files are placed
     */
    void
    readFilenames(vector<string>& filenames, const string& directory);
        
    /**
     * Read file from path and convert to string 
     * @param path in the filesystem + name of the file
     * @return per string is one file, if not can open. there is empty vector.
     */
    vector<string> readInTestCase(string path);
};

#endif /* FILEMANAGER_H */

