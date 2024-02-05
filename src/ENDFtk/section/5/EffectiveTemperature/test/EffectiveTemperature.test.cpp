// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using EffectiveTemperature =
section::Type< 5 >::EffectiveTemperature;

std::string chunk();
void verifyChunk( const EffectiveTemperature& );
std::string invalidChunk();

SCENARIO( "EffectiveTemperature" ) {

  GIVEN( "valid data for a EffectiveTemperature" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > energies = { 0.0, 1e+4, 2e+4,
                                         1.83e+6, 1.84e+6 };
      std::vector< double > thetas = { 2.265227e-7, 2.029471e-6, 2.272542e-6,
                                       0.0, 0.0 };

      EffectiveTemperature chunk( std::move( boundaries ),
                       std::move( interpolants ),
                       std::move( energies ),
                       std::move( thetas ) );

      THEN( "a EffectiveTemperature can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EffectiveTemperature chunk( begin, end, lineNumber, 9437, 5, 455 );

      THEN( "a EffectiveTemperature can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a EffectiveTemperature" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 5 };
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< double > energies = { 0.0, 1e+4, 2e+4,
                                         1.83e+6, 1.84e+6 };
      std::vector< double > thetas = { 2.265227e-7, 2.029471e-6, 2.272542e-6,
                                       0.0, 0.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EffectiveTemperature( std::move( boundaries ),
                                              std::move( wrongInterpolants ),
                                              std::move( energies ),
                                              std::move( thetas ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EffectiveTemperature( begin, end, lineNumber,
                                              9437, 5, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 0.000000+0 2.265227-7 1.000000+4 2.029471-6 2.000000+4 2.272542-69437 5455     \n"
    " 1.830000+6 0.000000+0 1.840000+6 0.000000+0                      9437 5455     \n";
}

void verifyChunk( const EffectiveTemperature& chunk ) {

  CHECK( 5 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 5 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.E().size() );
  CHECK( 5 == chunk.energies().size() );
  CHECK( 5 == chunk.thetas().size() );
  CHECK_THAT( 0.0, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 2e+4, WithinRel( chunk.E()[2] ) );
  CHECK_THAT( 1.83e+6, WithinRel( chunk.E()[3] ) );
  CHECK_THAT( 1.84e+6, WithinRel( chunk.E()[4] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2e+4, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.83e+6, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 1.84e+6, WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 2.265227e-7, WithinRel( chunk.thetas()[0] ) );
  CHECK_THAT( 2.029471e-6, WithinRel( chunk.thetas()[1] ) );
  CHECK_THAT( 2.272542e-6, WithinRel( chunk.thetas()[2] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.thetas()[3] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.thetas()[4] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}
