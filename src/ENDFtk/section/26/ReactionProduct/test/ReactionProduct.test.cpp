#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct =
section::Type< 26 >::ReactionProduct;
using Multiplicity =
section::Type< 26 >::Multiplicity;
using Distribution =
section::Type< 26 >::Distribution;
using ContinuumEnergyAngle =
section::Type< 26 >::ContinuumEnergyAngle;
using LegendreCoefficients =
section::Type< 26 >::ContinuumEnergyAngle::LegendreCoefficients;
using DiscreteTwoBodyScattering =
section::Type< 26 >::DiscreteTwoBodyScattering;
using TabulatedDistribution =
section::Type< 26 >::DiscreteTwoBodyScattering::TabulatedDistribution;
using EnergyTransfer =
section::Type< 26 >::EnergyTransfer;

std::string chunkWithLAW1();
void verifyChunkWithLAW1( const ReactionProduct& );
std::string chunkWithLAW2();
void verifyChunkWithLAW2( const ReactionProduct& );
std::string chunkWithLAW8();
void verifyChunkWithLAW8( const ReactionProduct& );
std::string invalidLAW();

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with LAW=1" ) {

    std::string string = chunkWithLAW1();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1000., .9992414, 1, { 2 }, { 4 },
        { 10., 1e+11 },
        { 1., 1. } );
      Distribution distribution =
        ContinuumEnergyAngle(
          2, { 2 }, { 1 },
          { LegendreCoefficients(
                10., 0, 0,
                { .1, 10. },
                { { 2.1394 }, {  .0212245 } } ),
            LegendreCoefficients(
                1e+11, 0, 0, { .1, 1e+11 }, { { 1.84823 }, { .00876641 } } ) } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 100, 26, 525 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=2" ) {

    std::string string = chunkWithLAW2();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1000., .9992414, 2, { 2 }, { 4 },
        { 10., 1e+11 },
        { 1., 1. } );
      Distribution distribution =
        DiscreteTwoBodyScattering(
          { 2 }, { 1 },
          { TabulatedDistribution( 10., 12, { -1, 1 }, { .5, .5 } ),
            TabulatedDistribution( 1e+11, 12, { -1, 1 }, { .75, .25 } ) } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunkWithLAW2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 100, 26, 525 );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunkWithLAW2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=8" ) {

    std::string string = chunkWithLAW8();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity( 11., 5.438673E-4, 8, { 2 }, { 2 },
                                 { 10., 1.e+11 }, { 1., 1. } );
      Distribution distribution = EnergyTransfer( { 2 }, { 2 },
                                                  { 10., 1.e+11 },
                                                  { 1.e-5, 2e+4 } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunkWithLAW8( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 100, 26, 525 );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunkWithLAW8( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an inconsistent LAW between the Multiplicity and the Distribution" ) {

    Multiplicity multiplicity(
      1000., .9992414, 2, { 2 }, { 4 },
      { 10., 1e+11 },
      { 1., 1. } );
    Distribution distribution =
      ContinuumEnergyAngle(
        2, { 2 }, { 1 },
        { LegendreCoefficients(
              10., 0, 0,
              { .1, 10. },
              { { 2.1394 }, {  .0212245 } } ),
          LegendreCoefficients(
              1e+11, 0, 0, { .1, 1e+11 }, { { 1.84823 }, { .00876641 } } ) } );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( ReactionProduct( std::move( multiplicity ),
                                     std::move( distribution ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of a ReactionProduct with an invalid LAW" ) {

    std::string string = invalidLAW();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( ReactionProduct( begin, end, lineNumber, 100, 26, 525 ) );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLAW1() {

  return
    " 1.000000+3 9.992414-1          0          1          1          2 10026525     \n"
    "          2          4                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n"
    " 0.000000+0 0.000000+0          1          2          1          2 10026525     \n"
    "          2          1                                             10026525     \n"
    " 0.000000+0 1.000000+1          0          0          4          2 10026525     \n"
    " 1.000000-1 2.139400+0 1.000000+1 2.122450-2                       10026525     \n"
    " 0.000000+0 1.00000+11          0          0          4          2 10026525     \n"
    " 1.000000-1 1.848230+0 1.00000+11 8.766410-3                       10026525     \n";
}

void verifyChunkWithLAW1( const ReactionProduct& chunk ) {

  CHECK( 1000. == Approx( chunk.ZAP() ) );
  CHECK( 0.9992414 == Approx( chunk.AWI() ) );
  CHECK( 1 == chunk.LAW() );

  CHECK( 1000. == Approx( chunk.multiplicity().ZAP() ) );
  CHECK( 0.9992414 == Approx( chunk.multiplicity().AWI() ) );
  CHECK( 1 == chunk.multiplicity().LAW() );

  CHECK( 2 == chunk.multiplicity().NP() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 4 == chunk.multiplicity().interpolants()[0] );
  CHECK( 2 == chunk.multiplicity().boundaries()[0] );
  CHECK( 2 == chunk.multiplicity().energies().size() );
  CHECK( 2 == chunk.multiplicity().multiplicities().size() );
  CHECK( 10. == Approx( chunk.multiplicity().energies()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.multiplicity().energies()[1] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[0] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[1] ) );

  auto law = std::get< ContinuumEnergyAngle >( chunk.distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.NE() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 1 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  auto energies = law.distributions();

  CHECK( 10. == Approx( energies[0].incidentEnergy() ) );
  CHECK( 0 == energies[0].ND() );
  CHECK( 0 == energies[0].NA() );
  CHECK( 4 == energies[0].NW() );
  CHECK( 2 == energies[0].NEP() );
  CHECK( 2 == energies[0].energies().size() );
  CHECK( .1 == Approx( energies[0].energies()[0] ) );
  CHECK( 10. == Approx( energies[0].energies()[1] ) );
  CHECK( 2 == energies[0].coefficients().size() );
  CHECK( 2.1394 == Approx( energies[0].coefficients()[0][0] ) );
  CHECK( 2.122450e-2 == Approx( energies[0].coefficients()[1][0] ) );
  CHECK( 2 == energies[0].totalEmissionProbabilities().size() );
  CHECK( 2.1394 == Approx( energies[0].totalEmissionProbabilities()[0] ) );
  CHECK( 2.12245e-2 == Approx( energies[0].totalEmissionProbabilities()[1] ) );

  CHECK( 1e+11 == Approx( energies[1].incidentEnergy() ) );
  CHECK( 1 == energies[1].LANG() );
  CHECK( 0 == energies[1].ND() );
  CHECK( 0 == energies[1].NA() );
  CHECK( 4 == energies[1].NW() );
  CHECK( 2 == energies[1].NEP() );
  CHECK( 2 == energies[1].energies().size() );
  CHECK( .1 == Approx( energies[1].energies()[0] ) );
  CHECK( 1e+11 == Approx( energies[1].energies()[1] ) );
  CHECK( 2 == energies[1].coefficients().size() );
  CHECK( 1.84823 == Approx( energies[1].coefficients()[0][0] ) );
  CHECK( 8.76641e-3 == Approx( energies[1].coefficients()[1][0] ) );
  CHECK( 2 == energies[1].totalEmissionProbabilities().size() );
  CHECK( 1.84823 == Approx( energies[1].totalEmissionProbabilities()[0] ) );
  CHECK( 8.76641e-3 == Approx( energies[1].totalEmissionProbabilities()[1] ) );

  CHECK( 9 == chunk.NC() );
}

std::string chunkWithLAW2() {

  return
    " 1.000000+3 9.992414-1          0          2          1          2 10026525     \n"
    "          2          4                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n"
    " 0.000000+0 0.000000+0          0          0          1          2 10026525     \n"
    "          2          1                                             10026525     \n"
    " 0.000000+0 1.000000+1         12          0          4          2 10026525     \n"
    "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                       10026525     \n"
    " 0.000000+0 1.00000+11         12          0          4          2 10026525     \n"
    "-1.000000+0 7.500000-1 1.000000+0 2.500000-1                       10026525     \n";
}

void verifyChunkWithLAW2( const ReactionProduct& chunk ) {

  CHECK( 1000. == Approx( chunk.ZAP() ) );
  CHECK( 0.9992414 == Approx( chunk.AWI() ) );
  CHECK( 2 == chunk.LAW() );

  CHECK( 1000. == Approx( chunk.multiplicity().ZAP() ) );
  CHECK( 0.9992414 == Approx( chunk.multiplicity().AWI() ) );
  CHECK( 2 == chunk.multiplicity().LAW() );

  CHECK( 2 == chunk.multiplicity().NP() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 4 == chunk.multiplicity().interpolants()[0] );
  CHECK( 2 == chunk.multiplicity().boundaries()[0] );
  CHECK( 2 == chunk.multiplicity().energies().size() );
  CHECK( 2 == chunk.multiplicity().multiplicities().size() );
  CHECK( 10. == Approx( chunk.multiplicity().energies()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.multiplicity().energies()[1] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[0] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[1] ) );

  auto law = std::get< DiscreteTwoBodyScattering >( chunk.distribution() );

  CHECK( 2 == law.LAW() );
  CHECK( 2 == law.NE() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 1 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  auto energies = law.distributions();

  CHECK( 10. == Approx( energies[0].E() ) );
  CHECK( 10. == Approx( energies[0].incidentEnergy() ) );

  CHECK( 12 == energies[0].LANG() );
  CHECK( 4 == energies[0].NW() );
  CHECK( 2 == energies[0].NL() );
  CHECK( 2 == energies[0].numberCosineValues() );
  CHECK( 2 == energies[0].MU().size() );
  CHECK( 2 == energies[0].cosines().size() );
  CHECK( -1. == Approx( energies[0].MU()[0] ) );
  CHECK( 1. == Approx( energies[0].MU()[1] ) );
  CHECK( -1. == Approx( energies[0].cosines()[0] ) );
  CHECK( 1. == Approx( energies[0].cosines()[1] ) );
  CHECK( 2 == energies[0].F().size() );
  CHECK( 2 == energies[0].probabilities().size() );
  CHECK( .5 == Approx( energies[0].F()[0] ) );
  CHECK( .5 == Approx( energies[0].F()[1] ) );
  CHECK( .5 == Approx( energies[0].probabilities()[0] ) );
  CHECK( .5 == Approx( energies[0].probabilities()[1] ) );

  CHECK( 1e+11 == Approx( energies[1].E() ) );
  CHECK( 1e+11 == Approx( energies[1].incidentEnergy() ) );

  CHECK( 12 == energies[1].LANG() );
  CHECK( 4 == energies[1].NW() );
  CHECK( 2 == energies[1].NL() );
  CHECK( 2 == energies[1].numberCosineValues() );
  CHECK( 2 == energies[1].MU().size() );
  CHECK( 2 == energies[1].cosines().size() );
  CHECK( -1. == Approx( energies[1].MU()[0] ) );
  CHECK( 1. == Approx( energies[1].MU()[1] ) );
  CHECK( -1. == Approx( energies[1].cosines()[0] ) );
  CHECK( 1. == Approx( energies[1].cosines()[1] ) );
  CHECK( 2 == energies[1].F().size() );
  CHECK( 2 == energies[1].probabilities().size() );
  CHECK( .75 == Approx( energies[1].F()[0] ) );
  CHECK( .25 == Approx( energies[1].F()[1] ) );
  CHECK( .75 == Approx( energies[1].probabilities()[0] ) );
  CHECK( .25 == Approx( energies[1].probabilities()[1] ) );

  CHECK( 9 == chunk.NC() );
}

std::string chunkWithLAW8() {

  return
    " 1.100000+1 5.438673-4          0          8          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n"
    " 0.000000+0 0.000000+0          0          0          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n";
}

void verifyChunkWithLAW8( const ReactionProduct& chunk ) {

  CHECK( 11. == Approx( chunk.ZAP() ) );
  CHECK( 5.438673e-4 == Approx( chunk.AWI() ) );
  CHECK( 8 == chunk.LAW() );

  CHECK( 11. == Approx( chunk.multiplicity().ZAP() ) );
  CHECK( 5.438673e-4 == Approx( chunk.multiplicity().AWI() ) );

  CHECK( 8 == chunk.multiplicity().LAW() );
  CHECK( 2 == chunk.multiplicity().NP() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 2 == chunk.multiplicity().boundaries()[0] );
  CHECK( 2 == chunk.multiplicity().E().size() );
  CHECK( 2 == chunk.multiplicity().energies().size() );
  CHECK( 2 == chunk.multiplicity().Y().size() );
  CHECK( 2 == chunk.multiplicity().multiplicities().size() );
  CHECK( 10. == Approx( chunk.multiplicity().E()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.multiplicity().E()[1] ) );
  CHECK( 10. == Approx( chunk.multiplicity().energies()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.multiplicity().energies()[1] ) );
  CHECK( 1. == Approx( chunk.multiplicity().Y()[0] ) );
  CHECK( 1. == Approx( chunk.multiplicity().Y()[1] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[0] ) );
  CHECK( 1. == Approx( chunk.multiplicity().multiplicities()[1] ) );

  auto law = std::get< EnergyTransfer >( chunk.distribution() );

  CHECK( 8 == law.LAW() );

  CHECK( 2 == law.NP() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 2 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );
  CHECK( 2 == law.E().size() );
  CHECK( 2 == law.energies().size() );
  CHECK( 2 == law.ET().size() );
  CHECK( 2 == law.energyTransferValues().size() );
  CHECK( 10. == Approx( law.E()[0] ) );
  CHECK( 1.e+11 == Approx( law.E()[1] ) );
  CHECK( 10. == Approx( law.energies()[0] ) );
  CHECK( 1.e+11 == Approx( law.energies()[1] ) );
  CHECK( 1.e-5 == Approx( law.ET()[0] ) );
  CHECK( 2e+4 == Approx( law.ET()[1] ) );
  CHECK( 1.e-5 == Approx( law.energyTransferValues()[0] ) );
  CHECK( 2e+4 == Approx( law.energyTransferValues()[1] ) );

  CHECK( 6 == chunk.NC() );
}

std::string invalidLAW() {
  return
    " 1.100000+1 5.438673-4          0          3          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n"
    " 0.000000+0 0.000000+0          0          0          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n";
}
