#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscreteTwoBodyScattering =
section::Type< 6 >::DiscreteTwoBodyScattering;
using Variant =
section::Type< 6 >::DiscreteTwoBodyScattering::Variant;
using LegendreCoefficients =
section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;
using Tabulated =
section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated;

std::string chunk();
void verifyChunk( const DiscreteTwoBodyScattering& );
std::string invalidLANG();

SCENARIO( "DiscreteTwoBodyScattering" ) {

  GIVEN( "valid data for a DiscreteTwoBodyScattering" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< Variant > sequence = {
        LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
        Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };

      DiscreteTwoBodyScattering
        chunk( std::move( boundaries ), std::move( interpolants ),
               std::move( sequence ) );

      THEN( "a DiscreteTwoBodyScattering can "
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

      DiscreteTwoBodyScattering chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a DiscreteTwoBodyScattering can "
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

  GIVEN( "invalid data for a DiscreteTwoBodyScattering" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< Variant > sequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
          Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };

        CHECK_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongBoundaries ),
                                       std::move( interpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< Variant > sequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ),
          Tabulated( 2e+7, 12, {1., 2., 3., 4., 5., 6.} ) };

        CHECK_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongInterpolants ),
                                       std::move( wrongInterpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< Variant > wrongSequence = {
          LegendreCoefficients( 1e-5, { 1., 2., 3., 4. } ) };

        CHECK_THROWS(
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

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( DiscreteTwoBodyScattering( begin, end, lineNumber,
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

      CHECK( 2 == chunk.LAW() );
      CHECK( 2 == chunk.NE() );
      CHECK( 1 == chunk.NR() );
      CHECK( 1 == chunk.interpolants().size() );
      CHECK( 1 == chunk.boundaries().size() );
      CHECK( 1 == chunk.interpolants()[0] );
      CHECK( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      auto subsection1 = std::get< LegendreCoefficients >( energies[0] );
      CHECK( 1e-5 == Approx( subsection1.energy() ) );
      CHECK( 0 == subsection1.LANG() );
      CHECK( 4 == subsection1.NW() );
      CHECK( 4 == subsection1.NL() );
      CHECK( 4 == subsection1.coefficients().size() );
      CHECK( 1. == Approx( subsection1.coefficients()[0] ) );
      CHECK( 2. == Approx( subsection1.coefficients()[1] ) );
      CHECK( 3. == Approx( subsection1.coefficients()[2] ) );
      CHECK( 4. == Approx( subsection1.coefficients()[3] ) );

      auto subsection2 = std::get< Tabulated >( energies[1] );
      CHECK( 2e+7 == Approx( subsection2.energy() ) );
      CHECK( 12 == subsection2.LANG() );
      CHECK( 6 == subsection2.NW() );
      CHECK( 3 == subsection2.NL() );
      CHECK( 3 == subsection2.cosines().size() );
      CHECK( 1. == Approx( subsection2.cosines()[0] ) );
      CHECK( 3. == Approx( subsection2.cosines()[1] ) );
      CHECK( 5. == Approx( subsection2.cosines()[2] ) );
      CHECK( 3 == subsection2.probabilities().size() );
      CHECK( 2. == Approx( subsection2.probabilities()[0] ) );
      CHECK( 4. == Approx( subsection2.probabilities()[1] ) );
      CHECK( 6. == Approx( subsection2.probabilities()[2] ) );

      CHECK( 6 == chunk.NC() );
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
