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

//#include <iostream>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <fstream>
//#include <stdio.h>
//
//#include "wx/app.h"
//#include <wx/grid.h>
//#include <wx/treectrl.h>
//#include <wx/spinctrl.h>
//#include <wx/artprov.h>
//#include <wx/clipbrd.h>
//#include <wx/image.h>
//#include <wx/colordlg.h>
//#include <wx/wxhtml.h>
//#include <wx/imaglist.h>
//#include <wx/dataobj.h>
//#include <wx/dcclient.h>
//#include <wx/bmpbuttn.h>
//#include <wx/menu.h>
//#include <wx/toolbar.h>
//#include <wx/statusbr.h>
//#include <wx/msgdlg.h>
//#include <wx/textdlg.h>
//#include <wx/aui/aui.h>
//
//#include "parser.hxx"
//#include "scanner.hpp"
//#include "ast.hpp"
//#include "parseroutput.h"
//#include "exceptions.h"
//#include "filemanager.h"
//#include "parsemanager.h"
//#include "constants.h"
//
//#include "gui.h"
//#include "guimemlaymgr.h"
//
///**
// * Main App is the class for our application.
// * It just acts as a container for the window, or frame in MainFrame.
// * It contains the window and all objects in it
// */
//class MainApp : public wxApp
//{
//public:
//
//  /**
//   * CTOR MainApp
//   * Read in test cases to verify the parser.
//   */
//  MainApp()
//  {
//    // init
//    FileManager* fm = FileManager::instance()->instance();
//    ParseManager* pm = ParseManager::instance()->instance();
//
//
//    // readin testcase
//    // vector<string> linker_script = fm->readInTestCase( TEST_LOCATION + "memory_1.ld");
//    // std::vector<std::string> linker_script = fm->readInTestCase( TEST_BENCHES + TEST_HEADER + "onlyHeader_0.ld");
//    // std::vector<std::string> linker_script = fm->readInTestCase("../../testbenches/some_tests.ld");
//    // std::vector<std::string> linker_script = fm->readInTestCase("../../testbenches/section.ld");
//
//    auto test_cases = fm->getTestCases();
//    std::vector<std::string> linker_script;
//
//    for (auto te_cas : test_cases)
//    {
//      linker_script.push_back(fm->readInTestCase(TEST_BENCHES + TEST_MEMORY + te_cas)[0]);
//    }
//
//    // parse file
////    ParserOutput* out = new ParserOutput();
////    pm->parse(linker_script, out);
//
//    std::cout << "===========> after parsing" << std::endl;
//    //    pm->printMap();
//    //    pm->printRegionList();
//    pm->printIncludes();
//  }
//
//  /**
//   * DTOR MainApp
//   */
//  virtual
//  ~MainApp()
//  {
//    std::cout << "DTOR: Good Bye :)" << std::endl;
//  }
//
//  /**
//   * OnInit is the "main" function which creates the top window.
//   * @return boolean value which indicates whether processing should
//   * continue (true) or not (false).
//   */
//  virtual bool
//  OnInit() // case sensitive do not change.
//  {
//    // Add the common image handlers
//    wxImage::AddHandler(new wxPNGHandler);
//    wxImage::AddHandler(new wxJPEGHandler);
//    GUIMemLayMgr* mainFrame = new GUIMemLayMgr(NULL);
//    SetTopWindow(mainFrame);
//
//    return GetTopWindow()->Show();
//  }
//};
//
//DECLARE_APP(MainApp)
//IMPLEMENT_APP(MainApp) // A macro that tells wxWidgets to create an instance of our application.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

#include "parser.hxx"
#include "scanner.hpp"
#include "ast.hpp"
#include "parseroutput.h"
#include "exceptions.h"
#include "filemanager.h"
#include "parsemanager.h"
#include "constants.h"

int main()
{
  // init
  FileManager* fm = FileManager::instance()->instance();
  ParseManager* pm = ParseManager::instance()->instance();
  bool running = true;
  std::string read_line;
  std::vector<std::string> linker_script;
  std::string main_path = "";
  std::vector<std::string> paths;

  // start cli
  // "Read in test cases? (y)es , n or (e)xit"
  // Depends on your decision. You will get different further instructions.
  while (running)
  {
    std::cout << std::endl
        << "Read in test cases? (y)es , n or (e)xit" << std::endl;
    std::getline(std::cin, read_line);

    try
    {
      if (read_line == "n")
      {
        std::cout << std::endl
            << "Please, press enter file path: '\\n' as standard path" << std::endl;
        read_line.clear();
        linker_script.clear();
        std::getline(std::cin, read_line);

        if (read_line.empty())
        {
          linker_script = fm->readInTestCase("tricore_4.ld");
          main_path = "../testbenches/test_aurix/";
        }
        else
        {
          linker_script = fm->readInTestCase(read_line);
          if (linker_script.empty())
            throw Exceptions(Exceptions::OPEN_FILE);
        }
      }
      else if (read_line == "exit" or read_line == "e")
      {
        throw Exceptions(Exceptions::Exceptions::EXIT);
      }
      else if (read_line == "" or read_line == "y" or read_line == "yes")
      {
        auto test_cases = fm->getTestCases();
        for (auto te_cas : test_cases)
        {
          linker_script.push_back(fm->readInTestCase(TEST_BENCHES + TEST_MEMORY + te_cas)[0]);
        }

        running = false;
      }
      else // unknown command
      {
        throw Exceptions(Exceptions::UNKNONW_INPUT);
      }

      read_line.clear();
    }
    catch(Exceptions& ex)
    {
      std::cout << ex.what() << std::endl;
      if(ex.getErrorType() == Exceptions::EXIT)
        running = false;
      continue;
    }

    // parse file
    ParserOutput* out = new ParserOutput();
    if(pm->parse(linker_script, out) == -1)
      continue;

    pm->addIncludes(pm->includes_list_);

    // fill
    for (const auto include : pm->includes_)
    {
      for (const auto item_include : include)
      {
        paths.push_back(main_path + item_include);
        std::vector<string> tmp_file = fm->readInTestCase(main_path + item_include);
      }
    }

    std::cout << "===========> after parsing" << std::endl;
    std::cout << "ENTRY \t\t"     << pm->entry_ << std::endl;
    std::cout << "OUTPUT_ARCH \t" << pm->output_arch_ << std::endl;
    std::cout << "Output \t\t"    << pm->output_ << std::endl;
    std::cout << "TARGET_K \t"    << pm->target_k_ << std::endl;
    std::cout << "SEARCH_DIR \t"  << pm->search_dir_ << std::endl;
    pm->output_format_->printOutputFormat();

    pm->printRegionList();
    pm->printIncludes();
    pm->printMap();
    
    // clean up
    pm->includes_.clear();
    pm->includes_list_.clear();
    pm->regions_list_.clear();
  }

  return 0;
}
