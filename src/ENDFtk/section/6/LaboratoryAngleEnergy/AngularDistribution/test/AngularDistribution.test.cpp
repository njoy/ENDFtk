#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using AngularDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::AngularDistribution;
using EnergyDistribution =
section::Type< 6 >::LaboratoryAngleEnergy::EnergyDistribution;

std::string chunk();
void verifyChunk( const AngularDistribution& );
std::string invalidChunk();

SCENARIO( "AngularDistribution" ) {

  GIVEN( "valid data for a "
         "AngularDistribution" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 4 };
      std::vector< EnergyDistribution >
        cosines = { EnergyDistribution(
                      1.0, { 4 }, { 2 },
                      { 1e-5, 1.1e+7, 1.147e+7, 3e+7 }, { 0., 2., 4., 6. } ),
                    EnergyDistribution(
                      -1.0, { 3 }, { 5 },
                      { 1e-5, 1e+6, 3e+7 }, { 6., 4., 2. } ) };

      THEN( "a AngularDistribution can be constructed and members can be "
            "tested" ) {

        AngularDistribution chunk( energy,
                                   std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( cosines ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a AngularDistribution can be constructed and members can be "
            "tested" ) {

        AngularDistribution chunk(begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of AngularDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    AngularDistribution
      chunk(begin, end, lineNumber, 9228, 6, 5 );

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

        double energy = 1e-5;
        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 4 };
        std::vector< EnergyDistribution >
          cosines = { EnergyDistribution(
                        1.0, { 4 }, { 2 },
                        { 1e-5, 1.1e+7, 1.147e+7, 3e+7 }, { 0., 2., 4., 6. } ),
                      EnergyDistribution(
                        -1.0, { 3 }, { 5 },
                        { 1e-5, 1e+6, 3e+7 }, { 6., 4., 2. } ) };

        CHECK_THROWS(
            AngularDistribution( energy,
                                 std::move( wrongBoundaries ),
                                 std::move( interpolants ),
                                 std::move( cosines ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        double energy = 1e-5;
        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 4, 2 };
        std::vector< EnergyDistribution >
          cosines = { EnergyDistribution(
                        1.0, { 4 }, { 2 },
                        { 1e-5, 1.1e+7, 1.147e+7, 3e+7 }, { 0., 2., 4., 6. } ),
                      EnergyDistribution(
                        -1.0, { 3 }, { 5 },
                        { 1e-5, 1e+6, 3e+7 }, { 6., 4., 2. } ) };

        CHECK_THROWS(
            AngularDistribution( energy,
                                 std::move( boundaries ),
                                 std::move( wrongInterpolants ),
                                 std::move( cosines ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        double energy = 1e-5;
        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 4 };
        std::vector< EnergyDistribution >
          wrongCosines =
              { EnergyDistribution(
                  1.0, { 4 }, { 2 },
                  { 1e-5, 1.1e+7, 1.147e+7, 3e+7 }, { 0., 2., 4., 6. } ) };

        CHECK_THROWS(
            AngularDistribution( energy,
                                 std::move( boundaries ),
                                 std::move( interpolants ),
                                 std::move( wrongCosines ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          AngularDistribution( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n"
    " 3.000000+7 6.000000+0                                            9228 6  5     \n"
    " 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n"
    "          3          5                                            9228 6  5     \n"
    " 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n";
}

void verifyChunk( const AngularDistribution& chunk ) {

  CHECK( 1e-5 == Approx( chunk.energy() ) );

  CHECK( 2 == chunk.NMU() );
  CHECK( 1 == chunk.NRM() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 4 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

      auto cosines = chunk.energyDistributions();
  CHECK( 2 == cosines.size() );

  CHECK( 1. == Approx( cosines[0].cosine() ) );
  CHECK( 1 == cosines[0].NRP() );
  CHECK( 4 == cosines[0].NEP() );
  CHECK( 1 == cosines[0].interpolants().size() );
  CHECK( 1 == cosines[0].boundaries().size() );
  CHECK( 2 == cosines[0].interpolants()[0] );
  CHECK( 4 == cosines[0].boundaries()[0] );
  CHECK( 4 == cosines[0].energies().size() );
  CHECK( 4 == cosines[0].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[0].energies()[0] ) );
  CHECK( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
  CHECK( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
  CHECK( 3e+7 == Approx( cosines[0].energies()[3] ) );
  CHECK( 0. == Approx( cosines[0].probabilities()[0] ) );
  CHECK( 2. == Approx( cosines[0].probabilities()[1] ) );
  CHECK( 4. == Approx( cosines[0].probabilities()[2] ) );
  CHECK( 6. == Approx( cosines[0].probabilities()[3] ) );

  CHECK( -1. == Approx( cosines[1].cosine() ) );
  CHECK( 1 == cosines[1].NRP() );
  CHECK( 3 == cosines[1].NEP() );
  CHECK( 1 == cosines[1].interpolants().size() );
  CHECK( 1 == cosines[1].boundaries().size() );
  CHECK( 5 == cosines[1].interpolants()[0] );
  CHECK( 3 == cosines[1].boundaries()[0] );
  CHECK( 3 == cosines[1].energies().size() );
  CHECK( 3 == cosines[1].probabilities().size() );
  CHECK( 1e-5 == Approx( cosines[1].energies()[0] ) );
  CHECK( 1e+6 == Approx( cosines[1].energies()[1] ) );
  CHECK( 3e+7 == Approx( cosines[1].energies()[2] ) );
  CHECK( 6. == Approx( cosines[1].probabilities()[0] ) );
  CHECK( 4. == Approx( cosines[1].probabilities()[1] ) );
  CHECK( 2. == Approx( cosines[1].probabilities()[2] ) );

  CHECK( 9 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 1.000000+0          0          0          1          59228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n"
    " 3.000000+7 6.000000+0                                            9228 6  5     \n"
    " 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n"
    "          3          5                                            9228 6  5     \n"
    " 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n";
}
