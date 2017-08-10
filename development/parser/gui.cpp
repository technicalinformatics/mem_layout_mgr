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

#include "gui.h"
#include "constants.h"

MemLayMgr::MemLayMgr(wxWindow* parent, wxWindowID id, const wxString& title, 
                     const wxPoint& pos, const wxSize& size, long style) : 
                     wxFrame(parent, id, title, pos, size, style)
{
  bSizer1 = new wxBoxSizer(wxVERTICAL);
  bSizer1->SetMinSize(wxSize(DEF_WIN_SIZE, DEF_WIN_SIZE));
  bSizer14 = new wxBoxSizer(wxHORIZONTAL);
  
  // Menu Bar 
  m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("Main"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText4->Wrap(-1);
  bSizer14->Add(m_staticText4, 0, wxTOP | wxBOTTOM | wxLEFT | wxALIGN_CENTER_VERTICAL, 5);
 
  // File Picker
  m_filePicker1 = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, SELECT_FILE_MSG, LD_ENDING, 
                                       wxDefaultPosition, wxSize(400, -1), 
                                       wxFLP_OPEN | wxFLP_SMALL | wxFLP_USE_TEXTCTRL | wxDOUBLE_BORDER);
  
  bSizer14->Add(m_filePicker1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
  m_staticline2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
  m_staticline2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

  bSizer14->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);
  
  // CPU
  m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("CPU"), wxDefaultPosition, wxDefaultSize, 0);
  m_staticText5->Wrap(-1);
  bSizer14->Add(m_staticText5, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_comboBox2 = new wxComboBox(this, wxID_ANY, wxT("MSP430"), wxDefaultPosition, wxDefaultSize, 0, 
                               NULL, wxCB_DROPDOWN | wxCB_READONLY | wxCB_SORT | wxTE_PROCESS_ENTER);
  m_comboBox2->Append(wxT("MSP430"));
  m_comboBox2->Append(wxT("TriCore"));
  m_comboBox2->SetSelection(1);
  bSizer14->Add(m_comboBox2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_staticline3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL | wxLI_VERTICAL);
  bSizer14->Add(m_staticline3, 0, wxEXPAND | wxALL, 5);
  
  // RUN Button
  m_button1 = new wxButton(this, wxID_ANY, wxT("RUN"), wxDefaultPosition, wxDefaultSize, 0);
  bSizer14->Add(m_button1, 0, wxALL, 5);

  bSizer1->Add(bSizer14, 0, 0, 5);
  bSizer10 = new wxBoxSizer(wxHORIZONTAL);
  
//  wxSplitterWindow* m_splitter2 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
//  m_splitter2->Connect(wxEVT_IDLE, wxIdleEventHandler(MyFrame1::m_splitter2OnIdle), NULL, this);
//  wxPanel* m_panel3 = new wxPanel(m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  
  bSizer11 = new wxBoxSizer(wxVERTICAL);
  bSizer4 = new wxBoxSizer(wxVERTICAL);

  // add scrolled window
  m_notebook2 = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
  m_scrolledWindow3 = new wxScrolledWindow(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
  m_scrolledWindow3->SetScrollRate(5, 5);
  setupEditor(m_scrolledWindow3, std::string("Main"), true);
  
  // add editor to sizer for right expandations
  bSizer4->Add(m_notebook2, 1, wxEXPAND | wxALL, 5);
  bSizer11->Add(bSizer4, 1, wxEXPAND, 5);
  bSizer10->Add(bSizer11, 1, wxEXPAND, 5);

  wxBoxSizer* bSizer12 = new wxBoxSizer(wxVERTICAL);
  visualizeMemoryInfos = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);

  m_Visualizer = new wxNotebook(visualizeMemoryInfos, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
  m_scrolledWindowConstants = new wxScrolledWindow(m_Visualizer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
  m_scrolledWindowConstants->SetScrollRate(5, 5);
  
  // Property Grid
  wxBoxSizer* bConstantsSizer = new wxBoxSizer(wxVERTICAL);
  m_propertyGrid1 = new wxPropertyGrid(m_scrolledWindowConstants, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                                       wxPG_DEFAULT_STYLE | wxHSCROLL | wxVSCROLL);
  bConstantsSizer->Add(m_propertyGrid1, 1, wxALL | wxEXPAND, 5);
  setupPropertyGrid();
  m_scrolledWindowConstants->SetSizer(bConstantsSizer);
  m_scrolledWindowConstants->Layout();
  
  // Constant Window
  bConstantsSizer->Fit(m_scrolledWindowConstants);
  m_Visualizer->AddPage(m_scrolledWindowConstants, wxT("Constants"), true);
  m_scrolledWindowMemory = new wxScrolledWindow(m_Visualizer, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxHSCROLL | wxVSCROLL);
  m_scrolledWindowMemory->SetScrollRate(5, 5);
  
  // Memory Window
  bMemorySizer= new wxBoxSizer(wxVERTICAL);

  wxBitmap bitmap(BITMAP_SIZE.first, BITMAP_SIZE.second);
  m_bitmap1 = new wxStaticBitmap(m_scrolledWindowMemory,
                                 wxID_ANY,
                                 bitmap,
                                 wxDefaultPosition,
                                 wxDefaultSize, 0);
  addBitmap(bitmap);

  bMemorySizer->Add(m_bitmap1, 0, wxEXPAND | wxALL, 5);
  
  m_scrolledWindowMemory->SetSizer(bMemorySizer);
  m_scrolledWindowMemory->Layout();
  bMemorySizer->Fit(m_scrolledWindowMemory);
  m_Visualizer->AddPage(m_scrolledWindowMemory, wxT("Memory"), false);
  bSizer3->Add(m_Visualizer, 1, wxEXPAND | wxALL, 5);

  visualizeMemoryInfos->SetSizer(bSizer3);
  visualizeMemoryInfos->Layout();
  bSizer3->Fit(visualizeMemoryInfos);
  
  // Console Window
  bSizer12->Add(visualizeMemoryInfos, 1, wxEXPAND | wxALL, 5);
  bSizer10->Add(bSizer12, 1, wxEXPAND, 5);
  bSizer1->Add(bSizer10, 1, wxEXPAND, 5);
  wxBoxSizer* bSizerConsole = new wxBoxSizer(wxHORIZONTAL);
  bSizerConsole->SetMinSize(wxSize(-1, 100));
  m_textCtrlConsole = new wxTextCtrl(this, wxID_ANY, wxT("Console\n"), wxDefaultPosition, wxDefaultSize, 
                                     wxHSCROLL | wxTE_LEFT | wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxCLIP_CHILDREN | wxHSCROLL | wxVSCROLL);
  bSizerConsole->Add(m_textCtrlConsole, 1, wxALL | wxEXPAND, 5);
  bSizer1->Add(bSizerConsole, 0, wxEXPAND, 5);
  this->SetSizer(bSizer1);
  this->Layout();
  
  setupMenuBar();

  // Connect Events
  m_filePicker1->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MemLayMgr::mainFilePath), NULL, this);
  m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MemLayMgr::klickedRun), NULL, this);
  m_notebook2->Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler(MemLayMgr::onAuiPageClose), NULL, this);
  m_notebook2->Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED, wxAuiNotebookEventHandler(MemLayMgr::onAuiPageClosed), NULL, this);
  m_propertyGrid1->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(MemLayMgr::onPropGridChanged), NULL, this);
  m_propertyGrid1->Connect(wxEVT_PG_CHANGING, wxPropertyGridEventHandler(MemLayMgr::onPropGridChanging), NULL, this);
  m_textCtrlConsole->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MemLayMgr::changeConsoleText), NULL, this);
  this->Connect(Open->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedOpen));
  this->Connect(Save->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedSave));
  this->Connect(SaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedSaveAs));
  this->Connect(Quit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickClose));
  this->Connect(Font->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedFont));
  this->Connect(About->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedAbout));
}

