# Memory Layout Manager for Single and MultiCore Systems
[![Build Status](https://travis-ci.org/tompollard/phd_thesis_markdown.svg?branch=master)](https://travis-ci.org/tompollard/phd_thesis_markdown)  

 The memory layout manager is a simple GUI, which should help to parse and
 verify linker scripts projects.

 I recommend to use Netbeans IDE 8.x, because the bison support is working out  
 of the box. Otherwise, I would recommend and install a  plugin for bison flex.

## Installation

A toolchain is provided to start the project out of the box.

  * Bison 3.0.4
  * Flex 2.6.1
  * WxWidgets 3.1.0
  * C++11 >= 6

Go in the root folder and execute
`./install_tc.sh`.
It will last around 40 minutes.

In Windows, you need to run a bash window first. [Activate bash shell](http://www.windowscentral.com/how-install-bash-shell-command-line-windows-10)
in Windows 10.  

In Arch Linux, it is recommended to take a look to [Link](https://wiki.filezilla-project.org/Compiling_FileZilla_3_under_Windows)

## Usage

    make help // shows you a list of options

Find a graphical overview of the grammar, klick [here](#Grammar-Overview).

## History

This file started with LinkerScript Parser v0.0 and tracks the feature of this tool.
Each line will describe a single addition/removement/change and adhere to the following format:

`<Author> <Type> : <Textual_description_without_linebreak>`

Authors (so far):

  * MB   Marcel Baunach
  * RG   Renata Gomes
  * PL   Peter Lorenz

Type:

  * \+ Addition
  * \- Removement
  * \# Modification
  * \~ Fix
  * \! Misc.
  * (very significant entries should be in upper case and prefixed with "-----" )

Table of changes:

  * `PL + The initial setup is done. Version 0.0`
  * todo add changes

## Credits

  * Master Project, written by Peter Lorenz.
  * Marcel Baunach and Renata Gomez supervised this project.

See also the list of [contributors](https://www.tugraz.at/en/institutes/iti/research/research-areas/embedded-automotive-systems/) who participated in this project.

## License

Copyright (C) 2016 EAS Group. All rights reserved.

---

### Grammar-Overview
Go to development/parser/output/parser.png
