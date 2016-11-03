#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "TextRecord Tests", "[ENDFtk], [TextRecord]" ){
  std::string line = 
    "The new R-matrix analysis of the N-N system on which the ENDF/B-   125 1451   12\n";

  std::string text = 
    "The new R-matrix analysis of the N-N system on which the ENDF/B-  ";

  GIVEN( "a string ravlue, the ctor works"){
    REQUIRE_NOTHROW( TextRecord( utility::copy(text) ) );
  }
  GIVEN( "iterators and a line number"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    WHEN("the tail values match, the ctor works"){
      REQUIRE_NOTHROW( TextRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("the MAT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( TextRecord( it, end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("the MF value doesn't match, the ctor throws"){
      REQUIRE_THROWS( TextRecord( it, end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("the MT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( TextRecord( it, end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN( "A constructed text record"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    auto textRecord0 = TextRecord( it, end, lineNumber, 125, 1, 451 );
    const auto& constTextRecord0 = textRecord0;
    auto textRecord1 = TextRecord( utility::copy( text ) );
    const auto& constTextRecord1 = textRecord1;
    THEN( "the getter will work" ){
      REQUIRE( textRecord0.text() == text );
      REQUIRE( textRecord1.text() == text );
      REQUIRE( constTextRecord0.text() == text );
      REQUIRE( constTextRecord1.text() == text );
      textRecord0.text() = "foobar";
      textRecord1.text() = "foobaz";
      REQUIRE( textRecord0.text() == "foobar" );
      REQUIRE( textRecord1.text() == "foobaz" );
      /* can't assign to const. doesn't compile */
      // constTextRecord0.text() = "foobar";
    }
    THEN( "the equality and inequality operators will work" ){
      REQUIRE( textRecord0 == textRecord1 );
      textRecord0.text() = "foobar";
      textRecord1.text() = "foobaz";
      REQUIRE( textRecord0 != textRecord1 );
    }
  }
  GIVEN("A line with a typo"){
    std::string line = 
      "The new R-matrix analysis of the N-N system on which the ENDF/B-   1a5 1451   12\n";
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    
    THEN("the ctor throws"){
      REQUIRE_THROWS( TextRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
  }
}
