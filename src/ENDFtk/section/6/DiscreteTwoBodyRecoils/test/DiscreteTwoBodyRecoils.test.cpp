#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "section::Type< 6 >::DiscreteTwoBodyRecoils" ) {

  GIVEN( "a string representation of a valid section::Type< 6 >::DiscreteTwoBodyRecoils" ) {

    THEN( "a section::Type< 6 >::DiscreteTwoBodyRecoils can be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyRecoils chunk;

      REQUIRE( 4 == chunk.LAW() );

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyRecoils" ) {

    section::Type< 6 >::DiscreteTwoBodyRecoils chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

