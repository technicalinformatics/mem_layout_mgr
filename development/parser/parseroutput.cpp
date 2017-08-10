#include "parseroutput.h"
#include "parser.hxx"
#include "scanner.hpp"
#include "ast.hpp"

#include <string>

void ParserOutput::memInit(ast::Regions reg)
{
  pm->addRegion(reg);
  std::cout << "parse output: " << reg.size() << std::endl;
  for (auto r : reg)
  {
    std::cout << "memInit " << r.name_ <<  " (" << r.attributes_ << ") " << " org = " << 
            r.origin_ << ", l = " << r.length_ <<  std::endl;
  }
}

void ParserOutput::includeFiles(ast::Includes in)
{
  pm->addIncludes(in);
  std::cout << "include files " << std::endl;
  for (auto include : in)
    std::cout << include << std::endl;
}

void ParserOutput::secInit(ast::Sections sec)
{
  std::cout << "todo  Parsing Sections is not implemented! " << std::endl;
}
