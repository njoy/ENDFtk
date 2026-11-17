// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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
using Law2TabulatedDistribution =
section::Type< 6 >::DiscreteTwoBodyScattering::TabulatedDistribution;
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
void verifyChunkWithLAW0( const ReactionProduct& );
std::string chunkWithLAW1();
void verifyChunkWithLAW1( const ReactionProduct& );
std::string chunkWithLAW2();
void verifyChunkWithLAW2( const ReactionProduct& );
std::string chunkWithLAW3();
void verifyChunkWithLAW3( const ReactionProduct& );
std::string chunkWithLAW4();
void verifyChunkWithLAW4( const ReactionProduct& );
std::string chunkWithLAW5();
void verifyChunkWithLAW5( const ReactionProduct& );
std::string chunkWithLAW6();
void verifyChunkWithLAW6( const ReactionProduct& );
std::string chunkWithLAW7();
void verifyChunkWithLAW7( const ReactionProduct& );
std::string chunkWithNegativeLAW4();
void verifyChunkWithNegativeLAW4( const ReactionProduct& );
std::string chunkWithNegativeLAW5();
void verifyChunkWithNegativeLAW5( const ReactionProduct& );
std::string chunkWithNegativeLAW14();
void verifyChunkWithNegativeLAW14( const ReactionProduct& );
std::string chunkWithNegativeLAW15();
void verifyChunkWithNegativeLAW15( const ReactionProduct& );
std::string invalidLAW();
std::string chunkWithInvalidMTForNegativeLAW();

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct with LAW=0" ) {

    std::string string = chunkWithLAW0();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001., 0.9986234, 0, 0, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = Unknown();

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=1" ) {

    std::string string = chunkWithLAW1();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 1, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution =
        ContinuumEnergyAngle(
          2, { 2 }, { 1 },
          { LegendreCoefficients(
                1e-5, 0, 1,
                { 1., 4., 7., 10. },
                { { 2., 3. }, { 5., 6. },
                  { 8., 9. }, {  11., 12. } } ),
            LegendreCoefficients(
                2e+7, 0, 1, { 1., 4. }, { { 2., 3. }, { 5., 6. } } ) } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=2" ) {

    std::string string = chunkWithLAW2();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001., 0.9986234, 0, 2, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution =
        DiscreteTwoBodyScattering(
          { 2 }, { 1 },
          { Law2LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
            Law2TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=3" ) {

    std::string string = chunkWithLAW3();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 3, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = IsotropicDiscreteEmission();

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=4" ) {

    std::string string = chunkWithLAW4();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 4, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = DiscreteTwoBodyRecoils();

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW4( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW4( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=5" ) {

    std::string string = chunkWithLAW5();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 5, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution =
        ChargedParticleElasticScattering(
          0.5, 1, { 2 }, { 1 },
          { Law5NuclearAmplitudeExpansion( 1e-5, 3,
                                           { 1., 2., 3., 4. },
                                           { { 5., 6. }, { 7., 8. },
                                             { 9., 10. }, { 11., 12. } } ),
            Law5NuclearPlusInterference( 2e+7, 15,
                                         { 1., 3., 5.}, {2., 4., 6. } ) } );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=6" ) {

    std::string string = chunkWithLAW6();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 6, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = NBodyPhaseSpace( 5., 4 );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW6( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW6( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=7" ) {

    std::string string = chunkWithLAW7();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, 7, { 4 }, { 2 },
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

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW7( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithLAW7( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-4" ) {

    std::string string = chunkWithNegativeLAW4();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, -4, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = DefinedElsewhere( -4 );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW4( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW4( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-5" ) {

    std::string string = chunkWithNegativeLAW5();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, -5, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = DefinedElsewhere( -5 );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-14" ) {

    std::string string = chunkWithNegativeLAW14();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, -14, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = DefinedElsewhere( -14 );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW14( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW14( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ReactionProduct with LAW=-15" ) {

    std::string string = chunkWithNegativeLAW15();

    WHEN( "the data is given explicitly" ) {

      Multiplicity multiplicity(
        1001, 0.9986234, 0, -15, { 4 }, { 2 },
        { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
        { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
      Distribution distribution = DefinedElsewhere( -15 );

      ReactionProduct chunk( std::move( multiplicity ),
                             std::move( distribution ) );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW15( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9228, 6, 18 );

      THEN( "a ReactionProduct can "
            "be constructed and members can be tested" ) {

        verifyChunkWithNegativeLAW15( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 18 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an inconsistent LAW between the Multiplicity and the Distribution" ) {

    Multiplicity multiplicity(
      1001, 0.9986234, 0, 2, { 4 }, { 2 },
      { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
      { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } );
    Distribution distribution(
      ContinuumEnergyAngle(
        2, { 2 }, { 1 },
        { LegendreCoefficients(
              1e-5, 0, 1,
              { 1., 4., 7., 10. },
              { { 2., 3. }, { 5., 6. },
                { 8., 9. }, {  11., 12. } } ),
          LegendreCoefficients(
              2e+7, 0, 1, { 1., 4. }, { { 2., 3. }, { 5., 6. } } ) } ) );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( ReactionProduct( std::move( multiplicity ),
                                       std::move( distribution ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of a ReactionProduct"
         " with an invalid LAW" ){
    std::string string = invalidLAW();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( ReactionProduct( begin, end, lineNumber, 9228, 6, 5 ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of a ReactionProduct"
         " with an invalid MT for LAW<0" ) {

    std::string string = chunkWithInvalidMTForNegativeLAW();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( ReactionProduct( begin, end, lineNumber, 9228, 6, 5 ) );
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

void verifyChunkWithLAW0( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK( 1001 == chunk.productIdentifier() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK_THAT( 0.9986234, WithinRel( chunk.productWeightRatio() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 0 == chunk.productModifierFlag() );
  CHECK( 0 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK( 1001 == chunk.multiplicity().productIdentifier() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().productWeightRatio() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 0 == chunk.multiplicity().productModifierFlag() );
  CHECK( 0 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< Unknown >( chunk.distribution() );

  CHECK( 0 == law.LAW() );

  CHECK( 4 == chunk.NC() );
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

void verifyChunkWithLAW1( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 1 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 1 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< ContinuumEnergyAngle >( chunk.distribution() );

  CHECK( 1 == law.LAW() );
  CHECK( 2 == law.LEP() );
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

  auto subsection1 =
      std::get< LegendreCoefficients >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
  CHECK( 0 == subsection1.ND() );
  CHECK( 1 == subsection1.NA() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 4 == subsection1.NEP() );
  CHECK( 4 == subsection1.energies().size() );
  CHECK_THAT( 1., WithinRel( subsection1.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection1.energies()[1] ) );
  CHECK_THAT( 7., WithinRel( subsection1.energies()[2] ) );
  CHECK_THAT( 10., WithinRel( subsection1.energies()[3] ) );
  CHECK( 4 == subsection1.coefficients().size() );
  CHECK_THAT( 2., WithinRel( subsection1.coefficients()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection1.coefficients()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection1.coefficients()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.coefficients()[1][1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.coefficients()[2][0] ) );
  CHECK_THAT( 9., WithinRel( subsection1.coefficients()[2][1] ) );
  CHECK_THAT( 11., WithinRel( subsection1.coefficients()[3][0] ) );
  CHECK_THAT( 12., WithinRel( subsection1.coefficients()[3][1] ) );
  CHECK( 4 == subsection1.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.totalEmissionProbabilities()[2] ) );
  CHECK_THAT( 11., WithinRel( subsection1.totalEmissionProbabilities()[3] ) );

  auto subsection2 = std::get< LegendreCoefficients >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
  CHECK( 1 == subsection2.LANG() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 1 == subsection2.NA() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 2 == subsection2.NEP() );
  CHECK( 2 == subsection2.energies().size() );
  CHECK_THAT( 1., WithinRel( subsection2.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.coefficients().size() );
  CHECK_THAT( 2., WithinRel( subsection2.coefficients()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.coefficients()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.coefficients()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection2.coefficients()[1][1] ) );
  CHECK( 2 == subsection2.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection2.totalEmissionProbabilities()[1] ) );

  CHECK( 11 == chunk.NC() );
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

void verifyChunkWithLAW2( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 2 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 2 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DiscreteTwoBodyScattering >( chunk.distribution() );

  CHECK( 2 == law.LAW() );
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

  auto subsection1 = std::get< Law2LegendreCoefficients >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
  CHECK( 0 == subsection1.LANG() );
  CHECK( 4 == subsection1.NW() );
  CHECK( 4 == subsection1.NL() );
  CHECK( 4 == subsection1.coefficients().size() );
  CHECK_THAT( 1., WithinRel( subsection1.coefficients()[0] ) );
  CHECK_THAT( 2., WithinRel( subsection1.coefficients()[1] ) );
  CHECK_THAT( 3., WithinRel( subsection1.coefficients()[2] ) );
  CHECK_THAT( 4., WithinRel( subsection1.coefficients()[3] ) );

  auto subsection2 = std::get< Law2TabulatedDistribution >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
  CHECK( 12 == subsection2.LANG() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 3 == subsection2.NL() );
  CHECK( 3 == subsection2.cosines().size() );
  CHECK_THAT( 1., WithinRel( subsection2.cosines()[0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.cosines()[1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.cosines()[2] ) );
  CHECK( 3 == subsection2.probabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection2.probabilities()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.probabilities()[1] ) );
  CHECK_THAT( 6., WithinRel( subsection2.probabilities()[2] ) );

  CHECK( 10 == chunk.NC() );
}

std::string chunkWithLAW3() {
  return
    " 1.001000+3 9.986234-1          0          3          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}

void verifyChunkWithLAW3( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 3 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 3 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< IsotropicDiscreteEmission >( chunk.distribution() );

  CHECK( 3 == law.LAW() );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithLAW4() {
  return
    " 1.001000+3 9.986234-1          0          4          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n";
}

void verifyChunkWithLAW4( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 4 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 4 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DiscreteTwoBodyRecoils >( chunk.distribution() );

  CHECK( 4 == law.LAW() );

  CHECK( 4 == chunk.NC() );
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

void verifyChunkWithLAW5( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 5 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 5 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< ChargedParticleElasticScattering >( chunk.distribution() );

  CHECK( 5 == law.LAW() );

  CHECK_THAT( 0.5, WithinRel( law.SPI() ) );
  CHECK( 1 == law.LIDP() );
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

  auto subsection1 =
  std::get< Law5NuclearAmplitudeExpansion >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.E() ) );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
  CHECK( 1 == subsection1.LTP() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 3 == subsection1.NL() );
  CHECK( 4 == subsection1.B().size() );
  CHECK( 4 == subsection1.scatteringCoefficients().size() );
  CHECK_THAT( 1., WithinRel( subsection1.B()[0] ) );
  CHECK_THAT( 2., WithinRel( subsection1.B()[1] ) );
  CHECK_THAT( 3., WithinRel( subsection1.B()[2] ) );
  CHECK_THAT( 4., WithinRel( subsection1.B()[3] ) );
  CHECK_THAT( 1., WithinRel( subsection1.scatteringCoefficients()[0] ) );
  CHECK_THAT( 2., WithinRel( subsection1.scatteringCoefficients()[1] ) );
  CHECK_THAT( 3., WithinRel( subsection1.scatteringCoefficients()[2] ) );
  CHECK_THAT( 4., WithinRel( subsection1.scatteringCoefficients()[3] ) );
  CHECK( 4 == subsection1.AR().size() );
  CHECK( 4 == subsection1.realInterferenceCoefficients().size() );
  CHECK_THAT( 5., WithinRel( subsection1.AR()[0] ) );
  CHECK_THAT( 7., WithinRel( subsection1.AR()[1] ) );
  CHECK_THAT( 9., WithinRel( subsection1.AR()[2] ) );
  CHECK_THAT( 11., WithinRel( subsection1.AR()[3] ) );
  CHECK_THAT( 5., WithinRel( subsection1.realInterferenceCoefficients()[0] ) );
  CHECK_THAT( 7., WithinRel( subsection1.realInterferenceCoefficients()[1] ) );
  CHECK_THAT( 9., WithinRel( subsection1.realInterferenceCoefficients()[2] ) );
  CHECK_THAT( 11., WithinRel( subsection1.realInterferenceCoefficients()[3] ) );
  CHECK( 4 == subsection1.AI().size() );
  CHECK( 4 == subsection1.imaginaryInterferenceCoefficients().size() );
  CHECK_THAT( 6., WithinRel( subsection1.AI()[0] ) );
  CHECK_THAT( 8., WithinRel( subsection1.AI()[1] ) );
  CHECK_THAT( 10., WithinRel( subsection1.AI()[2] ) );
  CHECK_THAT( 12., WithinRel( subsection1.AI()[3] ) );
  CHECK_THAT( 6., WithinRel( subsection1.imaginaryInterferenceCoefficients()[0] ) );
  CHECK_THAT( 8., WithinRel( subsection1.imaginaryInterferenceCoefficients()[1] ) );
  CHECK_THAT( 10., WithinRel( subsection1.imaginaryInterferenceCoefficients()[2] ) );
  CHECK_THAT( 12., WithinRel( subsection1.imaginaryInterferenceCoefficients()[3] ) );

  auto subsection2 = std::get< Law5NuclearPlusInterference >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
  CHECK( 15 == subsection2.LTP() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 3 == subsection2.NL() );
  CHECK( 3 == subsection2.MU().size() );
  CHECK( 3 == subsection2.cosines().size() );
  CHECK_THAT( 1., WithinRel( subsection2.MU()[0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.MU()[1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.MU()[2] ) );
  CHECK_THAT( 1., WithinRel( subsection2.cosines()[0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.cosines()[1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.cosines()[2] ) );
  CHECK( 3 == subsection2.PNI().size() );
  CHECK( 3 == subsection2.probabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection2.PNI()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.PNI()[1] ) );
  CHECK_THAT( 6., WithinRel( subsection2.PNI()[2] ) );
  CHECK_THAT( 2., WithinRel( subsection2.probabilities()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.probabilities()[1] ) );
  CHECK_THAT( 6., WithinRel( subsection2.probabilities()[2] ) );

  CHECK( 11 == chunk.NC() );
}

std::string chunkWithLAW6() {
  return
    " 1.001000+3 9.986234-1          0          6          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}

void verifyChunkWithLAW6( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 6 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 6 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< NBodyPhaseSpace >( chunk.distribution() );

  CHECK( 6 == law.LAW() );

  CHECK_THAT( 5., WithinRel( law.APSX() ) );
  CHECK_THAT( 5., WithinRel( law.totalMass() ) );
  CHECK( 4 == law.NPSX() );
  CHECK( 4 == law.numberParticles() );

  CHECK( 5 == chunk.NC() );
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

void verifyChunkWithLAW7( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 7 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( 7 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< LaboratoryAngleEnergy >( chunk.distribution() );

  CHECK( 7 == law.LAW() );

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

  auto energies = law.angularDistributions();

  CHECK_THAT( 1e-5, WithinRel( energies[0].incidentEnergy() ) );

  CHECK( 2 == energies[0].NMU() );
  CHECK( 1 == energies[0].NRM() );
  CHECK( 1 == energies[0].interpolants().size() );
  CHECK( 1 == energies[0].boundaries().size() );
  CHECK( 4 == energies[0].interpolants()[0] );
  CHECK( 2 == energies[0].boundaries()[0] );

  auto cosines = energies[0].energyDistributions();
  CHECK( 2 == cosines.size() );

  CHECK_THAT( 1., WithinRel( cosines[0].cosine() ) );
  CHECK( 1 == cosines[0].NRP() );
  CHECK( 4 == cosines[0].NEP() );
  CHECK( 1 == cosines[0].interpolants().size() );
  CHECK( 1 == cosines[0].boundaries().size() );
  CHECK( 2 == cosines[0].interpolants()[0] );
  CHECK( 4 == cosines[0].boundaries()[0] );
  CHECK( 4 == cosines[0].energies().size() );
  CHECK( 4 == cosines[0].probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( cosines[0].energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( cosines[0].energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( cosines[0].energies()[2] ) );
  CHECK_THAT( 3e+7, WithinRel( cosines[0].energies()[3] ) );
  CHECK_THAT( 0., WithinRel( cosines[0].probabilities()[0] ) );
  CHECK_THAT( 2., WithinRel( cosines[0].probabilities()[1] ) );
  CHECK_THAT( 4., WithinRel( cosines[0].probabilities()[2] ) );
  CHECK_THAT( 6., WithinRel( cosines[0].probabilities()[3] ) );

  CHECK_THAT( -1., WithinRel( cosines[1].cosine() ) );
  CHECK( 1 == cosines[1].NRP() );
  CHECK( 3 == cosines[1].NEP() );
  CHECK( 1 == cosines[1].interpolants().size() );
  CHECK( 1 == cosines[1].boundaries().size() );
  CHECK( 2 == cosines[1].interpolants()[0] );
  CHECK( 3 == cosines[1].boundaries()[0] );
  CHECK( 3 == cosines[1].energies().size() );
  CHECK( 3 == cosines[1].probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( cosines[1].energies()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( cosines[1].energies()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( cosines[1].energies()[2] ) );
  CHECK_THAT( 6., WithinRel( cosines[1].probabilities()[0] ) );
  CHECK_THAT( 4., WithinRel( cosines[1].probabilities()[1] ) );
  CHECK_THAT( 2., WithinRel( cosines[1].probabilities()[2] ) );

  CHECK_THAT( 2e+7, WithinRel( energies[1].incidentEnergy() ) );

  CHECK( 2 == energies[1].NMU() );
  CHECK( 1 == energies[1].NRM() );
  CHECK( 1 == energies[1].interpolants().size() );
  CHECK( 1 == energies[1].boundaries().size() );
  CHECK( 4 == energies[1].interpolants()[0] );
  CHECK( 2 == energies[1].boundaries()[0] );

  cosines = energies[1].energyDistributions();
  CHECK( 2 == cosines.size() );

  CHECK_THAT( .9, WithinRel( cosines[0].cosine() ) );
  CHECK( 1 == cosines[0].NRP() );
  CHECK( 4 == cosines[0].NEP() );
  CHECK( 1 == cosines[0].interpolants().size() );
  CHECK( 1 == cosines[0].boundaries().size() );
  CHECK( 2 == cosines[0].interpolants()[0] );
  CHECK( 4 == cosines[0].boundaries()[0] );
  CHECK( 4 == cosines[0].energies().size() );
  CHECK( 4 == cosines[0].probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( cosines[0].energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( cosines[0].energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( cosines[0].energies()[2] ) );
  CHECK_THAT( 3e+7, WithinRel( cosines[0].energies()[3] ) );
  CHECK_THAT( 1., WithinRel( cosines[0].probabilities()[0] ) );
  CHECK_THAT( 3., WithinRel( cosines[0].probabilities()[1] ) );
  CHECK_THAT( 5., WithinRel( cosines[0].probabilities()[2] ) );
  CHECK_THAT( 7., WithinRel( cosines[0].probabilities()[3] ) );

  CHECK_THAT( -.9, WithinRel( cosines[1].cosine() ) );
  CHECK( 1 == cosines[1].NRP() );
  CHECK( 3 == cosines[1].NEP() );
  CHECK( 1 == cosines[1].interpolants().size() );
  CHECK( 1 == cosines[1].boundaries().size() );
  CHECK( 2 == cosines[1].interpolants()[0] );
  CHECK( 3 == cosines[1].boundaries()[0] );
  CHECK( 3 == cosines[1].energies().size() );
  CHECK( 3 == cosines[1].probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( cosines[1].energies()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( cosines[1].energies()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( cosines[1].energies()[2] ) );
  CHECK_THAT( 5., WithinRel( cosines[1].probabilities()[0] ) );
  CHECK_THAT( 3., WithinRel( cosines[1].probabilities()[1] ) );
  CHECK_THAT( 1., WithinRel( cosines[1].probabilities()[2] ) );

  CHECK( 24 == chunk.NC() );
}

std::string chunkWithNegativeLAW4() {
  return
    " 1.001000+3 9.986234-1          0         -4          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

void verifyChunkWithNegativeLAW4( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( -4 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( -4 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DefinedElsewhere >( chunk.distribution() );

  CHECK( -4 == law.LAW() );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithNegativeLAW5() {
  return
    " 1.001000+3 9.986234-1          0         -5          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

void verifyChunkWithNegativeLAW5( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( -5 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( -5 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DefinedElsewhere >( chunk.distribution() );

  CHECK( -5 == law.LAW() );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithNegativeLAW14() {
  return
    " 1.001000+3 9.986234-1          0        -14          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

void verifyChunkWithNegativeLAW14( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( -14 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( -14 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DefinedElsewhere >( chunk.distribution() );

  CHECK( -14 == law.LAW() );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithNegativeLAW15() {
  return
    " 1.001000+3 9.986234-1          0        -15          1          49228 6 18     \n"
    "          4          2                                            9228 6 18     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6 18     \n"
    " 2.000000+7 2.149790-1                                            9228 6 18     \n";
}

void verifyChunkWithNegativeLAW15( const ReactionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.AWP() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( -15 == chunk.LAW() );

  CHECK( 1001 == chunk.multiplicity().ZAP() );
  CHECK_THAT( 0.9986234, WithinRel( chunk.multiplicity().AWP() ) );
  CHECK( 0 == chunk.multiplicity().LIP() );
  CHECK( -15 == chunk.multiplicity().LAW() );

  CHECK( 4 == chunk.multiplicity().NP() );
  CHECK( 4 == chunk.multiplicity().numberPoints() );
  CHECK( 1 == chunk.multiplicity().NR() );
  CHECK( 1 == chunk.multiplicity().numberInterpolationRegions() );
  CHECK( 1 == chunk.multiplicity().INT().size() );
  CHECK( 1 == chunk.multiplicity().NBT().size() );
  CHECK( 2 == chunk.multiplicity().INT()[0] );
  CHECK( 4 == chunk.multiplicity().NBT()[0] );
  CHECK( 1 == chunk.multiplicity().interpolants().size() );
  CHECK( 1 == chunk.multiplicity().boundaries().size() );
  CHECK( 2 == chunk.multiplicity().interpolants()[0] );
  CHECK( 4 == chunk.multiplicity().boundaries()[0] );
  CHECK( 4 == chunk.multiplicity().energies().size() );
  CHECK( 4 == chunk.multiplicity().multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.multiplicity().energies()[0] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.multiplicity().energies()[1] ) );
  CHECK_THAT( 1.147e+7, WithinRel( chunk.multiplicity().energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.multiplicity().energies()[3] ) );
  CHECK_THAT( 0., WithinRel( chunk.multiplicity().multiplicities()[0] ) );
  CHECK_THAT( 8.45368e-11, WithinRel( chunk.multiplicity().multiplicities()[1] ) );
  CHECK_THAT( 6.622950e-8, WithinRel( chunk.multiplicity().multiplicities()[2] ) );
  CHECK_THAT( 2.149790e-1, WithinRel( chunk.multiplicity().multiplicities()[3] ) );

  auto law = std::get< DefinedElsewhere >( chunk.distribution() );

  CHECK( -15 == law.LAW() );

  CHECK( 4 == chunk.NC() );
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
