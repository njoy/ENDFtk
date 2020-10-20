#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using OutgoingEnergyDistribution = 
section::Type< 5 >::TabulatedSpectrum::OutgoingEnergyDistribution;

std::string chunk();
void verifyChunk( const OutgoingEnergyDistribution& );
std::string invalidChunk();

SCENARIO( "OutgoingEnergyDistribution" ) {

  GIVEN( "valid data for an OutgoingEnergyDistribution" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 1e-5;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 0.0, 1e+5, 3e+7 };
      std::vector< double > values = { 0.0, 1.757570e-9, 1.843350e-9 };

      OutgoingEnergyDistribution chunk( incident,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( energies ),
                                        std::move( values ) );

      THEN( "an OutgoingEnergyDistribution can be constructed and members can "
            "be tested" ) {

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

      OutgoingEnergyDistribution chunk( begin, end, lineNumber, 9437, 5, 18 );

      THEN( "an OutgoingEnergyDistribution can be constructed and members can "
            "be tested" ) {

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

  GIVEN( "invalid data for an OutgoingEnergyDistribution" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double incident = 1e-5;
      std::vector< long > boundaries = { 3 };
      std::vector< long > wrongInterpolants = { 2, 4 };
      std::vector< double > energies = { 0.0, 1e+5, 3e+7 };
      std::vector< double > values = { 0.0, 1.757570e-9, 1.843350e-9 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS(
                OutgoingEnergyDistribution( incident,
                                            std::move( boundaries ),
                                            std::move( wrongInterpolants ),
                                            std::move( energies ),
                                            std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( OutgoingEnergyDistribution( begin, end, lineNumber,
                                                    9437, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n";
}

void verifyChunk( const OutgoingEnergyDistribution& chunk ) {

  REQUIRE( 1e-5 == Approx( chunk.E() ) );
  REQUIRE( 1e-5 == Approx( chunk.incomingEnergy() ) );

  REQUIRE( 3 == chunk.NF() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 2 == chunk.interpolants()[0] );
  REQUIRE( 3 == chunk.boundaries()[0] );
  REQUIRE( 3 == chunk.EPRIME().size() );
  REQUIRE( 3 == chunk.outgoingEnergies().size() );
  REQUIRE( 3 == chunk.g().size() );
  REQUIRE( 3 == chunk.probabilities().size() );
  REQUIRE( 0.0 == Approx( chunk.EPRIME()[0] ) );
  REQUIRE( 1e+5 == Approx( chunk.EPRIME()[1] ) );
  REQUIRE( 3e+7 == Approx( chunk.EPRIME()[2] ) );
  REQUIRE( 0.0 == Approx( chunk.outgoingEnergies()[0] ) );
  REQUIRE( 1e+5 == Approx( chunk.outgoingEnergies()[1] ) );
  REQUIRE( 3e+7 == Approx( chunk.outgoingEnergies()[2] ) );
  REQUIRE( 0. == Approx( chunk.g()[0] ) );
  REQUIRE( 1.757570e-9 == Approx( chunk.g()[1] ) );
  REQUIRE( 1.843350e-9 == Approx( chunk.g()[2] ) );
  REQUIRE( 0. == Approx( chunk.probabilities()[0] ) );
  REQUIRE( 1.757570e-9 == Approx( chunk.probabilities()[1] ) );
  REQUIRE( 1.843350e-9 == Approx( chunk.probabilities()[2] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0          2          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n";
}
