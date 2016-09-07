#include "catch.hpp"

#include "utility.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

SCENARIO( "Testing MF=3" ){
  GIVEN( "a string representation of of File 3" ){
    static const std::string mf3 = utility::slurpFileToMemory( "./MF3.endf" );
    WHEN( "a File<3> is constructed from the string" ){

      auto begin = mf3.begin();
      auto start = mf3.begin();
      auto end = mf3.end();
      long lineNumber = 0;
      
      HeadRecord head( begin, end, lineNumber);
      
      FileSkeleton< std::string::iterator >
        MF3Skeleton( head, start, begin, end, lineNumber );

      File<3> myFile(head, MF3Skeleton);
    }
  } // GIVEN
} // SCENARIO

