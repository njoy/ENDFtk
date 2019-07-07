#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
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

        REQUIRE( buffer == string );
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

        REQUIRE( buffer == string );
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

        REQUIRE_THROWS( MixedDistributions(  std::move( legendre ),
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

        REQUIRE_THROWS( MixedDistributions( begin, end, lineNumber,
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

  REQUIRE( 3 == chunk.LTT() );
  REQUIRE( 3 == chunk.LAW() );

  REQUIRE( 2 == chunk.NR() );
  REQUIRE( 4 == chunk.NE() );
  REQUIRE( 2 == chunk.interpolants().size() );
  REQUIRE( 2 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );
  REQUIRE( 5 == chunk.interpolants()[1] );
  REQUIRE( 2 == chunk.boundaries()[0] );
  REQUIRE( 4 == chunk.boundaries()[1] );

  auto distributions = chunk.angularDistributions();

  REQUIRE( 0 == distributions[0].index() );
  REQUIRE( 0 == distributions[1].index() );
  REQUIRE( 1 == distributions[2].index() );
  REQUIRE( 1 == distributions[3].index() );

  REQUIRE( 1e-5 == Approx( std::visit( [] (const auto& value) { return value.get().E(); }, distributions[0] ) ) );

  REQUIRE( 2 == chunk.legendre().NE() );
  REQUIRE( 1 == chunk.legendre().NR() );
  REQUIRE( 1 == chunk.legendre().interpolants().size() );
  REQUIRE( 1 == chunk.legendre().boundaries().size() );
  REQUIRE( 1 == chunk.legendre().interpolants()[0] );
  REQUIRE( 2 == chunk.legendre().boundaries()[0] );

  auto ldistributions = chunk.legendre().angularDistributions();

  auto ld = ldistributions[0];
  REQUIRE( 1e-5 == Approx( ld.E() ) );
  REQUIRE( 1e-5 == Approx( ld.incidentEnergy() ) );
  REQUIRE( 3 == ld.NL() );
  REQUIRE( 3 == ld.legendreOrder() );
  REQUIRE( 3 == ld.coefficients().size() );
  REQUIRE( 7.392510e-5  == Approx( ld.coefficients()[0] ) );
  REQUIRE( 8.477139e-9 == Approx( ld.coefficients()[1] ) );
  REQUIRE( 1.17106e-13 == Approx( ld.coefficients()[2] ) );

  ld = ldistributions[1];
  REQUIRE( 1e+6 == Approx( ld.E() ) );
  REQUIRE( 1e+6 == Approx( ld.incidentEnergy() ) );
  REQUIRE( 2 == ld.NL() );
  REQUIRE( 2 == ld.legendreOrder() );
  REQUIRE( 2 == ld.coefficients().size() );
  REQUIRE( 2.874390e-2   == Approx( ld.coefficients()[0] ) );
  REQUIRE( 3.19645e-11 == Approx( ld.coefficients()[1] ) );

  REQUIRE( 2 == chunk.tabulated().NE() );
  REQUIRE( 1 == chunk.tabulated().NR() );
  REQUIRE( 1 == chunk.tabulated().interpolants().size() );
  REQUIRE( 1 == chunk.tabulated().boundaries().size() );
  REQUIRE( 5 == chunk.tabulated().interpolants()[0] );
  REQUIRE( 2 == chunk.tabulated().boundaries()[0] );

  auto tdistributions = chunk.tabulated().angularDistributions();

  auto td = tdistributions[0];
  REQUIRE( 1e+6 == Approx( td.E() ) );
  REQUIRE( 1e+6 == Approx( td.incidentEnergy() ) );
  REQUIRE( 2 == td.NP() );
  REQUIRE( 1 == td.NR() );
  REQUIRE( 1 == td.boundaries().size() );
  REQUIRE( 1 == td.interpolants().size() );
  REQUIRE( 2 == td.boundaries()[0] );
  REQUIRE( 2 == td.interpolants()[0] );
  REQUIRE( 2 == td.cosines().size() );
  REQUIRE( -1.0  == Approx( td.cosines()[0] ) );
  REQUIRE( 1.0 == Approx( td.cosines()[1] ) );
  REQUIRE( 2 == td.probabilities().size() );
  REQUIRE( 0.5  == Approx( td.probabilities()[0] ) );
  REQUIRE( 0.5 == Approx( td.probabilities()[1] ) );

  td = tdistributions[1];
  REQUIRE( 2e+7 == Approx( td.E() ) );
  REQUIRE( 2e+7 == Approx( td.incidentEnergy() ) );
  REQUIRE( 3 == td.NP() );
  REQUIRE( 1 == td.NR() );
  REQUIRE( 1 == td.boundaries().size() );
  REQUIRE( 1 == td.interpolants().size() );
  REQUIRE( 3 == td.boundaries()[0] );
  REQUIRE( 2 == td.interpolants()[0] );
  REQUIRE( 3 == td.cosines().size() );
  REQUIRE( -1.0  == Approx( td.cosines()[0] ) );
  REQUIRE( 0.0 == Approx( td.cosines()[1] ) );
  REQUIRE( 1.0 == Approx( td.cosines()[2] ) );
  REQUIRE( 3 == td.probabilities().size() );
  REQUIRE( 0.0  == Approx( td.probabilities()[0] ) );
  REQUIRE( 1.0 == Approx( td.probabilities()[1] ) );
  REQUIRE( 0.0 == Approx( td.probabilities()[2] ) );

  REQUIRE( 14 == chunk.NC() );
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
