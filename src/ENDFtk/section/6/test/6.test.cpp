#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes
#include "ENDFtk/tree/Tape.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct =
section::Type< 6 >::ReactionProduct;
using Multiplicity =
section::Type< 6 >::Multiplicity;
using Distribution =
section::Type< 6 >::Distribution;
using ContinuumEnergyAngle =
section::Type< 6 >::ContinuumEnergyAngle;
using LegendreCoefficients =
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;

std::string chunk();
void verifyChunk( const section::Type< 6 >& );
std::string invalidLAW();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 6 >" ) {

  GIVEN( "valid data for a section::Type< 6 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 2.330248e+2;
      int jp = 0;
      int lct = 2;
      int mt = 5;
      std::vector< ReactionProduct > products = {
        ReactionProduct(
          // multiplicity
          { 1001., 0.9986234, 0, 1, { 4 }, { 2 },
            { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
            { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } },
          // distribution
          { ContinuumEnergyAngle(
              2, { 2 }, { 1 },
              { LegendreCoefficients(
                    1e-5, 0, 1,
                    { 1., 4., 7., 10. },
                    { { 2., 3. }, { 5., 6. },
                      { 8., 9. }, {  11., 12. } } ),
                LegendreCoefficients(
                    2e+7, 0, 1, { 1., 4. }, { { 2., 3. }, { 5., 6. } } ) } ) } ),
        ReactionProduct(
          // multiplicity
          { 1., 1., 0, 1, { 2 }, { 2 },
            { 1.858639e+7, 2.e+7 },
            { 4., 4. } },
          // distribution
          { ContinuumEnergyAngle(
              2, { 2 }, { 22 },
              { LegendreCoefficients(
                    1.858639e+7, 0, 0, { 0., 0.5, 1. }, { { 0. }, { 2. }, { 0. } } ),
                LegendreCoefficients(
                    2e+7, 0, 0, { 0., 0.5, 1. }, { { 0. }, { 2. }, { 0. } } ) } ) } ),
        ReactionProduct(
          // multiplicity
          { 0., 0., 0, 1, { 3 }, { 2 },
            { 1.858639e+7, 1.9e+7, 2.e+7 },
            { 1., 2., 3. } },
          // distribution
          { ContinuumEnergyAngle(
            2, { 2 }, { 5 },
            { LegendreCoefficients(
                   1.858639e+7, 0, 0, { 0., 1., 2. }, { { 0. }, { 1. }, { 0. } } ),
              LegendreCoefficients(
                   2e+7, 0, 0, { 0., 1., 2. }, { { 0. }, { 1. }, { 0. } } ) } ) } ) };

      section::Type< 6 > chunk( mt, zaid, awr, jp, lct, std::move( products ) );

      THEN( "a section::Type< 6 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 6 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 6 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 6 > chunk = section.parse< 6 >( lineNumber );

      THEN( "a section::Type< 6 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6 );
        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation for a section::Type< 6 > with an "
         "invalid LAW" ) {

    std::string sectionString = invalidLAW() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 6 >( head, begin, end, lineNumber, 9228 ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation with an invalid SEND" ) {

    std::string sectionString = chunk() + invalidSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 6 >( head, begin, end, lineNumber, 9228 ) );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 9.223500+4 2.330248+2          0          2          3          09228 6  5     \n"
    " 1.001000+3 9.986234-1          0          1          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 1.000000+0 1.000000+0          0          1          1          29228 6  5     \n"
    "          2          2                                            9228 6  5     \n"
    " 1.858639+7 4.000000+0 2.000000+7 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2         22                                            9228 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 0.000000+0          0          1          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.858639+7 1.000000+0 1.900000+7 2.000000+0 2.000000+7 3.000000+09228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          5                                            9228 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n";
}

void verifyChunk( const section::Type< 6 >& chunk ) {

  CHECK( 92235. == Approx( chunk.ZA() ) );
  CHECK( 2.330248e+2 == Approx( chunk.AWR() ) );
  CHECK( 0 == chunk.JP() );
  CHECK( 0 == chunk.averageMultipleParticlesFlag() );
  CHECK( 2 == chunk.LCT() );
  CHECK( 2 == chunk.referenceFrame() );
  CHECK( 3 == chunk.NK() );
  CHECK( 3 == chunk.numberReactionProducts() );
  CHECK( 5 == chunk.MT() );

  auto products = chunk.reactionProducts();
  CHECK( 3 == products.size() );

  // product 1
  CHECK( 1001. == Approx( products[0].ZAP() ) );
  CHECK( 1001. == Approx( products[0].productIdentifier() ) );
  CHECK( 0.9986234 == Approx( products[0].AWP() ) );
  CHECK( 0.9986234 == Approx( products[0].productWeightRatio() ) );
  CHECK( 0 == products[0].LIP() );
  CHECK( 0 == products[0].productModifierFlag() );
  CHECK( 1 == products[0].LAW() );

  CHECK( 1001. == Approx( products[0].multiplicity().ZAP() ) );
  CHECK( 1001. == Approx( products[0].multiplicity().productIdentifier() ) );
  CHECK( 0.9986234 == Approx( products[0].multiplicity().AWP() ) );
  CHECK( 0.9986234 == Approx( products[0].multiplicity().productWeightRatio() ) );
  CHECK( 0 == products[0].multiplicity().LIP() );
  CHECK( 0 == products[0].multiplicity().productModifierFlag() );
  CHECK( 1 == products[0].multiplicity().LAW() );

  CHECK( 4 == products[0].multiplicity().NP() );
  CHECK( 1 == products[0].multiplicity().NR() );
  CHECK( 1 == products[0].multiplicity().interpolants().size() );
  CHECK( 1 == products[0].multiplicity().boundaries().size() );
  CHECK( 2 == products[0].multiplicity().interpolants()[0] );
  CHECK( 4 == products[0].multiplicity().boundaries()[0] );
  CHECK( 4 == products[0].multiplicity().energies().size() );
  CHECK( 4 == products[0].multiplicity().multiplicities().size() );
  CHECK( 1e-5 == Approx( products[0].multiplicity().energies()[0] ) );
  CHECK( 1.1e+7 == Approx( products[0].multiplicity().energies()[1] ) );
  CHECK( 1.147e+7 == Approx( products[0].multiplicity().energies()[2] ) );
  CHECK( 2e+7 == Approx( products[0].multiplicity().energies()[3] ) );
  CHECK( 0. == Approx( products[0].multiplicity().multiplicities()[0] ) );
  CHECK( 8.45368e-11 ==
           Approx( products[0].multiplicity().multiplicities()[1] ) );
  CHECK( 6.622950e-8 ==
           Approx( products[0].multiplicity().multiplicities()[2] ) );
  CHECK( 2.149790e-1 ==
           Approx( products[0].multiplicity().multiplicities()[3] ) );

  auto law = std::get< ContinuumEnergyAngle >(
                 products[0].distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.LEP() );
  CHECK( 2 == law.NE() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 1 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  auto energies = law.distributions();

  auto subsection1 =
      std::get< LegendreCoefficients >( energies[0] );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 1 == subsection1.NA() );
  CHECK( 1 == subsection1.numberAngularParameters() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 4 == subsection1.NEP() );
  CHECK( 4 == subsection1.numberSecondaryEnergies() );
  CHECK( 4 == subsection1.energies().size() );
  CHECK( 1. == Approx( subsection1.energies()[0] ) );
  CHECK( 4. == Approx( subsection1.energies()[1] ) );
  CHECK( 7. == Approx( subsection1.energies()[2] ) );
  CHECK( 10. == Approx( subsection1.energies()[3] ) );
  CHECK( 4 == subsection1.coefficients().size() );
  CHECK( 2. == Approx( subsection1.coefficients()[0][0] ) );
  CHECK( 3. == Approx( subsection1.coefficients()[0][1] ) );
  CHECK( 5. == Approx( subsection1.coefficients()[1][0] ) );
  CHECK( 6. == Approx( subsection1.coefficients()[1][1] ) );
  CHECK( 8. == Approx( subsection1.coefficients()[2][0] ) );
  CHECK( 9. == Approx( subsection1.coefficients()[2][1] ) );
  CHECK( 11. == Approx( subsection1.coefficients()[3][0] ) );
  CHECK( 12. == Approx( subsection1.coefficients()[3][1] ) );
  CHECK( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
  CHECK( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

  auto subsection2 =
      std::get< LegendreCoefficients >( energies[1] );
  CHECK( 1 == subsection2.LANG() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 1 == subsection2.NA() );
  CHECK( 1 == subsection2.numberAngularParameters() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 2 == subsection2.NEP() );
  CHECK( 2 == subsection2.numberSecondaryEnergies() );
  CHECK( 2 == subsection2.energies().size() );
  CHECK( 1. == Approx( subsection2.energies()[0] ) );
  CHECK( 4. == Approx( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.coefficients().size() );
  CHECK( 2. == Approx( subsection2.coefficients()[0][0] ) );
  CHECK( 3. == Approx( subsection2.coefficients()[0][1] ) );
  CHECK( 5. == Approx( subsection2.coefficients()[1][0] ) );
  CHECK( 6. == Approx( subsection2.coefficients()[1][1] ) );
  CHECK( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

  // product 2
  CHECK( 1. == Approx( products[1].ZAP() ) );
  CHECK( 1. == Approx( products[1].productIdentifier() ) );
  CHECK( 1. == Approx( products[1].AWP() ) );
  CHECK( 1. == Approx( products[1].productWeightRatio() ) );
  CHECK( 0 == products[1].LIP() );
  CHECK( 0 == products[1].productModifierFlag() );
  CHECK( 1 == products[1].LAW() );

  CHECK( 1. == Approx( products[1].multiplicity().ZAP() ) );
  CHECK( 1. == Approx( products[1].multiplicity().productIdentifier() ) );
  CHECK( 1. == Approx( products[1].multiplicity().AWP() ) );
  CHECK( 1. == Approx( products[1].multiplicity().productWeightRatio() ) );
  CHECK( 0 == products[1].multiplicity().LIP() );
  CHECK( 0 == products[1].multiplicity().productModifierFlag() );
  CHECK( 1 == products[1].multiplicity().LAW() );

  CHECK( 2 == products[1].multiplicity().NP() );
  CHECK( 1 == products[1].multiplicity().NR() );
  CHECK( 1 == products[1].multiplicity().interpolants().size() );
  CHECK( 1 == products[1].multiplicity().boundaries().size() );
  CHECK( 2 == products[1].multiplicity().interpolants()[0] );
  CHECK( 2 == products[1].multiplicity().boundaries()[0] );
  CHECK( 2 == products[1].multiplicity().energies().size() );
  CHECK( 2 == products[1].multiplicity().multiplicities().size() );
  CHECK( 1.858639e+7 == Approx( products[1].multiplicity().energies()[0] ) );
  CHECK( 2e+7 == Approx( products[1].multiplicity().energies()[1] ) );
  CHECK( 4. == Approx( products[1].multiplicity().multiplicities()[0] ) );
  CHECK( 4. == Approx( products[1].multiplicity().multiplicities()[1] ) );

  law =
      std::get< ContinuumEnergyAngle >(
          products[1].distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.LEP() );
  CHECK( 2 == law.NE() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 22 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  energies = law.distributions();

  subsection1 =
      std::get< LegendreCoefficients >( energies[0] );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 0 == subsection1.NA() );
  CHECK( 0 == subsection1.numberAngularParameters() );
  CHECK( 6 == subsection1.NW() );
  CHECK( 3 == subsection1.NEP() );
  CHECK( 3 == subsection1.numberSecondaryEnergies() );
  CHECK( 3 == subsection1.energies().size() );
  CHECK( 0. == Approx( subsection1.energies()[0] ) );
  CHECK( 0.5 == Approx( subsection1.energies()[1] ) );
  CHECK( 1. == Approx( subsection1.energies()[2] ) );
  CHECK( 3 == subsection1.coefficients().size() );
  CHECK( 0. == Approx( subsection1.coefficients()[0][0] ) );
  CHECK( 2. == Approx( subsection1.coefficients()[1][0] ) );
  CHECK( 0. == Approx( subsection1.coefficients()[2][0] ) );
  CHECK( 3 == Approx( subsection1.totalEmissionProbabilities().size() ) );
  CHECK( 0. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK( 2. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK( 0. == Approx( subsection1.totalEmissionProbabilities()[2] ) );

  subsection2 =
      std::get< LegendreCoefficients >( energies[1] );
  CHECK( 1 == subsection2.LANG() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 0 == subsection2.NA() );
  CHECK( 0 == subsection2.numberAngularParameters() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 3 == subsection2.NEP() );
  CHECK( 3 == subsection2.numberSecondaryEnergies() );
  CHECK( 3 == subsection2.energies().size() );
  CHECK( 0. == Approx( subsection2.energies()[0] ) );
  CHECK( .5 == Approx( subsection2.energies()[1] ) );
  CHECK( 1. == Approx( subsection2.energies()[2] ) );
  CHECK( 3 == subsection2.coefficients().size() );
  CHECK( 0. == Approx( subsection2.coefficients()[0][0] ) );
  CHECK( 2. == Approx( subsection2.coefficients()[1][0] ) );
  CHECK( 0. == Approx( subsection2.coefficients()[2][0] ) );
  CHECK( 3 == Approx( subsection2.totalEmissionProbabilities().size() ) );
  CHECK( 0. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK( 2. == Approx( subsection2.totalEmissionProbabilities()[1] ) );
  CHECK( 0. == Approx( subsection2.totalEmissionProbabilities()[2] ) );

  // product 3
  CHECK( 0. == Approx( products[2].ZAP() ) );
  CHECK( 0. == Approx( products[2].productIdentifier() ) );
  CHECK( 0. == Approx( products[2].AWP() ) );
  CHECK( 0. == Approx( products[2].productWeightRatio() ) );
  CHECK( 0 == products[2].LIP() );
  CHECK( 0 == products[2].productModifierFlag() );
  CHECK( 1 == products[2].LAW() );

  CHECK( 0. == Approx( products[2].multiplicity().ZAP() ) );
  CHECK( 0. == Approx( products[2].multiplicity().productIdentifier() ) );
  CHECK( 0. == Approx( products[2].multiplicity().AWP() ) );
  CHECK( 0. == Approx( products[2].multiplicity().productWeightRatio() ) );
  CHECK( 0 == products[2].multiplicity().LIP() );
  CHECK( 0 == products[2].multiplicity().productModifierFlag() );
  CHECK( 1 == products[2].multiplicity().LAW() );

  CHECK( 3 == products[2].multiplicity().NP() );
  CHECK( 1 == products[2].multiplicity().NR() );
  CHECK( 1 == products[2].multiplicity().interpolants().size() );
  CHECK( 1 == products[2].multiplicity().boundaries().size() );
  CHECK( 2 == products[2].multiplicity().interpolants()[0] );
  CHECK( 3 == products[2].multiplicity().boundaries()[0] );
  CHECK( 3 == products[2].multiplicity().energies().size() );
  CHECK( 3 == products[2].multiplicity().multiplicities().size() );
  CHECK( 1.858639e+7 ==
           Approx( products[2].multiplicity().energies()[0] ) );
  CHECK( 1.9e+7 == Approx( products[2].multiplicity().energies()[1] ) );
  CHECK( 2e+7 == Approx( products[2].multiplicity().energies()[2] ) );
  CHECK( 1. == Approx( products[2].multiplicity().multiplicities()[0] ) );
  CHECK( 2. == Approx( products[2].multiplicity().multiplicities()[1] ) );
  CHECK( 3. == Approx( products[2].multiplicity().multiplicities()[2] ) );

  law =
      std::get< ContinuumEnergyAngle >(
          products[2].distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.LEP() );
  CHECK( 2 == law.NE() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 5 == law.interpolants()[0] );
  CHECK( 2 == law.boundaries()[0] );

  energies = law.distributions();

  subsection1 =
      std::get< LegendreCoefficients >( energies[0] );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 0 == subsection1.NA() );
  CHECK( 0 == subsection1.numberAngularParameters() );
  CHECK( 6 == subsection1.NW() );
  CHECK( 3 == subsection1.NEP() );
  CHECK( 3 == subsection1.numberSecondaryEnergies() );
  CHECK( 3 == subsection1.energies().size() );
  CHECK( 0. == Approx( subsection1.energies()[0] ) );
  CHECK( 1. == Approx( subsection1.energies()[1] ) );
  CHECK( 2. == Approx( subsection1.energies()[2] ) );
  CHECK( 3 == subsection1.coefficients().size() );
  CHECK( 0. == Approx( subsection1.coefficients()[0][0] ) );
  CHECK( 1. == Approx( subsection1.coefficients()[1][0] ) );
  CHECK( 0. == Approx( subsection1.coefficients()[2][0] ) );
  CHECK( 3 == Approx( subsection1.totalEmissionProbabilities().size() ) );
  CHECK( 0. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK( 1. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK( 0. == Approx( subsection1.totalEmissionProbabilities()[2] ) );

  subsection2 =
      std::get< LegendreCoefficients >( energies[1] );
  CHECK( 1 == subsection2.LANG() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 0 == subsection2.NA() );
  CHECK( 0 == subsection2.numberAngularParameters() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 3 == subsection2.NEP() );
  CHECK( 3 == subsection2.numberSecondaryEnergies() );
  CHECK( 3 == subsection2.energies().size() );
  CHECK( 0. == Approx( subsection2.energies()[0] ) );
  CHECK( 1. == Approx( subsection2.energies()[1] ) );
  CHECK( 2. == Approx( subsection2.energies()[2] ) );
  CHECK( 3 == subsection2.coefficients().size() );
  CHECK( 0. == Approx( subsection2.coefficients()[0][0] ) );
  CHECK( 1. == Approx( subsection2.coefficients()[1][0] ) );
  CHECK( 0. == Approx( subsection2.coefficients()[2][0] ) );
  CHECK( 3 == Approx( subsection2.totalEmissionProbabilities().size() ) );
  CHECK( 0. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK( 1. == Approx( subsection2.totalEmissionProbabilities()[1] ) );
  CHECK( 0. == Approx( subsection2.totalEmissionProbabilities()[2] ) );

  CHECK( 30 == chunk.NC() );
}

std::string invalidLAW() {
  return
    " 9.223500+4 2.330248+2          0          2          3          09228 6  5     \n"
    " 1.001000+3 9.986234-1          0          8          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 1.000000+0 1.000000+0          0          1          1          29228 6  5     \n"
    "          2          2                                            9228 6  5     \n"
    " 1.858639+7 4.000000+0 2.000000+7 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2         22                                            9228 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 0.000000+0          0          1          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.858639+7 1.000000+0 1.900000+7 2.000000+0 2.000000+7 3.000000+09228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          5                                            9228 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n"
    " 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 6  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 6  1     \n";
}
