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

#ifndef CUSTOMDIALOGS_H
#define CUSTOMDIALOGS_H

#include "gui.h"
#include "constants.h"
#include "wxconstants.h"

class InfoDialog : public wxFrame
{
protected:
    wxStaticText* Version;

public:
    /**
     * InfoDialog CTOR for the MENU About
     * @param parent derived from parent window
     * @param id is random 
     * @param title is "About"
     * @param pos = default
     * @param size = 500 x 300
     * @param style = frame
     */
    InfoDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = ABOUT, 
               const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), 
               long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
    
    /**
     * DTOR 
     * should give a msg in shell, when it is closed.
     */
    ~InfoDialog();
};

#endif /* CUSTOMDIALOGS_H */

