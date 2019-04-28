#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using TabulatedSpectrum = 
section::Type< 5 >::TabulatedSpectrum;
using OutgoingEnergyDistribution = 
section::Type< 5 >::TabulatedSpectrum::OutgoingEnergyDistribution;

std::string chunk();
void verifyChunk( const TabulatedSpectrum& );
std::string invalidChunk();

SCENARIO( "TabulatedSpectrum" ) {

  GIVEN( "valid data for a TabulatedSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 4 };
      std::vector< OutgoingEnergyDistribution > outgoing = {
          OutgoingEnergyDistribution( 1e-5, { 3 }, { 2 },
                                      { 0.0, 1e+5, 3e+7 },
                                      { 0.0, 1.757570e-9, 1.843350e-9 } ),
          OutgoingEnergyDistribution( 3e+7, { 4 }, { 2 },
                                      { 0.0, 10., 11., 3e+7 },
                                      { 0.0, 1.733405e-9, 1.818010e-9,
                                        1.898849e-9 } ) };

      TabulatedSpectrum chunk( std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( outgoing ) );

      THEN( "a TabulatedSpectrum can be constructed" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TabulatedSpectrum chunk( begin, end, lineNumber, 9437, 5, 18 );

      THEN( "a TabulatedSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedSpectrum" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 4, 2 };
      std::vector< OutgoingEnergyDistribution > outgoing = {
          OutgoingEnergyDistribution( 1e-5, { 3 }, { 2 },
                                      { 0.0, 1e+5, 3e+7 },
                                      { 0.0, 1.757570e-9, 1.843350e-9 } ),
          OutgoingEnergyDistribution( 3e+7, { 4 }, { 2 },
                                      { 0.0, 10., 11., 3e+7 },
                                      { 0.0, 1.733405e-9, 1.818010e-9,
                                        1.898849e-9 } ) };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( TabulatedSpectrum( std::move( boundaries ),
                                           std::move( wrongInterpolants ),
                                           std::move( outgoing ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( TabulatedSpectrum( begin, end, lineNumber,
                                           9437, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n"
    "          2          4                                            9437 5 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n"
    "          4          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n"
    " 3.000000+7 1.898849-9                                            9437 5 18     \n";
}

void verifyChunk( const TabulatedSpectrum& chunk ) {

  REQUIRE( 1 == chunk.LF() );
  REQUIRE( 1 == chunk.distributionType() );

  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 2 == chunk.NE() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 2 == chunk.boundaries()[0] );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 4 == chunk.interpolants()[0] );

  auto value = chunk.outgoingDistributions()[0];
  REQUIRE( 1e-5 == Approx( value.incidentEnergy() ) );
  REQUIRE( 3 == value.NP() );
  REQUIRE( 1 == value.NR() );
  REQUIRE( 1 == value.interpolants().size() );
  REQUIRE( 1 == value.boundaries().size() );
  REQUIRE( 2 == value.interpolants()[0] );
  REQUIRE( 3 == value.boundaries()[0] );
  REQUIRE( 3 == value.energies().size() );
  REQUIRE( 3 == value.probabilities().size() );
  REQUIRE( 0.0 == Approx( value.energies()[0] ) );
  REQUIRE( 1e+5 == Approx( value.energies()[1] ) );
  REQUIRE( 3e+7 == Approx( value.energies()[2] ) );
  REQUIRE( 0. == Approx( value.probabilities()[0] ) );
  REQUIRE( 1.757570e-9 == Approx( value.probabilities()[1] ) );
  REQUIRE( 1.843350e-9 == Approx( value.probabilities()[2] ) );

  value = chunk.outgoingDistributions()[1];
  REQUIRE( 3e+7 == Approx( value.incidentEnergy() ) );
   REQUIRE( 4 == value.NP() );
  REQUIRE( 1 == value.NR() );
  REQUIRE( 1 == value.interpolants().size() );
  REQUIRE( 1 == value.boundaries().size() );
  REQUIRE( 2 == value.interpolants()[0] );
  REQUIRE( 4 == value.boundaries()[0] );
  REQUIRE( 4 == value.energies().size() );
  REQUIRE( 4 == value.probabilities().size() );
  REQUIRE( 0.0 == Approx( value.energies()[0] ) );
  REQUIRE( 10. == Approx( value.energies()[1] ) );
  REQUIRE( 11. == Approx( value.energies()[2] ) );
  REQUIRE( 3e+7 == Approx( value.energies()[3] ) );
  REQUIRE( 0. == Approx( value.probabilities()[0] ) );
  REQUIRE( 1.733405e-9 == Approx( value.probabilities()[1] ) );
  REQUIRE( 1.818010e-9 == Approx( value.probabilities()[2] ) );
  REQUIRE( 1.898849e-9 == Approx( value.probabilities()[3] ) );

  REQUIRE( 9 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          29437 5 18     \n"
    "          2          4                                            9437 5 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n"
    "          4          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n"
    " 3.000000+7 1.898849-9                                            9437 5 18     \n";
}
