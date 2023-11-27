// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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
using TabulatedDistribution =
section::Type< 6 >::DiscreteTwoBodyScattering::TabulatedDistribution;

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
        TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

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
          TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

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
          TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

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

      CHECK( 2 == chunk.E().size() );
      CHECK( 2 == chunk.incidentEnergies().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.E()[0] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.E()[1] ) );
      CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[1] ) );

      auto energies = chunk.distributions();

      auto subsection1 = std::get< LegendreCoefficients >( energies[0] );
      CHECK_THAT( 1e-5, WithinRel( subsection1.E() ) );
      CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
      CHECK( 0 == subsection1.LANG() );
      CHECK( 4 == subsection1.NW() );
      CHECK( 4 == subsection1.NL() );
      CHECK( 4 == subsection1.A().size() );
      CHECK( 4 == subsection1.coefficients().size() );
      CHECK_THAT( 1., WithinRel( subsection1.A()[0] ) );
      CHECK_THAT( 2., WithinRel( subsection1.A()[1] ) );
      CHECK_THAT( 3., WithinRel( subsection1.A()[2] ) );
      CHECK_THAT( 4., WithinRel( subsection1.A()[3] ) );
      CHECK_THAT( 1., WithinRel( subsection1.coefficients()[0] ) );
      CHECK_THAT( 2., WithinRel( subsection1.coefficients()[1] ) );
      CHECK_THAT( 3., WithinRel( subsection1.coefficients()[2] ) );
      CHECK_THAT( 4., WithinRel( subsection1.coefficients()[3] ) );

      auto subsection2 = std::get< TabulatedDistribution >( energies[1] );
      CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
      CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
      CHECK( 12 == subsection2.LANG() );
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
      CHECK( 3 == subsection2.F().size() );
      CHECK( 3 == subsection2.probabilities().size() );
      CHECK_THAT( 2., WithinRel( subsection2.F()[0] ) );
      CHECK_THAT( 4., WithinRel( subsection2.F()[1] ) );
      CHECK_THAT( 6., WithinRel( subsection2.F()[2] ) );
      CHECK_THAT( 2., WithinRel( subsection2.probabilities()[0] ) );
      CHECK_THAT( 4., WithinRel( subsection2.probabilities()[1] ) );
      CHECK_THAT( 6., WithinRel( subsection2.probabilities()[2] ) );

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
