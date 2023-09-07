#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/34.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionBlock = section::Type< 34 >::ReactionBlock;
using LegendreBlock = section::Type< 34 >::LegendreBlock;
using SquareMatrix = section::Type< 34 >::SquareMatrix;

std::string chunk();
void verifyChunk( const section::Type< 34 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 34 >" ) {

  GIVEN( "valid data for a section::Type< 34 > with data" ) {

    std::string string = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      // LegendreBlock
      auto subsub = LegendreBlock( 1, 1, 0,
          { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } );

      // ReactionBlock
      auto sub = ReactionBlock( 2, 51, 1, 1, {subsub} );

      // Section
      auto chunk = section::Type< 34 >( 2, 94239., 2.369986e+2, 1, {sub} );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 34 > chunk( head, begin, end, lineNumber, 9437 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = string.begin();
      auto position = begin;
      auto end = string.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section section( head, begin, position, end, lineNumber );

      section::Type< 34 > chunk = section.parse< 34 >( lineNumber );

      THEN( "a section::Type< 34 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "a string representation with an invalid SEND" ) {

    std::string sectionString = chunk() + invalidSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 34 >( head, begin, end, lineNumber, 9437 ) );
    } // THEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 9.423900+4 2.369986+2          0          1          0          1943734  2     \n"
    " 0.000000+0 0.000000+0          0         51          1          1943734  2     \n"
    " 0.000000+0 0.000000+0          1          1          0          1943734  2     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
    " 4.000000+0                                                       943734  2     \n";
}

std::string validSEND() {
  return
    "                                                                  943734  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  943734  2     \n";
}

void verifyChunk( const section::Type< 34 >& chunk ) {

  // HEAD record
  CHECK( 94239. == Approx( chunk.ZA() ) );
  CHECK( 2.369986e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.369986e+2 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.LTT() );
  CHECK( 1 == chunk.representation() );
  CHECK( 1 == chunk.NMT1() );
  CHECK( 1 == chunk.numberReactions() );
  CHECK( 1 == chunk.reactions().size() );

  auto sub = chunk.reactions()[0];

  // subsection CONT record
  CHECK( 0 == sub.MAT1() );
  CHECK( 0 == sub.secondMaterialNumber() );
  CHECK( 51 == sub.MT1() );
  CHECK( 51 == sub.secondSectionNumber() );
  CHECK( 1 == sub.NL() );
  CHECK( 1 == sub.firstNumberLegendre() );
  CHECK( 1 == sub.NL1() );
  CHECK( 1 == sub.secondNumberLegendre() );
  CHECK( 1 == sub.NSS() );
  CHECK( 1 == sub.numberLegendreBlocks() );
  CHECK( 1 == sub.legendreBlocks().size() );

  CHECK( 6 == chunk.NC() );

}
