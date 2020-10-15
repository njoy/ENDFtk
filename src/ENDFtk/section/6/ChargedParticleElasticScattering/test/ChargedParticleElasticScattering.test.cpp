#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ChargedParticleElasticScattering =
section::Type< 6 >::ChargedParticleElasticScattering;
using Variant =
section::Type< 6 >::ChargedParticleElasticScattering::Variant;
using LegendreCoefficients =
section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;
using NuclearAmplitudeExpansion =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;
using NuclearPlusInterference =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;

std::string chunk();
void verifyChunk( const ChargedParticleElasticScattering& );
std::string invalidLTP();

SCENARIO( "ChargedParticleElasticScattering" ) {

  GIVEN( "valid data for a ChargedParticleElasticScattering" ) {

    WHEN( "the data is given explicitly" ) {

      double spin = 0.5;
      long lidp = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< Variant > sequence = {
        NuclearAmplitudeExpansion( 1e-5, 3, { 1., 2., 3., 4. },
                                            { { 5., 6. }, { 7., 8. },
                                              { 9., 10. }, { 11., 12. } } ),
        NuclearPlusInterference( 2e+7, 15, {1., 3., 5. }, { 2., 4., 6.} ) };

      THEN( "a ChargedParticleElasticScattering can "
            "be constructed and members can be tested" ) {

        ChargedParticleElasticScattering
          chunk( spin, lidp, std::move( boundaries ),
                 std::move( interpolants ), std::move( sequence ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a ChargedParticleElasticScattering can "
            "be constructed and members can be tested" ) {

        ChargedParticleElasticScattering
          chunk(begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of ChargedParticleElasticScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    ChargedParticleElasticScattering chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        double spin = 0.5;
        long lidp = 1;
        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< Variant > sequence = {
          NuclearAmplitudeExpansion( 1e-5, 3, { 1., 2., 3., 4. },
                                              { { 5., 6. }, { 7., 8. },
                                                { 9., 10. }, { 11., 12. } } ),
          NuclearPlusInterference( 2e+7, 15, {1., 3., 5. }, { 2., 4., 6.} ) };

        CHECK_THROWS(
          ChargedParticleElasticScattering( spin, lidp,
                                            std::move( wrongBoundaries ),
                                            std::move( interpolants ),
                                            std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        double spin = 0.5;
        long lidp = 1;
        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< Variant > sequence = {
          NuclearAmplitudeExpansion( 1e-5, 3, { 1., 2., 3., 4. },
                                              { { 5., 6. }, { 7., 8. },
                                                { 9., 10. }, { 11., 12. } } ),
          NuclearPlusInterference( 2e+7, 15, {1., 3., 5. }, { 2., 4., 6.} ) };

        CHECK_THROWS(
          ChargedParticleElasticScattering( spin, lidp,
                                            std::move( boundaries ),
                                            std::move( wrongInterpolants ),
                                            std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        double spin = 0.5;
        long lidp = 1;
        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1, 2 };
        std::vector< Variant > wrongSequence = {
          NuclearAmplitudeExpansion( 1e-5, 3, { 1., 2., 3., 4. },
                                              { { 5., 6. }, { 7., 8. },
                                                { 9., 10. }, { 11., 12. } } ) };

        CHECK_THROWS(
          ChargedParticleElasticScattering( spin, lidp,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with an invalid LTP" ) {

      std::string string = invalidLTP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS(
          ChargedParticleElasticScattering( begin, end, lineNumber,
                                            9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000-1 0.000000+0          1          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          1          0         12          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7         15          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunk( const ChargedParticleElasticScattering& chunk ) {

  CHECK( 5 == chunk.LAW() );
  CHECK( 0.5 == Approx( chunk.SPI() ) );
  CHECK( 0.5 == Approx( chunk.spin() ) );
  CHECK( true == chunk.LIDP() );
  CHECK( true == chunk.identicalParticles() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  auto energies = chunk.subsections();

  auto subsection1 =
    std::get< NuclearAmplitudeExpansion >( energies[0] );
  CHECK( 1e-5 == Approx( subsection1.incidentEnergy() ) );
  CHECK( 1 == subsection1.LTP() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 3 == subsection1.NL() );
  CHECK( 4 == subsection1.scatteringCoefficients().size() );
  CHECK( 1. == Approx( subsection1.scatteringCoefficients()[0] ) );
  CHECK( 2. == Approx( subsection1.scatteringCoefficients()[1] ) );
  CHECK( 3. == Approx( subsection1.scatteringCoefficients()[2] ) );
  CHECK( 4. == Approx( subsection1.scatteringCoefficients()[3] ) );
  CHECK( 4 == subsection1.realInterferenceCoefficients().size() );
  CHECK( 5. == Approx( subsection1.realInterferenceCoefficients()[0] ) );
  CHECK( 7. == Approx( subsection1.realInterferenceCoefficients()[1] ) );
  CHECK( 9. == Approx( subsection1.realInterferenceCoefficients()[2] ) );
  CHECK( 11. == Approx( subsection1.realInterferenceCoefficients()[3] ) );
  CHECK( 4 == subsection1.imaginaryInterferenceCoefficients().size() );
  CHECK( 6. == Approx( subsection1.imaginaryInterferenceCoefficients()[0] ) );
  CHECK( 8. == Approx( subsection1.imaginaryInterferenceCoefficients()[1] ) );
  CHECK( 10. == Approx( subsection1.imaginaryInterferenceCoefficients()[2] ) );
  CHECK( 12. == Approx( subsection1.imaginaryInterferenceCoefficients()[3] ) );
  CHECK( 4 == subsection1.interferenceCoefficients().size() );
  CHECK( 5. == Approx( subsection1.interferenceCoefficients()[0].real() ) );
  CHECK( 7. == Approx( subsection1.interferenceCoefficients()[1].real() ) );
  CHECK( 9. == Approx( subsection1.interferenceCoefficients()[2].real() ) );
  CHECK( 11. == Approx( subsection1.interferenceCoefficients()[3].real() ) );
  CHECK( 6. == Approx( subsection1.interferenceCoefficients()[0].imag() ) );
  CHECK( 8. == Approx( subsection1.interferenceCoefficients()[1].imag() ) );
  CHECK( 10. == Approx( subsection1.interferenceCoefficients()[2].imag() ) );
  CHECK( 12. == Approx( subsection1.interferenceCoefficients()[3].imag() ) );

  auto subsection2 =
    std::get< NuclearPlusInterference >( energies[1] );
  CHECK( 2e+7 == Approx( subsection2.incidentEnergy() ) );
  CHECK( 15 == subsection2.LTP() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 3 == subsection2.NL() );
  CHECK( 3 == subsection2.MU().size() );
  CHECK( 3 == subsection2.cosines().size() );
  CHECK( 1. == Approx( subsection2.MU()[0] ) );
  CHECK( 3. == Approx( subsection2.MU()[1] ) );
  CHECK( 5. == Approx( subsection2.MU()[2] ) );
  CHECK( 1. == Approx( subsection2.cosines()[0] ) );
  CHECK( 3. == Approx( subsection2.cosines()[1] ) );
  CHECK( 5. == Approx( subsection2.cosines()[2] ) );
  CHECK( 3 == subsection2.PNI().size() );
  CHECK( 3 == subsection2.probabilities().size() );
  CHECK( 2. == Approx( subsection2.PNI()[0] ) );
  CHECK( 4. == Approx( subsection2.PNI()[1] ) );
  CHECK( 6. == Approx( subsection2.PNI()[2] ) );
  CHECK( 2. == Approx( subsection2.probabilities()[0] ) );
  CHECK( 4. == Approx( subsection2.probabilities()[1] ) );
  CHECK( 6. == Approx( subsection2.probabilities()[2] ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidLTP() {
  return
    " 5.000000-1 0.000000+0          1          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0         12          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7         15          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
