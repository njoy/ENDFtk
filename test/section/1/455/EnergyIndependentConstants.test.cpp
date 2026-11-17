// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/455.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using EnergyIndependentConstants = section::Type< 1, 455 >::EnergyIndependentConstants;

std::string chunk();
void verifyChunk( const EnergyIndependentConstants& );

SCENARIO( "EnergyIndependentConstants" ) {

  GIVEN( "valid data for a EnergyIndependentConstants" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > constants = { 1.3336e-2, 3.2739e-2, 1.2078e-1,
                                          3.0278e-1, 8.4949e-1, 2.853 };

      EnergyIndependentConstants chunk( std::move( constants ) );

      THEN( "an EnergyIndependentConstants can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyIndependentConstants chunk( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "a EnergyIndependentConstants can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n";
}

void verifyChunk( const EnergyIndependentConstants& chunk ) {

  CHECK( 0 == chunk.LDG() );
  CHECK( 0 == chunk.type() );
  CHECK( 6 == chunk.NNF() );
  CHECK( 6 == chunk.numberPrecursors() );

  CHECK( 6 == chunk.lambdas().size() );
  CHECK( 6 == chunk.decayConstants().size() );
  CHECK_THAT( 0.013336, WithinRel( chunk.lambdas()[0] ) );
  CHECK_THAT( 0.032739, WithinRel( chunk.lambdas()[1] ) );
  CHECK_THAT( 0.12078, WithinRel( chunk.lambdas()[2] ) );
  CHECK_THAT( 0.30278, WithinRel( chunk.lambdas()[3] ) );
  CHECK_THAT( 0.84949, WithinRel( chunk.lambdas()[4] ) );
  CHECK_THAT( 2.853000, WithinRel( chunk.lambdas()[5] ) );
  CHECK_THAT( 0.013336, WithinRel( chunk.decayConstants()[0] ) );
  CHECK_THAT( 0.032739, WithinRel( chunk.decayConstants()[1] ) );
  CHECK_THAT( 0.12078, WithinRel( chunk.decayConstants()[2] ) );
  CHECK_THAT( 0.30278, WithinRel( chunk.decayConstants()[3] ) );
  CHECK_THAT( 0.84949, WithinRel( chunk.decayConstants()[4] ) );
  CHECK_THAT( 2.853000, WithinRel( chunk.decayConstants()[5] ) );

  CHECK( 2 == chunk.NC() );
}
