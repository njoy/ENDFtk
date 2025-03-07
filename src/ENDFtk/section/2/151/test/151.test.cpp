// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section2151 = section::Type< 2, 151 >;

std::string chunkSpecialCase();
void verifyChunkSpecialCase( const section::Type< 2, 151 >& );
std::string chunkResolvedSLBW();
void verifyChunkResolvedSLBW( const section::Type< 2, 151 >& );
std::string chunkResolvedMLBW();
void verifyChunkResolvedMLBW( const section::Type< 2, 151 >& );
std::string chunkResolvedRM();
void verifyChunkResolvedRM( const section::Type< 2, 151 >& );
std::string chunkResolvedRML();
void verifyChunkResolvedRML( const section::Type< 2, 151 >& );
std::string chunkUnresolvedEnergyIndependent();
void verifyChunkUnresolvedEnergyIndependent( const section::Type< 2, 151 >& );
std::string chunkUnresolvedEnergyDependentFission();
void verifyChunkUnresolvedEnergyDependentFission( const section::Type< 2, 151 >& );
std::string chunkUnresolvedEnergyDependent();
void verifyChunkUnresolvedEnergyDependent( const section::Type< 2, 151 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 2, 151 >" ) {

  GIVEN( "valid data for the special case (only channel radius) in "
         "section::Type< 2, 151 >" ) {

    std::string sectionString = chunkSpecialCase() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 1001;
      double awr = 0.9991673;
      double el = 1e-5;
      double eh = 1e+5;
      double spi = 0.5;
      double ap = 1.275246;

      section::Type< 2, 151 > chunk( zaid, awr, el, eh, spi, ap );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkSpecialCase( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkSpecialCase( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkSpecialCase( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for resolved SLBW (LRF1) in section::Type< 2, 151 >" ) {

    std::string sectionString = chunkResolvedSLBW() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedSLBW( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedSLBW( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for resolved MLBW (LRF2) in section::Type< 2, 151 >" ) {

    std::string sectionString = chunkResolvedMLBW() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedMLBW( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedMLBW( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for resolved RM (LRF3) in section::Type< 2, 151 >" ) {

    std::string sectionString = chunkResolvedRM() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedRM( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedRM( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for resolved RML (LRF7) in section::Type< 2, 151 >" ) {

    std::string sectionString = chunkResolvedRM() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedRM( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkResolvedRM( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for unresolved energy independent data in "
         "section::Type< 2, 151 >" ) {

    std::string sectionString = chunkUnresolvedEnergyIndependent() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyIndependent( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyIndependent( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for unresolved energy dependent fission data in "
         "section::Type< 2, 151 >" ) {

    std::string sectionString = chunkUnresolvedEnergyDependentFission() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyDependentFission( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyDependentFission( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for unresolved energy dependent data in "
         "section::Type< 2, 151 >" ) {

    std::string sectionString = chunkUnresolvedEnergyDependent() + validSEND();

    WHEN( "the data is given explicitly" ) {

      //! @todo finish test

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 151 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyDependent( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 2, 151, std::string( sectionString ) );

      section::Type< 2, 151 > chunk = section.parse< 2, 151 >();

      THEN( "a section::Type< 2, 151 > can be constructed and members can be "
            "tested" ) {

        verifyChunkUnresolvedEnergyDependent( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 2 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkSpecialCase() {
  return
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.275246+0          0          0          0          0 125 2151     \n";
}

void verifyChunkSpecialCase( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 4 == chunk.NC() );
}

std::string chunkResolvedSLBW() {
  return
    " 6.114800+4 1.466500+2          0          0          1          0 125 2151     \n"
    " 6.114800+4 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+0          1          1          0          0 125 2151     \n"
    " 6.000000+0 6.380900-1          0          0          1          0 125 2151     \n"
    " 1.466470+2 0.000000+0          0          0          6          1 125 2151     \n"
    " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+0 125 2151     \n";
}

void verifyChunkResolvedSLBW( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 61148 == chunk.ZA() );
  CHECK( 61148 == chunk.targetIdentifier() );
  CHECK_THAT( 146.65, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 146.65, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 6 == chunk.NC() );
}

std::string chunkResolvedMLBW() {
  return
    " 1.202400+4 2.377900+1          0          0          1          0 125 2151     \n"
    " 1.202400+4 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 5.200000+5          1          2          0          0 125 2151     \n"
    " 0.000000+0 5.400000-1          0          0          3          0 125 2151     \n"
    " 2.377900+1 0.000000+0          0          0         30          5 125 2151     \n"
    "-1.000000+5 5.000000-1 3.011300+3 3.000000+3 1.130000+1 0.000000+0 125 2151     \n"
    " 6.585000+5 5.000000-1 2.100770+4 2.100000+4 7.700000+0 0.000000+0 125 2151     \n"
    " 1.035200+6 5.000000-1 1.000500+4 1.000000+4 5.000000+0 0.000000+0 125 2151     \n"
    " 1.075200+6 5.000000-1 2.000500+4 2.000000+4 5.000000+0 0.000000+0 125 2151     \n"
    " 1.567000+6 5.000000-1 4.205000+3 4.200000+3 5.000000+0 0.000000+0 125 2151     \n"
    " 2.377900+1 0.000000+0          1          0         54          9 125 2151     \n"
    " 8.349990+4 1.500000+0 9.004700+3 9.000000+3 4.700000+0 0.000000+0 125 2151     \n"
    " 2.660000+5 5.000000-1 1.150060+5 1.150000+5 5.600000+0 0.000000+0 125 2151     \n"
    " 4.306000+5 1.500000+0 3.100700+4 3.100000+4 7.000000+0 0.000000+0 125 2151     \n"
    " 4.982000+5 1.500000+0 5.303790+2 5.299990+2 3.800000-1 0.000000+0 125 2151     \n"
    " 6.419000+5 5.000000-1 9.012300+2 8.999990+2 1.230900+0 0.000000+0 125 2151     \n"
    " 1.290900+6 1.500000+0 4.201230+3 4.200000+3 1.230900+0 0.000000+0 125 2151     \n"
    " 1.603000+6 1.500000+0 1.500120+4 1.500000+4 1.230900+0 0.000000+0 125 2151     \n"
    " 1.629000+6 5.000000-1 3.500120+4 3.500000+4 1.230900+0 0.000000+0 125 2151     \n"
    " 1.754000+6 5.000000-1 2.601230+3 2.600000+3 1.230900+0 0.000000+0 125 2151     \n"
    " 2.377900+1 0.000000+0          2          0         84         14 125 2151     \n"
    " 4.635000+4 1.500000+0 1.820000+0 7.200000-1 1.100000+0 0.000000+0 125 2151     \n"
    " 1.767000+5 1.500000+0 3.230900+0 2.000000+0 1.230900+0 0.000000+0 125 2151     \n"
    " 2.572000+5 1.500000+0 4.030000+1 3.800000+1 2.300000+0 0.000000+0 125 2151     \n"
    " 4.754000+5 2.500000+0 1.437330+1 1.333330+1 1.040000+0 0.000000+0 125 2151     \n"
    " 5.554000+5 1.500000+0 1.000450+4 1.000000+4 4.500000+0 0.000000+0 125 2151     \n"
    " 8.442000+5 1.500000+0 1.300600+4 1.300000+4 6.000000+0 0.000000+0 125 2151     \n"
    " 9.520000+5 1.500000+0 5.512300+2 5.499990+2 1.230900+0 0.000000+0 125 2151     \n"
    " 1.021800+6 2.500000+0 1.251230+3 1.250000+3 1.230900+0 0.000000+0 125 2151     \n"
    " 1.027300+6 1.500000+0 3.412310+2 3.400000+2 1.230900+0 0.000000+0 125 2151     \n"
    " 1.063500+6 1.500000+0 6.712310+2 6.700000+2 1.230900+0 0.000000+0 125 2151     \n"
    " 1.279700+6 2.500000+0 1.801230+3 1.800000+3 1.230900+0 0.000000+0 125 2151     \n"
    " 1.301300+6 1.500000+0 8.401220+3 8.399990+3 1.230900+0 0.000000+0 125 2151     \n"
    " 1.319200+6 1.500000+0 5.512300+2 5.499990+2 1.230900+0 0.000000+0 125 2151     \n"
    " 1.709000+6 2.500000+0 9.601220+3 9.599990+3 1.230900+0 0.000000+0 125 2151     \n";
}

void verifyChunkResolvedMLBW( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 12024 == chunk.ZA() );
  CHECK( 12024 == chunk.targetIdentifier() );
  CHECK_THAT( 23.779, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 23.779, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 35 == chunk.NC() );
}

std::string chunkResolvedRM() {
  return
    " 1.402800+4 2.773700+1          0          0          1          0 125 2151     \n"
    " 1.402800+4 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.750000+6          1          3          0          1 125 2151     \n"
    " 0.000000+0 4.136400-1          1          0          3          3 125 2151     \n"
    " 2.773700+1 4.136400-1          0          0         96         16 125 2151     \n"
    "-3.622100+6 5.000000-1 3.936200+6 1.453600+2 0.000000+0 0.000000+0 125 2151     \n"
    "-8.737300+5 5.000000-1 1.015100-1 1.025300+0 0.000000+0 0.000000+0 125 2151     \n"
    "-3.652900+5 5.000000-1 3.040600-2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-6.315900+4 5.000000-1 4.689400-2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-4.880100+4 5.000000-1 9.249600-3 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.567700+4 5.000000-1 6.533100+2 1.580300+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.816200+5 5.000000-1 3.489400+4 5.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.013100+5 5.000000-1 2.354800+0 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.902900+5 5.000000-1 5.236600+2 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.085200+6 5.000000-1 7.279400+1 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.162700+6 5.000000-1 3.013600+3 3.800000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.201200+6 5.000000-1 4.601200+3 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.256400+6 5.000000-1 1.738300+4 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.248700+6 5.000000-1 4.447600+5 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.007300+6 5.000000-1 2.899600+2 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.067800+6 5.000000-1 4.222900+2 3.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.773700+1 4.943700-1          1          0        102         17 125 2151     \n"
    " 6.773300+4 1.500000+0 2.658900+0 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.679700+4 1.500000+0 7.261800-1 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.996800+5 1.500000+0 8.136100-1 6.600000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.326600+5 1.500000+0 5.328100+2 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.655800+5 1.500000+0 1.095300+4 2.900000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.871700+5 5.000000-1 1.991600+2 8.800000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.140400+5 1.500000+0 1.216500+0 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.124900+5 1.500000+0 3.010000+4 9.700000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.100400+5 1.500000+0 3.673300+3 1.130000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.622300+5 5.000000-1 7.661400+4 1.600000+1 0.000000+0 0.000000+0 125 2151     \n"
    " 1.199500+6 5.000000-1 1.491400+4 7.600000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.408300+6 1.500000+0 5.198300+3 2.700000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.482400+6 5.000000-1 8.869400-1 8.800000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.592800+6 5.000000-1 1.119900+4 8.800000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.658600+6 5.000000-1 1.555300+3 8.800000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.805700+6 1.500000+0 1.299100+3 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.852400+6 1.500000+0 7.070700+4 2.500000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.773700+1 4.136400-1          2          0        150         25 125 2151     \n"
    " 3.174000+4 2.500000+0 1.566700-2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.080000+4 2.500000+0 2.961700-2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.987000+5 2.500000+0 9.886000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.545900+5 2.500000+0 1.446000+1 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.024700+5 1.500000+0 5.049100+1 3.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.717100+5 2.500000+0 5.313900+1 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.452300+5 1.500000+0 3.979100+2 2.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.723100+5 2.500000+0 3.214000+1 1.300000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.017800+6 2.500000+0 7.619200+1 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.042900+6 2.500000+0 9.337000+2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.148100+6 2.500000+0 3.146900+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.264400+6 2.500000+0 8.436400+2 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.379900+6 1.500000+0 6.529900+1 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.479900+6 1.500000+0 3.502500+3 1.650000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.512300+6 2.500000+0 9.149300+1 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.528700+6 1.500000+0 2.922500+3 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.580600+6 1.500000+0 1.495500+3 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.597200+6 1.500000+0 4.017200+3 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.639600+6 2.500000+0 1.529300+4 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.651100+6 2.500000+0 2.155500+4 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.665000+6 1.500000+0 2.159000+2 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.785000+6 1.500000+0 1.929400+2 2.400000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.850700+6 2.500000+0 3.551500+4 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.923700+6 2.500000+0 1.017100+3 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.968900+6 2.500000+0 5.734100+3 1.000000+0 0.000000+0 0.000000+0 125 2151     \n";
}

void verifyChunkResolvedRM( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 14028 == chunk.ZA() );
  CHECK( 14028 == chunk.targetIdentifier() );
  CHECK_THAT( 27.737, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 27.737, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 65 == chunk.NC() );
}

std::string chunkResolvedRML() {
  return
    " 1.703500+4 3.466850+1          0          0          1          0 125 2151     \n"
    " 1.703500+4 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.200000+6          1          7          0          0 125 2151     \n"
    " 0.000000+0 0.000000+0          0          3          8          0 125 2151     \n"
    " 0.000000+0 0.000000+0          3          0         36          6 125 2151     \n"
    " 0.000000+0 3.566850+1 0.000000+0 0.000000+0 1.000000+0 0.000000+0 125 2151     \n"
    " 0.000000+0 0.000000+0-1.000000+0 1.020000+2 0.000000+0 0.000000+0 125 2151     \n"
    " 1.000000+0 3.466850+1 0.000000+0 0.000000+0 5.000000-1 1.500000+0 125 2151     \n"
    " 0.000000+0 1.000000+0-1.000000+0 2.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.986240-1 3.466850+1 1.000000+0 1.600000+1 5.000000-1 1.500000+0 125 2151     \n"
    " 6.152200+5 1.000000+0-1.000000+0 6.000000+2 0.000000+0 0.000000+0 125 2151     \n"
    " 1.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 0.000000+0 1.000000+0 0.000000+0 3.667980-1 4.822220-1 125 2151     \n"
    " 3.000000+0 0.000000+0 1.000000+0 0.000000+0 3.667980-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         23        138         23 125 2151     \n"
    " 5.493200+4 3.672600-1 4.644240+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.823616+4 3.933600-1 2.179040+2 1.000000-5 0.000000+0 0.000000+0 125 2151     \n"
    " 1.150980+5 7.390000-1 4.307780+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.825230+5 7.451500-1 1.759740+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 2.397427+5 6.871600-1 2.685470+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.351287+5 3.583800-1 5.525660+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.991469+5 7.409700-1 1.093810+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.156650+5 3.286800-1 1.146260+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.506303+5 3.929900-1 4.613320+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.997896+5 6.704600-1 2.312410+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.422214+5 6.060000-1 5.220340+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.542074+5 6.060000-1 5.186030+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.652896+5 6.060000-1 1.406720+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.723573+5 6.060000-1 5.754080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.780000+5 6.060000-1 1.331580+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.949358+5 6.060000-1 1.824950+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.251773+5 6.060000-1 1.672450+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.546912+5 6.060000-1 2.690680+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.814646+5 6.060000-1 1.294130+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.315787+5 8.600000-1 4.453040+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.829776+5 6.060000-1 9.780610+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.109188+6 6.060000-1 2.742350+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.205687+6 6.060000-1 6.425840+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 0.000000+0 2.000000+0 0.000000+0 3.667980-1 4.822220-1 125 2151     \n"
    " 3.000000+0 0.000000+0 2.000000+0 0.000000+0 3.667980-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         32        192         32 125 2151     \n"
    "-1.806500+2 5.301500-1 1.327700+1 5.992300-3 0.000000+0 0.000000+0 125 2151     \n"
    " 1.480195+4 3.456800-1 3.259950+1 2.800020-2 0.000000+0 0.000000+0 125 2151     \n"
    " 2.661579+4 3.041500-1 1.154980+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.549467+4 8.059200-1 7.991540-2 1.000000-5 0.000000+0 0.000000+0 125 2151     \n"
    " 1.304435+5 7.593500-1 7.665700-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.149232+5 3.485100-1 6.528390+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.425998+5 9.018300-1 3.440090+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.846570+5 4.994200-1 1.194020+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.137503+5 4.763300-1 1.475680+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.310710+5 3.982400-1 3.276200+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.389756+5 2.383300+0 8.777960+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.802625+5 4.630100-1 1.178590+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.864177+5 4.180700-1 1.240150+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.593615+5 6.156500-1 3.859970+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.886274+5 4.081400-1 7.806800+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.143982+5 6.060000-1 5.284320+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.279391+5 6.060000-1 2.812390+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.590263+5 6.060000-1 1.813310+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.908121+5 6.060000-1 3.235630+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.216780+5 6.060000-1 6.758690+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.310363+5 6.060000-1 1.636760+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.408054+5 6.060000-1 8.597480+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.578143+5 6.060000-1 2.069420+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.810575+5 6.060000-1 6.654900+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.902708+5 6.060000-1 4.632110+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.799749+5 6.060000-1 5.311180+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.249523+5 6.060000-1 2.763840+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.609610+5 6.060000-1 7.202410+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.053393+6 6.060000-1 2.038130+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.137885+6 6.060000-1 1.835530+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.257680+6 6.060000-1 1.749830+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.563145+6 3.839800-1 6.219050+5 1.000000+3 0.000000+0 0.000000+0 125 2151     \n"
    " 0.000000+0-1.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0          9         54          9 125 2151     \n"
    " 2.239640+4 1.724800+0 9.663670-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.660415+4 1.565000+0 2.761380+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.300740+5 3.240100-1 8.118180+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.432153+5 7.032000-1 2.174300+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.454785+5 8.319700-1 6.556420+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.413389+5 6.549700-1 5.720320+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.812809+5 7.821300-1 1.774270+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.048567+5 8.600000-1 6.790940+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.478545+5 8.600000-1 7.640130+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-1.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         38        228         38 125 2151     \n"
    " 4.250762+3 4.720000-1 6.280000-1 2.300000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.491020+3 9.702100-1 3.863540-3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.776792+4 1.912000-1 4.407970-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.416635+4 1.042900+0 3.054660+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.277945+4 6.209000-1 1.345600+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.035154+5 3.880500-1 3.819530+2 1.972980+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.351161+5 3.410900-1 1.875460+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.625608+5 6.471800-1 5.634890+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.654823+5 1.050100+0 2.072840+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.199922+5 4.001800-1 3.847750+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.241121+5 4.033900-1 7.567220+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.288860+5 5.941900-1 1.768540+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.615514+5 8.458200-1 1.063750+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.791149+5 3.767200-1 1.254490+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.845043+5 9.053700-1 4.161730+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.060336+5 5.628500-1 7.718360+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.074111+5 6.403400-1 1.172260+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.406957+5 5.654300-1 3.875200+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.819655+5 8.183600+0 1.602770+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.878895+5 9.112300-1 3.238570+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.044696+5 1.492300+0 1.010090+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.526283+5 8.600500-1 3.430810+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 4.653384+5 3.666800-1 6.938600+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.526254+5 8.600000-1 2.791240+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.592470+5 8.600000-1 5.857230+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.913358+5 8.600000-1 1.674080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.008407+5 8.600000-1 1.208510+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.295837+5 8.600000-1 6.225330+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.593525+5 8.600000-1 1.356080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.183788+5 8.600000-1 9.740400+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.328902+5 8.600000-1 1.955950+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.103378+5 8.600000-1 5.088680+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.715664+5 8.600000-1 1.987240+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 9.439464+5 8.600000-1 5.556340+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.845132+5 8.600000-1 1.801810+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.138720+6 8.600000-1 9.544250+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.353551+6 8.600000-1 3.879680+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.435502+6 8.600000-1 5.365630+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-2.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         67        402         67 125 2151     \n"
    "-3.369334+5 5.340100-1 3.820180+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.734636+4 4.579210-1 6.027800+0 1.472210-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.297412+4 5.624100-1 8.159470-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.781159+4 5.380650-1 1.073890+2 9.980470-1 0.000000+0 0.000000+0 125 2151     \n"
    " 9.042023+4 7.164960-1 2.178860+1 2.740270-1 0.000000+0 0.000000+0 125 2151     \n"
    " 9.052563+4 1.275920-1 4.235150+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.134033+5 3.369900-1 1.422880+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.408311+5 5.458500-1 9.871460+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.498295+5 7.555300-1 1.132080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.926794+5 2.287600-1 3.381170+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.010949+5 2.905500-1 3.650400+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.066160+5 5.943300-1 5.594230-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.145480+5 2.323800-1 4.238200+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.153514+5 7.735500-1 4.558520+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.170986+5 6.185100-1 5.772230+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.213851+5 1.592700+0 4.073280+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.458488+5 7.646700-1 5.612490+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.501986+5 4.046000-1 4.345790+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.856091+5 8.420300-1 1.568700+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.900777+5 1.615200+0 1.520800+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.014487+5 4.017200-1 8.855620+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.038357+5 1.697600+0 6.957360+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.455490+5 3.479100-1 6.319440+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.543783+5 2.329000-1 8.058180+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.844697+5 5.785800+0 1.985550+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.078202+5 5.513100-1 2.040430+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.386472+5 6.448700-1 1.273690+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.444759+5 2.050000-1 1.810450+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.513762+5 1.759900+0 5.759080+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.578911+5 1.147400+0 7.322610+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.655024+5 5.580100-1 4.040480+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.691015+5 9.520300-1 3.761160+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.771962+5 5.403700-1 1.658970+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.854618+5 1.273200+0 4.799550+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.437824+5 8.600000-1 6.917280+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.645835+5 8.600000-1 5.359800+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.738796+5 8.600000-1 1.469740+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.330964+5 8.600000-1 1.445360+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 6.427422+5 8.600000-1 9.499240+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.125272+5 8.600000-1 3.300900+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 7.295798+5 8.600000-1 6.465640+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.398106+5 8.600000-1 3.042130+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.702915+5 8.600000-1 3.185460+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.985633+5 8.600000-1 2.910980+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 8.273814+5 6.060000-1 4.360650+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.322588+5 8.600000-1 1.382530+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.484064+5 8.600000-1 2.391310+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.524894+5 8.600000-1 1.726720+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.950719+5 8.600000-1 1.505930+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.156492+5 8.600000-1 1.033970+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.331357+5 8.600000-1 9.386810+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.533511+5 8.600000-1 1.000950+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 9.915402+5 8.600000-1 4.348100+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.006461+6 8.600000-1 3.591290+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.028543+6 8.600000-1 2.388860+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.055512+6 8.600000-1 3.888630+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.074009+6 8.600000-1 1.039250+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.080187+6 8.600000-1 7.511970+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.115662+6 8.600000-1 3.444140+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.131997+6 8.600000-1 1.523380+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.165343+6 8.600000-1 7.309520+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.198501+6 8.600000-1 3.243460+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.218130+6 8.600000-1 3.246660+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.243534+6 8.600000-1 3.096960+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.311787+6 8.600000-1 7.946430+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.354056+6 8.600000-1 1.103350+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.434336+6 8.600000-1 5.422940+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-1.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         18        108         18 125 2151     \n"
    " 1.339884+5 2.314200+0 6.600970+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 2.251416+5 1.346200+0 5.685270+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 3.728997+5 2.107900+0 1.796360+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 4.019221+5 3.329500-1 1.212200+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.221047+5 2.868200+0 8.577140+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.836869+5 1.907300+0 2.735270+3 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.811770+5 8.600000-1 2.087720+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.142552+5 8.600000-1 1.153480+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.219908+5 8.600000-1 8.268190+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.484834+5 8.600000-1 1.023870+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.654137+5 8.600000-1 1.519860+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.927810+5 8.600000-1 1.040840+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.451494+5 8.600000-1 4.176760+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.366575+5 8.600000-1 6.061270+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.747505+5 8.600000-1 3.259090+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.091954+6 8.600000-1 1.974980+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.177028+6 8.600000-1 1.488160+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.225254+6 8.600000-1 1.807190+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-2.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         28        168         28 125 2151     \n"
    " 3.978154+2 6.650000-1 5.050000-2 3.220000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 1.136064+5 2.947700-1 3.972030+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.430242+5 4.921800-1 3.147430+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.059671+5 4.506700-1 5.887780-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.837547+5 6.466700-1 4.237100+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.870089+5 5.536890-1 2.126030+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.949461+5 7.387600-1 4.747470+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 5.903574+5 8.600000-1 7.550480+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 6.181025+5 8.600000-1 1.075440+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.036239+5 8.600000-1 9.311240+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.350094+5 8.600000-1 3.777530+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.013281+5 8.600000-1 6.807230+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.358532+5 8.600000-1 1.181190+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.769947+5 8.600000-1 5.757280+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.225158+5 8.600000-1 1.571600+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.461013+5 8.600000-1 4.806310+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.810389+5 8.600000-1 4.229000+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.998479+5 8.600000-1 3.022270+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.016475+6 8.600000-1 4.019670+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.050581+6 8.600000-1 1.304140+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.088712+6 8.600000-1 5.239370+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.116025+6 8.600000-1 4.363740+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.172051+6 8.600000-1 1.494510+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.283751+6 8.600000-1 5.041400+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.337132+6 8.600000-1 4.850280+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.366148+6 8.600000-1 8.350230+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.403885+6 8.600000-1 8.067070+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.441365+6 8.600000-1 1.608740+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    "-3.000000+0 0.000000+0          0          0         18          3 125 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-1 125 2151     \n"
    " 0.000000+0 0.000000+0          0         57        342         57 125 2151     \n"
    " 1.635612+4 3.865000-1 5.981800+0 1.640190-1 0.000000+0 0.000000+0 125 2151     \n"
    " 1.713387+4 8.022800-1 1.409590+1 3.199990-2 0.000000+0 0.000000+0 125 2151     \n"
    " 4.027028+4 5.774900-1 1.773460-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.160803+4 4.471700-2 2.417150+0 9.599660-2 0.000000+0 0.000000+0 125 2151     \n"
    " 9.520675+4 4.531600-1 1.549000-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.944099+4 2.322700-1 2.393210+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.120451+5 3.240700-1 2.642330-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.400910+5 3.664800-1 3.778030+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.416415+5 3.131300-1 3.954240+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.529224+5 2.989300-1 3.820560-1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.835405+5 3.333300-1 4.615080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.852814+5 4.665000-1 4.482330+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.881523+5 4.975300-1 4.222480+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.901806+5 2.935300-1 1.024950+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.929420+5 7.559100-1 1.635970+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.991683+5 2.550000-1 2.775550+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 2.933823+5 1.802700+0 5.941830+0 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 3.367631+5 4.162100-1 2.890370+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 4.753035+5 8.300600-1 2.791800+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.097591+5 8.600000-1 3.870270+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.298958+5 8.600000-1 1.353670+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 5.352483+5 8.600000-1 4.481020+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.080558+5 8.600000-1 7.747700+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.657961+5 8.600000-1 2.099450+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.739830+5 6.060000-1 4.896460+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.816687+5 8.600000-1 6.028770+1 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.850220+5 8.600000-1 1.172880+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.010023+5 8.600000-1 1.251920+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.574622+5 8.600000-1 3.780250+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.611067+5 8.600000-1 2.238910+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 7.749692+5 8.600000-1 3.689300+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.068823+5 8.600000-1 6.298260+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.389452+5 8.600000-1 3.394540+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.626053+5 8.600000-1 6.945570+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 8.865767+5 8.600000-1 3.197900+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.058611+5 8.600000-1 4.411560+2 4.000000-1 0.000000+0 0.000000+0 125 2151     \n"
    " 9.109009+5 8.600000-1 3.339470+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 9.504659+5 8.600000-1 6.451080+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.010401+6 8.600000-1 7.910460+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.033683+6 8.600000-1 3.549570+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.062148+6 8.600000-1 4.207760+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.071198+6 8.600000-1 1.944480+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.085425+6 8.600000-1 1.339760+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.103724+6 8.600000-1 1.609290+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.120932+6 8.600000-1 3.890220+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.126914+6 8.600000-1 6.155220+2 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.144865+6 8.600000-1 1.586600+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.155330+6 8.600000-1 1.577740+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.189685+6 8.600000-1 7.290220+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.209020+6 8.600000-1 3.485080+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.237194+6 8.600000-1 5.888380+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.268642+6 8.600000-1 2.391480+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.277668+6 8.600000-1 2.984480+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.315129+6 8.600000-1 1.210580+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.390745+6 8.600000-1 5.502450+3 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.425393+6 8.600000-1 1.381970+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 1.485128+6 8.600000-1 1.054090+4 0.000000+0 0.000000+0 0.000000+0 125 2151     \n";
}

void verifyChunkResolvedRML( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 323 == chunk.NC() );
}

std::string chunkUnresolvedEnergyIndependent() {
  return
    " 5.614000+4 1.387080+2          0          0          1          0 125 2151     \n"
    " 5.614000+4 1.000000+0          0          0          1          0 125 2151     \n"
    " 2.300000+4 1.000000+5          2          1          0          0 125 2151     \n"
    " 0.000000+0 6.233000-1          0          0          3          0 125 2151     \n"
    " 1.387090+2 0.000000+0          0          0          6          1 125 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 4.400000-1 5.000000-2 0.000000+0 125 2151     \n"
    " 1.387090+2 0.000000+0          1          0         12          2 125 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+0 125 2151     \n"
    " 2.200000+3 1.500000+0 1.000000+0 2.640000-1 9.000000-2 0.000000+0 125 2151     \n"
    " 1.387090+2 0.000000+0          2          0         12          2 125 2151     \n"
    " 2.200000+3 1.500000+0 1.000000+0 3.300000-2 5.000000-2 0.000000+0 125 2151     \n"
    " 1.466670+3 2.500000+0 1.000000+0 2.200000-2 5.000000-2 0.000000+0 125 2151     \n";
}

void verifyChunkUnresolvedEnergyIndependent( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 56140 == chunk.ZA() );
  CHECK( 56140 == chunk.targetIdentifier() );
  CHECK_THAT( 138.708, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 138.708, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 12 == chunk.NC() );
}

std::string chunkUnresolvedEnergyDependentFission() {
  return
    " 9.424000+4 2.379920+2          0          0          1          0 125 2151     \n"
    " 9.424000+4 1.000000+0          0          1          1          0 125 2151     \n"
    " 5.700000+3 4.000000+4          2          1          0          0 125 2151     \n"
    " 0.000000+0 8.880000-1          0          0         14          3 125 2151     \n"
    " 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+4 125 2151     \n"
    " 1.400000+4 1.600000+4 1.800000+4 2.000000+4 2.500000+4 3.000000+4 125 2151     \n"
    " 3.500000+4 4.000000+4                                             125 2151     \n"
    " 2.379920+2 0.000000+0          0          0          1          0 125 2151     \n"
    " 0.000000+0 0.000000+0          0          1         20          0 125 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+0 125 2151     \n"
    " 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-3 125 2151     \n"
    " 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-3 125 2151     \n"
    " 1.481000-3 1.403000-3                                             125 2151     \n"
    " 2.379920+2 0.000000+0          1          0          2          0 125 2151     \n"
    " 0.000000+0 0.000000+0          1          1         20          0 125 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+0 125 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-3 125 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-2 125 2151     \n"
    " 1.456000-2 1.542000-2                                             125 2151     \n"
    " 0.000000+0 0.000000+0          1          2         20          0 125 2151     \n"
    " 6.697000+0 1.500000+0 1.000000+0 1.540000-3 3.100000-2 0.000000+0 125 2151     \n"
    " 1.207000-3 1.299000-3 1.326000-3 1.397000-3 1.544000-3 1.973000-3 125 2151     \n"
    " 2.317000-3 2.581000-3 2.811000-3 3.075000-3 3.494000-3 3.887000-3 125 2151     \n"
    " 4.290000-3 4.586000-3                                             125 2151     \n"
    " 2.379920+2 0.000000+0          2          0          2          0 125 2151     \n"
    " 0.000000+0 0.000000+0          2          1         20          0 125 2151     \n"
    " 6.697000+0 1.500000+0 1.000000+0 8.304300-4 3.100000-2 0.000000+0 125 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 125 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 125 2151     \n"
    " 1.000000-9 1.000000-9                                             125 2151     \n"
    " 0.000000+0 0.000000+0          2          2         20          0 125 2151     \n"
    " 4.633000+0 2.500000+0 1.000000+0 5.744900-4 3.100000-2 0.000000+0 125 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 125 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 125 2151     \n"
    " 1.000000-9 1.000000-9                                             125 2151     \n";
}

void verifyChunkUnresolvedEnergyDependentFission( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 94240 == chunk.ZA() );
  CHECK( 94240 == chunk.targetIdentifier() );
  CHECK_THAT( 237.992, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 237.992, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 35 == chunk.NC() );
}

std::string chunkUnresolvedEnergyDependent() {
  return
    " 3.809000+4 8.913540+1          0          0          1          0 125 2151     \n"
    " 3.809000+4 1.000000+0          0          1          1          0 125 2151     \n"
    " 6.000000+3 1.000000+5          2          2          0          0 125 2151     \n"
    " 0.000000+0 6.795900-1          0          0          3          0 125 2151     \n"
    " 8.913540+1 0.000000+0          0          0          1          0 125 2151     \n"
    " 5.000000-1 0.000000+0          5          0         84         13 125 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 4.590100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 4.590100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 4.590100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+4 1.231300+4 0.000000+0 4.555800-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+4 1.226300+4 0.000000+0 4.537400-1 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+4 1.212200+4 0.000000+0 4.485000-1 2.050000-1 0.000000+0 125 2151     \n"
    " 3.000000+4 1.205400+4 0.000000+0 4.460100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 4.000000+4 1.191800+4 0.000000+0 4.409700-1 2.050000-1 0.000000+0 125 2151     \n"
    " 5.000000+4 1.181000+4 0.000000+0 4.369800-1 2.050000-1 0.000000+0 125 2151     \n"
    " 6.000000+4 1.113000+4 0.000000+0 4.118100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+4 1.077400+4 0.000000+0 3.986200-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+4 1.039500+4 0.000000+0 3.846100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+5 9.669700+3 0.000000+0 3.577800-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.913540+1 0.000000+0          1          0          2          0 125 2151     \n"
    " 5.000000-1 0.000000+0          5          0         84         13 125 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+4 1.231300+4 0.000000+0 6.673600+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+4 1.226300+4 0.000000+0 6.646600+0 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+4 1.212200+4 0.000000+0 6.569900+0 2.050000-1 0.000000+0 125 2151     \n"
    " 3.000000+4 1.205400+4 0.000000+0 6.533500+0 2.050000-1 0.000000+0 125 2151     \n"
    " 4.000000+4 1.191800+4 0.000000+0 6.459600+0 2.050000-1 0.000000+0 125 2151     \n"
    " 5.000000+4 1.181000+4 0.000000+0 6.401200+0 2.050000-1 0.000000+0 125 2151     \n"
    " 6.000000+4 1.113000+4 0.000000+0 6.032400+0 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+4 1.077400+4 0.000000+0 5.839300+0 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+4 1.039500+4 0.000000+0 5.634100+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+5 9.669700+3 0.000000+0 5.241000+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+0 0.000000+0          5          0         84         13 125 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+4 6.156500+3 0.000000+0 3.336800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+4 6.131600+3 0.000000+0 3.323300+0 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+4 6.060800+3 0.000000+0 3.285000+0 2.050000-1 0.000000+0 125 2151     \n"
    " 3.000000+4 6.027200+3 0.000000+0 3.266800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 4.000000+4 5.959100+3 0.000000+0 3.229800+0 2.050000-1 0.000000+0 125 2151     \n"
    " 5.000000+4 5.905100+3 0.000000+0 3.200600+0 2.050000-1 0.000000+0 125 2151     \n"
    " 6.000000+4 5.564900+3 0.000000+0 3.016200+0 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+4 5.386800+3 0.000000+0 2.919600+0 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+4 5.197500+3 0.000000+0 2.817000+0 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+5 4.834900+3 0.000000+0 2.620500+0 2.050000-1 0.000000+0 125 2151     \n"
    " 8.913540+1 0.000000+0          2          0          2          0 125 2151     \n"
    " 1.500000+0 0.000000+0          5          0         84         13 125 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 2.233000-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+3 6.202800+3 0.000000+0 2.233000-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 2.233000-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+4 6.156500+3 0.000000+0 2.216300-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+4 6.131600+3 0.000000+0 2.207400-1 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+4 6.060800+3 0.000000+0 2.181900-1 2.050000-1 0.000000+0 125 2151     \n"
    " 3.000000+4 6.027200+3 0.000000+0 2.169800-1 2.050000-1 0.000000+0 125 2151     \n"
    " 4.000000+4 5.959100+3 0.000000+0 2.145300-1 2.050000-1 0.000000+0 125 2151     \n"
    " 5.000000+4 5.905100+3 0.000000+0 2.125900-1 2.050000-1 0.000000+0 125 2151     \n"
    " 6.000000+4 5.564900+3 0.000000+0 2.003400-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+4 5.386800+3 0.000000+0 1.939200-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+4 5.197500+3 0.000000+0 1.871100-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+5 4.834900+3 0.000000+0 1.740500-1 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+0 0.000000+0          5          0         84         13 125 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+0 125 2151     \n"
    " 6.000000+3 4.135200+3 0.000000+0 1.488700-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+3 4.135200+3 0.000000+0 1.488700-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+3 4.135200+3 0.000000+0 1.488700-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+4 4.104300+3 0.000000+0 1.477600-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.500000+4 4.087700+3 0.000000+0 1.471600-1 2.050000-1 0.000000+0 125 2151     \n"
    " 2.500000+4 4.040500+3 0.000000+0 1.454600-1 2.050000-1 0.000000+0 125 2151     \n"
    " 3.000000+4 4.018100+3 0.000000+0 1.446500-1 2.050000-1 0.000000+0 125 2151     \n"
    " 4.000000+4 3.972700+3 0.000000+0 1.430200-1 2.050000-1 0.000000+0 125 2151     \n"
    " 5.000000+4 3.936800+3 0.000000+0 1.417200-1 2.050000-1 0.000000+0 125 2151     \n"
    " 6.000000+4 3.710000+3 0.000000+0 1.335600-1 2.050000-1 0.000000+0 125 2151     \n"
    " 7.000000+4 3.591200+3 0.000000+0 1.292800-1 2.050000-1 0.000000+0 125 2151     \n"
    " 8.000000+4 3.465000+3 0.000000+0 1.247400-1 2.050000-1 0.000000+0 125 2151     \n"
    " 1.000000+5 3.223200+3 0.000000+0 1.160400-1 2.050000-1 0.000000+0 125 2151     \n";
}

void verifyChunkUnresolvedEnergyDependent( const section::Type< 2, 151 >& chunk ) {

  CHECK( 151 == chunk.MT() );
  CHECK( 151 == chunk.sectionNumber() );
  CHECK( 38090 == chunk.ZA() );
  CHECK( 38090 == chunk.targetIdentifier() );
  CHECK_THAT( 89.1354, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 89.1354, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.isotopes().size() );

  //! @todo finish test

  CHECK( 82 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                   125 2  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   125 2  1     \n";
}
