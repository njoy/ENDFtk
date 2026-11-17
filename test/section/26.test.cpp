// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/26.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

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

std::string chunk();
void verifyChunk( const section::Type< 26 >& );
std::string invalidLAW();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 26 >" ) {

  GIVEN( "valid data for a section::Type< 26 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 1000;
      double awr = .9992414;
      int mt = 525;
      std::vector< ReactionProduct > products = {
        ReactionProduct(

          // multiplicity
          { 1000, .9992414, 1, { 2 }, { 4 },
            { 10., 1e+11 },
            { 1., 1. } },
          // distribution
          { ContinuumEnergyAngle(
            2, { 2 }, { 1 },
            { LegendreCoefficients(
                  10., 0, 0,
                  { .1, 10. },
                  { { 2.1394 }, {  .0212245 } } ),
              LegendreCoefficients(
                  1e+11, 0, 0, { .1, 1e+11 }, { { 1.84823 }, { .00876641 } } ) } ) } ) };

      section::Type< 26 > chunk( mt, zaid, awr, std::move( products ) );

      THEN( "a section::Type< 26 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 26 > chunk( head, begin, end, lineNumber, 100 );

      THEN( "a section::Type< 26 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 100, 26, 525, std::string( sectionString ) );

      section::Type< 26 > chunk = section.parse< 26 >();

      THEN( "a section::Type< 26 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation for a section::Type< 26 > with an "
         "invalid LAW" ) {

    std::string sectionString = invalidLAW() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 26 >( head, begin, end, lineNumber, 100 ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation with an invalid SEND" ) {

    std::string sectionString = chunk() + invalidSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 26 >( head, begin, end, lineNumber, 100 ) );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+3 9.992414-1          0          0          1          0 10026525     \n"
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

void verifyChunk( const section::Type< 26 >& chunk ) {

  CHECK( 525 == chunk.MT() );
  CHECK( 525 == chunk.sectionNumber() );

  CHECK( 1000 == chunk.ZA() );
  CHECK( 1000 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9992414, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9992414, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberReactionProducts() );
  CHECK( 525 == chunk.MT() );

  CHECK( true == chunk.hasReactionProduct( 1000 ) );
  CHECK( false == chunk.hasReactionProduct( 11 ) );

  auto products = chunk.reactionProducts();
  CHECK( 1 == products.size() );

  CHECK( 1000 == products[0].ZAP() );
  CHECK_THAT( 0.9992414, WithinRel( products[0].AWI() ) );
  CHECK( 1 == products[0].LAW() );

  CHECK( 1000 == products[0].multiplicity().ZAP() );
  CHECK_THAT( 0.9992414, WithinRel( products[0].multiplicity().AWI() ) );
  CHECK( 1 == products[0].multiplicity().LAW() );

  CHECK( 2 == products[0].multiplicity().NP() );
  CHECK( 2 == products[0].multiplicity().numberPoints() );
  CHECK( 1 == products[0].multiplicity().NR() );
  CHECK( 1 == products[0].multiplicity().numberInterpolationRegions() );
  CHECK( 1 == products[0].multiplicity().INT().size() );
  CHECK( 1 == products[0].multiplicity().NBT().size() );
  CHECK( 4 == products[0].multiplicity().INT()[0] );
  CHECK( 2 == products[0].multiplicity().NBT()[0] );
  CHECK( 1 == products[0].multiplicity().interpolants().size() );
  CHECK( 1 == products[0].multiplicity().boundaries().size() );
  CHECK( 4 == products[0].multiplicity().interpolants()[0] );
  CHECK( 2 == products[0].multiplicity().boundaries()[0] );
  CHECK( 2 == products[0].multiplicity().energies().size() );
  CHECK( 2 == products[0].multiplicity().multiplicities().size() );
  CHECK_THAT( 10., WithinRel( products[0].multiplicity().energies()[0] ) );
  CHECK_THAT( 1.e+11, WithinRel( products[0].multiplicity().energies()[1] ) );
  CHECK_THAT( 1., WithinRel( products[0].multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 1., WithinRel( products[0].multiplicity().multiplicities()[1] ) );

  auto law = std::get< ContinuumEnergyAngle >( products[0].distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.NE() );
  CHECK( 2 == law.numberIncidentEnergies() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.numberInterpolationRegions() );
  CHECK( 1 == law.INT().size() );
  CHECK( 1 == law.NBT().size() );
  CHECK( 1 == law.INT()[0] );
  CHECK( 2 == law.NBT()[0] );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 1 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  auto energies = law.distributions();

  CHECK_THAT( 10., WithinRel( energies[0].incidentEnergy() ) );
  CHECK( 0 == energies[0].ND() );
  CHECK( 0 == energies[0].NA() );
  CHECK( 4 == energies[0].NW() );
  CHECK( 2 == energies[0].NEP() );
  CHECK( 2 == energies[0].energies().size() );
  CHECK_THAT( .1, WithinRel( energies[0].energies()[0] ) );
  CHECK_THAT( 10., WithinRel( energies[0].energies()[1] ) );
  CHECK( 2 == energies[0].coefficients().size() );
  CHECK_THAT( 2.1394, WithinRel( energies[0].coefficients()[0][0] ) );
  CHECK_THAT( 2.122450e-2, WithinRel( energies[0].coefficients()[1][0] ) );
  CHECK( 2 == energies[0].totalEmissionProbabilities().size() );
  CHECK_THAT( 2.1394, WithinRel( energies[0].totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 2.12245e-2, WithinRel( energies[0].totalEmissionProbabilities()[1] ) );

  CHECK_THAT( 1e+11, WithinRel( energies[1].incidentEnergy() ) );
  CHECK( 1 == energies[1].LANG() );
  CHECK( 0 == energies[1].ND() );
  CHECK( 0 == energies[1].NA() );
  CHECK( 4 == energies[1].NW() );
  CHECK( 2 == energies[1].NEP() );
  CHECK( 2 == energies[1].energies().size() );
  CHECK_THAT( .1, WithinRel( energies[1].energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( energies[1].energies()[1] ) );
  CHECK( 2 == energies[1].coefficients().size() );
  CHECK_THAT( 1.84823, WithinRel( energies[1].coefficients()[0][0] ) );
  CHECK_THAT( 8.76641e-3, WithinRel( energies[1].coefficients()[1][0] ) );
  CHECK( 2 == energies[1].totalEmissionProbabilities().size() );
  CHECK_THAT( 1.84823, WithinRel( energies[1].totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 8.76641e-3, WithinRel( energies[1].totalEmissionProbabilities()[1] ) );

  auto product = chunk.reactionProduct( 1000 );
  CHECK( 1000 == product.ZAP() );
  CHECK( 1000 == product.productIdentifier() );

  CHECK( 10 == chunk.NC() );
}

std::string invalidLAW() {
  return
    " 1.000000+3 9.992414-1          0          0          1          0 10026525     \n"
    " 1.000000+3 9.992414-1          0          3          1          2 10026525     \n"
    "          2          4                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n"
    " 0.000000+0 0.000000+0          1          2          1          2 10026525     \n"
    "          2          1                                             10026525     \n"
    " 0.000000+0 1.000000+1          0          0          4          2 10026525     \n"
    " 1.000000-1 2.139400+0 1.000000+1 2.122450-2                       10026525     \n"
    " 0.000000+0 1.00000+11          0          0          4          2 10026525     \n"
    " 1.000000-1 1.848230+0 1.00000+11 8.766410-3                       10026525     \n";
}

std::string validSEND() {
  return
    "                                                                   10026  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                   10026  1     \n";
}
