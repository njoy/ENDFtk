// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/40.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using LevelBlock = section::Type< 40 >::LevelBlock;
using ReactionBlock = section::ReactionBlock;
using SquareMatrix = section::SquareMatrix;

std::string chunk();
void verifyChunk( const section::Type< 40 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 40 >" ) {

  GIVEN( "valid data for a section::Type< 40 > with data" ) {

    std::string string = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      // LevelBlock
      auto block = LevelBlock( 3.14, 6.28, 314, 628, {
          ReactionBlock( 3.0, 1.0, 55, 66,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
          ReactionBlock( 3.0, 1.0, 77, 88,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } );

      // Section
      auto chunk = section::Type< 40 >( 51, 94239., 2.369986e+2, 1.0, {block} );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 40 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 40 > chunk( head, begin, end, lineNumber, 9437 );

      THEN( "a Section object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 40 );
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

      section::Type< 40 > chunk = section.parse< 40 >( lineNumber );

      THEN( "a section::Type< 40 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 40 );
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

      CHECK_THROWS( section::Type< 40 >( head, begin, end, lineNumber, 9437 ) );
    } // THEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 9.423900+4 2.369986+2          1          0          1          0943740 51     \n"
    " 3.140000+0 6.280000+0        314        628          0          2943740 51     \n"
    " 3.000000+0 1.000000+0         55         66          0          1943740 51     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
    " 4.000000+0                                                       943740 51     \n"
    " 3.000000+0 1.000000+0         77         88          0          1943740 51     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
    " 4.000000+0                                                       943740 51     \n";
}

std::string validSEND() {
  return
    "                                                                  943740  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  943740 51     \n";
}

void verifyChunk( const section::Type< 40 >& chunk ) {

  // HEAD record
  CHECK( 94239 == chunk.ZA() );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.LIS() );
  CHECK( 1 == chunk.excitedLevel() );

  CHECK( 1 == chunk.NS() );
  CHECK( 1 == chunk.numberLevelBlocks() );
  CHECK( 1 == chunk.levelBlocks().size() );
  CHECK( 51 == chunk.MT() );
  CHECK( 51 == chunk.sectionNumber() );

  auto sub = chunk.levelBlocks()[0];

  // LevelBlock CONT record
  CHECK_THAT( 3.14, WithinRel( sub.QM() ) );
  CHECK_THAT( 3.14, WithinRel( sub.massDifferenceQValue() ) );
  CHECK_THAT( 6.28, WithinRel( sub.QI() ) );
  CHECK_THAT( 6.28, WithinRel( sub.reactionQValue() ) );
  CHECK( 314 == sub.IZAP() );
  CHECK( 314 == sub.productIdentifier() );
  CHECK( 628 == sub.LFS() );
  CHECK( 628 == sub.excitedLevel() );
  CHECK( 2 == sub.NL() );
  CHECK( 2 == sub.numberReactions() );

  auto block1 = sub.reactionBlocks()[0];

  // ReactionBlock CONT record
  CHECK( 3 == block1.XMF1() );
  CHECK( 1 == block1.XLFS1() );
  CHECK( 55 == block1.MAT1() );
  CHECK( 66 == block1.MT1() );

  auto block2 = sub.reactionBlocks()[1];

  // ReactionBlock CONT record
  CHECK( 3 == block2.XMF1() );
  CHECK( 1 == block2.XLFS1() );
  CHECK( 77 == block2.MAT1() );
  CHECK( 88 == block2.MT1() );

  CHECK( 10 == chunk.NC() );
}
