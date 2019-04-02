#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using NBodyPhaseSpace = 
section::Type< 6 >::NBodyPhaseSpace;

std::string chunk();

SCENARIO( "NBodyPhaseSpace" ) {

  GIVEN( "valid data for a NBodyPhaseSpace" ) {

    double APSX = 5.;
    long NPSX = 4;
      
    THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {
      NBodyPhaseSpace chunk( APSX, NPSX );

      REQUIRE( 6 == chunk.LAW() );

      REQUIRE( 5. == Approx( chunk.APSX() ) );
      REQUIRE( 5. == Approx( chunk.totalMass() ) );
      REQUIRE( 4 == chunk.NPSX() );
      REQUIRE( 4 == chunk.numberParticles() );

      REQUIRE( 1 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid NBodyPhaseSpace" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {
      NBodyPhaseSpace chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 6 == chunk.LAW() );

      REQUIRE( 5. == Approx( chunk.APSX() ) );
      REQUIRE( 5. == Approx( chunk.totalMass() ) );
      REQUIRE( 4 == chunk.NPSX() );
      REQUIRE( 4 == chunk.numberParticles() );

      REQUIRE( 1 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of NBodyPhaseSpace" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    NBodyPhaseSpace chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}
