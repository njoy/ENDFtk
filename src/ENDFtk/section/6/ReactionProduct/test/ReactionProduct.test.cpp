#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct =
section::Type< 6 >::ReactionProduct;
using Multiplicity =
section::Type< 6 >::Multiplicity;
using Distribution =
section::Type< 6 >::Distribution;
using DefinedElsewhere =
section::Type< 6 >::DefinedElsewhere;
using Unknown =
section::Type< 6 >::Unknown;
using ContinuumEnergyAngle =
section::Type< 6 >::ContinuumEnergyAngle;
using LegendreCoefficients =
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;
using DiscreteTwoBodyScattering =
section::Type< 6 >::DiscreteTwoBodyScattering;
using Law2LegendreCoefficients =
section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;
using Law2Tabulated =
section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated;
using IsotropicDiscreteEmission =
section::Type< 6 >::IsotropicDiscreteEmission;
using DiscreteTwoBodyRecoils =
section::Type< 6 >::DiscreteTwoBodyRecoils;
using ChargedParticleElasticScattering =
section::Type< 6 >::ChargedParticleElasticScattering;
using Law5LegendreCoefficients =
section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;
using Law5NuclearAmplitudeExpansion =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;
using Law5NuclearPlusInterference =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;
using NBodyPhaseSpace =
section::Type< 6 >::NBodyPhaseSpace;
using LaboratoryAngleEnergy =
section::Type< 6 >::LaboratoryAngleEnergy;
using AngularDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::AngularDistribution;
using EnergyDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::EnergyDistribution;

