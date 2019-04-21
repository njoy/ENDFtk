#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using AnalyticalFunctions = 
section::Type< 7, 4 >::AnalyticalFunctions;

SCENARIO( "AnalyticalFunctions" ) {

  GIVEN( "a valid AnalyticalFunctions" ) {

    THEN( "an AnalyticalFunctions can be constructed and "
          "members can be tested" ) {

      AnalyticalFunctions chunk;

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of DefinedElsewhere" ) {

    AnalyticalFunctions chunk;

    THEN( "it does not print anything" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 4 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

