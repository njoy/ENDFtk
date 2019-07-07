#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Isotropic = section::Type< 4 >::Isotropic;
using MixedDistributions = section::Type< 4 >::MixedDistributions;
using LegendreDistributions = section::Type< 4 >::LegendreDistributions;
using LegendreCoefficients = section::Type< 4 >::LegendreCoefficients;
using TabulatedDistributions = section::Type< 4 >::TabulatedDistributions;
using TabulatedDistribution = section::Type< 4 >::TabulatedDistribution;

std::string chunkWithLTT0();
void verifyChunkWithLTT0( const section::Type< 4 >& );
std::string chunkWithLTT1();
void verifyChunkWithLTT1( const section::Type< 4 >& );
std::string chunkWithLTT2();
void verifyChunkWithLTT2( const section::Type< 4 >& );
std::string chunkWithLTT3();
void verifyChunkWithLTT3( const section::Type< 4 >& );
std::string chunkWithInvalidLTT();
std::string chunkWithBadBoundary();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 4 >" ) {

  GIVEN( "valid data for a section::Type< 4 > with LTT=0" ) {

    std::string sectionString = chunkWithLTT0() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      int lct = 1;
      double za = 92235.;
      double awr = 2.330250e+2;

      auto distribution = Isotropic();

      section::Type< 4 > chunk( mt, za, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 4 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=1" ) {

    std::string sectionString = chunkWithLTT1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      double za = 92235.;
      double awr = 2.330250e+2;

      LegendreDistributions distribution =
        { { 2 }, { 1 },
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } } };

      section::Type< 4 > chunk( mt, za, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 4 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=2" ) {

    std::string sectionString = chunkWithLTT2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      double za = 92235.;
      double awr = 2.330250e+2;

      TabulatedDistributions distribution =
        { { 2 }, { 1 },
          { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } };

      section::Type< 4 > chunk( mt, za, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 4 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=3" ) {

    std::string sectionString = chunkWithLTT3() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      double za = 92235.;
      double awr = 2.330250e+2;

      MixedDistributions distribution =
        { { { 2 }, { 1 },
            { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
              { 1e+6, { 2.874390e-2, 3.19645e-11 } } } },
          { { 2 }, { 5 },
            { { 1e+6, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
              { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } } };

      section::Type< 4 > chunk( mt, za, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 4 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 4 >" ) {

    WHEN( "a string representation of a section::Type< 4 > with an "
          "invalid LTT" ) {

      std::string sectionString = chunkWithInvalidLTT() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 4 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 4 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunkWithLTT0() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 4 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLTT0() {
  return
    " 9.223500+4 2.330250+2          0          0          0          09228 4 18     \n"
    " 0.000000+0 2.330250+2          1          1          0          09228 4 18     \n";
}

void verifyChunkWithLTT0( const section::Type< 4 >& chunk ) {

  REQUIRE( 18 == chunk.MT() );
  REQUIRE( 18 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );

  REQUIRE( 1 == chunk.LCT() );
  REQUIRE( 1 == chunk.referenceFrame() );
  REQUIRE( 0 == chunk.LTT() );
  REQUIRE( 0 == chunk.LAW() );
  REQUIRE( true == chunk.LI() );
  REQUIRE( true == chunk.isotropicAngularDistributions() );

  const auto& distribution =
                  std::experimental::get< Isotropic >( chunk.distributions() );
  REQUIRE( 0 == distribution.LTT() );
  REQUIRE( 0 == distribution.LAW() );

  REQUIRE( 2 == chunk.NC() );
}

std::string chunkWithLTT1() {
  return
    " 9.223500+4 2.330250+2          0          1          0          09228 4  2     \n"
    " 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n"
    " 2.874390-2 3.19645-11                                            9228 4  2     \n";
}

void verifyChunkWithLTT1( const section::Type< 4 >& chunk ) {

  REQUIRE( 2 == chunk.MT() );
  REQUIRE( 2 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );

  REQUIRE( 1 == chunk.LCT() );
  REQUIRE( 1 == chunk.referenceFrame() );
  REQUIRE( 1 == chunk.LTT() );
  REQUIRE( 1 == chunk.LAW() );
  REQUIRE( false == chunk.LI() );
  REQUIRE( false == chunk.isotropicAngularDistributions() );

  const auto& distribution =
    std::experimental::get< LegendreDistributions >( chunk.distributions() );

  REQUIRE( 1 == distribution.LTT() );
  REQUIRE( 1 == distribution.LAW() );

  REQUIRE( 2 == distribution.NE() );
  REQUIRE( 1 == distribution.NR() );
  REQUIRE( 1 == distribution.interpolants().size() );
  REQUIRE( 1 == distribution.boundaries().size() );
  REQUIRE( 1 == distribution.interpolants()[0] );
  REQUIRE( 2 == distribution.boundaries()[0] );

  auto distributions = distribution.angularDistributions();

  auto d = distributions[0];
  REQUIRE( 1e-5 == Approx( d.E() ) );
  REQUIRE( 1e-5 == Approx( d.incidentEnergy() ) );
  REQUIRE( 3 == d.NL() );
  REQUIRE( 3 == d.legendreOrder() );
  REQUIRE( 3 == d.coefficients().size() );
  REQUIRE( 7.392510e-5  == Approx( d.coefficients()[0] ) );
  REQUIRE( 8.477139e-9 == Approx( d.coefficients()[1] ) );
  REQUIRE( 1.17106e-13 == Approx( d.coefficients()[2] ) );

  d = distributions[1];
  REQUIRE( 2e+7 == Approx( d.E() ) );
  REQUIRE( 2e+7 == Approx( d.incidentEnergy() ) );
  REQUIRE( 2 == d.NL() );
  REQUIRE( 2 == d.legendreOrder() );
  REQUIRE( 2 == d.coefficients().size() );
  REQUIRE( 2.874390e-2   == Approx( d.coefficients()[0] ) );
  REQUIRE( 3.19645e-11 == Approx( d.coefficients()[1] ) );

  REQUIRE( 8 == chunk.NC() );
}

std::string chunkWithLTT2() {
  return
    " 9.223500+4 2.330250+2          0          2          0          09228 4  2     \n"
    " 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          1          29228 4  2     \n"
    "          2          2                                            9228 4  2     \n"
    "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}

void verifyChunkWithLTT2( const section::Type< 4 >& chunk ) {

  REQUIRE( 2 == chunk.MT() );
  REQUIRE( 2 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );

  REQUIRE( 1 == chunk.LCT() );
  REQUIRE( 1 == chunk.referenceFrame() );
  REQUIRE( 2 == chunk.LTT() );
  REQUIRE( 2 == chunk.LAW() );
  REQUIRE( false == chunk.LI() );
  REQUIRE( false == chunk.isotropicAngularDistributions() );

  const auto& distribution =
    std::experimental::get< TabulatedDistributions >( chunk.distributions() );

  REQUIRE( 2 == distribution.LTT() );
  REQUIRE( 2 == distribution.LAW() );

  REQUIRE( 2 == distribution.NE() );
  REQUIRE( 1 == distribution.NR() );
  REQUIRE( 1 == distribution.interpolants().size() );
  REQUIRE( 1 == distribution.boundaries().size() );
  REQUIRE( 1 == distribution.interpolants()[0] );
  REQUIRE( 2 == distribution.boundaries()[0] );

  auto distributions = distribution.angularDistributions();

  auto d = distributions[0];
  REQUIRE( 1e-5 == Approx( d.E() ) );
  REQUIRE( 1e-5 == Approx( d.incidentEnergy() ) );
  REQUIRE( 2 == d.NP() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 2 == d.boundaries()[0] );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 2 == d.cosines().size() );
  REQUIRE( -1.0  == Approx( d.cosines()[0] ) );
  REQUIRE( 1.0 == Approx( d.cosines()[1] ) );
  REQUIRE( 2 == d.probabilities().size() );
  REQUIRE( 0.5  == Approx( d.probabilities()[0] ) );
  REQUIRE( 0.5 == Approx( d.probabilities()[1] ) );

  d = distributions[1];
  REQUIRE( 2e+7 == Approx( d.E() ) );
  REQUIRE( 2e+7 == Approx( d.incidentEnergy() ) );
  REQUIRE( 3 == d.NP() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 3 == d.boundaries()[0] );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 3 == d.cosines().size() );
  REQUIRE( -1.0  == Approx( d.cosines()[0] ) );
  REQUIRE( 0.0 == Approx( d.cosines()[1] ) );
  REQUIRE( 1.0 == Approx( d.cosines()[2] ) );
  REQUIRE( 3 == d.probabilities().size() );
  REQUIRE( 0.0  == Approx( d.probabilities()[0] ) );
  REQUIRE( 1.0 == Approx( d.probabilities()[1] ) );
  REQUIRE( 0.0 == Approx( d.probabilities()[2] ) );

  REQUIRE( 10 == chunk.NC() );
}

std::string chunkWithLTT3() {
  return
    " 9.223500+4 2.330250+2          0          3          0          09228 4  2     \n"
    " 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n"
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

void verifyChunkWithLTT3( const section::Type< 4 >& chunk ) {

  REQUIRE( 2 == chunk.MT() );
  REQUIRE( 2 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );

  REQUIRE( 1 == chunk.LCT() );
  REQUIRE( 1 == chunk.referenceFrame() );
  REQUIRE( 3 == chunk.LTT() );
  REQUIRE( 3 == chunk.LAW() );
  REQUIRE( false == chunk.LI() );
  REQUIRE( false == chunk.isotropicAngularDistributions() );

  const auto& distribution =
    std::experimental::get< MixedDistributions >( chunk.distributions() );

  REQUIRE( 3 == distribution.LTT() );
  REQUIRE( 3 == distribution.LAW() );

  REQUIRE( 2 == distribution.NR() );
  REQUIRE( 4 == distribution.NE() );
  REQUIRE( 2 == distribution.interpolants().size() );
  REQUIRE( 2 == distribution.boundaries().size() );
  REQUIRE( 1 == distribution.interpolants()[0] );
  REQUIRE( 5 == distribution.interpolants()[1] );
  REQUIRE( 2 == distribution.boundaries()[0] );
  REQUIRE( 4 == distribution.boundaries()[1] );

  REQUIRE( 2 == distribution.legendre().NE() );
  REQUIRE( 1 == distribution.legendre().NR() );
  REQUIRE( 1 == distribution.legendre().interpolants().size() );
  REQUIRE( 1 == distribution.legendre().boundaries().size() );
  REQUIRE( 1 == distribution.legendre().interpolants()[0] );
  REQUIRE( 2 == distribution.legendre().boundaries()[0] );

  auto ldistributions = distribution.legendre().angularDistributions();

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

  REQUIRE( 2 == distribution.tabulated().NE() );
  REQUIRE( 1 == distribution.tabulated().NR() );
  REQUIRE( 1 == distribution.tabulated().interpolants().size() );
  REQUIRE( 1 == distribution.tabulated().boundaries().size() );
  REQUIRE( 5 == distribution.tabulated().interpolants()[0] );
  REQUIRE( 2 == distribution.tabulated().boundaries()[0] );

  auto tdistributions = distribution.tabulated().angularDistributions();

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

  REQUIRE( 16 == chunk.NC() );
}

std::string chunkWithInvalidLTT() {
  return
    " 9.223500+4 2.330250+2          0          4          0          09228 4 18     \n"
    " 0.000000+0 2.330250+2          1          1          0          09228 4 18     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 4  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 4  4     \n";
}
