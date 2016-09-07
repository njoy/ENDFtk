#include "catch.hpp"

#include "utility.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

SCENARIO( "Testing MF=3" ){
  GIVEN( "a string representation of of File 3" ){
    std::string H1 = utility::slurpFileToMemory( "./n-001_H_001.endf" );
    WHEN( "a File<3> is constructed from the string" ){

      auto tapeBegin = H1.begin();
      auto tapeEnd = H1.end();
      long lineNumber = 0;
      
      auto& MF3Skeleton =
        TapeSkeleton< std::string::iterator >
        ( tapeBegin, tapeEnd, lineNumber ).MAT(125)[0].MF(3);
        
      auto it = MF3Skeleton.bufferBegin();
      auto end = MF3Skeleton.bufferEnd();
      lineNumber = 0;
      HeadRecord head( it, end, lineNumber);
      File<3> myFile(head, it, end, lineNumber );
    }
  } // GIVEN
} // SCENARIO