MemLayMgr::~MemLayMgr()
{
  
  std::cout << "DTOR MemLayMgr" << std::endl;
  
  // Disconnect Events
  m_filePicker1->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MemLayMgr::mainFilePath), NULL, this);
  m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MemLayMgr::klickedRun), NULL, this);
  m_notebook2->Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler(MemLayMgr::onAuiPageClose), NULL, this);
  m_notebook2->Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED, wxAuiNotebookEventHandler(MemLayMgr::onAuiPageClosed), NULL, this);
  m_propertyGrid1->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(MemLayMgr::onPropGridChanged), NULL, this);
  m_propertyGrid1->Disconnect(wxEVT_PG_CHANGING, wxPropertyGridEventHandler(MemLayMgr::onPropGridChanging), NULL, this);
  m_textCtrlConsole->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MemLayMgr::changeConsoleText), NULL, this);
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedOpen));
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedSave));
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedSaveAs));
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickClose));
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedFont));
  this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MemLayMgr::onKlickedAbout));
}

wxScrolledWindow* MemLayMgr::setupScrolledWin()
{
  wxScrolledWindow* m_scrolledWindow = new wxScrolledWindow(m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
  m_scrolledWindow->SetScrollRate(5, 5);
  
  return m_scrolledWindow;
}

void MemLayMgr::setupEditor(wxScrolledWindow* m_scrolledwindow, const std::string tab_name, bool dummy_text)
{
  wxBoxSizer* bSizerEditor = new wxBoxSizer(wxVERTICAL);
  
  m_scintilla1 = new wxStyledTextCtrl(m_scrolledwindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN, wxEmptyString);
  m_scintilla1->SetUseTabs(false);
  m_scintilla1->SetTabWidth(2);
  m_scintilla1->SetIndent(2);
  m_scintilla1->SetTabIndents(true);
  m_scintilla1->SetBackSpaceUnIndents(true);
  m_scintilla1->SetViewEOL(false);
  m_scintilla1->SetViewWhiteSpace(true);
  m_scintilla1->SetMarginWidth(1, 0);
  m_scintilla1->SetIndentationGuides(true);
  m_scintilla1->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
  m_scintilla1->SetMarginMask(1, wxSTC_MASK_FOLDERS);
  m_scintilla1->SetMarginWidth(1, 10);
  m_scintilla1->SetMarginSensitive(1, true);
  m_scintilla1->SetProperty(wxT("fold"), wxT("1"));
  m_scintilla1->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
  m_scintilla1->SetMarginType(0, wxSTC_MARGIN_NUMBER);
  m_scintilla1->SetMarginWidth(0, m_scintilla1->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("_99999")));
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
  m_scintilla1->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("BLACK")));
  m_scintilla1->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("WHITE")));
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
  m_scintilla1->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("BLACK")));
  m_scintilla1->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("WHITE")));
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS);
  m_scintilla1->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("BLACK")));
  m_scintilla1->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("WHITE")));
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS);
  m_scintilla1->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("BLACK")));
  m_scintilla1->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("WHITE")));
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
  m_scintilla1->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);
  m_scintilla1->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
  m_scintilla1->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
  m_scintilla1->SetLexer(wxSTC_LEX_CPP);
  m_scintilla1->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColor(150, 150, 150));
  m_scintilla1->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColor(0, 0, 255));
  m_scintilla1->StyleSetForeground(wxSTC_C_STRING, wxColor(255, 60, 10));
  m_scintilla1->StyleSetForeground(wxSTC_C_WORD, wxColor(0, 50, 255));
  m_scintilla1->StyleSetForeground(wxSTC_C_NUMBER, wxColor(0, 150, 150));
  m_scintilla1->StyleSetForeground(wxSTC_C_COMMENT, wxColor(150, 150, 150));

  // http://www.needfulsoftware.com/Documentation/WxWidgetsStyledTextCtrl
  m_scintilla1->SetKeyWords(0, wxT("return int char INCLUDE MEMORY REGION_ALIAS LD_FEATURE "
                                   "ORIGIN org VERSION BLOCK BIND LENGTH l ALIGN DATA_SEGMENT_ALIGN DATA_SEGMENT_RELRO_END "
                                   "DATA_SEGMENT_END ADDR LOADADDR ALIGNOF MAX MIN LOG2CEIL ASSERT ENTRY EXTERN NEXT "
                                   "SIZEOF_HEADERS sizeof_headers SEGMENT_START MAP SIZEOF TARGET SEARCH_DIR OUTPUT INPUT "
                                   "GROUP AS_NEEDED DEFINED CREATE_OBJECT_SYMBOLS CONSTRUCTORS FORCE_COMMON_ALLOCATION "
                                   "INHIBIT_COMMON_ALLOCATION SECTIONS INSERT AFTER BEFORE FILL STARTUP OUTPUT_FORMAT "
                                   "OUTPUT_ARCH HLL SYSLIB FLOAT NOFLOAT QUAD SQUAD LONG SHORT BYTE NOCROSSREFS NOCROSSREFS_TO "
                                   "OVERLAY SORT_BY_NAME SORT_BY_ALIGNMENT SORT SORT_NONE NOLOAD DSECT COPY INFO OVERLAY "
                                   "ONLY_IF_RO ONLY_IF_RW SPECIAL INPUT_SECTION_FLAGS PHDRS @ AT ALIGN_WITH_INPUT SUBALIGN "
                                   "HIDDEN PROVIDE PROVIDE_HIDDEN KEEP EXCLUDE_FILE CONSTANT ABSOLUTE absolute V_TAG "
                                   "V_IDENTIFIER GLOBAL LOCAL data text bss rx !rx  Rx rX !Rx !RX !xR XR !XR wx !wx Wx !Wx wX !xW XW !XW"));

  bSizerEditor->Add(m_scintilla1, 1, wxEXPAND | wxALL, 5);

  if (dummy_text)
  {
    m_scintilla1->AddText("// A simple program\n\n");
    m_scintilla1->AddText("OUTPUT_FORMAT(elf32 - i386, elf32 - i386, elf32-i386)\n");
    m_scintilla1->AddText("OUTPUT_ARCH(i386)\n");
    m_scintilla1->AddText("ENTRY(mymain)\n");
    m_scintilla1->AddText("rom (rx) : ORIGIN = 0, LENGTH = 256K\n");
    m_scintilla1->AddText("SECTIONS\n");
    m_scintilla1->AddText("{\n");
    m_scintilla1->AddText("    . = 0x10000;\n");
    m_scintilla1->AddText("    .text : { *(.text) }\n");
    m_scintilla1->AddText("    . = 0x8000000;\n");
    m_scintilla1->AddText("    .data : { *(.data) }\n");
    m_scintilla1->AddText("    .bss : { *(.bss) }\n");
    m_scintilla1->AddText("}\n");
  }
  
  m_scrolledwindow->SetSizer(bSizerEditor);
  m_scrolledwindow->Layout();
  bSizerEditor->Fit(m_scrolledwindow);
  
  m_notebook2->AddPage(m_scrolledwindow, tab_name.c_str(), false, wxNullBitmap);
}

