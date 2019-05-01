#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Isotropic = 
section::Type< 4 >::Isotropic;

SCENARIO( "Isotropic" ) {

  GIVEN( "a valid Isotropic" ) {

    THEN( "an Isotropic can be constructed and members can be tested" ) {

      Isotropic chunk;

      REQUIRE( 0 == chunk.LTT() );
      REQUIRE( 0 == chunk.distributionType() );

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of Isotropic" ) {

    Isotropic chunk;

    THEN( "it does not print anything" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 4, 18 );

      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

