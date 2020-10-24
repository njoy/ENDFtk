#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;

std::string chunk();
void verifyChunk( const IncoherentElastic& );
std::string invalidChunk();

SCENARIO( "IncoherentElastic" ) {

  GIVEN( "valid data for a IncoherentElastic" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double sb = 8.198006e+1;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > temperatures = { 296., 400., 500. };
      std::vector< double > debyeWallerValues = { 8.486993e+0, 9.093191e+0,
                                                  9.828159e+0 };

      IncoherentElastic chunk( sb,
                               std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( temperatures ),
                               std::move( debyeWallerValues ) );

      THEN( "an IncoherentElastic can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      IncoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );

      THEN( "a IncoherentElastic can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a IncoherentElastic" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double sb = 8.198006e+1;
      std::vector< long > wrongBoundaries = { 3, 4 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > temperatures = { 296., 400., 500. };
      std::vector< double > debyeWallerValues = { 8.486993e+0, 9.093191e+0,
                                                  9.828159e+0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( IncoherentElastic( sb,
                                           std::move( wrongBoundaries ),
                                           std::move( interpolants ),
                                           std::move( temperatures ),
                                           std::move( debyeWallerValues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( IncoherentElastic( begin, end, lineNumber, 27, 7, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
}

void verifyChunk( const IncoherentElastic& chunk ) {

  CHECK( 2 == chunk.LTHR() );
  CHECK( 2 == chunk.elasticScatteringType() );
  CHECK( 8.198006e+1 == Approx( chunk.SB() ) );
  CHECK( 8.198006e+1 == Approx( chunk.boundCrossSection() ) );
  CHECK( 3 == chunk.NP() );
  CHECK( 3 == chunk.NT() );
  CHECK( 3 == chunk.numberTemperatures() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 3 == chunk.T().size() );
  CHECK( 3 == chunk.temperatures().size() );
  CHECK( 3 == chunk.W().size() );
  CHECK( 3 == chunk.debyeWallerValues().size() );
  CHECK( 296. == Approx( chunk.T()[0] ) );
  CHECK( 400. == Approx( chunk.T()[1] ) );
  CHECK( 500. == Approx( chunk.T()[2] ) );
  CHECK( 296. == Approx( chunk.temperatures()[0] ) );
  CHECK( 400. == Approx( chunk.temperatures()[1] ) );
  CHECK( 500. == Approx( chunk.temperatures()[2] ) );
  CHECK( 8.486993e+0 == Approx( chunk.W()[0] ) );
  CHECK( 9.093191e+0 == Approx( chunk.W()[1] ) );
  CHECK( 9.828159e+0 == Approx( chunk.W()[2] ) );
  CHECK( 8.486993e+0 == Approx( chunk.debyeWallerValues()[0] ) );
  CHECK( 9.093191e+0 == Approx( chunk.debyeWallerValues()[1] ) );
  CHECK( 9.828159e+0 == Approx( chunk.debyeWallerValues()[2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 8.198006+1 0.000000+0          0          0          1          4  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
}
