#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK_THROWS( TabulatedSpectrum( std::move( boundaries ),
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

        CHECK_THROWS( TabulatedSpectrum( begin, end, lineNumber,
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

  CHECK( 1 == chunk.LF() );
  CHECK( 1 == chunk.LAW() );

  CHECK( 1 == chunk.NR() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 4 == chunk.interpolants()[0] );

  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK( 1e-5 == Approx( chunk.incidentEnergies()[0] ) );
  CHECK( 3e+7 == Approx( chunk.incidentEnergies()[1] ) );

  auto value = chunk.outgoingDistributions()[0];
  CHECK( 1e-5 == Approx( value.E() ) );
  CHECK( 1e-5 == Approx( value.incidentEnergy() ) );
  CHECK( 3 == value.NP() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 3 == value.boundaries()[0] );
  CHECK( 3 == value.EP().size() );
  CHECK( 3 == value.outgoingEnergies().size() );
  CHECK( 3 == value.G().size() );
  CHECK( 3 == value.probabilities().size() );
  CHECK( 0.0 == Approx( value.EP()[0] ) );
  CHECK( 1e+5 == Approx( value.EP()[1] ) );
  CHECK( 3e+7 == Approx( value.EP()[2] ) );
  CHECK( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  CHECK( 1e+5 == Approx( value.outgoingEnergies()[1] ) );
  CHECK( 3e+7 == Approx( value.outgoingEnergies()[2] ) );
  CHECK( 0. == Approx( value.G()[0] ) );
  CHECK( 1.757570e-9 == Approx( value.G()[1] ) );
  CHECK( 1.843350e-9 == Approx( value.G()[2] ) );
  CHECK( 0. == Approx( value.probabilities()[0] ) );
  CHECK( 1.757570e-9 == Approx( value.probabilities()[1] ) );
  CHECK( 1.843350e-9 == Approx( value.probabilities()[2] ) );

  value = chunk.outgoingDistributions()[1];
  CHECK( 3e+7 == Approx( value.E() ) );
  CHECK( 3e+7 == Approx( value.incidentEnergy() ) );
  CHECK( 4 == value.NP() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 4 == value.boundaries()[0] );
  CHECK( 4 == value.EP().size() );
  CHECK( 4 == value.outgoingEnergies().size() );
  CHECK( 4 == value.G().size() );
  CHECK( 4 == value.probabilities().size() );
  CHECK( 0.0 == Approx( value.EP()[0] ) );
  CHECK( 10. == Approx( value.EP()[1] ) );
  CHECK( 11. == Approx( value.EP()[2] ) );
  CHECK( 3e+7 == Approx( value.EP()[3] ) );
  CHECK( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  CHECK( 10. == Approx( value.outgoingEnergies()[1] ) );
  CHECK( 11. == Approx( value.outgoingEnergies()[2] ) );
  CHECK( 3e+7 == Approx( value.outgoingEnergies()[3] ) );
  CHECK( 0. == Approx( value.G()[0] ) );
  CHECK( 1.733405e-9 == Approx( value.G()[1] ) );
  CHECK( 1.818010e-9 == Approx( value.G()[2] ) );
  CHECK( 1.898849e-9 == Approx( value.G()[3] ) );
  CHECK( 0. == Approx( value.probabilities()[0] ) );
  CHECK( 1.733405e-9 == Approx( value.probabilities()[1] ) );
  CHECK( 1.818010e-9 == Approx( value.probabilities()[2] ) );
  CHECK( 1.898849e-9 == Approx( value.probabilities()[3] ) );

  CHECK( 9 == chunk.NC() );
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
