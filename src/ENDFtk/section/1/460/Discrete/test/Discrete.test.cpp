#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/460.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string invalidNG();

SCENARIO( "section::Type< 1, 460 >::Discrete" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 460 >::Discrete" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 1, 460 >::Discrete can be constructed and members can be tested" ) {
      section::Type< 1, 460 >::Discrete chunk(
        { section::Type< 1, 460 >::DiscretePhoton( begin, end, lineNumber, 9228, 1, 460 ),
          section::Type< 1, 460 >::DiscretePhoton( begin, end, lineNumber, 9228, 1, 460 ) } );

      REQUIRE( 1 == chunk.LO() );
      REQUIRE( 2 == chunk.NG() );

      auto photons = chunk.photons();

      REQUIRE( 2 == photons.size() );

      section::Type< 1, 460 >::DiscretePhoton photon = photons[0];
      REQUIRE( 0.1 == Approx( photon.E() ) );
      REQUIRE( 1 == photon.index() );
      REQUIRE( 1 == photon.NR() );
      REQUIRE( 2 == photon.NP() );
      REQUIRE( 1 == photon.interpolants().size() );
      REQUIRE( 1 == photon.boundaries().size() );
      REQUIRE( 4 == photon.interpolants()[0] );
      REQUIRE( 2 == photon.boundaries()[0] );
      REQUIRE( 2 == photon.time().size() );
      REQUIRE( 2 == photon.multiplicity().size() );
      REQUIRE( 0. == Approx( photon.time()[0] ) );
      REQUIRE( 4. == Approx( photon.time()[1] ) );
      REQUIRE( 4.877451e-1 == Approx( photon.multiplicity()[0] ) );
      REQUIRE( 1.715686e-1 == Approx( photon.multiplicity()[1] ) );

      photon = photons[1];
      REQUIRE( 0.2 == Approx( photon.E() ) );
      REQUIRE( 2 == photon.index() );
      REQUIRE( 1 == photon.NR() );
      REQUIRE( 3 == photon.NP() );
      REQUIRE( 1 == photon.interpolants().size() );
      REQUIRE( 1 == photon.boundaries().size() );
      REQUIRE( 2 == photon.interpolants()[0] );
      REQUIRE( 3 == photon.boundaries()[0] );
      REQUIRE( 3 == photon.time().size() );
      REQUIRE( 3 == photon.multiplicity().size() );
      REQUIRE( 0. == Approx( photon.time()[0] ) );
      REQUIRE( 5. == Approx( photon.time()[1] ) );
      REQUIRE( 9. == Approx( photon.time()[2] ) );
      REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[0] ) );
      REQUIRE( 2.450980e-3 == Approx( photon.multiplicity()[1] ) );
      REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[2] ) );

      REQUIRE( 6 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 460 >::Discrete" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 1, 460 >::Discrete chunk(
      { section::Type< 1, 460 >::DiscretePhoton( begin, end, lineNumber, 9228, 1, 460 ),
        section::Type< 1, 460 >::DiscretePhoton( begin, end, lineNumber, 9228, 1, 460 ) } );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 460 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}
