#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string invalidLANG();

SCENARIO( "section::Type< 6 >::ReactionProduct" ) {

  GIVEN( "valid data for a "
         "section::Type< 6 >::ReactionProduct" ) {

    section::Type< 6 >::Multiplicity multiplicity(
      1001., 0.9986234, 0, 1, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    section::Type< 6 >::Distribution distribution(
      section::Type< 6 >::ContinuumEnergyAngle(
        1, 2, { 2 }, { 1 },
        { section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              1e-5, 0, 1, 4,
              { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ) ),
          section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) ) } ) );

    THEN( "a section::Type< 6 >::ReactionProduct can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 1 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 1 == chunk.multiplicity().LAW() );

      REQUIRE( 4 == chunk.multiplicity().NP() );
      REQUIRE( 1 == chunk.multiplicity().NR() );
      REQUIRE( 1 == chunk.multiplicity().interpolants().size() );
      REQUIRE( 1 == chunk.multiplicity().boundaries().size() );
      REQUIRE( 2 == chunk.multiplicity().interpolants()[0] );
      REQUIRE( 4 == chunk.multiplicity().boundaries()[0] );
      REQUIRE( 4 == chunk.multiplicity().energies().size() );
      REQUIRE( 4 == chunk.multiplicity().multiplicities().size() );
      REQUIRE( 1e-5 == Approx( chunk.multiplicity().energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( chunk.multiplicity().energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( chunk.multiplicity().energies()[2] ) );
      REQUIRE( 2e+7 == Approx( chunk.multiplicity().energies()[3] ) );
      REQUIRE( 0. == Approx( chunk.multiplicity().multiplicities()[0] ) );
      REQUIRE( 8.45368e-11 == Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 == Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 == Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle >( chunk.distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.energies();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NEP() );

      auto subsection1 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[0] );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NEP() );
      REQUIRE( 4 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 7. == Approx( subsection1.energies()[2] ) );
      REQUIRE( 10. == Approx( subsection1.energies()[3] ) );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 2. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 8. == Approx( subsection1.coefficients()[2][0] ) );
      REQUIRE( 9. == Approx( subsection1.coefficients()[2][1] ) );
      REQUIRE( 11. == Approx( subsection1.coefficients()[3][0] ) );
      REQUIRE( 12. == Approx( subsection1.coefficients()[3][1] ) );
      REQUIRE( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
      REQUIRE( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
      REQUIRE( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );

      auto subsection2 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[1] );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 1. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 2. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::ReactionProduct" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 6 >::ReactionProduct can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::ReactionProduct
        chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 1 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 1 == chunk.multiplicity().LAW() );

      REQUIRE( 4 == chunk.multiplicity().NP() );
      REQUIRE( 1 == chunk.multiplicity().NR() );
      REQUIRE( 1 == chunk.multiplicity().interpolants().size() );
      REQUIRE( 1 == chunk.multiplicity().boundaries().size() );
      REQUIRE( 2 == chunk.multiplicity().interpolants()[0] );
      REQUIRE( 4 == chunk.multiplicity().boundaries()[0] );
      REQUIRE( 4 == chunk.multiplicity().energies().size() );
      REQUIRE( 4 == chunk.multiplicity().multiplicities().size() );
      REQUIRE( 1e-5 == Approx( chunk.multiplicity().energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( chunk.multiplicity().energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( chunk.multiplicity().energies()[2] ) );
      REQUIRE( 2e+7 == Approx( chunk.multiplicity().energies()[3] ) );
      REQUIRE( 0. == Approx( chunk.multiplicity().multiplicities()[0] ) );
      REQUIRE( 8.45368e-11 == Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 == Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 == Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle >( chunk.distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.energies();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NEP() );

      auto subsection1 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[0] );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NEP() );
      REQUIRE( 4 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 7. == Approx( subsection1.energies()[2] ) );
      REQUIRE( 10. == Approx( subsection1.energies()[3] ) );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 2. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 8. == Approx( subsection1.coefficients()[2][0] ) );
      REQUIRE( 9. == Approx( subsection1.coefficients()[2][1] ) );
      REQUIRE( 11. == Approx( subsection1.coefficients()[3][0] ) );
      REQUIRE( 12. == Approx( subsection1.coefficients()[3][1] ) );
      REQUIRE( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
      REQUIRE( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
      REQUIRE( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );

      auto subsection2 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[1] );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 1. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 2. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::ReactionProduct" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "an inconsistent LAW between the Multicplivity and the Distribution" ){

    section::Type< 6 >::Multiplicity multiplicity(
      1001., 0.9986234, 0, 2, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    section::Type< 6 >::Distribution distribution(
      section::Type< 6 >::ContinuumEnergyAngle(
        1, 2, { 2 }, { 1 },
        { section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              1e-5, 0, 1, 4,
              { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ) ),
          section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) ) } ) );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section::Type< 6 >::ReactionProduct( std::move( multiplicity ), std::move( distribution ) ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 6 >::ReactionProduct"
         " with an invalid LAW" ){
    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section::Type< 6 >::ReactionProduct( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
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
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string invalidLANG() {
  return
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
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
