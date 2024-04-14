// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using MixedDistributions = section::Type< 4 >::MixedDistributions;
using LegendreDistributions = section::Type< 4 >::LegendreDistributions;
using LegendreCoefficients = section::Type< 4 >::LegendreCoefficients;
using TabulatedDistributions = section::Type< 4 >::TabulatedDistributions;
using TabulatedDistribution = section::Type< 4 >::TabulatedDistribution;

std::string chunk();
void verifyChunk( const MixedDistributions& );
std::string invalidChunk();

SCENARIO( "MixedDistributions" ) {

  GIVEN( "valid data for a MixedDistributions" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      LegendreDistributions legendre  =
        { { 2 }, { 1 },
      	  { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 1e+6, { 2.874390e-2, 3.19645e-11 } } } };
      TabulatedDistributions tabulated  =
        { { 2 }, { 5 },
          { { 1e+6, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } };

      MixedDistributions chunk( std::move( legendre ), std::move( tabulated ) );

      THEN( "a MixedDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      MixedDistributions chunk( begin, end, lineNumber, 9228, 4, 2 );

      THEN( "a MixedDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a MixedDistributions" ) {

    WHEN( "data for a MixedDistributions with a boundary mismatch is given" ) {

      LegendreDistributions legendre  =
        { { 2 }, { 1 },
      	  { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 1e+6, { 2.874390e-2, 3.19645e-11 } } } };
      TabulatedDistributions tabulated  =
        { { 2 }, { 5 },
          { { 1e+7, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedDistributions(  std::move( legendre ),
                                            std::move( tabulated ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a MixedDistributions with a "
          "boundary mismatch is given" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedDistributions( begin, end, lineNumber,
                                            9228, 4, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n"
    " 0.000000+0 1.000000+6          0          0          2          09228 4  2     \n"
    " 2.874390-2 3.19645-11                                            9228 4  2     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          5                                            9228 4  2     \n"
    " 0.000000+0 1.000000+6          0          0          1          29228 4  2     \n"
    "          2          2                                            9228 4  2     \n"
    "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}

void verifyChunk( const MixedDistributions& chunk ) {

  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );
  CHECK( 3 == chunk.LTT() );
  CHECK( 3 == chunk.LAW() );

  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberInterpolationRegions() );
  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );
  CHECK( 2 == chunk.INT().size() );
  CHECK( 2 == chunk.NBT().size() );
  CHECK( 1 == chunk.INT()[0] );
  CHECK( 5 == chunk.INT()[1] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 4 == chunk.NBT()[1] );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 5 == chunk.interpolants()[1] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );

  auto distributions = chunk.angularDistributions();

  CHECK( 0 == distributions[0].index() );
  CHECK( 0 == distributions[1].index() );
  CHECK( 1 == distributions[2].index() );
  CHECK( 1 == distributions[3].index() );

  auto getE = [] ( const auto& value ) { return value.get().E(); };
  auto getIE = [] ( const auto& value ) { return value.get().incidentEnergy(); };
  CHECK_THAT( 1e-5, WithinRel( std::visit( getE, distributions[0] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getE, distributions[1] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getE, distributions[2] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getE, distributions[3] ) ) );
  CHECK_THAT( 1e-5, WithinRel( std::visit( getIE, distributions[0] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getIE, distributions[1] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getIE, distributions[2] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getIE, distributions[3] ) ) );

  CHECK( 2 == chunk.legendre().NE() );
  CHECK( 2 == chunk.legendre().numberIncidentEnergies() );
  CHECK( 1 == chunk.legendre().NR() );
  CHECK( 1 == chunk.legendre().numberInterpolationRegions() );
  CHECK( 1 == chunk.legendre().INT().size() );
  CHECK( 1 == chunk.legendre().NBT().size() );
  CHECK( 1 == chunk.legendre().INT()[0] );
  CHECK( 2 == chunk.legendre().NBT()[0] );
  CHECK( 1 == chunk.legendre().interpolants().size() );
  CHECK( 1 == chunk.legendre().boundaries().size() );
  CHECK( 1 == chunk.legendre().interpolants()[0] );
  CHECK( 2 == chunk.legendre().boundaries()[0] );

  auto ldistributions = chunk.legendre().angularDistributions();

  auto ld = ldistributions[0];
  CHECK_THAT( 1e-5, WithinRel( ld.E() ) );
  CHECK_THAT( 1e-5, WithinRel( ld.incidentEnergy() ) );
  CHECK( 3 == ld.NL() );
  CHECK( 3 == ld.legendreOrder() );
  CHECK( 3 == ld.coefficients().size() );
  CHECK_THAT( 7.392510e-5 , WithinRel( ld.coefficients()[0] ) );
  CHECK_THAT( 8.477139e-9, WithinRel( ld.coefficients()[1] ) );
  CHECK_THAT( 1.17106e-13, WithinRel( ld.coefficients()[2] ) );

  ld = ldistributions[1];
  CHECK_THAT( 1e+6, WithinRel( ld.E() ) );
  CHECK_THAT( 1e+6, WithinRel( ld.incidentEnergy() ) );
  CHECK( 2 == ld.NL() );
  CHECK( 2 == ld.legendreOrder() );
  CHECK( 2 == ld.coefficients().size() );
  CHECK_THAT( 2.874390e-2  , WithinRel( ld.coefficients()[0] ) );
  CHECK_THAT( 3.19645e-11, WithinRel( ld.coefficients()[1] ) );

  CHECK( 2 == chunk.tabulated().NE() );
  CHECK( 2 == chunk.tabulated().numberIncidentEnergies() );
  CHECK( 1 == chunk.tabulated().NR() );
  CHECK( 1 == chunk.tabulated().numberInterpolationRegions() );
  CHECK( 1 == chunk.tabulated().INT().size() );
  CHECK( 1 == chunk.tabulated().NBT().size() );
  CHECK( 5 == chunk.tabulated().INT()[0] );
  CHECK( 2 == chunk.tabulated().NBT()[0] );
  CHECK( 1 == chunk.tabulated().interpolants().size() );
  CHECK( 1 == chunk.tabulated().boundaries().size() );
  CHECK( 5 == chunk.tabulated().interpolants()[0] );
  CHECK( 2 == chunk.tabulated().boundaries()[0] );

  auto tdistributions = chunk.tabulated().angularDistributions();

  auto td = tdistributions[0];
  CHECK_THAT( 1e+6, WithinRel( td.E() ) );
  CHECK_THAT( 1e+6, WithinRel( td.incidentEnergy() ) );
  CHECK( 2 == td.NP() );
  CHECK( 2 == td.numberPoints() );
  CHECK( 1 == td.NR() );
  CHECK( 1 == td.numberInterpolationRegions() );
  CHECK( 1 == td.NBT().size() );
  CHECK( 1 == td.INT().size() );
  CHECK( 2 == td.NBT()[0] );
  CHECK( 2 == td.INT()[0] );
  CHECK( 1 == td.boundaries().size() );
  CHECK( 1 == td.interpolants().size() );
  CHECK( 2 == td.boundaries()[0] );
  CHECK( 2 == td.interpolants()[0] );
  CHECK( 2 == td.cosines().size() );
  CHECK_THAT( -1.0 , WithinRel( td.cosines()[0] ) );
  CHECK_THAT( 1.0, WithinRel( td.cosines()[1] ) );
  CHECK( 2 == td.probabilities().size() );
  CHECK_THAT( 0.5 , WithinRel( td.probabilities()[0] ) );
  CHECK_THAT( 0.5, WithinRel( td.probabilities()[1] ) );

  td = tdistributions[1];
  CHECK_THAT( 2e+7, WithinRel( td.E() ) );
  CHECK_THAT( 2e+7, WithinRel( td.incidentEnergy() ) );
  CHECK( 3 == td.NP() );
  CHECK( 3 == td.numberPoints() );
  CHECK( 1 == td.NR() );
  CHECK( 1 == td.numberInterpolationRegions() );
  CHECK( 1 == td.NBT().size() );
  CHECK( 1 == td.INT().size() );
  CHECK( 3 == td.NBT()[0] );
  CHECK( 2 == td.INT()[0] );
  CHECK( 1 == td.boundaries().size() );
  CHECK( 1 == td.interpolants().size() );
  CHECK( 3 == td.boundaries()[0] );
  CHECK( 2 == td.interpolants()[0] );
  CHECK( 3 == td.cosines().size() );
  CHECK_THAT( -1.0 , WithinRel( td.cosines()[0] ) );
  CHECK_THAT( 0.0, WithinRel( td.cosines()[1] ) );
  CHECK_THAT( 1.0, WithinRel( td.cosines()[2] ) );
  CHECK( 3 == td.probabilities().size() );
  CHECK_THAT( 0.0 , WithinRel( td.probabilities()[0] ) );
  CHECK_THAT( 1.0, WithinRel( td.probabilities()[1] ) );
  CHECK_THAT( 0.0, WithinRel( td.probabilities()[2] ) );

  CHECK( 14 == chunk.NC() );
}

std::string invalidChunk() {
  return
  " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
  "          2          1                                            9228 4  2     \n"
  " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
  " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n"
  " 0.000000+0 1.000000+6          0          0          2          09228 4  2     \n"
  " 2.874390-2 3.19645-11                                            9228 4  2     \n"
  " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
  "          2          5                                            9228 4  2     \n"
  " 0.000000+0 1.000000+7          0          0          1          29228 4  2     \n"
  "          2          2                                            9228 4  2     \n"
  "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n"
  " 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n"
  "          3          2                                            9228 4  2     \n"
  "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}
