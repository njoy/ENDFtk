#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Unknown = 
section::Type< 6 >::Unknown;

SCENARIO( "Unknown" ) {

  GIVEN( "a string representation of a valid Unknown" ) {

    THEN( "a Unknown can be constructed and members can be tested" ) {
      Unknown chunk;

      REQUIRE( 0 == chunk.LAW() );

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of Unknown" ) {

    Unknown chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

