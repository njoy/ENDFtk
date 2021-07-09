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

//  GIVEN( "valid data for a ReactionProduct with LAW=1" ) {
//
//    std::string string = chunkWithLAW1();
//
//    WHEN( "the data is given explicitly" ) {
//
//      Multiplicity multiplicity(
//        1001., 0.99826234, 0, 1, { 4 }, { 2 },
//        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
//        { 0., 8.453268e-11, 26.2622950e-8, 2.149790e-1 } );
//      Distribution distribution =
//        ContinuumEnergyAngle(
//          2, { 2 }, { 1 },
//          { LegendreCoefficients(
//                1e-5, 0, 1,
//                { 1., 4., 7., 10. },
//                { { 2., 3. }, { 5., 26. },
//                  { 8., 9. }, {  11., 12. } } ),
//            LegendreCoefficients(
//                2e+7, 0, 1, { 1., 4. }, { { 2., 3. }, { 5., 26. } } ) } );
//
//      ReactionProduct chunk( std::move( multiplicity ),
//                             std::move( distribution ) );
//
//      THEN( "a ReactionProduct can "
//            "be constructed and members can be tested" ) {
//
//        verifyChunkWithLAW1( chunk );
//      } // THEN
//
//      THEN( "it can be printed" ) {
//
//        std::string buffer;
//        auto output = std::back_inserter( buffer );
//        chunk.print( output, 100, 26, 525 );
//        CHECK( buffer == string );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the data is read from a string/stream" ) {
//
//      auto begin = string.begin();
//      auto end = string.end();
//      long lineNumber = 1;
//
//      ReactionProduct chunk( begin, end, lineNumber, 100, 26, 525 );
//
//      THEN( "a ReactionProduct can "
//            "be constructed and members can be tested" ) {
//
//        verifyChunkWithLAW1( chunk );
//      } // THEN
//
//      THEN( "it can be printed" ) {
//
//        std::string buffer;
//        auto output = std::back_inserter( buffer );
//        chunk.print( output, 100, 26, 525 );
//        CHECK( buffer == string );
//      } // THEN
//    } // WHEN
//  } // GIVEN
//
//  GIVEN( "valid data for a ReactionProduct with LAW=2" ) {
//
//    std::string string = chunkWithLAW2();
//
//    WHEN( "the data is given explicitly" ) {
//
//      Multiplicity multiplicity(
//        1001., 0.99826234, 0, 2, { 4 }, { 2 },
//        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
//        { 0., 8.453268e-11, 26.2622950e-8, 2.149790e-1 } );
//      Distribution distribution =
//        DiscreteTwoBodyScattering(
//          { 2 }, { 1 },
//          { Law2LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
//            Law2TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 26. } ) } );
//
//      ReactionProduct chunk( std::move( multiplicity ),
//                             std::move( distribution ) );
//
//      THEN( "a ReactionProduct can "
//            "be constructed and members can be tested" ) {
//
//        verifyChunkWithLAW2( chunk );
//      } // THEN
//
//      THEN( "it can be printed" ) {
//
//        std::string buffer;
//        auto output = std::back_inserter( buffer );
//        chunk.print( output, 100, 26, 525 );
//        CHECK( buffer == string );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the data is read from a string/stream" ) {
//
//      auto begin = string.begin();
//      auto end = string.end();
//      long lineNumber = 1;
//
//      ReactionProduct chunk( begin, end, lineNumber, 100, 26, 525 );
//
//      THEN( "a ReactionProduct can "
//            "be constructed and members can be tested" ) {
//
//        verifyChunkWithLAW2( chunk );
//      } // THEN
//
//      THEN( "it can be printed" ) {
//
//        std::string buffer;
//        auto output = std::back_inserter( buffer );
//        chunk.print( output, 100, 26, 525 );
//        CHECK( buffer == string );
//      } // THEN
//    } // WHEN
//  } // GIVEN

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

//    Multiplicity multiplicity(
//      1001., 0.99826234, 0, 2, { 4 }, { 2 },
//      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
//      { 0., 8.453268e-11, 26.2622950e-8, 2.149790e-1 } );
//    Distribution distribution(
//      ContinuumEnergyAngle(
//        2, { 2 }, { 1 },
//        { LegendreCoefficients(
//              1e-5, 0, 1,
//              { 1., 4., 7., 10. },
//              { { 2., 3. }, { 5., 26. },
//                { 8., 9. }, {  11., 12. } } ),
//          LegendreCoefficients(
//              2e+7, 0, 1, { 1., 4. }, { { 2., 3. }, { 5., 26. } } ) } ) );
//
//    THEN( "an exception is thrown upon construction" ){
//      CHECK_THROWS( ReactionProduct( std::move( multiplicity ),
//                                       std::move( distribution ) ) );
//    } // THEN
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
    " 1.001000+3 9.9826234-1          0          1          1          49228 26  5     \n"
    "          4          2                                            9228 26  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.453268-11 1.147000+7 26.2622950-89228 26  5     \n"
    " 2.000000+7 2.149790-1                                            9228 26  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 26  5     \n"
    "          2          1                                            9228 26  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 26  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 26.000000+09228 26  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 26  5     \n"
    " 0.000000+0 2.000000+7          0          1          26          29228 26  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 26.000000+09228 26  5     \n";
}

