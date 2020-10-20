#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DefinedElsewhere = 
section::Type< 6 >::DefinedElsewhere;

SCENARIO( "DefinedElsewhere" ) {

  GIVEN( "valid data for DefinedElsewhere" ) {

    std::vector< int > laws = { -4, -5, -14, -15 };

    THEN( "a DefinedElsewhere can be constructed and members can be tested "
          "for all allowed LAW values" ) {

      for ( auto law : laws ) {

        DefinedElsewhere chunk( law );
        REQUIRE( law == chunk.LAW() );
        REQUIRE( 0 == chunk.NC() );
      }
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of DefinedElsewhere" ) {

    DefinedElsewhere chunk( -5 );

    THEN( "it does not print anything" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for DefinedElsewhere" ) {

    std::vector< int > invalid = { 1, 0, -3, -6, -13, -16, -20 };

    THEN( "an exception is thrown" ) {

      for ( auto law : invalid ) {

        REQUIRE_THROWS( DefinedElsewhere( law ) );
      }
    } // THEN
  } // GIVEN
} // SCENARIO
