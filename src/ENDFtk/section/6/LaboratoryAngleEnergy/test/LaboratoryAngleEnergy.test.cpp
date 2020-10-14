#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LaboratoryAngleEnergy =
section::Type< 6 >::LaboratoryAngleEnergy;
using AngularDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::AngularDistribution;
using EnergyDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::EnergyDistribution;

std::string chunk();
void verifyChunk( const LaboratoryAngleEnergy& );
std::string invalidChunk();

SCENARIO( "LaboratoryAngleEnergy" ) {

  GIVEN( "valid data for a LaboratoryAngleEnergy" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< AngularDistribution > energies =
        { AngularDistribution(
            1e-5, { 2 }, { 4 },
            { EnergyDistribution( 1.0, { 4 }, { 2 },
                                                { 1e-5, 1.1e+7, 1.147e+7,
                                                  3e+7 },
                                                { 0., 2., 4., 6. } ),
              EnergyDistribution( -1.0, { 3 }, { 2 },
                                                { 1e-5, 1e+6, 3e+7 },
                                                { 6., 4., 2. } ) } ),
          AngularDistribution(
            2e+7, { 2 }, { 4 },
            { EnergyDistribution( 0.9, { 4 }, { 2 },
                                                { 1e-5, 1.1e+7, 1.147e+7,
                                                  3e+7 },
                                                { 1., 3., 5., 7. } ),
              EnergyDistribution( -0.9, { 3 }, { 2 },
                                                { 1e-5, 1e+6, 3e+7 },
                                                { 5., 3., 1. } ) } ) };

      LaboratoryAngleEnergy chunk( std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( energies ) );

      THEN( "a LaboratoryAngleEnergy can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
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

      LaboratoryAngleEnergy chunk(begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a LaboratoryAngleEnergy can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a AngularDistribution" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< AngularDistribution > energies =
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
                                    { 5., 3., 1. } ) } ) };

        CHECK_THROWS( LaboratoryAngleEnergy( std::move( wrongBoundaries ),
                                               std::move( interpolants ),
                                               std::move( energies ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< AngularDistribution > energies =
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
                                    { 5., 3., 1. } ) } ) };

        CHECK_THROWS( LaboratoryAngleEnergy( std::move( boundaries ),
                                               std::move( wrongInterpolants ),
                                               std::move( energies ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< AngularDistribution > wrongEnergies =
          { AngularDistribution(
              1e-5, { 2 }, { 4 },
              { EnergyDistribution( 1.0, { 4 }, { 2 },
                                    { 1e-5, 1.1e+7, 1.147e+7, 3e+7 },
                                    { 0., 2., 4., 6. } ),
                EnergyDistribution( -1.0, { 3 }, { 2 },
                                    { 1e-5, 1e+6, 3e+7 },
                                    { 6., 4., 2. } ) } ) };

        CHECK_THROWS( LaboratoryAngleEnergy( std::move( boundaries ),
                                               std::move( interpolants ),
                                               std::move( wrongEnergies ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LaboratoryAngleEnergy( begin, end, lineNumber,
                                               9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
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

void verifyChunk( const LaboratoryAngleEnergy& chunk ) {

  CHECK( 7 == chunk.LAW() );

  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  CHECK( 1e-5 == Approx( chunk.angularDistributions()[0].E() ) );
  CHECK( 1e-5 == Approx( chunk.angularDistributions()[0].incidentEnergy() ) );

  CHECK( 2 == chunk.angularDistributions()[0].NMU() );
  CHECK( 1 == chunk.angularDistributions()[0].NRM() );
  CHECK( 1 == chunk.angularDistributions()[0].interpolants().size() );
  CHECK( 1 == chunk.angularDistributions()[0].boundaries().size() );
  CHECK( 4 == chunk.angularDistributions()[0].interpolants()[0] );
  CHECK( 2 == chunk.angularDistributions()[0].boundaries()[0] );

  auto cosines = chunk.angularDistributions()[0].energyDistributions();
  CHECK( 2 == cosines.size() );

  CHECK( 1. == Approx( cosines[0].MU() ) );
  CHECK( 1. == Approx( cosines[0].cosine() ) );
  CHECK( 1 == cosines[0].NRP() );
  CHECK( 4 == cosines[0].NEP() );
  CHECK( 1 == cosines[0].interpolants().size() );
  CHECK( 1 == cosines[0].boundaries().size() );
  CHECK( 2 == cosines[0].interpolants()[0] );
  CHECK( 4 == cosines[0].boundaries()[0] );
  CHECK( 4 == cosines[0].EP().size() );
  CHECK( 4 == cosines[0].energies().size() );
  CHECK( 4 == cosines[0].F().size() );
  CHECK( 4 == cosines[0].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[0].EP()[0] ) );
  CHECK( 1.1e+7 == Approx( cosines[0].EP()[1] ) );
  CHECK( 1.147e+7 == Approx( cosines[0].EP()[2] ) );
  CHECK( 3e+7 == Approx( cosines[0].EP()[3] ) );
  CHECK( 1e-5 == Approx( cosines[0].energies()[0] ) );
  CHECK( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
  CHECK( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
  CHECK( 3e+7 == Approx( cosines[0].energies()[3] ) );
  CHECK( 0. == Approx( cosines[0].F()[0] ) );
  CHECK( 2. == Approx( cosines[0].F()[1] ) );
  CHECK( 4. == Approx( cosines[0].F()[2] ) );
  CHECK( 6. == Approx( cosines[0].F()[3] ) );
  CHECK( 0. == Approx( cosines[0].probabilities()[0] ) );
  CHECK( 2. == Approx( cosines[0].probabilities()[1] ) );
  CHECK( 4. == Approx( cosines[0].probabilities()[2] ) );
  CHECK( 6. == Approx( cosines[0].probabilities()[3] ) );

  CHECK( -1. == Approx( cosines[1].cosine() ) );
  CHECK( 1 == cosines[1].NRP() );
  CHECK( 3 == cosines[1].NEP() );
  CHECK( 1 == cosines[1].interpolants().size() );
  CHECK( 1 == cosines[1].boundaries().size() );
  CHECK( 2 == cosines[1].interpolants()[0] );
  CHECK( 3 == cosines[1].boundaries()[0] );
  CHECK( 3 == cosines[1].EP().size() );
  CHECK( 3 == cosines[1].energies().size() );
  CHECK( 3 == cosines[1].F().size() );
  CHECK( 3 == cosines[1].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[1].EP()[0] ) );
  CHECK( 1e+6 == Approx( cosines[1].EP()[1] ) );
  CHECK( 3e+7 == Approx( cosines[1].EP()[2] ) );
  CHECK( 1e-5 == Approx( cosines[1].energies()[0] ) );
  CHECK( 1e+6 == Approx( cosines[1].energies()[1] ) );
  CHECK( 3e+7 == Approx( cosines[1].energies()[2] ) );
  CHECK( 6. == Approx( cosines[1].F()[0] ) );
  CHECK( 4. == Approx( cosines[1].F()[1] ) );
  CHECK( 2. == Approx( cosines[1].F()[2] ) );
  CHECK( 6. == Approx( cosines[1].probabilities()[0] ) );
  CHECK( 4. == Approx( cosines[1].probabilities()[1] ) );
  CHECK( 2. == Approx( cosines[1].probabilities()[2] ) );

  CHECK( 2e+7 == Approx( chunk.angularDistributions()[1].E() ) );
  CHECK( 2e+7 == Approx( chunk.angularDistributions()[1].incidentEnergy() ) );

  CHECK( 2 == chunk.angularDistributions()[1].NMU() );
  CHECK( 1 == chunk.angularDistributions()[1].NRM() );
  CHECK( 1 == chunk.angularDistributions()[1].interpolants().size() );
  CHECK( 1 == chunk.angularDistributions()[1].boundaries().size() );
  CHECK( 4 == chunk.angularDistributions()[1].interpolants()[0] );
  CHECK( 2 == chunk.angularDistributions()[1].boundaries()[0] );

  cosines = chunk.angularDistributions()[1].energyDistributions();
  CHECK( 2 == cosines.size() );

  CHECK( .9 == Approx( cosines[0].cosine() ) );
  CHECK( 1 == cosines[0].NRP() );
  CHECK( 4 == cosines[0].NEP() );
  CHECK( 1 == cosines[0].interpolants().size() );
  CHECK( 1 == cosines[0].boundaries().size() );
  CHECK( 2 == cosines[0].interpolants()[0] );
  CHECK( 4 == cosines[0].boundaries()[0] );
  CHECK( 4 == cosines[0].EP().size() );
  CHECK( 4 == cosines[0].energies().size() );
  CHECK( 4 == cosines[0].F().size() );
  CHECK( 4 == cosines[0].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[0].EP()[0] ) );
  CHECK( 1.1e+7 == Approx( cosines[0].EP()[1] ) );
  CHECK( 1.147e+7 == Approx( cosines[0].EP()[2] ) );
  CHECK( 3e+7 == Approx( cosines[0].EP()[3] ) );
  CHECK( 1e-5 == Approx( cosines[0].energies()[0] ) );
  CHECK( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
  CHECK( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
  CHECK( 3e+7 == Approx( cosines[0].energies()[3] ) );
  CHECK( 1. == Approx( cosines[0].F()[0] ) );
  CHECK( 3. == Approx( cosines[0].F()[1] ) );
  CHECK( 5. == Approx( cosines[0].F()[2] ) );
  CHECK( 7. == Approx( cosines[0].F()[3] ) );
  CHECK( 1. == Approx( cosines[0].probabilities()[0] ) );
  CHECK( 3. == Approx( cosines[0].probabilities()[1] ) );
  CHECK( 5. == Approx( cosines[0].probabilities()[2] ) );
  CHECK( 7. == Approx( cosines[0].probabilities()[3] ) );

  CHECK( -.9 == Approx( cosines[1].cosine() ) );
  CHECK( 1 == cosines[1].NRP() );
  CHECK( 3 == cosines[1].NEP() );
  CHECK( 1 == cosines[1].interpolants().size() );
  CHECK( 1 == cosines[1].boundaries().size() );
  CHECK( 2 == cosines[1].interpolants()[0] );
  CHECK( 3 == cosines[1].boundaries()[0] );
  CHECK( 3 == cosines[1].EP().size() );
  CHECK( 3 == cosines[1].energies().size() );
  CHECK( 3 == cosines[1].F().size() );
  CHECK( 3 == cosines[1].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[1].EP()[0] ) );
  CHECK( 1e+6 == Approx( cosines[1].EP()[1] ) );
  CHECK( 3e+7 == Approx( cosines[1].EP()[2] ) );
  CHECK( 1e-5 == Approx( cosines[1].energies()[0] ) );
  CHECK( 1e+6 == Approx( cosines[1].energies()[1] ) );
  CHECK( 3e+7 == Approx( cosines[1].energies()[2] ) );
  CHECK( 5. == Approx( cosines[1].F()[0] ) );
  CHECK( 3. == Approx( cosines[1].F()[1] ) );
  CHECK( 1. == Approx( cosines[1].F()[2] ) );
  CHECK( 5. == Approx( cosines[1].probabilities()[0] ) );
  CHECK( 3. == Approx( cosines[1].probabilities()[1] ) );
  CHECK( 1. == Approx( cosines[1].probabilities()[2] ) );

  CHECK( 20 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          49228 6  5     \n"
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
