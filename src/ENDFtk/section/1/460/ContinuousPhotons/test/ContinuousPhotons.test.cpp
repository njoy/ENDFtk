#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/460.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ContinuousPhotons = section::Type< 1, 460 >::ContinuousPhotons;

std::string chunk();
void verifyChunk( const ContinuousPhotons& );
std::string invalidNNF();

SCENARIO( "ContinuousPhotons" ) {

  GIVEN( "valid data for a ContinuousPhotons" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > constants = { 1.333600e-2, 3.273900e-2,
                                          1.207800e-1, 3.027800e-1,
                                          8.494900e-1, 2.853000e+0 };

      ContinuousPhotons chunk( std::move( constants ) );

      THEN( "an ContinuousPhotons can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 460 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuousPhotons chunk( begin, end, lineNumber, 9228, 1, 460 );

      THEN( "a ContinuousPhotons can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 460 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ContinuousPhotons" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (LIST takes care of tests)

      std::vector< double > empty = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ContinuousPhotons( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid NNF is given" ) {

      std::string string = invalidNNF();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ContinuousPhotons( begin, end, lineNumber, 9228, 1, 460 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          6          09228 1460     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n";
}

void verifyChunk( const ContinuousPhotons& chunk ) {

  CHECK( 2 == chunk.LO() );
  CHECK( 2 == chunk.representation() );
  CHECK( 0 == chunk.NG() );
  CHECK( 0 == chunk.numberDiscretePhotons() );
  CHECK( 6 == chunk.NNF() );
  CHECK( 6 == chunk.numberPrecursors() );

  CHECK( 6 == chunk.lambdas().size() );
  CHECK( 6 == chunk.decayConstants().size() );
  CHECK( 0.013336 == Approx( chunk.lambdas()[0] ) );
  CHECK( 0.032739 == Approx( chunk.lambdas()[1] ) );
  CHECK( 0.12078 == Approx( chunk.lambdas()[2] ) );
  CHECK( 0.30278 == Approx( chunk.lambdas()[3] ) );
  CHECK( 0.84949 == Approx( chunk.lambdas()[4] ) );
  CHECK( 2.853000 == Approx( chunk.lambdas()[5] ) );
  CHECK( 0.013336 == Approx( chunk.decayConstants()[0] ) );
  CHECK( 0.032739 == Approx( chunk.decayConstants()[1] ) );
  CHECK( 0.12078 == Approx( chunk.decayConstants()[2] ) );
  CHECK( 0.30278 == Approx( chunk.decayConstants()[3] ) );
  CHECK( 0.84949 == Approx( chunk.decayConstants()[4] ) );
  CHECK( 2.853000 == Approx( chunk.decayConstants()[5] ) );

  CHECK( 2 == chunk.NC() );
}

std::string invalidNNF() {
  return
    " 0.000000+0 0.000000+0          0          0          0          09228 1460     \n";
}
