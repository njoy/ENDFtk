// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/460.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section1460 = section::Type< 1, 460 >;
using DiscretePhotonMultiplicity = section::Type< 1, 460 >::DiscretePhotonMultiplicity;
using DiscretePhotons = section::Type< 1, 460 >::DiscretePhotons;
using ContinuousPhotons = section::Type< 1, 460 >::ContinuousPhotons;

std::string chunkLO1();
void verifyChunkLO1( const section::Type< 1, 460 >& );
std::string chunkLO2();
void verifyChunkLO2( const section::Type< 1, 460 >& );
std::string invalidLO();
std::string invalidNG();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 460 >" ) {

  GIVEN( "valid data for a section::Type< 1, 460 > with LO = 1" ) {

    std::string sectionString = chunkLO1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      DiscretePhotons photons(
        { DiscretePhotonMultiplicity( 0.1, 1, { 2 }, { 4 }, { 0., 4. },
                                      { 4.877451e-1, 1.715686e-1 } ),
          DiscretePhotonMultiplicity( 0.2, 2, { 3 }, { 2 }, { 0., 5., 9 },
                                      { 1.691176e-1, 2.450980e-3, 1.691176e-1 } ) } );

      section::Type< 1, 460 > chunk( zaid, awr, std::move( photons ) );

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 460 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 460, std::string( sectionString ) );

      section::Type< 1, 460 > chunk = section.parse< 1, 460 >();

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 460 > with LO = 2" ) {

    std::string sectionString = chunkLO2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      ContinuousPhotons photons( { 1.333600e-2, 3.273900e-2,
                                   1.207800e-1, 3.027800e-1,
                                   8.494900e-1, 2.853000e+0 } );

      section::Type< 1, 460 > chunk( zaid, awr, std::move( photons ) );

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 460 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 460, std::string( sectionString ) );

      section::Type< 1, 460 > chunk = section.parse< 1, 460 >();

      THEN( "a section::Type< 1, 460 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLO2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 1, 460 >" ) {

    WHEN( "a string representation of an File 1 Section 460 "
          "with an invalid LO" ) {

      std::string sectionString = invalidLO() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of an File 1 Section 460 "
          "with an invalid NG" ) {

      std::string sectionString = invalidNG() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLO1() {
  return
    " 9.223500+4 2.330248+2          1          0          2          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

void verifyChunkLO1( const section::Type< 1, 460 >& chunk ) {

  CHECK( 460 == chunk.MT() );
  CHECK( 460 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LO() );
  CHECK( 1 == chunk.representation() );
  CHECK( 2 == chunk.NG() );
  CHECK( 2 == chunk.numberDiscretePhotons() );

  const auto& photons = std::get< DiscretePhotons >( chunk.delayedPhotons() );

  CHECK( 1 == photons.LO() );
  CHECK( 1 == photons.representation() );
  CHECK( 2 == photons.NG() );
  CHECK( 2 == photons.numberDiscretePhotons() );

  CHECK( 2 == photons.photons().size() );

  CHECK_THAT( 0.1, WithinRel( photons.photons()[0].E() ) );
  CHECK( 1 == photons.photons()[0].index() );
  CHECK( 1 == photons.photons()[0].NR() );
  CHECK( 2 == photons.photons()[0].NP() );
  CHECK( 1 == photons.photons()[0].interpolants().size() );
  CHECK( 1 == photons.photons()[0].boundaries().size() );
  CHECK( 4 == photons.photons()[0].interpolants()[0] );
  CHECK( 2 == photons.photons()[0].boundaries()[0] );
  CHECK( 2 == photons.photons()[0].time().size() );
  CHECK( 2 == photons.photons()[0].multiplicities().size() );
  CHECK_THAT( 0., WithinRel( photons.photons()[0].time()[0] ) );
  CHECK_THAT( 4., WithinRel( photons.photons()[0].time()[1] ) );
  CHECK_THAT( 4.877451e-1, WithinRel( photons.photons()[0].multiplicities()[0] ) );
  CHECK_THAT( 1.715686e-1, WithinRel( photons.photons()[0].multiplicities()[1] ) );

  CHECK_THAT( 0.2, WithinRel( photons.photons()[1].E() ) );
  CHECK( 2 == photons.photons()[1].index() );
  CHECK( 1 == photons.photons()[1].NR() );
  CHECK( 3 == photons.photons()[1].NP() );
  CHECK( 1 == photons.photons()[1].interpolants().size() );
  CHECK( 1 == photons.photons()[1].boundaries().size() );
  CHECK( 2 == photons.photons()[1].interpolants()[0] );
  CHECK( 3 == photons.photons()[1].boundaries()[0] );
  CHECK( 3 == photons.photons()[1].time().size() );
  CHECK( 3 == photons.photons()[1].multiplicities().size() );
  CHECK_THAT( 0., WithinRel( photons.photons()[1].time()[0] ) );
  CHECK_THAT( 5., WithinRel( photons.photons()[1].time()[1] ) );
  CHECK_THAT( 9., WithinRel( photons.photons()[1].time()[2] ) );
  CHECK_THAT( 1.691176e-1, WithinRel( photons.photons()[1].multiplicities()[0] ) );
  CHECK_THAT( 2.450980e-3, WithinRel( photons.photons()[1].multiplicities()[1] ) );
  CHECK_THAT( 1.691176e-1, WithinRel( photons.photons()[1].multiplicities()[2] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkLO2() {
  return
    " 9.223500+4 2.330248+2          2          0          0          09228 1460     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1460     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n";
}

void verifyChunkLO2( const section::Type< 1, 460 >& chunk ) {

  CHECK( 460 == chunk.MT() );
  CHECK( 460 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );
  CHECK( 2 == chunk.LO() );
  CHECK( 2 == chunk.representation() );
  CHECK( 0 == chunk.NG() );
  CHECK( 0 == chunk.numberDiscretePhotons() );

  const auto& photons = std::get< ContinuousPhotons >( chunk.delayedPhotons() );

  CHECK( 2 == photons.LO() );
  CHECK( 2 == photons.representation() );
  CHECK( 0 == photons.NG() );
  CHECK( 0 == photons.numberDiscretePhotons() );
  CHECK( 6 == photons.NNF() );
  CHECK( 6 == photons.numberPrecursors() );

  CHECK( 6 == photons.lambdas().size() );
  CHECK( 6 == photons.decayConstants().size() );
  CHECK_THAT( 0.013336, WithinRel( photons.lambdas()[0] ) );
  CHECK_THAT( 0.032739, WithinRel( photons.lambdas()[1] ) );
  CHECK_THAT( 0.12078, WithinRel( photons.lambdas()[2] ) );
  CHECK_THAT( 0.30278, WithinRel( photons.lambdas()[3] ) );
  CHECK_THAT( 0.84949, WithinRel( photons.lambdas()[4] ) );
  CHECK_THAT( 2.853000, WithinRel( photons.lambdas()[5] ) );
  CHECK_THAT( 0.013336, WithinRel( photons.decayConstants()[0] ) );
  CHECK_THAT( 0.032739, WithinRel( photons.decayConstants()[1] ) );
  CHECK_THAT( 0.12078, WithinRel( photons.decayConstants()[2] ) );
  CHECK_THAT( 0.30278, WithinRel( photons.decayConstants()[3] ) );
  CHECK_THAT( 0.84949, WithinRel( photons.decayConstants()[4] ) );
  CHECK_THAT( 2.853000, WithinRel( photons.decayConstants()[5] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidLO() {
  return
    " 9.223500+4 2.330248+2          0          0          2          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

std::string invalidNG() {
  return
    " 9.223500+4 2.330248+2          1          0          0          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}
