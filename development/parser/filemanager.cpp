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

#include <fstream>
#include <sstream>

#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

#include "filemanager.h"
#include "exceptions.h"
#include "constants.h"

FileManager* FileManager::instance_ = 0;

FileManager::FileManager()
{
  std::cout << "ctor: FileManager" << std::endl; 
  readFilenames(test_cases_, TEST_BENCHES + TEST_MEMORY);
  for_each(test_cases_.begin(), test_cases_.end(), [](string & n) 
    { std::cout << n << std::endl; });
  
  std::cout << "----- nr test_cases " << test_cases_.size() << " -----" << std::endl << std::endl;
}

void
FileManager::readFilenames(vector<string> &filenames, const string &directory)
{
  DIR *dir;
  class dirent *ent;
  class stat st;

  dir = opendir(directory.c_str());
  while ((ent = readdir(dir)) != NULL)
  {
    const string file_name = ent->d_name;
    const string full_file_name = directory + "/" + file_name;

    if (file_name[0] == '.')
      continue;

    if (stat(full_file_name.c_str(), &st) == -1)
      continue;

    const bool is_directory = (st.st_mode & S_IFDIR) != 0;

    if (is_directory)
      continue;

    filenames.push_back(file_name);
  }
  closedir(dir);
}

vector<string> 
FileManager::readInTestCase(string path)
{
  // open file to test
  ifstream linker_script;
  linker_script.open(path);

  if (linker_script.is_open() == false)
  {
    return std::vector<string>();
  }
  
  stringstream buffer;
  buffer << linker_script.rdbuf();

  vector<string> linker_scripts;
  linker_scripts.push_back(buffer.str());

  return linker_scripts;
}