std::string chunkWithLAW0();
std::string chunkWithLAW1();
std::string chunkWithLAW2();
std::string chunkWithLAW3();
std::string chunkWithLAW4();
std::string chunkWithLAW5();
std::string chunkWithLAW6();
std::string chunkWithLAW7();
std::string chunkWithNegativeLAW4();
std::string chunkWithNegativeLAW5();
std::string chunkWithNegativeLAW14();
std::string chunkWithNegativeLAW15();
std::string invalidLAW();
std::string chunkWithInvalidMTForNegativeLAW();

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with LAW=0" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 0, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = Unknown();

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 1001. == Approx( chunk.productIdentifier() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.productMassRatio() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 0 == chunk.productModifierFlag() );
      REQUIRE( 0 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 1001. == Approx( chunk.multiplicity().productIdentifier() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().productMassRatio() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 0 == chunk.multiplicity().productModifierFlag() );
      REQUIRE( 0 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< Unknown >( chunk.distribution() );

      REQUIRE( 0 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=0" ) {

    std::string string = chunkWithLAW0();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 1001. == Approx( chunk.productIdentifier() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.productMassRatio() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 0 == chunk.productModifierFlag() );
      REQUIRE( 0 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 1001. == Approx( chunk.multiplicity().productIdentifier() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().productMassRatio() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 0 == chunk.multiplicity().productModifierFlag() );
      REQUIRE( 0 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< Unknown >( chunk.distribution() );

      REQUIRE( 0 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=1" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 1, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution =
      ContinuumEnergyAngle(
        2, { 2 }, { 1 },
        { LegendreCoefficients(
              1e-5, 0, 1, 4,
              { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ),
          LegendreCoefficients(
              2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) } );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< ContinuumEnergyAngle >( chunk.distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
          std::get< LegendreCoefficients >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
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

      auto subsection2 =
          std::get< LegendreCoefficients >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
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

  GIVEN( "a string representation of a valid ReactionProduct with LAW=1" ) {

    std::string string = chunkWithLAW1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< ContinuumEnergyAngle >( chunk.distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
          std::get< LegendreCoefficients >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
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

      auto subsection2 =
          std::get< LegendreCoefficients >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
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

  GIVEN( "valid data for a ReactionProduct with LAW=2" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 2, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution =
      DiscreteTwoBodyScattering(
        { 2 }, { 1 },
        { Law2LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
          Law2Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) } );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 2 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 2 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DiscreteTwoBodyScattering >( chunk.distribution() );

      REQUIRE( 2 == law.LAW() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
          std::get< Law2LegendreCoefficients >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
      REQUIRE( 0 == subsection1.LANG() );
      REQUIRE( 4 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NL() );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 1. == Approx( subsection1.coefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.coefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.coefficients()[3] ) );

      auto subsection2 =
           std::get< Law2Tabulated >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
      REQUIRE( 12 == subsection2.LANG() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 3 == subsection2.NL() );
      REQUIRE( 3 == subsection2.cosines().size() );
      REQUIRE( 1. == Approx( subsection2.cosines()[0] ) );
      REQUIRE( 3. == Approx( subsection2.cosines()[1] ) );
      REQUIRE( 5. == Approx( subsection2.cosines()[2] ) );
      REQUIRE( 3 == subsection2.probabilities().size() );
      REQUIRE( 2. == Approx( subsection2.probabilities()[0] ) );
      REQUIRE( 4. == Approx( subsection2.probabilities()[1] ) );
      REQUIRE( 6. == Approx( subsection2.probabilities()[2] ) );

      REQUIRE( 10 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=2" ) {

    std::string string = chunkWithLAW2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 2 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 2 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DiscreteTwoBodyScattering >( chunk.distribution() );

      REQUIRE( 2 == law.LAW() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
          std::get< Law2LegendreCoefficients >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
      REQUIRE( 0 == subsection1.LANG() );
      REQUIRE( 4 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NL() );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 1. == Approx( subsection1.coefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.coefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.coefficients()[3] ) );

      auto subsection2 =
           std::get< Law2Tabulated >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
      REQUIRE( 12 == subsection2.LANG() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 3 == subsection2.NL() );
      REQUIRE( 3 == subsection2.cosines().size() );
      REQUIRE( 1. == Approx( subsection2.cosines()[0] ) );
      REQUIRE( 3. == Approx( subsection2.cosines()[1] ) );
      REQUIRE( 5. == Approx( subsection2.cosines()[2] ) );
      REQUIRE( 3 == subsection2.probabilities().size() );
      REQUIRE( 2. == Approx( subsection2.probabilities()[0] ) );
      REQUIRE( 4. == Approx( subsection2.probabilities()[1] ) );
      REQUIRE( 6. == Approx( subsection2.probabilities()[2] ) );

      REQUIRE( 10 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=3" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 3, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = IsotropicDiscreteEmission();

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 3 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 3 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< IsotropicDiscreteEmission >( chunk.distribution() );

      REQUIRE( 3 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=3" ) {

    std::string string = chunkWithLAW3();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 3 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 3 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< IsotropicDiscreteEmission >( chunk.distribution() );

      REQUIRE( 3 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=4" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 4, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = DiscreteTwoBodyRecoils();

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 4 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 4 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DiscreteTwoBodyRecoils >( chunk.distribution() );

      REQUIRE( 4 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=4" ) {

    std::string string = chunkWithLAW4();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 4 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 4 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DiscreteTwoBodyRecoils >( chunk.distribution() );

      REQUIRE( 4 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=5" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 5, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution =
      ChargedParticleElasticScattering(
        0.5, 1, { 2 }, { 1 },
        { Law5NuclearAmplitudeExpansion( 1e-5, 3,
                                         { 1., 2., 3., 4., 5., 6.,
                                           7., 8., 9., 10., 11., 12. } ),
          Law5NuclearPlusInterference( 2e+7, 15,
                                       { 1., 2., 3., 4., 5., 6. } ) } );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 5 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 5 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< ChargedParticleElasticScattering >( chunk.distribution() );

      REQUIRE( 5 == law.LAW() );

      REQUIRE( 0.5 == Approx( law.SPI() ) );
      REQUIRE( 1 == law.LIDP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
      std::get< Law5NuclearAmplitudeExpansion >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
      REQUIRE( 1 == subsection1.LTP() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 3 == subsection1.NL() );
      REQUIRE( 4 == subsection1.scatteringCoefficients().size() );
      REQUIRE( 1. == Approx( subsection1.scatteringCoefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.scatteringCoefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.scatteringCoefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.scatteringCoefficients()[3] ) );
      REQUIRE( 4 == subsection1.realInterferenceCoefficients().size() );
      REQUIRE( 5. == Approx( subsection1.realInterferenceCoefficients()[0] ) );
      REQUIRE( 7. == Approx( subsection1.realInterferenceCoefficients()[1] ) );
      REQUIRE( 9. == Approx( subsection1.realInterferenceCoefficients()[2] ) );
      REQUIRE( 11. == Approx( subsection1.realInterferenceCoefficients()[3] ) );
      REQUIRE( 4 == subsection1.imaginaryInterferenceCoefficients().size() );
      REQUIRE( 6. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[0] ) );
      REQUIRE( 8. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[1] ) );
      REQUIRE( 10. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[2] ) );
      REQUIRE( 12. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[3] ) );

      auto subsection2 =
      std::get< Law5NuclearPlusInterference >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
      REQUIRE( 15 == subsection2.LTP() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 3 == subsection2.NL() );
      REQUIRE( 3 == subsection2.cosines().size() );
      REQUIRE( 1. == Approx( subsection2.cosines()[0] ) );
      REQUIRE( 3. == Approx( subsection2.cosines()[1] ) );
      REQUIRE( 5. == Approx( subsection2.cosines()[2] ) );
      REQUIRE( 3 == subsection2.probabilities().size() );
      REQUIRE( 2. == Approx( subsection2.probabilities()[0] ) );
      REQUIRE( 4. == Approx( subsection2.probabilities()[1] ) );
      REQUIRE( 6. == Approx( subsection2.probabilities()[2] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=5" ) {

    std::string string = chunkWithLAW5();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 5 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 5 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< ChargedParticleElasticScattering >( chunk.distribution() );

      REQUIRE( 5 == law.LAW() );

      REQUIRE( 0.5 == Approx( law.SPI() ) );
      REQUIRE( 1 == law.LIDP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.subsections();

      auto subsection1 =
      std::get< Law5NuclearAmplitudeExpansion >( energies[0] );
      REQUIRE( 1e-5 == Approx( subsection1.energy() ) );
      REQUIRE( 1 == subsection1.LTP() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 3 == subsection1.NL() );
      REQUIRE( 4 == subsection1.scatteringCoefficients().size() );
      REQUIRE( 1. == Approx( subsection1.scatteringCoefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.scatteringCoefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.scatteringCoefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.scatteringCoefficients()[3] ) );
      REQUIRE( 4 == subsection1.realInterferenceCoefficients().size() );
      REQUIRE( 5. == Approx( subsection1.realInterferenceCoefficients()[0] ) );
      REQUIRE( 7. == Approx( subsection1.realInterferenceCoefficients()[1] ) );
      REQUIRE( 9. == Approx( subsection1.realInterferenceCoefficients()[2] ) );
      REQUIRE( 11. == Approx( subsection1.realInterferenceCoefficients()[3] ) );
      REQUIRE( 4 == subsection1.imaginaryInterferenceCoefficients().size() );
      REQUIRE( 6. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[0] ) );
      REQUIRE( 8. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[1] ) );
      REQUIRE( 10. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[2] ) );
      REQUIRE( 12. ==
               Approx( subsection1.imaginaryInterferenceCoefficients()[3] ) );

      auto subsection2 =
      std::get< Law5NuclearPlusInterference >( energies[1] );
      REQUIRE( 2e+7 == Approx( subsection2.energy() ) );
      REQUIRE( 15 == subsection2.LTP() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 3 == subsection2.NL() );
      REQUIRE( 3 == subsection2.cosines().size() );
      REQUIRE( 1. == Approx( subsection2.cosines()[0] ) );
      REQUIRE( 3. == Approx( subsection2.cosines()[1] ) );
      REQUIRE( 5. == Approx( subsection2.cosines()[2] ) );
      REQUIRE( 3 == subsection2.probabilities().size() );
      REQUIRE( 2. == Approx( subsection2.probabilities()[0] ) );
      REQUIRE( 4. == Approx( subsection2.probabilities()[1] ) );
      REQUIRE( 6. == Approx( subsection2.probabilities()[2] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=6" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 6, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = NBodyPhaseSpace( 5., 4 );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 6 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 6 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< NBodyPhaseSpace >( chunk.distribution() );

      REQUIRE( 6 == law.LAW() );

      REQUIRE( 5. == Approx( law.APSX() ) );
      REQUIRE( 5. == Approx( law.totalMass() ) );
      REQUIRE( 4 == law.NPSX() );
      REQUIRE( 4 == law.numberParticles() );

      REQUIRE( 5 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=6" ) {

    std::string string = chunkWithLAW6();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 6 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 6 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< NBodyPhaseSpace >( chunk.distribution() );

      REQUIRE( 6 == law.LAW() );

      REQUIRE( 5. == Approx( law.APSX() ) );
      REQUIRE( 5. == Approx( law.totalMass() ) );
      REQUIRE( 4 == law.NPSX() );
      REQUIRE( 4 == law.numberParticles() );

      REQUIRE( 5 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=7" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 7, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution =
      LaboratoryAngleEnergy(
        { 2 }, { 1 },
        { AngularDistribution(
            1e-5, { 2 }, { 4 },
            { EnergyDistribution( 1.0, { 4 }, { 2 },
                                                { 1e-5, 1.1e+7, 1.147e+7, 3e+7 },
                                                { 0., 2., 4., 6. } ),
              EnergyDistribution( -1.0, { 3 }, { 2 },
                                                { 1e-5, 1e+6, 3e+7 },
                                                { 6., 4., 2. } ) } ),
          AngularDistribution(
            2e+7, { 2 }, { 4 },
            { EnergyDistribution( 0.9, { 4 }, { 2 },
                                                { 1e-5, 1.1e+7, 1.147e+7, 3e+7 },
                                                { 1., 3., 5., 7. } ),
              EnergyDistribution( -0.9, { 3 }, { 2 },
                                                { 1e-5, 1e+6, 3e+7 },
                                                { 5., 3., 1. } ) } ) } );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 7 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 7 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< LaboratoryAngleEnergy >( chunk.distribution() );

      REQUIRE( 7 == law.LAW() );

      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.angularDistributions();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );

      REQUIRE( 2 == energies[0].NMU() );
      REQUIRE( 1 == energies[0].NRM() );
      REQUIRE( 1 == energies[0].interpolants().size() );
      REQUIRE( 1 == energies[0].boundaries().size() );
      REQUIRE( 4 == energies[0].interpolants()[0] );
      REQUIRE( 2 == energies[0].boundaries()[0] );

      auto cosines = energies[0].energyDistributions();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( 1. == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energies().size() );
      REQUIRE( 4 == cosines[0].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energies()[3] ) );
      REQUIRE( 0. == Approx( cosines[0].probabilities()[0] ) );
      REQUIRE( 2. == Approx( cosines[0].probabilities()[1] ) );
      REQUIRE( 4. == Approx( cosines[0].probabilities()[2] ) );
      REQUIRE( 6. == Approx( cosines[0].probabilities()[3] ) );

      REQUIRE( -1. == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energies().size() );
      REQUIRE( 3 == cosines[1].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energies()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energies()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energies()[2] ) );
      REQUIRE( 6. == Approx( cosines[1].probabilities()[0] ) );
      REQUIRE( 4. == Approx( cosines[1].probabilities()[1] ) );
      REQUIRE( 2. == Approx( cosines[1].probabilities()[2] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );

      REQUIRE( 2 == energies[1].NMU() );
      REQUIRE( 1 == energies[1].NRM() );
      REQUIRE( 1 == energies[1].interpolants().size() );
      REQUIRE( 1 == energies[1].boundaries().size() );
      REQUIRE( 4 == energies[1].interpolants()[0] );
      REQUIRE( 2 == energies[1].boundaries()[0] );

      cosines = energies[1].energyDistributions();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( .9 == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energies().size() );
      REQUIRE( 4 == cosines[0].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energies()[3] ) );
      REQUIRE( 1. == Approx( cosines[0].probabilities()[0] ) );
      REQUIRE( 3. == Approx( cosines[0].probabilities()[1] ) );
      REQUIRE( 5. == Approx( cosines[0].probabilities()[2] ) );
      REQUIRE( 7. == Approx( cosines[0].probabilities()[3] ) );

      REQUIRE( -.9 == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energies().size() );
      REQUIRE( 3 == cosines[1].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energies()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energies()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energies()[2] ) );
      REQUIRE( 5. == Approx( cosines[1].probabilities()[0] ) );
      REQUIRE( 3. == Approx( cosines[1].probabilities()[1] ) );
      REQUIRE( 1. == Approx( cosines[1].probabilities()[2] ) );

      REQUIRE( 24 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=7" ) {

    std::string string = chunkWithLAW7();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( 7 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( 7 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< LaboratoryAngleEnergy >( chunk.distribution() );

      REQUIRE( 7 == law.LAW() );

      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.angularDistributions();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );

      REQUIRE( 2 == energies[0].NMU() );
      REQUIRE( 1 == energies[0].NRM() );
      REQUIRE( 1 == energies[0].interpolants().size() );
      REQUIRE( 1 == energies[0].boundaries().size() );
      REQUIRE( 4 == energies[0].interpolants()[0] );
      REQUIRE( 2 == energies[0].boundaries()[0] );

      auto cosines = energies[0].energyDistributions();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( 1. == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energies().size() );
      REQUIRE( 4 == cosines[0].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energies()[3] ) );
      REQUIRE( 0. == Approx( cosines[0].probabilities()[0] ) );
      REQUIRE( 2. == Approx( cosines[0].probabilities()[1] ) );
      REQUIRE( 4. == Approx( cosines[0].probabilities()[2] ) );
      REQUIRE( 6. == Approx( cosines[0].probabilities()[3] ) );

      REQUIRE( -1. == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energies().size() );
      REQUIRE( 3 == cosines[1].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energies()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energies()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energies()[2] ) );
      REQUIRE( 6. == Approx( cosines[1].probabilities()[0] ) );
      REQUIRE( 4. == Approx( cosines[1].probabilities()[1] ) );
      REQUIRE( 2. == Approx( cosines[1].probabilities()[2] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );

      REQUIRE( 2 == energies[1].NMU() );
      REQUIRE( 1 == energies[1].NRM() );
      REQUIRE( 1 == energies[1].interpolants().size() );
      REQUIRE( 1 == energies[1].boundaries().size() );
      REQUIRE( 4 == energies[1].interpolants()[0] );
      REQUIRE( 2 == energies[1].boundaries()[0] );

      cosines = energies[1].energyDistributions();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( .9 == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energies().size() );
      REQUIRE( 4 == cosines[0].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energies()[3] ) );
      REQUIRE( 1. == Approx( cosines[0].probabilities()[0] ) );
      REQUIRE( 3. == Approx( cosines[0].probabilities()[1] ) );
      REQUIRE( 5. == Approx( cosines[0].probabilities()[2] ) );
      REQUIRE( 7. == Approx( cosines[0].probabilities()[3] ) );

      REQUIRE( -.9 == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energies().size() );
      REQUIRE( 3 == cosines[1].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energies()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energies()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energies()[2] ) );
      REQUIRE( 5. == Approx( cosines[1].probabilities()[0] ) );
      REQUIRE( 3. == Approx( cosines[1].probabilities()[1] ) );
      REQUIRE( 1. == Approx( cosines[1].probabilities()[2] ) );

      REQUIRE( 24 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-4" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, -4, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = DefinedElsewhere( -4 );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -4 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -4 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -4 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=-4" ) {

    std::string string = chunkWithNegativeLAW4();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -4 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -4 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -4 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-5" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, -5, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = DefinedElsewhere( -5 );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -5 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -5 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -5 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=-5" ) {

    std::string string = chunkWithNegativeLAW5();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -5 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -5 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -5 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-14" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, -14, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = DefinedElsewhere( -14 );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -14 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -14 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -14 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=-14" ) {

    std::string string = chunkWithNegativeLAW14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -14 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -14 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -14 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-15" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, -15, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution = DefinedElsewhere( -15 );

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct
        chunk( std::move( multiplicity ), std::move( distribution ) );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -15 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -15 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -15 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ReactionProduct with LAW=-15" ) {

    std::string string = chunkWithNegativeLAW15();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a ReactionProduct can "
          "be constructed and members can be tested" ) {
      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      REQUIRE( 1001. == Approx( chunk.ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
      REQUIRE( 0 == chunk.LIP() );
      REQUIRE( -15 == chunk.LAW() );

      REQUIRE( 1001. == Approx( chunk.multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( chunk.multiplicity().AWP() ) );
      REQUIRE( 0 == chunk.multiplicity().LIP() );
      REQUIRE( -15 == chunk.multiplicity().LAW() );

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
      REQUIRE( 8.45368e-11 ==
               Approx( chunk.multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 ==
               Approx( chunk.multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 ==
               Approx( chunk.multiplicity().multiplicities()[3] ) );

      auto law =
         std::get< DefinedElsewhere >( chunk.distribution() );

      REQUIRE( -15 == law.LAW() );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=0" ) {

    std::string string = chunkWithLAW0();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=1" ) {

    std::string string = chunkWithLAW1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=2" ) {

    std::string string = chunkWithLAW2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=3" ) {

    std::string string = chunkWithLAW3();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=4" ) {

    std::string string = chunkWithLAW4();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=5" ) {

    std::string string = chunkWithLAW5();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=6" ) {

    std::string string = chunkWithLAW6();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=7" ) {

    std::string string = chunkWithLAW7();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=-4" ) {

    std::string string = chunkWithNegativeLAW4();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=-5" ) {

    std::string string = chunkWithNegativeLAW5();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=-14" ) {

    std::string string = chunkWithNegativeLAW14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of ReactionProduct with LAW=-15" ) {

    std::string string = chunkWithNegativeLAW15();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ReactionProduct
      chunk( begin, end, lineNumber, 9228, 6, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "an inconsistent LAW between the Multiplicity and the Distribution" ) {

    Multiplicity multiplicity(
      1001., 0.9986234, 0, 2, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution(
      ContinuumEnergyAngle(
        2, { 2 }, { 1 },
        { LegendreCoefficients(
              1e-5, 0, 1, 4,
              { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ),
          LegendreCoefficients(
              2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) } ) );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( ReactionProduct( std::move( multiplicity ),
                                       std::move( distribution ) ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a ReactionProduct"
         " with an invalid LAW" ){
    std::string string = invalidLAW();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( ReactionProduct( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a ReactionProduct"
         " with an invalid MT for LAW<0" ){
    std::string string = chunkWithInvalidMTForNegativeLAW();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( ReactionProduct( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunkWithLAW0() {
  return
    " 1.001000+3 9.986234-1          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}

std::string chunkWithLAW1() {
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

std::string chunkWithLAW2() {
  return
    " 1.001000+3 9.986234-1          0          2          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkWithLAW3() {
  return
    " 1.001000+3 9.986234-1          0          3          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}

std::string chunkWithLAW4() {
  return
    " 1.001000+3 9.986234-1          0          4          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}

std::string chunkWithLAW5() {
  return
    " 1.001000+3 9.986234-1          0          5          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 5.000000-1 0.000000+0          1          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          1          0         12          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7         15          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkWithLAW6() {
  return
    " 1.001000+3 9.986234-1          0          6          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}

std::string chunkWithLAW7() {
  return
    " 1.001000+3 9.986234-1          0          7          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n"
    " 3.000000+7 6.000000+0                                            9228 6  5     \n"
    " 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 9.000000-1          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 1.000000+0 1.100000+7 3.000000+0 1.147000+7 5.000000+09228 6  5     \n"
    " 3.000000+7 7.000000+0                                            9228 6  5     \n"
    " 0.000000+0-9.000000-1          0          0          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.000000-5 5.000000+0 1.000000+6 3.000000+0 3.000000+7 1.000000+09228 6  5     \n";
}

std::string chunkWithNegativeLAW4() {
  return
    " 1.001000+3 9.986234-1          0         -4          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

std::string chunkWithNegativeLAW5() {
  return
    " 1.001000+3 9.986234-1          0         -5          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

std::string chunkWithNegativeLAW14() {
  return
    " 1.001000+3 9.986234-1          0        -14          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

std::string chunkWithNegativeLAW15() {
  return
    " 1.001000+3 9.986234-1          0        -15          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

std::string invalidLAW() {
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

std::string chunkWithInvalidMTForNegativeLAW() {
  return
    " 1.001000+3 9.986234-1          0         -5          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}
