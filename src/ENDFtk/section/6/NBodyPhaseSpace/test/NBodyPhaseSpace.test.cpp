#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using NBodyPhaseSpace = 
section::Type< 6 >::NBodyPhaseSpace;

std::string chunk();
void verifyChunk( const NBodyPhaseSpace& );
std::string invalidChunk();

SCENARIO( "NBodyPhaseSpace" ) {

  GIVEN( "valid data for a NBodyPhaseSpace" ) {

    WHEN( "the data is given explicitly" ) {

      double APSX = 5.;
      long NPSX = 4;

      THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {

        NBodyPhaseSpace chunk( APSX, NPSX );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {

        NBodyPhaseSpace chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
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
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a Multiplicity" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (CONT takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( NBodyPhaseSpace( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}

void verifyChunk( const NBodyPhaseSpace& chunk ) {

  REQUIRE( 6 == chunk.LAW() );

  REQUIRE( 5. == Approx( chunk.APSX() ) );
  REQUIRE( 5. == Approx( chunk.totalMass() ) );
  REQUIRE( 4 == chunk.NPSX() );
  REQUIRE( 4 == chunk.numberParticles() );

  REQUIRE( 1 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 5.000000+0 0.000000+0 1        0          0          0          49228 6  5     \n";
}