void MemLayMgr::addMemoryProp(std::string region_name, std::string flags, uint64_t origin, uint64_t length, std::string alias, int cord_id)
{
  wxPGProperty* memoryProp = m_propertyGrid1->Append(new wxStringProperty(region_name.c_str(), wxPG_LABEL, wxT("<composed>")));
  m_propertyGrid1->AppendIn(memoryProp, new wxStringProperty(wxT("Alias"), wxPG_LABEL, alias.empty() == true ? "none" : alias.c_str()));
  m_propertyGrid1->AppendIn(memoryProp, new wxIntProperty(wxT("CoreID"), wxPG_LABEL, cord_id));
  m_propertyGrid1->AppendIn(memoryProp, new wxStringProperty(wxT("Flags"), wxPG_LABEL, flags.c_str()));
  m_propertyGrid1->AppendIn(memoryProp, new wxIntProperty(wxT("Origin"), wxPG_LABEL, origin));
  m_propertyGrid1->AppendIn(memoryProp, new wxIntProperty(wxT("Length"), wxPG_LABEL, length));
}

void MemLayMgr::addSectionsProp(std::string section_name)
{
  wxPGProperty* secProp = m_propertyGrid1->Append(new wxStringProperty(section_name.c_str(), wxPG_LABEL, wxT("<composed>")));
  wxPGProperty* secAttrProp = m_propertyGrid1->AppendIn(secProp, new wxStringProperty(wxT("SecAttributes"), wxPG_LABEL, wxT("<composed>")));
  m_propertyGrid1->AppendIn(secAttrProp, new wxStringProperty(wxT("some filler"), wxPG_LABEL, wxT("blah")));
}