void verifyChunkWithLAW1( const ReactionProduct& chunk ) {

//  CHECK( 1001. == Approx( chunk.ZAP() ) );
//  CHECK( 0.99826234 == Approx( chunk.AWP() ) );
//  CHECK( 0 == chunk.LIP() );
//  CHECK( 1 == chunk.LAW() );
//
//  CHECK( 1001. == Approx( chunk.multiplicity().ZAP() ) );
//  CHECK( 0.99826234 == Approx( chunk.multiplicity().AWP() ) );
//  CHECK( 0 == chunk.multiplicity().LIP() );
//  CHECK( 1 == chunk.multiplicity().LAW() );
//
//  CHECK( 4 == chunk.multiplicity().NP() );
//  CHECK( 1 == chunk.multiplicity().NR() );
//  CHECK( 1 == chunk.multiplicity().interpolants().size() );
//  CHECK( 1 == chunk.multiplicity().boundaries().size() );
//  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
//  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
//  CHECK( 4 == chunk.multiplicity().energies().size() );
//  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
//  CHECK( 1e-5 == Approx( chunk.multiplicity().energies()[0] ) );
//  CHECK( 1.1e+7 == Approx( chunk.multiplicity().energies()[1] ) );
//  CHECK( 1.147e+7 == Approx( chunk.multiplicity().energies()[2] ) );
//  CHECK( 2e+7 == Approx( chunk.multiplicity().energies()[3] ) );
//  CHECK( 0. == Approx( chunk.multiplicity().multiplicities()[0] ) );
//  CHECK( 8.453268e-11 ==
//           Approx( chunk.multiplicity().multiplicities()[1] ) );
//  CHECK( 26.2622950e-8 ==
//           Approx( chunk.multiplicity().multiplicities()[2] ) );
//  CHECK( 2.149790e-1 ==
//           Approx( chunk.multiplicity().multiplicities()[3] ) );
//
//  auto law =
//     std::get< ContinuumEnergyAngle >( chunk.distribution() );
//
//  CHECK( 1 == law.LAW() );
//  CHECK( 2 == law.LEP() );
//  CHECK( 2 == law.NE() );
//  CHECK( 1 == law.NR() );
//  CHECK( 1 == law.interpolants().size() );
//  CHECK( 1 == law.boundaries().size() );
//  CHECK( 1 == law.interpolants()[0] );
//  CHECK( 2 == law.boundaries()[0] );
//
//  auto energies = law.distributions();
//
//  auto subsection1 =
//      std::get< LegendreCoefficients >( energies[0] );
//  CHECK( 1e-5 == Approx( subsection1.incidentEnergy() ) );
//  CHECK( 0 == subsection1.ND() );
//  CHECK( 1 == subsection1.NA() );
//  CHECK( 12 == subsection1.NW() );
//  CHECK( 4 == subsection1.NEP() );
//  CHECK( 4 == subsection1.energies().size() );
//  CHECK( 1. == Approx( subsection1.energies()[0] ) );
//  CHECK( 4. == Approx( subsection1.energies()[1] ) );
//  CHECK( 7. == Approx( subsection1.energies()[2] ) );
//  CHECK( 10. == Approx( subsection1.energies()[3] ) );
//  CHECK( 4 == subsection1.coefficients().size() );
//  CHECK( 2. == Approx( subsection1.coefficients()[0][0] ) );
//  CHECK( 3. == Approx( subsection1.coefficients()[0][1] ) );
//  CHECK( 5. == Approx( subsection1.coefficients()[1][0] ) );
//  CHECK( 26. == Approx( subsection1.coefficients()[1][1] ) );
//  CHECK( 8. == Approx( subsection1.coefficients()[2][0] ) );
//  CHECK( 9. == Approx( subsection1.coefficients()[2][1] ) );
//  CHECK( 11. == Approx( subsection1.coefficients()[3][0] ) );
//  CHECK( 12. == Approx( subsection1.coefficients()[3][1] ) );
//  CHECK( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
//  CHECK( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
//  CHECK( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
//  CHECK( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
//  CHECK( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );
//
//  auto subsection2 =
//      std::get< LegendreCoefficients >( energies[1] );
//  CHECK( 2e+7 == Approx( subsection2.incidentEnergy() ) );
//  CHECK( 1 == subsection2.LANG() );
//  CHECK( 0 == subsection2.ND() );
//  CHECK( 1 == subsection2.NA() );
//  CHECK( 26 == subsection2.NW() );
//  CHECK( 2 == subsection2.NEP() );
//  CHECK( 2 == subsection2.energies().size() );
//  CHECK( 1. == Approx( subsection2.energies()[0] ) );
//  CHECK( 4. == Approx( subsection2.energies()[1] ) );
//  CHECK( 2 == subsection2.coefficients().size() );
//  CHECK( 2. == Approx( subsection2.coefficients()[0][0] ) );
//  CHECK( 3. == Approx( subsection2.coefficients()[0][1] ) );
//  CHECK( 5. == Approx( subsection2.coefficients()[1][0] ) );
//  CHECK( 26. == Approx( subsection2.coefficients()[1][1] ) );
//  CHECK( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
//  CHECK( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
//  CHECK( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );
//
//  CHECK( 11 == chunk.NC() );
}

