#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


std::string getMFD3Record();


SCENARIO( "reading a GendfDataRecord" ) {
  GIVEN( "a string representation" ) {
    WHEN( "a valid record is given" ) {

      std::string buffer = getMFD3Record();

      auto begin = buffer.begin();
      auto end = buffer.end();
      long int lineNo = 2;

      THEN( "the object can be created" ) {
        GendfDataRecord record( begin, end, lineNo, 1, 1, 9228, 3, 2 );

        // check data
        CHECK( record.temperature() == Approx(293.6) );
        CHECK( record.NG2() == 2 );
        CHECK( record.numSecondaryPositions() == 2 );
        CHECK( record.IG2LO() == 1 );
        CHECK( record.lowestGroup() == 1 );
        CHECK( record.IG() == 1 );
        CHECK( record.group() == 1);
        CHECK( record.flux()[0] == Approx(8.86484e+4) );
        CHECK( record.values()[0] == Approx(14.69141) );
      }
    }
  }
}


std::string getMFD3Record() {
  return
    " 2.936000+2 0.000000+0          2          1          2          19228 3  2    2\n"
    " 8.864840+4 1.469141+1                                            9228 3  2    3\n";
}