void MemLayMgr::setupPropertyGrid()
{
  // http://students.mimuw.edu.pl/~bbekier/doxygen/out/html/overview_propgrid.html
  m_propertyGrid1->Append(new wxPropertyCategory(wxT("General")));  
  m_propertyGrid1->Append(new wxPropertyCategory(wxT("Memory")));
  m_propertyGrid1->Append(new wxPropertyCategory(wxT("Sections")));
  addSectionsProp("bss");
  addSectionsProp("text");
}

wxMenuItem* MemLayMgr::addMenuItem(wxMenu* menu, wxMenuItem* m_menuItem, std::string name, std::string shortcut)
{
  if(not shortcut.empty())
  {
    m_menuItem = new wxMenuItem(menu, wxID_ANY, wxString(name + wxT('\t') + shortcut), wxEmptyString, wxITEM_NORMAL);
  }
  else 
  {
    m_menuItem = new wxMenuItem(menu, wxID_ANY, wxString(name), wxEmptyString, wxITEM_NORMAL);
  }
  menu->Append(m_menuItem);
  
  return m_menuItem;
}

void MemLayMgr::setupMenuBar()
{
  m_statusBar1 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);
  m_menubar1 = new wxMenuBar(0);
  
  File = new wxMenu();
  Open = addMenuItem(File, Open, "Open", "CTRL+O");
  Save = addMenuItem(File, Save, "Save", "CTRL+S");
  SaveAs = addMenuItem(File, SaveAs, "Save as", "CTRL+SHIFT+S");
  Quit = addMenuItem(File, Quit, "Close", "CTRL+Q");
  m_menubar1->Append(File, wxT("File"));

  Help = new wxMenu();
  Font = addMenuItem(Help, Font, "Font", "CTRL+SHIFT+F");
  About = addMenuItem(Help, About, "About", "");
  m_menubar1->Append(Help, wxT("Help"));

  this->SetMenuBar(m_menubar1);
  this->Centre(wxBOTH);
}