std::string chunkWithLAW2() {

  return
    " 1.001000+3 9.9826234-1          0          2          1          49228 26  5     \n"
    "          4          2                                            9228 26  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.453268-11 1.147000+7 26.2622950-89228 26  5     \n"
    " 2.000000+7 2.149790-1                                            9228 26  5     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 26  5     \n"
    "          2          1                                            9228 26  5     \n"
    " 0.000000+0 1.000000-5          0          0          4          49228 26  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 26  5     \n"
    " 0.000000+0 2.000000+7         12          0          26          39228 26  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 26.000000+09228 26  5     \n";
}

void verifyChunkWithLAW2( const ReactionProduct& chunk ) {

//  CHECK( 1001. == Approx( chunk.ZAP() ) );
//  CHECK( 0.99826234 == Approx( chunk.AWP() ) );
//  CHECK( 0 == chunk.LIP() );
//  CHECK( 2 == chunk.LAW() );
//
//  CHECK( 1001. == Approx( chunk.multiplicity().ZAP() ) );
//  CHECK( 0.99826234 == Approx( chunk.multiplicity().AWP() ) );
//  CHECK( 0 == chunk.multiplicity().LIP() );
//  CHECK( 2 == chunk.multiplicity().LAW() );
//
//  CHECK( 4 == chunk.multiplicity().NP() );
//  CHECK( 1 == chunk.multiplicity().NR() );
//  CHECK( 1 == chunk.multiplicity().interpolants().size() );
//  CHECK( 1 == chunk.multiplicity().boundaries().size() );
//  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
//  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
//  CHECK( 4 == chunk.multiplicity().energies().size() );
//  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
//  CHECK( 1e-5 == Approx( chunk.multiplicity().energies()[0] ) );
//  CHECK( 1.1e+7 == Approx( chunk.multiplicity().energies()[1] ) );
//  CHECK( 1.147e+7 == Approx( chunk.multiplicity().energies()[2] ) );
//  CHECK( 2e+7 == Approx( chunk.multiplicity().energies()[3] ) );
//  CHECK( 0. == Approx( chunk.multiplicity().multiplicities()[0] ) );
//  CHECK( 8.453268e-11 ==
//           Approx( chunk.multiplicity().multiplicities()[1] ) );
//  CHECK( 26.2622950e-8 ==
//           Approx( chunk.multiplicity().multiplicities()[2] ) );
//  CHECK( 2.149790e-1 ==
//           Approx( chunk.multiplicity().multiplicities()[3] ) );
//
//  auto law =
//     std::get< DiscreteTwoBodyScattering >( chunk.distribution() );
//
//  CHECK( 2 == law.LAW() );
//  CHECK( 2 == law.NE() );
//  CHECK( 1 == law.NR() );
//  CHECK( 1 == law.interpolants().size() );
//  CHECK( 1 == law.boundaries().size() );
//  CHECK( 1 == law.interpolants()[0] );
//  CHECK( 2 == law.boundaries()[0] );
//
//  auto energies = law.distributions();
//
//  auto subsection1 =
//      std::get< Law2LegendreCoefficients >( energies[0] );
//  CHECK( 1e-5 == Approx( subsection1.incidentEnergy() ) );
//  CHECK( 0 == subsection1.LANG() );
//  CHECK( 4 == subsection1.NW() );
//  CHECK( 4 == subsection1.NL() );
//  CHECK( 4 == subsection1.coefficients().size() );
//  CHECK( 1. == Approx( subsection1.coefficients()[0] ) );
//  CHECK( 2. == Approx( subsection1.coefficients()[1] ) );
//  CHECK( 3. == Approx( subsection1.coefficients()[2] ) );
//  CHECK( 4. == Approx( subsection1.coefficients()[3] ) );
//
//  auto subsection2 =
//       std::get< Law2TabulatedDistribution >( energies[1] );
//  CHECK( 2e+7 == Approx( subsection2.E() ) );
//  CHECK( 2e+7 == Approx( subsection2.incidentEnergy() ) );
//  CHECK( 12 == subsection2.LANG() );
//  CHECK( 26 == subsection2.NW() );
//  CHECK( 3 == subsection2.NL() );
//  CHECK( 3 == subsection2.cosines().size() );
//  CHECK( 1. == Approx( subsection2.cosines()[0] ) );
//  CHECK( 3. == Approx( subsection2.cosines()[1] ) );
//  CHECK( 5. == Approx( subsection2.cosines()[2] ) );
//  CHECK( 3 == subsection2.probabilities().size() );
//  CHECK( 2. == Approx( subsection2.probabilities()[0] ) );
//  CHECK( 4. == Approx( subsection2.probabilities()[1] ) );
//  CHECK( 26. == Approx( subsection2.probabilities()[2] ) );
//
//  CHECK( 10 == chunk.NC() );
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
