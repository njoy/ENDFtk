#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/458.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string chunk();

SCENARIO( "section::Type< 1, 458 >::EnergyReleaseComponent" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 458 >::EnergyReleaseComponent" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 1, 458 >::EnergyReleaseComponent can be constructed and members can be tested" ) {
      section::Type< 1, 458 >::EnergyReleaseComponent chunk(begin, end, lineNumber, 9228, 1, 458 );

      REQUIRE( 2 == chunk.LDRV() );
      REQUIRE( 1 == chunk.IFC() );

      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energy().size() );
      REQUIRE( 3 == chunk.release().size() );
      REQUIRE( 1e-5 == Approx( chunk.energy()[0] ) );
      REQUIRE( 0.0253 == Approx( chunk.energy()[1] ) );
      REQUIRE( 2e+7 == Approx( chunk.energy()[2] ) );
      REQUIRE( 1.6913e+8 == Approx( chunk.release()[0] ) );
      REQUIRE( 1.691e+8 == Approx( chunk.release()[1] ) );
      REQUIRE( 1.69e+8 == Approx( chunk.release()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 >::EnergyReleaseComponent" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 1, 458 >::EnergyReleaseComponent chunk(begin, end, lineNumber, 9228, 1, 458 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 458 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n";
}
