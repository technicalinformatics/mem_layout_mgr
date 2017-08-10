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

#include "guimemlaymgr.h"
#include "parsemanager.h"
#include "constants.h"

GUIMemLayMgr::GUIMemLayMgr(wxWindow* parent) :

MemLayMgr(parent)
{
  std::cout << "CTOR MemLayMgr" << std::endl;
}

void
GUIMemLayMgr::openFile(std::string path, bool save)
{
  if (main_path_file_ == path and not save)
  {
    m_textCtrlConsole->AppendText("File already open!\n");
    //return;
  }
  main_path_file_ = path;

  std::size_t found = path.find_last_of("/\\");
  main_path_ = path.substr(0, found);

  if(not save)
  {
    resetTabs();
    m_textCtrlConsole->AppendText("\n Open File: " + main_path_file_ + "\n");
  }
  
  main_file_ = fm_->readInTestCase(main_path_file_);
  m_scintilla1->ClearAll();
  m_scintilla1->AppendText(main_file_.at(0));
}

void
GUIMemLayMgr::mainFilePath(wxFileDirPickerEvent& event)
{
  openFile(event.GetPath().GetData().AsChar());
}

void
GUIMemLayMgr::klickedRun(wxCommandEvent& event)
{
  m_textCtrlConsole->AppendText(RUN_MSG);
  
  // clean up
  m_propertyGrid1->Clear();
  pm_->resetValues();
  pm_->resetIncludes();
  resetTabs();

  // parse
  ParserOutput* out = new ParserOutput();
  
  pm_->parse(main_file_, out);
  pm->addIncludes(pm->includes_list_);

  // fill
  for (const auto include : pm_->includes_)
  {
    for (const auto item_include : include)
    {
      paths_.push_back(main_path_ + "\\" + item_include);
      std::vector<string> tmp_file = fm_->readInTestCase(main_path_ + "\\" + item_include);
      if (tmp_file.size() > 0)
      {
        setupEditor(setupScrolledWin(), item_include);
        m_scintilla1->AppendText(tmp_file[0]);
      }
    }
  }

  m_propertyGrid1->Append(new wxPropertyCategory(wxT("General")));
  if (pm_->entry_ != "")
  {
    m_propertyGrid1->Append(new wxStringProperty("Entry", wxPG_LABEL,
                                                 pm_->entry_.c_str()));
  }
  if (pm_->output_ != "")
  {
    m_propertyGrid1->Append(new wxStringProperty(wxT("Output"), wxPG_LABEL,
                                                 pm_->output_.c_str()));
  }
  if (pm_->output_arch_ != "")
  {
    m_comboBox2->Clear();
    m_comboBox2->Append(pm_->output_arch_); 
    m_comboBox2->SetSelection(0);
    m_propertyGrid1->Append(new wxStringProperty(wxT("Output_Arch"), wxPG_LABEL,
                                                 pm_->output_arch_.c_str()));
  }
  if (pm_->search_dir_ != "")
  {
    m_propertyGrid1->Append(new wxStringProperty(wxT("Search_Dir"), wxPG_LABEL,
                                                 pm_->search_dir_.c_str()));
  }
  if (pm_->target_k_ != "")
  {
    m_propertyGrid1->Append(new wxStringProperty(wxT("Tarket_K"), wxPG_LABEL,
                                                 pm_->target_k_.c_str()));
  }

  m_propertyGrid1->Append(new wxPropertyCategory(wxT("Memory")));
  for (auto item_reg_list : pm_->regions_list_)
  {
    for (auto r : item_reg_list)
    {
      MemLayMgr::addMemoryProp(r.name_, pm_->mapFlags(r.attributes_), r.origin_,
                               r.length_, pm_->findRegionAlias(r.name_), r.core_id_);
    }
  }
  
  // visualization
  wxBitmap bitmap(BITMAP_SIZE.first, BITMAP_SIZE.second);
  addBitmap(bitmap);  
}

void
GUIMemLayMgr::onAuiPageClose(wxAuiNotebookEvent& event)
{
  m_textCtrlConsole->AppendText("onAuiPageClose\n");
  wxAuiNotebook* ctrl = (wxAuiNotebook*) event.GetEventObject();
  if (ctrl->GetSelection() == (int) 0)
  {
    int res = wxMessageBox(wxT("Are you sure you want to close/hide this main page?"),
                           wxT("wxAUI"),
                           wxYES_NO,
                           this);
    if (res != wxYES)
      event.Veto();
    
    if (res == wxYES)
      paths_.clear();
    
    return;
  }

  paths_.at(m_notebook2->GetSelection()).erase();
}

void
GUIMemLayMgr::onAuiPageClosed(wxAuiNotebookEvent& event)
{
  wxAuiNotebook* ctrl = (wxAuiNotebook*) event.GetEventObject();

  // selection should always be a valid index
  wxASSERT_MSG(ctrl->GetSelection() < (int) ctrl->GetPageCount(),
               wxString::Format("Invalid selection %d, only %d pages left",
                                ctrl->GetSelection(),
                                (int) ctrl->GetPageCount()));

  event.Skip();
}

void
GUIMemLayMgr::onPropGridChanged(wxPropertyGridEvent& event)
{
  // TODO: Implement onPropGridChanged
  m_textCtrlConsole->AppendText("onPropGridChanged\n");
}

void
GUIMemLayMgr::onPropGridChanging(wxPropertyGridEvent& event)
{
  // TODO: Implement onPropGridChanging
  m_textCtrlConsole->AppendText("onPropGridChanging\n");
}

void
GUIMemLayMgr::changeConsoleText(wxCommandEvent& event) 
{
  // m_textCtrlConsole->AppendText("changeConsoleText\n");
  //  std::cout << event.GetString() << std::endl;
  //  if (event.GetString() == std::string("clear"))
  //    m_textCtrlConsole->AppendText("changeConsoleText\n");

  //  event.SetString("console Output");
}

void
GUIMemLayMgr::onKlickedOpen(wxCommandEvent& event)
{
  wxFileDialog *OpenDialog = new wxFileDialog(this, _(OPEN_FILE_MSG), wxEmptyString,
                                              wxEmptyString,
                                              _(SAVE_ENDINGS),
                                              wxFD_OPEN, wxDefaultPosition);

  // Creates a "open file" dialog with 2 file types
  if (OpenDialog->ShowModal() == wxID_OK)
  {
    openFile(OpenDialog->GetPath().ToStdString());
  }
}

void
GUIMemLayMgr::onKlickedSave(wxCommandEvent& event)
{
  m_textCtrlConsole->AppendText("Save: " + paths_.at(m_notebook2->GetSelection()) + "\n");
  
  std::cout << "=======================" << std::endl;
  std::cout << "paths size " << paths_.size() << std::endl;
  for (auto a : paths_)
    std::cout << a << std::endl;
  
  std::cout << " get selection : " << m_notebook2->GetSelection() << std::endl;
  openFile(main_path_file_, true);
}

void
GUIMemLayMgr::onKlickedSaveAs(wxCommandEvent& event)
{
  wxFileDialog *SaveDialog = new wxFileDialog(this, _(SAVE_AS), wxEmptyString, wxEmptyString,
                                              _(SAVE_ENDINGS),
                                              wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
                                              wxDefaultPosition);

  if (SaveDialog->ShowModal() == wxID_OK) // if the user clicked "OK"
  {
    main_path_file_ = SaveDialog->GetPath().ToStdString();
    std::cout << " which file to open  " << main_path_file_ << std::endl;
    m_scintilla1->SaveFile(main_path_file_);
  }

  // Clean up after ourselves
  SaveDialog->Destroy();
}

void
GUIMemLayMgr::onKlickClose(wxCommandEvent& event)
{
  if (wxMessageBox(CAUTION_MSG, CAUTION, wxOK) == wxOK)
  {
    Close(TRUE);
  }
}

void
GUIMemLayMgr::onKlickedFont(wxCommandEvent& event)
{
  // TODO: Implement onKlickedFont
  m_textCtrlConsole->AppendText("Font\n");

  // http://zetcode.com/gui/wxwidgets/dialogs/
  wxFontDialog *fontDialog = new wxFontDialog(m_scintilla1);
  if (fontDialog->ShowModal() == wxID_OK)
  {
    m_scintilla1->SetFont(fontDialog->GetFontData().GetChosenFont());
  }
}

void
GUIMemLayMgr::onKlickedAbout(wxCommandEvent& event)
{
  m_textCtrlConsole->AppendText("About\n");
  InfoDialog *frame = new InfoDialog(0, -1, _(ABOUT), wxPoint(50, 50), wxSize(320, 220));
  frame->Show(true);
}

void
GUIMemLayMgr::resetTabs() 
{
  std::cout << " m_notebook2->GetPageCount() " << m_notebook2->GetPageCount() << std::endl;
  for (unsigned i_page = 1; i_page <= m_notebook2->GetPageCount(); i_page++)
  {
    std::cout << "delta page " << i_page << std::endl;
    m_notebook2->DeletePage(1);
  }
  
  std::cout << "=====================" << std::endl;
  std::cout << "pahts_ " << paths_.size() << std::endl;
  paths_.clear();
  paths_.push_back(main_path_file_);
  
  std::cout << "pageco " << m_notebook2->GetPageCount() << std::endl;
}
