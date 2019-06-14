#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using MaxwellianFissionSpectrum = 
section::Type< 5 >::MaxwellianFissionSpectrum;

std::string chunk();
void verifyChunk( const MaxwellianFissionSpectrum& );
std::string invalidChunk();

SCENARIO( "MaxwellianFissionSpectrum" ) {

  GIVEN( "valid data for a MaxwellianFissionSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > energies = { 0.0, 1e+4, 2e+4,
                                         1.83e+6, 1.84e+6 };
      std::vector< double > thetas = { 2.265227e-7, 2.029471e-6, 2.272542e-6,
                                       0.0, 0.0 };

      MaxwellianFissionSpectrum chunk( std::move( boundaries ),
                                       std::move( interpolants ),
                                       std::move( energies ),
                                       std::move( thetas ) );

      THEN( "a MaxwellianFissionSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      MaxwellianFissionSpectrum chunk( begin, end, lineNumber, 9437, 5, 455 );

      THEN( "a MaxwellianFissionSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a MaxwellianFissionSpectrum" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 5 };
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< double > energies = { 0.0, 1e+4, 2e+4,
                                         1.83e+6, 1.84e+6 };
      std::vector< double > thetas = { 2.265227e-7, 2.029471e-6, 2.272542e-6,
                                       0.0, 0.0 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( MaxwellianFissionSpectrum( std::move( boundaries ),
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

        REQUIRE_THROWS( MaxwellianFissionSpectrum( begin, end, lineNumber,
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

void verifyChunk( const MaxwellianFissionSpectrum& chunk ) {

  REQUIRE( 7 == chunk.LF() );
  REQUIRE( 7 == chunk.LAW() );

  REQUIRE( 5 == chunk.NE() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );
  REQUIRE( 5 == chunk.boundaries()[0] );
  REQUIRE( 5 == chunk.E().size() );
  REQUIRE( 5 == chunk.energies().size() );
  REQUIRE( 5 == chunk.thetas().size() );
  REQUIRE( 5 == chunk.values().size() );
  REQUIRE( 0.0 == Approx( chunk.E()[0] ) );
  REQUIRE( 1e+4 == Approx( chunk.E()[1] ) );
  REQUIRE( 2e+4 == Approx( chunk.E()[2] ) );
  REQUIRE( 1.83e+6 == Approx( chunk.E()[3] ) );
  REQUIRE( 1.84e+6 == Approx( chunk.E()[4] ) );
  REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
  REQUIRE( 1e+4 == Approx( chunk.energies()[1] ) );
  REQUIRE( 2e+4 == Approx( chunk.energies()[2] ) );
  REQUIRE( 1.83e+6 == Approx( chunk.energies()[3] ) );
  REQUIRE( 1.84e+6 == Approx( chunk.energies()[4] ) );
  REQUIRE( 2.265227e-7 == Approx( chunk.thetas()[0] ) );
  REQUIRE( 2.029471e-6 == Approx( chunk.thetas()[1] ) );
  REQUIRE( 2.272542e-6 == Approx( chunk.thetas()[2] ) );
  REQUIRE( 0.0 == Approx( chunk.thetas()[3] ) );
  REQUIRE( 0.0 == Approx( chunk.thetas()[4] ) );
  REQUIRE( 2.265227e-7 == Approx( chunk.values()[0] ) );
  REQUIRE( 2.029471e-6 == Approx( chunk.values()[1] ) );
  REQUIRE( 2.272542e-6 == Approx( chunk.values()[2] ) );
  REQUIRE( 0.0 == Approx( chunk.values()[3] ) );
  REQUIRE( 0.0 == Approx( chunk.values()[4] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}
