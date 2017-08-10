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

#ifndef WXCONSTANTS_H
#define WXCONSTANTS_H

#include <string>
#include <wx/string.h>

// ====================== GUI ======================
const std::string ABOUT_COPYRIGHT = "Memory Layout Manager for MultiCore Systems \n\n "
    "(C) Embedded Automotive Systems Group \n Version 1.0 \n\n\n"
    "A tool for parsing and verifying linker scripts.";

const int DEF_WIN_SIZE = 800;
const std::string ABOUT = "About";

const wxString SELECT_FILE_MSG = wxT("Select a file");
const wxString LD_ENDING = wxT("*.ld");
const std::string SAVE_ENDINGS = "Linker Scripts (*.ld)|*.ld|All files (*.*)|*.*";
const std::string SAVE_AS = "Save File As _?";
const std::string CAUTION = "Caution";
const std::string CAUTION_MSG = "Check, if files saved!";
const std::string OPEN_FILE_MSG = "Choose a file to open";
const std::string RUN_MSG = "\n RUN Button pressed! Parse Project. Wait... \n";

#endif /* WXCONSTANTS_H */

