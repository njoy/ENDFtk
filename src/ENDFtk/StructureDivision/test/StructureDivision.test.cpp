// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/StructureDivision.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

SCENARIO( "StructureDivision" ) {

  THEN( "The end record generators work" ) {

    CHECK_THROWS( SEND( 0, 1) );
    CHECK_THROWS( SEND( 1, 0) );
    CHECK_NOTHROW( SEND( 1, 1) );
    CHECK_NOTHROW( SEND( 125, 2) );
    CHECK_THROWS( FEND( -2 ) );
    CHECK_THROWS( FEND( 0 ) );
    CHECK_NOTHROW( FEND( 1 ) );
    CHECK_NOTHROW( FEND( 125 ) );
    CHECK_NOTHROW( MEND() );
    CHECK_NOTHROW( TEND() );

    CHECK( SEND( 1, 1 ).isSend() );
    CHECK( not SEND( 1, 1 ).isHead() );
    CHECK( not SEND( 1, 1 ).isFend() );
    CHECK( not SEND( 1, 1 ).isMend() );
    CHECK( not SEND( 1, 1 ).isTend() );

    CHECK( FEND( 1 ).isFend() );
    CHECK( not FEND( 1 ).isHead() );
    CHECK( not FEND( 1 ).isSend() );
    CHECK( not FEND( 1 ).isMend() );
    CHECK( not FEND( 1 ).isTend() );

    CHECK( MEND().isMend() );
    CHECK( not MEND().isHead() );
    CHECK( not MEND().isSend() );
    CHECK( not MEND().isFend() );
    CHECK( not MEND().isTend() );

    CHECK( TEND().isTend() );
    CHECK( not TEND().isHead() );
    CHECK( not TEND().isSend() );
    CHECK( not TEND().isFend() );
    CHECK( not TEND().isMend() );
  }

  GIVEN( "a head record string") {

    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          5 125 1451    1";

    WHEN( "passed to the parsing ctor" ) {

      THEN( "the structure division will be built correctly" ) {

        auto lineNumber = 0l;
        auto it = line.begin() + 1;
        auto end = line.end();
        CHECK_NOTHROW( StructureDivision( it, end, lineNumber ) );
      }

      auto lineNumber = 0l;
      auto it = line.begin() + 1;
      auto end = line.end();
      auto record = StructureDivision( it, end, lineNumber );

      THEN( "the record will not be an end record" ) {

        CHECK( not record.isSend() );
        CHECK( not record.isFend() );
        CHECK( not record.isMend() );
        CHECK( not record.isTend() );
      }
      THEN( "the record will be a head record" ) {

        CHECK( record.isHead() );
      }
    }
  }

  GIVEN( "a head record string with an illegal MAT" ) {

    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0  -2 1451    1";

    THEN( "the ctor will throw" ) {

      auto lineNumber = 0l;
      auto it = line.begin() + 1;
      auto end = line.end();
      CHECK_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }

  GIVEN( "a head record string with an illegal MF" ) {

    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125-1451    1";

    THEN( "the ctor will throw" ) {

      auto lineNumber = 0l;
      auto it = line.begin() + 1;
      auto end = line.end();
      CHECK_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }

  GIVEN( "a head record string with an illegal MT" ) {

    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125 1 -1    1";

    THEN( "the ctor will throw" ) {

      auto lineNumber = 0l;
      auto it = line.begin() + 1;
      auto end = line.end();
      CHECK_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }

  GIVEN( "a valid instance of a head record" ) {
    std::string string =
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n";
    auto lineNumber = 0l;
    auto it = string.begin();
    auto end = string.end();
    auto record = StructureDivision( it, end, lineNumber );
    THEN( "the head record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      CHECK( buffer == string );
    }
  }

  GIVEN( "a valid instance of a SEND record" ) {
    std::string string =
    "                                                                   125 1  0     \n";
    auto record = SEND( 125, 1 );
    THEN( "the SEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      CHECK( buffer == string );
    }
  }

  GIVEN( "a valid instance of a FEND record" ) {

    std::string string =
    "                                                                   125 0  0     \n";
    auto record = FEND( 125 );
    THEN( "the SEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      CHECK( buffer == string );
    }
  }

  GIVEN( "a valid instance of a MEND record" ) {

    std::string string =
    "                                                                     0 0  0     \n";
    auto record = MEND();
    THEN( "the MEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      CHECK( buffer == string );
    }
  }

  GIVEN( "a valid instance of a TEND record" ) {

    std::string string =
    "                                                                    -1 0  0     \n";
    auto record = TEND();
    THEN( "the TEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      CHECK( buffer == string );
    }
  }
}
