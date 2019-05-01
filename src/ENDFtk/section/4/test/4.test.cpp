#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Isotropic = section::Type< 4 >::Isotropic;

std::string chunkWithLTT0();
void verifyChunkWithLTT0( const section::Type< 4 >& );
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

    WHEN( "there is a syntaxTree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 4 > chunk = section.parse< 4 >( lineNumber );

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
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 4 >" ) {

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
  REQUIRE( 0 == chunk.distributionType() );
  REQUIRE( true == chunk.LI() );
  REQUIRE( true == chunk.isotropicAngularDistributions() );

  const auto& distribution =
                  std::experimental::get< Isotropic >( chunk.distribution() );
  REQUIRE( 0 == distribution.LTT() );
  REQUIRE( 0 == distribution.distributionType() );

  REQUIRE( 2 == chunk.NC() );
}

std::string validSEND() {
  return
    "                                                                  9228 4  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 4  4     \n";
}
