#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using IsotropicDiscreteEmission = 
section::Type< 6 >::IsotropicDiscreteEmission;

SCENARIO( "IsotropicDiscreteEmission" ) {

  GIVEN( "a string representation of a valid IsotropicDiscreteEmission" ) {

    THEN( "a IsotropicDiscreteEmission can be constructed and "
          "members can be tested" ) {
      IsotropicDiscreteEmission chunk;

      REQUIRE( 3 == chunk.LAW() );

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of IsotropicDiscreteEmission" ) {

    IsotropicDiscreteEmission chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

