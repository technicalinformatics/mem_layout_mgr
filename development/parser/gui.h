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

#ifndef GUI_H
#define GUI_H

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/valtext.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stc/stc.h>
#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/aui/auibook.h>
#include <wx/fontdlg.h>
#include <wx/splitter.h>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/stc/stc.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/aui/auibook.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

#include "customdialogs.h"
//#include "constants.h"

#include "parsemanager.h"

class MemLayMgr : public wxFrame
{
protected:
  ParseManager* pm = ParseManager::instance()->instance();

  wxBoxSizer* bSizer1;
  wxBoxSizer* bSizer14;
  wxBoxSizer* bSizer10;
  wxBoxSizer* bSizer11;
  wxBoxSizer* bSizer4;

  wxMenuItem* Open;
  wxMenuItem* Quit;
  wxMenuItem* Save;
  wxMenuItem* SaveAs;
  wxMenuItem* Font;
  wxMenuItem* About;

  wxStaticText* m_staticText4;
  wxFilePickerCtrl* m_filePicker1;
  wxStaticLine* m_staticline2;
  wxStaticText* m_staticText5;
  wxComboBox* m_comboBox2;
  wxStaticLine* m_staticline3;
  wxButton* m_button1;
  wxAuiNotebook* m_notebook2;
  wxScrolledWindow* m_scrolledWindow3;
//  std::vector< wxStyledTextCtrl* > m_scintilla;
  wxStyledTextCtrl* m_scintilla1;
  wxPanel* visualizeMemoryInfos;
  wxNotebook* m_Visualizer;
  wxScrolledWindow* m_scrolledWindowConstants;
  wxScrolledWindow* m_scrolledWindowMemory;
  wxBoxSizer* bMemorySizer;

  wxStaticBitmap* m_bitmap1;

  wxPropertyGrid* m_propertyGrid1;
  wxTextCtrl* m_textCtrlConsole;
  wxStatusBar* m_statusBar1;
  wxMenuBar* m_menubar1;
  wxMenu* File;
  wxMenu* Edit;
  wxMenu* Help;

  // helper functions

  /**
   * Make a new scollable window for the text editor scintilla
   * @return a window, should be used for the method setupEditor
   */
  wxScrolledWindow* setupScrolledWin();

  /**
   * Make a new tab in the text editor
   * @param m_scrolledwindow is need, object can be gotten by setupScrolledWin
   * @param tab_name, e.g. "msp430_main.ld"
   * @param dummy_text, if no file is added and dummytext is needed.
   */
  void setupEditor(wxScrolledWindow* m_scrolledwindow, const std::string tab_name, bool dummy_text = false);

  /**
   * "rom (rx)  : ORIGIN = 0, LENGTH = 256K" should be parsed and shown
   * int the gui tag "Console"
   * @param region_name "rom"
   * @param flags "rx"
   * @param origin "0"
   * @param length "256K"
   * @param core_id -1 if functionality not possible else 0,1,2,3,...
   */
  void addMemoryProp(std::string region_name, std::string flags, uint64_t origin, uint64_t length, std::string alias = "", int core_id = -1);

  /**
   * same as memory prop 
   * @param section_name
   */
  void addSectionsProp(std::string section_name);

  /**
   * It is a "main" method, where the addMemoryProp and addSectionsProp is called.
   */
  void setupPropertyGrid();

  /**
   * addMenuItem(File, Open, "Open", "CTRL+O");
   * @param menu to which menu it belongs to
   * @param m_menuItem how the button is called in the menu
   * @param name, which is shown to the user
   * @param shortcut <optional>, "" - empty string for no shortcut, else as
   * in the tile...
   * @return the wxMenuItem, in this case Open.
   */
  wxMenuItem* addMenuItem(wxMenu* menu, wxMenuItem* m_menuItem, std::string name, std::string shortcut);

  /**
   * It is a "main" method, where the addMenuItem is called.
   */
  void setupMenuBar();
  
  
  void addBitmap(wxBitmap& bm);

  // Virtual event handlers, override them in your derived class
  virtual void mainFilePath(wxFileDirPickerEvent& event)
  {
    event.Skip();
  }

  virtual void klickedRun(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onAuiPageClose(wxAuiNotebookEvent& event)
  {
    event.Skip();
  }

  virtual void onAuiPageClosed(wxAuiNotebookEvent& event)
  {
    event.Skip();
  }

  virtual void onPropGridChanged(wxPropertyGridEvent& event)
  {
    event.Skip();
  }

  virtual void onPropGridChanging(wxPropertyGridEvent& event)
  {
    event.Skip();
  }

  virtual void changeConsoleText(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickedOpen(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickedSave(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickedSaveAs(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickClose(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickedFont(wxCommandEvent& event)
  {
    event.Skip();
  }

  virtual void onKlickedAbout(wxCommandEvent& event)
  {
    event.Skip();
  }

public:
  
  /**
   * This CTOR makes 
   * @param parent window above 
   * @param id 
   * @param title of the window. seen by the user
   * @param pos
   * @param size - initial size
   * @param style 
   */
  MemLayMgr(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Memory Layout Manager"),
      const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(796, 690),
      long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
  
  /**
   * DTOR - Should be closed.
   * Close msg should be shown in the shell. Not in the GUI.
   */
  ~MemLayMgr();
};

#endif /* GUI_H */
