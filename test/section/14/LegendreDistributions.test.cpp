// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/14.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreDistributions = section::Type< 14 >::LegendreDistributions;
using LegendreCoefficients = section::Type< 14 >::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreDistributions& );
std::string invalidChunk();

SCENARIO( "LegendreDistributions" ) {

  GIVEN( "valid data for a LegendreDistributions" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1.0;
      double level = 2.0;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< LegendreCoefficients > sequence =
        { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
          { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

      LegendreDistributions chunk( energy, level,
                                   std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( sequence ) );

      THEN( "an LegendreDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LegendreDistributions chunk( begin, end, lineNumber, 9228, 14, 2 );

      THEN( "a LegendreDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreDistributions" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        double energy = 1.0;
        double level = 2.0;
        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< LegendreCoefficients > sequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

        CHECK_THROWS(
          LegendreDistributions( energy, level,
                                 std::move( wrongBoundaries ),
                                 std::move( interpolants ),
                                 std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        double energy = 1.0;
        double level = 2.0;
        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< LegendreCoefficients > sequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

        CHECK_THROWS(
          LegendreDistributions( energy, level,
                                 std::move( boundaries ),
                                 std::move( wrongInterpolants ),
                                 std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        double energy = 1.0;
        double level = 2.0;
        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< LegendreCoefficients > wrongSequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } } };

        CHECK_THROWS(
          LegendreDistributions( energy, level,
                                 std::move( boundaries ),
                                 std::move( interpolants ),
                                 std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (LIST takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreDistributions( begin, end, lineNumber,
                                              9228, 14, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 2.000000+0          0          0          1          2922814  2     \n"
    "          2          1                                            922814  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          0922814  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 922814  2     \n"
    " 0.000000+0 2.000000+7          0          0          2          0922814  2     \n"
    " 2.874390-2 3.19645-11                                            922814  2     \n";
}

void verifyChunk( const LegendreDistributions& chunk ) {

  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );
  CHECK( 1 == chunk.LTT() );
  CHECK( 1 == chunk.LAW() );

  CHECK_THAT( 1., WithinRel( chunk.EG() ) );
  CHECK_THAT( 1., WithinRel( chunk.photonEnergy() ) );
  CHECK_THAT( 2., WithinRel( chunk.ES() ) );
  CHECK_THAT( 2., WithinRel( chunk.levelEnergy() ) );

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

  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK( 2 == chunk.angularDistributions().size() );

  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[1] ) );

  auto distributions = chunk.angularDistributions();

  auto d = distributions[0];
  CHECK_THAT( 1e-5, WithinRel( d.E() ) );
  CHECK_THAT( 1e-5, WithinRel( d.incidentEnergy() ) );
  CHECK( 3 == d.NL() );
  CHECK( 3 == d.legendreOrder() );
  CHECK( 3 == d.coefficients().size() );
  CHECK_THAT( 7.392510e-5 , WithinRel( d.coefficients()[0] ) );
  CHECK_THAT( 8.477139e-9, WithinRel( d.coefficients()[1] ) );
  CHECK_THAT( 1.17106e-13, WithinRel( d.coefficients()[2] ) );

  d = distributions[1];
  CHECK_THAT( 2e+7, WithinRel( d.E() ) );
  CHECK_THAT( 2e+7, WithinRel( d.incidentEnergy() ) );
  CHECK( 2 == d.NL() );
  CHECK( 2 == d.legendreOrder() );
  CHECK( 2 == d.coefficients().size() );
  CHECK_THAT( 2.874390e-2  , WithinRel( d.coefficients()[0] ) );
  CHECK_THAT( 3.19645e-11, WithinRel( d.coefficients()[1] ) );

  CHECK( 6 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          3          2922814  2     \n"
    "          2          1                                            922814  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          0922814  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 922814  2     \n"
    " 0.000000+0 2.000000+7          0          0          2          0922814  2     \n"
    " 2.874390-2 3.19645-11                                            922814  2     \n";
}