void
MemLayMgr::addBitmap(wxBitmap& bm) 
{
  wxMemoryDC memDC;
  memDC.SelectObject(bm);
  memDC.SetBackground(*wxWHITE_BRUSH);
  memDC.Clear();
  memDC.SetPen(*wxBLACK_PEN);
  memDC.SetBrush(*wxTRANSPARENT_BRUSH);
  memDC.DrawText(wxString(wxT("Memory")), 10, 5);
  
  memDC.DrawRectangle(wxRect(RECT_X, RECT_Y, RECT_W, RECT_H));
  
  for (const auto region : pm->regions_list_)
  {
    for (const auto i_reg : region)
    {
      size_t o_kbytes = i_reg.origin_ / TO_KBYTES;
      size_t l_kbytes = i_reg.length_ / TO_KBYTES;
       
      auto func = [] (size_t a) -> size_t { return a * NR_PIXELS; };
      size_t o_pixels = func(o_kbytes);
      size_t l_pixels = func(l_kbytes);
      
      if (o_pixels > l_pixels)
      {
        m_textCtrlConsole->AppendText("Error: Origin > Length!\n");
        break;
      }
      
      if(RECT_Y + 300 - l_pixels - o_pixels > BITMAP_SIZE.second)
      {
        m_textCtrlConsole->AppendText("Error: Bitmap out of boundary!\n");
        break;
      }
      
      std::string tmp(i_reg.name_ + std::string("{ o=") + 
          patch::long_to_hex(i_reg.origin_ / 1024.0) + 
          std::string(", l=") + 
          patch::long_to_hex(i_reg.length_ / 1024.0) + std::string(" }"));
      
      
      memDC.DrawText(wxString(tmp.c_str()), RECT_X + RECT_W + 2 ,RECT_Y + 300 - l_pixels - o_pixels);
      memDC.DrawRectangle(wxRect(RECT_X, RECT_Y + 300 - l_pixels - o_pixels, RECT_W, l_pixels));
    }
  }
  
  memDC.SelectObject(wxNullBitmap);
  m_bitmap1->SetBitmap(bm);
}
