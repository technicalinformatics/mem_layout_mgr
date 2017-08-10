################################################################################
#		Copyright Notice and Disclaimer for the mosartMCU Project.
# Copyright (C) 2016 EAS Group. All rights reserved.
#
# This file was released for educational use within the
#             Embedded Automotive Systems Group,
#             Institute of Technical Informatics,
#           Graz University of Technology, Austria
# This copyright may not be removed, modified or relocated within this file.
################################################################################
# Peter Lorenz, peter.lorenz@student.tugraz.at
################################################################################
## MEMORY MANAGER build environment V0.0

.PHONY : help doc parse scan

include toolchain.mk

OUTPUT=output
DOXYGEN=buildenv/doxygen
DIRWXWIDGETS=wxwidget

CPPFLAGS=-std=gnu++11 -Wall -Wno-deprecated
WXWIDGETSFLAGS= -mthreads  -lwxmsw30u_richtext -lwxmsw30u_xrc -lwxmsw30u_aui \
 -lwxmsw30u_media -lwxbase30u_net -lwxmsw30u_gl -lwxbase30u_xml \
 -lwxmsw30u_adv -lwxmsw30u_html -lwxmsw30u_core -lwxbase30u -lwxpng -lwxjpeg \
 -lwxtiff -lwxzlib -lwxregexu -lwxexpat
WX_LIBS=-IC:/wxWidgets-3.0.2/include -IC:/wxWidgets-3.0.2/lib/gcc_dll/mswu
libs=-Ilibs

parser=$(wildcard *.y)
scanner=$(wildcard *.l)
src=$(wildcard *.cpp)
bin=mem_lay_mgr
obj3=scanner.o parser.o

SOURCE_PARSER=exceptions.cpp filemanager.cpp parsemanager.cpp parseroutput.cpp main.cpp

parse_all: gram
	   $(CXX) $(libs) $(SOURCE_PARSER) $(obj3) -o $(OUTPUT)/only_parser $(CPPFLAGS)

all:	gram
	$(CXX) $(libs) $(src) $(obj3)  $(CPPFLAGS) $(WXWIDGETSFLAGS) -o $(OUTPUT)/$(bin) $(WX_LIBS)

parse:
	@echo ""
	@echo "************************************"
	@echo "*** BUILDING MM Parser ****"
	@echo "************************************"
	win_bison -v $(parser)
	$(CXX) -c $(libs) $(CPPFLAGS) parser.hxx parseroutput.h parseroutput.cpp parser.cxx
	mv *.output $(OUTPUT)

scan:
	@echo ""
	@echo "************************************"
	@echo "*** BUILDING MM Scanner ****"
	@echo "************************************"
	win_flex $(scanner)
	$(CXX) $(libs) -c $(CPPFLAGS) parseroutput.h parseroutput.cpp scanner.cxx

gram: parse scan

clean:
	rm -f *.cxx *.hxx *.hh
	rm -f $(OUTPUT)/$(bin)
	rm -f *.o

graph:
	@echo ""
	@echo "************************************"
	@echo "*** Creating MM PDF ****"
	@echo "************************************"
	win_bison -g parser.y
	mv parser.dot $(OUTPUT)
	dot -Tpng $(OUTPUT)/parser.dot -o $(OUTPUT)/parser.png

doc:
	@echo "doc"
	@doxygen buildenv/doxygen/documentation.Doxyfile
	rm -fr $(DOXYGEN)/html
	rm -fr $(DOXYGEN)/man
	rm -fr $(DOXYGEN)/latex
	mv -i html -t $(DOXYGEN)/
	mv -i latex -t $(DOXYGEN)/
	mv -i man -t $(DOXYGEN)/

valgrind:
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$(OUTPUT)/$(bin)

run: 
	@echo "run"
	./output/only_parser.exe

help:
	@echo ""
	@echo "************************************"
	@echo "*** BUILDING MM HELP ****"
	@echo "************************************"
	@echo "<make all>       ; will call gram"
	@echo "<make parse>     ; bison parser"
	@echo "<make scan>      ; lexer"
	@echo "<make gram>      ; bison lexer"
	@echo "<make valgrind>  ; memory leaks check"
	@echo "<make graph>     ; makes a pdf in the folder output"
	@echo "<make doc>"
	@echo "<make run>"
