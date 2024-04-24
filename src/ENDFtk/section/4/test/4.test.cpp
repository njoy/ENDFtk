// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/4.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
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
      int zaid = 92235;
      double awr = 2.330250e+2;

      auto distribution = Isotropic();

      section::Type< 4 > chunk( mt, zaid, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
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

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 4, 18, std::string( sectionString ) );

      section::Type< 4 > chunk = section.parse< 4 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=1" ) {

    std::string sectionString = chunkWithLTT1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      int zaid = 92235;
      double awr = 2.330250e+2;

      LegendreDistributions distribution =
        { { 2 }, { 1 },
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } } };

      section::Type< 4 > chunk( mt, zaid, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
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

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 4, 2, std::string( sectionString ) );

      section::Type< 4 > chunk = section.parse< 4 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=2" ) {

    std::string sectionString = chunkWithLTT2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      int zaid = 92235;
      double awr = 2.330250e+2;

      TabulatedDistributions distribution =
        { { 2 }, { 1 },
          { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } };

      section::Type< 4 > chunk( mt, zaid, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
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

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 4, 2, std::string( sectionString ) );

      section::Type< 4 > chunk = section.parse< 4 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 4 > with LTT=3" ) {

    std::string sectionString = chunkWithLTT3() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      int lct = 1;
      int zaid = 92235;
      double awr = 2.330250e+2;

      MixedDistributions distribution =
        { { { 2 }, { 1 },
            { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
              { 1e+6, { 2.874390e-2, 3.19645e-11 } } } },
          { { 2 }, { 5 },
            { { 1e+6, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
              { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } } } };

      section::Type< 4 > chunk( mt, zaid, awr, lct, std::move( distribution ) );

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
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

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 4, 2, std::string( sectionString ) );

      section::Type< 4 > chunk = section.parse< 4 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
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

        CHECK_THROWS( section::Type< 4 >( head, begin, end,
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

        CHECK_THROWS( section::Type< 4 >( head, begin, end,
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

  CHECK( 18 == chunk.MT() );
  CHECK( 18 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.LCT() );
  CHECK( 1 == chunk.referenceFrame() );
  CHECK( 0 == chunk.LTT() );
  CHECK( 0 == chunk.LAW() );
  CHECK( true == chunk.LI() );
  CHECK( true == chunk.isotropicDistributions() );

  CHECK( 0 == chunk.NE() );
  CHECK( 0 == chunk.numberIncidentEnergies() );
  CHECK( 0 == chunk.NR() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == ranges::cpp20::distance( chunk.NBT() ) );
  CHECK( 0 == ranges::cpp20::distance( chunk.INT() ) );
  CHECK( 0 == ranges::cpp20::distance( chunk.boundaries() ) );
  CHECK( 0 == ranges::cpp20::distance( chunk.interpolants() ) );
  CHECK( 0 == ranges::cpp20::distance( chunk.incidentEnergies() ) );
  CHECK( 0 == ranges::cpp20::distance( chunk.angularDistributions() ) );

  const auto& distribution = std::get< Isotropic >( chunk.distributions() );
  CHECK( 0 == distribution.LTT() );
  CHECK( 0 == distribution.LAW() );

  CHECK( 2 == chunk.NC() );
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

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.LCT() );
  CHECK( 1 == chunk.referenceFrame() );
  CHECK( 1 == chunk.LTT() );
  CHECK( 1 == chunk.LAW() );
  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberIncidentEnergies() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == ranges::cpp20::distance( chunk.NBT() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.INT() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.boundaries() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.interpolants() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.incidentEnergies() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.angularDistributions() ) );

  CHECK( 1 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[1] ) );

  auto angulars = chunk.angularDistributions();
  CHECK( 0 == angulars[0].index() );
  CHECK( 0 == angulars[1].index() );

  auto getE = [] ( const auto& value ) { return value.get().E(); };
  auto getIE = [] ( const auto& value ) { return value.get().incidentEnergy(); };
  CHECK_THAT( 1e-5, WithinRel( std::visit( getE, angulars[0] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getE, angulars[1] ) ) );
  CHECK_THAT( 1e-5, WithinRel( std::visit( getIE, angulars[0] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getIE, angulars[1] ) ) );

  const auto& distribution =
    std::get< LegendreDistributions >( chunk.distributions() );

  CHECK( 1 == distribution.LTT() );
  CHECK( 1 == distribution.LAW() );

  CHECK( 2 == distribution.NE() );
  CHECK( 2 == distribution.numberIncidentEnergies() );
  CHECK( 1 == distribution.NR() );
  CHECK( 1 == distribution.numberInterpolationRegions() );
  CHECK( 1 == distribution.INT().size() );
  CHECK( 1 == distribution.NBT().size() );
  CHECK( 1 == distribution.INT()[0] );
  CHECK( 2 == distribution.NBT()[0] );
  CHECK( 1 == distribution.interpolants().size() );
  CHECK( 1 == distribution.boundaries().size() );
  CHECK( 1 == distribution.interpolants()[0] );
  CHECK( 2 == distribution.boundaries()[0] );

  auto distributions = distribution.angularDistributions();

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

  CHECK( 8 == chunk.NC() );
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

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.LCT() );
  CHECK( 1 == chunk.referenceFrame() );
  CHECK( 2 == chunk.LTT() );
  CHECK( 2 == chunk.LAW() );
  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberIncidentEnergies() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == ranges::cpp20::distance( chunk.NBT() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.INT() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.boundaries() ) );
  CHECK( 1 == ranges::cpp20::distance( chunk.interpolants() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.incidentEnergies() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.angularDistributions() ) );

  CHECK( 1 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[1] ) );

  auto angulars = chunk.angularDistributions();
  CHECK( 1 == angulars[0].index() );
  CHECK( 1 == angulars[1].index() );

  auto getE = [] ( const auto& value ) { return value.get().E(); };
  auto getIE = [] ( const auto& value ) { return value.get().incidentEnergy(); };
  CHECK_THAT( 1e-5, WithinRel( std::visit( getE, angulars[0] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getE, angulars[1] ) ) );
  CHECK_THAT( 1e-5, WithinRel( std::visit( getIE, angulars[0] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getIE, angulars[1] ) ) );

  const auto& distribution =
    std::get< TabulatedDistributions >( chunk.distributions() );

  CHECK( 2 == distribution.LTT() );
  CHECK( 2 == distribution.LAW() );

  CHECK( 2 == distribution.NE() );
  CHECK( 2 == distribution.numberIncidentEnergies() );
  CHECK( 1 == distribution.NR() );
  CHECK( 1 == distribution.numberInterpolationRegions() );
  CHECK( 1 == distribution.INT().size() );
  CHECK( 1 == distribution.NBT().size() );
  CHECK( 1 == distribution.INT()[0] );
  CHECK( 2 == distribution.NBT()[0] );
  CHECK( 1 == distribution.interpolants().size() );
  CHECK( 1 == distribution.boundaries().size() );
  CHECK( 1 == distribution.interpolants()[0] );
  CHECK( 2 == distribution.boundaries()[0] );

  auto distributions = distribution.angularDistributions();

  auto d = distributions[0];
  CHECK_THAT( 1e-5, WithinRel( d.E() ) );
  CHECK_THAT( 1e-5, WithinRel( d.incidentEnergy() ) );
  CHECK( 2 == d.NP() );
  CHECK( 2 == d.numberPoints() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 1 == d.INT().size() );
  CHECK( 2 == d.NBT()[0] );
  CHECK( 2 == d.INT()[0] );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 2 == d.boundaries()[0] );
  CHECK( 2 == d.interpolants()[0] );
  CHECK( 2 == d.cosines().size() );
  CHECK_THAT( -1.0 , WithinRel( d.cosines()[0] ) );
  CHECK_THAT( 1.0, WithinRel( d.cosines()[1] ) );
  CHECK( 2 == d.probabilities().size() );
  CHECK_THAT( 0.5 , WithinRel( d.probabilities()[0] ) );
  CHECK_THAT( 0.5, WithinRel( d.probabilities()[1] ) );

  d = distributions[1];
  CHECK_THAT( 2e+7, WithinRel( d.E() ) );
  CHECK_THAT( 2e+7, WithinRel( d.incidentEnergy() ) );
  CHECK( 3 == d.NP() );
  CHECK( 3 == d.numberPoints() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 1 == d.INT().size() );
  CHECK( 3 == d.NBT()[0] );
  CHECK( 2 == d.INT()[0] );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 3 == d.boundaries()[0] );
  CHECK( 2 == d.interpolants()[0] );
  CHECK( 3 == d.cosines().size() );
  CHECK_THAT( -1.0 , WithinRel( d.cosines()[0] ) );
  CHECK_THAT( 0.0, WithinRel( d.cosines()[1] ) );
  CHECK_THAT( 1.0, WithinRel( d.cosines()[2] ) );
  CHECK( 3 == d.probabilities().size() );
  CHECK_THAT( 0.0 , WithinRel( d.probabilities()[0] ) );
  CHECK_THAT( 1.0, WithinRel( d.probabilities()[1] ) );
  CHECK_THAT( 0.0, WithinRel( d.probabilities()[2] ) );

  CHECK( 10 == chunk.NC() );
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

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.LCT() );
  CHECK( 1 == chunk.referenceFrame() );
  CHECK( 3 == chunk.LTT() );
  CHECK( 3 == chunk.LAW() );
  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );
  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberInterpolationRegions() );
  CHECK( 2 == ranges::cpp20::distance( chunk.NBT() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.boundaries() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.INT() ) );
  CHECK( 2 == ranges::cpp20::distance( chunk.interpolants() ) );
  CHECK( 4 == ranges::cpp20::distance( chunk.incidentEnergies() ) );
  CHECK( 4 == ranges::cpp20::distance( chunk.angularDistributions() ) );

  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 5 == chunk.interpolants()[1] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.boundaries()[1] );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.incidentEnergies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.incidentEnergies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.incidentEnergies()[3] ) );

  auto angulars = chunk.angularDistributions();
  CHECK( 0 == angulars[0].index() );
  CHECK( 0 == angulars[1].index() );
  CHECK( 1 == angulars[2].index() );
  CHECK( 1 == angulars[3].index() );

  auto getE = [] ( const auto& value ) { return value.get().E(); };
  auto getIE = [] ( const auto& value ) { return value.get().incidentEnergy(); };
  CHECK_THAT( 1e-5, WithinRel( std::visit( getE, angulars[0] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getE, angulars[1] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getE, angulars[2] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getE, angulars[3] ) ) );
  CHECK_THAT( 1e-5, WithinRel( std::visit( getIE, angulars[0] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getIE, angulars[1] ) ) );
  CHECK_THAT( 1e+6, WithinRel( std::visit( getIE, angulars[2] ) ) );
  CHECK_THAT( 2e+7, WithinRel( std::visit( getIE, angulars[3] ) ) );

  const auto& distribution =
    std::get< MixedDistributions >( chunk.distributions() );

  CHECK( 3 == distribution.LTT() );
  CHECK( 3 == distribution.LAW() );

  CHECK( 2 == distribution.NR() );
  CHECK( 2 == distribution.numberInterpolationRegions() );
  CHECK( 4 == distribution.NE() );
  CHECK( 4 == distribution.numberIncidentEnergies() );
  CHECK( 2 == distribution.INT().size() );
  CHECK( 2 == distribution.NBT().size() );
  CHECK( 1 == distribution.INT()[0] );
  CHECK( 5 == distribution.INT()[1] );
  CHECK( 2 == distribution.NBT()[0] );
  CHECK( 4 == distribution.NBT()[1] );
  CHECK( 2 == distribution.interpolants().size() );
  CHECK( 2 == distribution.boundaries().size() );
  CHECK( 1 == distribution.interpolants()[0] );
  CHECK( 5 == distribution.interpolants()[1] );
  CHECK( 2 == distribution.boundaries()[0] );
  CHECK( 4 == distribution.boundaries()[1] );

  CHECK( 2 == distribution.legendre().NE() );
  CHECK( 2 == distribution.legendre().numberIncidentEnergies() );
  CHECK( 1 == distribution.legendre().NR() );
  CHECK( 1 == distribution.legendre().numberInterpolationRegions() );
  CHECK( 1 == distribution.legendre().INT().size() );
  CHECK( 1 == distribution.legendre().NBT().size() );
  CHECK( 1 == distribution.legendre().INT()[0] );
  CHECK( 2 == distribution.legendre().NBT()[0] );
  CHECK( 1 == distribution.legendre().interpolants().size() );
  CHECK( 1 == distribution.legendre().boundaries().size() );
  CHECK( 1 == distribution.legendre().interpolants()[0] );
  CHECK( 2 == distribution.legendre().boundaries()[0] );

  auto ldistributions = distribution.legendre().angularDistributions();

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

  CHECK( 2 == distribution.tabulated().NE() );
  CHECK( 2 == distribution.tabulated().numberIncidentEnergies() );
  CHECK( 1 == distribution.tabulated().NR() );
  CHECK( 1 == distribution.tabulated().numberInterpolationRegions() );
  CHECK( 1 == distribution.tabulated().INT().size() );
  CHECK( 1 == distribution.tabulated().NBT().size() );
  CHECK( 5 == distribution.tabulated().INT()[0] );
  CHECK( 2 == distribution.tabulated().NBT()[0] );
  CHECK( 1 == distribution.tabulated().interpolants().size() );
  CHECK( 1 == distribution.tabulated().boundaries().size() );
  CHECK( 5 == distribution.tabulated().interpolants()[0] );
  CHECK( 2 == distribution.tabulated().boundaries()[0] );

  auto tdistributions = distribution.tabulated().angularDistributions();

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

  CHECK( 16 == chunk.NC() );
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
