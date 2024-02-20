// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double APSX = 5.;
      long NPSX = 4;

      NBodyPhaseSpace chunk( APSX, NPSX );

      THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      NBodyPhaseSpace chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a NBodyPhaseSpace can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Multiplicity" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (CONT takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NBodyPhaseSpace( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}

void verifyChunk( const NBodyPhaseSpace& chunk ) {

  CHECK( 6 == chunk.LAW() );

  CHECK_THAT( 5., WithinRel( chunk.APSX() ) );
  CHECK_THAT( 5., WithinRel( chunk.totalMass() ) );
  CHECK( 4 == chunk.NPSX() );
  CHECK( 4 == chunk.numberParticles() );

  CHECK( 1 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 5.000000+0 0.000000+0 1        0          0          0          49228 6  5     \n";
}
