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

#ifndef GUIMEMLAYMGR_H
#define GUIMEMLAYMGR_H

#include "gui.h"
#include "filemanager.h"
#include "parsemanager.h"
#include "parseroutput.h"

class GUIMemLayMgr : public MemLayMgr
{
  FileManager* fm_ = FileManager::instance()->instance();
  ParseManager* pm_ = ParseManager::instance()->instance();
  std::string main_path_file_;
  std::string main_path_;
  std::vector<std::string> paths_;
  std::vector<std::string> main_file_;

  /**
   * Open File for a given path and shows the text in the scintilla editor.
   * @param path absolute path. caution is given to a member variable.
   */
  void openFile(std::string path, bool save = false);
  
  /**
   * should reset the tabs in the text editor. but the first one stays.
   */
  void resetTabs();
    
protected:
  // Handlers for MemLayMgr events.
  
  /**
   * Handles the file path you selected in your filesystem
   * @param event
   */
  void mainFilePath(wxFileDirPickerEvent& event);
  
  /**
   * Run button event. Where everything will be cleaned up in advanced. 
   * @param event
   */
  void klickedRun(wxCommandEvent& event);
  
  /**
   * If the user wants to close a tab in the editor. If it is a warning the last
   * is reached. 
   * @param event
   */
  void onAuiPageClose(wxAuiNotebookEvent& event);
  
  /**
   * Checking if the selection as a valid index. Just to be sure, if it does, 
   * what it should.
   * @param event
   */
  void onAuiPageClosed(wxAuiNotebookEvent& event);
  
  /**
   * NOT IMPORTANT! 
   * If the user wants to change some values in the table.
   * @param event
   */
  void onPropGridChanged(wxPropertyGridEvent& event);
  
  /**
   * NOT IMPORTANT!
   * If the user wants to change some values in the table.
   * @param event
   */
  void onPropGridChanging(wxPropertyGridEvent& event);
  
  /**
   * NOT IMPORTANT!
   * https://wiki.wxwidgets.org/Writing_Your_First_Application-Common_Dialogs
   * @param event
   */
  void changeConsoleText(wxCommandEvent& event);
  
  /**
   * MENU OPEN
   * @param event
   */
  void onKlickedOpen(wxCommandEvent& event);
  
  /**
   * MENU SAVE
   * @param event
   */
  void onKlickedSave(wxCommandEvent& event);
  
  /**
   * MENU SAVE AS
   * @param event
   */
  void onKlickedSaveAs(wxCommandEvent& event);
  
  /**
   * MENU CLOSE
   * @param event
   */
  void onKlickClose(wxCommandEvent& event);
  
  /**
   * MENU FONT
   * @param event
   */
  void onKlickedFont(wxCommandEvent& event);
  
  /**
   * MENU ABOUT
   * @param event
   */
  void onKlickedAbout(wxCommandEvent& event);
    
public:
  /**
   * CTOR
   * @param parent the window frame above. 
   */
  GUIMemLayMgr(wxWindow* parent);
};

#endif /* GUIMEMLAYMGR_H */
