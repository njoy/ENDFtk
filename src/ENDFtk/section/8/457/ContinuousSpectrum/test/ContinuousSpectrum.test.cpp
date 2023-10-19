// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ContinuousSpectrum = section::Type< 8, 457 >::ContinuousSpectrum;

std::string chunk();
void verifyChunk( const ContinuousSpectrum& );
std::string invalidChunk();

SCENARIO( "ContinuousSpectrum" ) {

  GIVEN( "valid data for a ContinuousSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double decayChain = 4.;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > energies = { 0.0, 5e+5, 7.3e+6 };
      std::vector< double > spectralValues = { 6.133200e-7, 6.133300e-7,
                                               6.02040e-17 };

      ContinuousSpectrum chunk( decayChain,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( spectralValues ) );

      THEN( "a ContinuousSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuousSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a ContinuousSpectrum can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ContinuousSpectrum" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double decayChain = 4.;
      std::vector< long > wrongBoundaries = { 3, 4 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > energies = { 0.0, 5e+5, 7.3e+6 };
      std::vector< double > spectralValues = { 6.133200e-7, 6.133300e-7,
                                               6.02040e-17 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ContinuousSpectrum( decayChain,
                                            std::move( wrongBoundaries ),
                                            std::move( interpolants ),
                                            std::move( energies ),
                                            std::move( spectralValues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ContinuousSpectrum( begin, end, lineNumber,
                                            9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}

void verifyChunk( const ContinuousSpectrum& chunk )
{
  CHECK( 4. == chunk.RTYP() );
  CHECK( 4. == chunk.decayChain() );
  CHECK( 3 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.RP().size() );
  CHECK( 3 == chunk.spectralValues().size() );
  CHECK_THAT( 0.0, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 5e+5, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 7.3e+6, WithinRel( chunk.E()[2] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 5e+5, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.3e+6, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 6.133200e-7, WithinRel( chunk.RP()[0] ) );
  CHECK_THAT( 6.133300e-7, WithinRel( chunk.RP()[1] ) );
  CHECK_THAT( 6.02040e-17, WithinRel( chunk.RP()[2] ) );
  CHECK_THAT( 6.133200e-7, WithinRel( chunk.spectralValues()[0] ) );
  CHECK_THAT( 6.133300e-7, WithinRel( chunk.spectralValues()[1] ) );
  CHECK_THAT( 6.02040e-17, WithinRel( chunk.spectralValues()[2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 4.000000+0 0.000000+0          0          0          1          43580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}
