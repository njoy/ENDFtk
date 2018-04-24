#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "InterpolationSequenceRecord" ) {

  GIVEN( "a string representation of a valid InterpolationSequenceRecord" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a InterpolationSequenceRecord can be constructed and members can be tested" ) {
      InterpolationSequenceRecord< ControlRecord >
        chunk( begin, end, lineNumber, 9228, 1, 455 );

      REQUIRE( 4 == chunk.NC() );

      InterpolationRecord tab2 = chunk.tab2();
      auto interpolants = tab2.interpolants();
      auto boundaries = tab2.boundaries();
      auto records = chunk.records();

      REQUIRE( 3. == Approx( tab2.C1() ) );
      REQUIRE( 5. == Approx( tab2.C2() ) );
      REQUIRE( 6 == tab2.L1() );
      REQUIRE( 7 == tab2.L2() );
      REQUIRE( 1 == tab2.NR() );
      REQUIRE( 2 == tab2.NZ() );
      REQUIRE( 1 == interpolants.size() );
      REQUIRE( 1 == boundaries.size() );
      REQUIRE( 4 == interpolants[0] );
      REQUIRE( 2 == boundaries[0] );

      REQUIRE( 2 == records.size() );
      REQUIRE( 8. == Approx( records[0].C1() ) );
      REQUIRE( 9. == Approx( records[0].C2() ) );
      REQUIRE( 10 == records[0].L1() );
      REQUIRE( 11 == records[0].L2() );
      REQUIRE( 12 == records[0].N1() );
      REQUIRE( 13 == records[0].N2() );
      REQUIRE( 14. == Approx( records[1].C1() ) );
      REQUIRE( 15. == Approx( records[1].C2() ) );
      REQUIRE( 16 == records[1].L1() );
      REQUIRE( 17 == records[1].L2() );
      REQUIRE( 18 == records[1].N1() );
      REQUIRE( 19 == records[1].N2() );
    }
  } // GIVEN

  GIVEN( "a valid instance of InterpolationSequenceRecord" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    InterpolationSequenceRecord< ControlRecord >
      chunk( begin, end, lineNumber, 9228, 1, 455 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 455 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 3.000000+0 5.000000+0          6          7          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 8.000000+0 9.000000+0         10         11         12         139228 1455     \n"
    " 1.400000+1 1.500000+1         16         17         18         199228 1455     \n";
}

