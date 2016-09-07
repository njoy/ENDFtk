#include "catch.hpp"

#include "utility.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

SCENARIO( "Testing MF=3" ){
  GIVEN( "a string representation of of File 3" ){
    std::string MF3str = utility::slurpFileToMemory( "./MF3.endf" );
    WHEN( "a File<3> is constructed from the string" ){

      auto begin = MF3str.begin();
      auto end = MF3str.end();
      long lineNumber = 0;
      
      lineNumber = 0;
      StructureDivision division( begin, end, lineNumber);
      File<3> MF3(division, begin, end, lineNumber );
    }
  } // GIVEN
} // SCENARIO

