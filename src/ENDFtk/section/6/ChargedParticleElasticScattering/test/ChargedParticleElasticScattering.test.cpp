#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ChargedParticleElasticScattering = 
section::Type< 6 >::ChargedParticleElasticScattering;
using SubSection = 
section::Type< 6 >::ChargedParticleElasticScattering::SubSection;
using LegendreCoefficients = 
section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;
using NuclearAmplitudeExpansion = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;
using NuclearPlusInterference = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;

std::string chunk();
std::string invalidLTP();

SCENARIO( "ChargedParticleElasticScattering" ) {

  GIVEN( "valid data for a "
         "ChargedParticleElasticScattering" ) {

    double spin = 0.5;
    long lidp = 1;
    std::vector< long > boundaries = { 2 };
    std::vector< long > interpolants = { 1 };
    std::vector< SubSection > sequence = {
      NuclearAmplitudeExpansion( 1e-5, 3, { 1., 2., 3., 4., 5., 6.,
                                              7., 8., 9., 10., 11., 12. } ),
      NuclearPlusInterference( 2e+7, 15, {1., 2., 3., 4., 5., 6.} )
    };

    THEN( "a ChargedParticleElasticScattering can "
          "be constructed and members can be tested" ) {
      ChargedParticleElasticScattering
        chunk( spin, lidp, std::move( boundaries ),
               std::move( interpolants ), std::move( sequence ) );

      REQUIRE( 5 == chunk.LAW() );
      REQUIRE( 0.5 == Approx( chunk.SPI() ) );
      REQUIRE( 0.5 == Approx( chunk.spin() ) );
      REQUIRE( true == chunk.LIDP() );
      REQUIRE( true == chunk.identicalParticles() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LTP() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 3 == energies[0].NL() );

      auto subsection1 =
      std::experimental::get< NuclearAmplitudeExpansion >( energies[0].data() );
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
      REQUIRE( 4 == subsection1.interferenceCoefficients().size() );
      REQUIRE( 5. == Approx( subsection1.interferenceCoefficients()[0].real() ) );
      REQUIRE( 7. == Approx( subsection1.interferenceCoefficients()[1].real() ) );
      REQUIRE( 9. == Approx( subsection1.interferenceCoefficients()[2].real() ) );
      REQUIRE( 11. == Approx( subsection1.interferenceCoefficients()[3].real() ) );
      REQUIRE( 6. == Approx( subsection1.interferenceCoefficients()[0].imag() ) );
      REQUIRE( 8. == Approx( subsection1.interferenceCoefficients()[1].imag() ) );
      REQUIRE( 10. == Approx( subsection1.interferenceCoefficients()[2].imag() ) );
      REQUIRE( 12. == Approx( subsection1.interferenceCoefficients()[3].imag() ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 15 == energies[1].LTP() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 3 == energies[1].NL() );

      auto subsection2 =
      std::experimental::get< NuclearPlusInterference >( energies[1].data() );
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

      REQUIRE( 7 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "ChargedParticleElasticScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a ChargedParticleElasticScattering can "
          "be constructed and members can be tested" ) {
      ChargedParticleElasticScattering
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 5 == chunk.LAW() );
      REQUIRE( 0.5 == Approx( chunk.SPI() ) );
      REQUIRE( 0.5 == Approx( chunk.spin() ) );
      REQUIRE( 1 == chunk.LIDP() );
      REQUIRE( 1 == chunk.identicalParticles() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LTP() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 3 == energies[0].NL() );

      auto subsection1 =
      std::experimental::get< NuclearAmplitudeExpansion >( energies[0].data() );
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
      REQUIRE( 4 == subsection1.interferenceCoefficients().size() );
      REQUIRE( 5. == Approx( subsection1.interferenceCoefficients()[0].real() ) );
      REQUIRE( 7. == Approx( subsection1.interferenceCoefficients()[1].real() ) );
      REQUIRE( 9. == Approx( subsection1.interferenceCoefficients()[2].real() ) );
      REQUIRE( 11. == Approx( subsection1.interferenceCoefficients()[3].real() ) );
      REQUIRE( 6. == Approx( subsection1.interferenceCoefficients()[0].imag() ) );
      REQUIRE( 8. == Approx( subsection1.interferenceCoefficients()[1].imag() ) );
      REQUIRE( 10. == Approx( subsection1.interferenceCoefficients()[2].imag() ) );
      REQUIRE( 12. == Approx( subsection1.interferenceCoefficients()[3].imag() ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 15 == energies[1].LTP() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 3 == energies[1].NL() );

      auto subsection2 =
      std::experimental::get< NuclearPlusInterference >( energies[1].data() );
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

      REQUIRE( 7 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of ChargedParticleElasticScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    ChargedParticleElasticScattering
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a ChargedParticleElasticScattering"
         " with an invalid LTP" ){
    std::string string = invalidLTP();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ) {
      REQUIRE_THROWS( ChargedParticleElasticScattering( begin, end, lineNumber,
                                                        9228, 6, 5 ) );
    }
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
