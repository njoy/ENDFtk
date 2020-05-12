#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DiscreteTwoBodyScattering = 
section::Type< 6 >::DiscreteTwoBodyScattering;
using SubSection = 
section::Type< 6 >::DiscreteTwoBodyScattering::SubSection;
using LegendreCoefficients = 
section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;
using Tabulated = 
section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated;

std::string chunk();
void verifyChunk( const DiscreteTwoBodyScattering& );
std::string invalidLANG();

SCENARIO( "DiscreteTwoBodyScattering" ) {

  GIVEN( "valid data for a DiscreteTwoBodyScattering" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< SubSection > sequence = {
        LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
        Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };
      
      THEN( "a DiscreteTwoBodyScattering can "
            "be constructed and members can be tested" ) {

        DiscreteTwoBodyScattering
          chunk( std::move( boundaries ), std::move( interpolants ),
                 std::move( sequence ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a DiscreteTwoBodyScattering can "
            "be constructed and members can be tested" ) {

        DiscreteTwoBodyScattering chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of DiscreteTwoBodyScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteTwoBodyScattering
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a DiscreteTwoBodyScattering" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< SubSection > sequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
          Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };

        REQUIRE_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongBoundaries ),
                                       std::move( interpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< SubSection > sequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
          Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };

        REQUIRE_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongInterpolants ),
                                       std::move( wrongInterpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< SubSection > wrongSequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ) };

        REQUIRE_THROWS(
            DiscreteTwoBodyScattering( std::move( boundaries ),
                                       std::move( interpolants ),
                                       std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LANG" ) {

      std::string string = invalidLANG();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ){
        REQUIRE_THROWS( DiscreteTwoBodyScattering( begin, end, lineNumber,
                        9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunk( const DiscreteTwoBodyScattering& chunk ) {

      REQUIRE( 2 == chunk.LAW() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 0 == energies[0].LANG() );
      REQUIRE( 4 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NL() );

      auto subsection1 =
           std::get< LegendreCoefficients >( energies[0].data() );
      REQUIRE( 0 == subsection1.LANG() );
      REQUIRE( 4 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NL() );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 1. == Approx( subsection1.coefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.coefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.coefficients()[3] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 12 == energies[1].LANG() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 3 == energies[1].NL() );

      auto subsection2 =
           std::get< Tabulated >( energies[1].data() );
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

      REQUIRE( 6 == chunk.NC() );
}

std::string invalidLANG() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          1          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

