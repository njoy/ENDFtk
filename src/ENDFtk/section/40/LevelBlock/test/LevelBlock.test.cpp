// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/40.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LevelBlock = section::Type< 40 >::LevelBlock;
using ReactionBlock = section::ReactionBlock;
using SquareMatrix = section::SquareMatrix;

std::string chunk();
void verifyChunk( const LevelBlock& );


SCENARIO( "LevelBlock" ) {

  GIVEN( "valid data for a LevelBlock" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      auto chunk = LevelBlock( 3.14, 6.28, 314, 628, {
          ReactionBlock( 3.0, 1.0, 55, 66,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
          ReactionBlock( 3.0, 1.0, 77, 88,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 40, 51 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LevelBlock chunk( begin, end, lineNumber, 9437, 40, 51 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 40, 51 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
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

void verifyChunk( const LevelBlock& chunk ) {

  // LevelBlock CONT record
  CHECK_THAT( 3.14, WithinRel( chunk.QM() ) );
  CHECK_THAT( 3.14, WithinRel( chunk.massDifferenceQValue() ) );
  CHECK_THAT( 6.28, WithinRel( chunk.QI() ) );
  CHECK_THAT( 6.28, WithinRel( chunk.reactionQValue() ) );
  CHECK( 314 == chunk.IZAP() );
  CHECK( 314 == chunk.productIdentifier() );
  CHECK( 628 == chunk.LFS() );
  CHECK( 628 == chunk.excitedLevel() );
  CHECK( 2 == chunk.NL() );
  CHECK( 2 == chunk.numberReactions() );

  auto block1 = chunk.reactionBlocks()[0];

  // ReactionBlock CONT record
  CHECK( 3 == block1.XMF1() );
  CHECK( 1 == block1.XLFS1() );
  CHECK( 55 == block1.MAT1() );
  CHECK( 66 == block1.MT1() );

  auto block2 = chunk.reactionBlocks()[1];

  // ReactionBlock CONT record
  CHECK( 3 == block2.XMF1() );
  CHECK( 1 == block2.XLFS1() );
  CHECK( 77 == block2.MAT1() );
  CHECK( 88 == block2.MT1() );

  CHECK( 9 == chunk.NC() );

}
