#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "section::Type< 6 >::DefinedElsewhere" ) {

  GIVEN( "a string representation of a valid section::Type< 6 >::DefinedElsewhere" ) {

    THEN( "a section::Type< 6 >::DefinedElsewhere can be constructed and members can be tested" ) {
      section::Type< 6 >::DefinedElsewhere chunk( -5 );

      REQUIRE( -5 == chunk.LAW() );

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DefinedElsewhere" ) {

    section::Type< 6 >::DefinedElsewhere chunk( -5 );

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

