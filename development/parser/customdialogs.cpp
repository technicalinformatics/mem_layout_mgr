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

#include "customdialogs.h"
#include "constants.h"

InfoDialog::InfoDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
                       const wxPoint& pos, const wxSize& size, long style) : 
    wxFrame(parent, id, title, pos, size, style)
{
  SetSizeHints(wxDefaultSize, wxDefaultSize);
  wxBoxSizer* bSizerInfo = new wxBoxSizer(wxVERTICAL);

  Version = new wxStaticText(this, wxID_ANY, ABOUT_COPYRIGHT, 
                             wxDefaultPosition, wxDefaultSize, 0);
  Version->Wrap(-1);
  bSizerInfo->Add(Version, 0, wxALL, 5);

  SetSizer(bSizerInfo);
  Layout();
  Centre(wxBOTH);
}

InfoDialog::~InfoDialog()
{
  std::cout << "DTOR InfoDialog" << std::endl;
}