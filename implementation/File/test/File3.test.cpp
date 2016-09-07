#include "catch.hpp"

#include "utility.hpp"

#include "ENDFtk.hpp"

SCENARIO( "Testing MF=3" ){
  GIVEN( "a string representation of of File 3" ){
    static const std::string mf3 = utility::slurpFileToMemory( "./MF3.endf" );
    WHEN( "a File<3> is constructed from the string" ){

      ENDFtk::implementation::File<3> myFile(mf3);
    }
  } // GIVEN
} // SCENARIO

