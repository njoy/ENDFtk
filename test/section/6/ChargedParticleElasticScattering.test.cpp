// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

    std::string string = chunk();

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

      ChargedParticleElasticScattering
        chunk( spin, lidp, std::move( boundaries ),
               std::move( interpolants ), std::move( sequence ) );

      THEN( "a ChargedParticleElasticScattering can "
            "be constructed and members can be tested" ) {

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

      ChargedParticleElasticScattering
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ChargedParticleElasticScattering can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
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
  CHECK_THAT( 0.5, WithinRel( chunk.SPI() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spin() ) );
  CHECK( true == chunk.LIDP() );
  CHECK( true == chunk.identicalParticles() );
  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberIncidentEnergies() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 1 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[1] ) );

  auto energies = chunk.distributions();

  auto subsection1 =
  std::get< NuclearAmplitudeExpansion >( energies[0] );
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
  CHECK( 4 == subsection1.A().size() );
  CHECK( 4 == subsection1.interferenceCoefficients().size() );
  CHECK_THAT( 5., WithinRel( subsection1.A()[0].real() ) );
  CHECK_THAT( 7., WithinRel( subsection1.A()[1].real() ) );
  CHECK_THAT( 9., WithinRel( subsection1.A()[2].real() ) );
  CHECK_THAT( 11., WithinRel( subsection1.A()[3].real() ) );
  CHECK_THAT( 6., WithinRel( subsection1.A()[0].imag() ) );
  CHECK_THAT( 8., WithinRel( subsection1.A()[1].imag() ) );
  CHECK_THAT( 10., WithinRel( subsection1.A()[2].imag() ) );
  CHECK_THAT( 12., WithinRel( subsection1.A()[3].imag() ) );
  CHECK_THAT( 5., WithinRel( subsection1.interferenceCoefficients()[0].real() ) );
  CHECK_THAT( 7., WithinRel( subsection1.interferenceCoefficients()[1].real() ) );
  CHECK_THAT( 9., WithinRel( subsection1.interferenceCoefficients()[2].real() ) );
  CHECK_THAT( 11., WithinRel( subsection1.interferenceCoefficients()[3].real() ) );
  CHECK_THAT( 6., WithinRel( subsection1.interferenceCoefficients()[0].imag() ) );
  CHECK_THAT( 8., WithinRel( subsection1.interferenceCoefficients()[1].imag() ) );
  CHECK_THAT( 10., WithinRel( subsection1.interferenceCoefficients()[2].imag() ) );
  CHECK_THAT( 12., WithinRel( subsection1.interferenceCoefficients()[3].imag() ) );

  auto subsection2 =
  std::get< NuclearPlusInterference >( energies[1] );
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
