#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscreteTwoBodyRecoils =
section::Type< 6 >::DiscreteTwoBodyRecoils;

SCENARIO( "DiscreteTwoBodyRecoils" ) {

  GIVEN( "a string representation of a valid DiscreteTwoBodyRecoils" ) {

    THEN( "a DiscreteTwoBodyRecoils can be constructed and "
          "members can be tested" ) {
      DiscreteTwoBodyRecoils chunk;

      CHECK( 4 == chunk.LAW() );

      CHECK( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteTwoBodyRecoils" ) {

    DiscreteTwoBodyRecoils chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO
