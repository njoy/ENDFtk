#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/40.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LevelBlock = section::Type< 40 >::LevelBlock;
using ReactionBlock = section::Type< 40 >::ReactionBlock;
using SquareMatrix = section::Type< 40 >::SquareMatrix;

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
  CHECK( 3.14 == Approx( chunk.QM() ) );
  CHECK( 3.14 == Approx( chunk.massDifferenceQValue() ) );
  CHECK( 6.28 == Approx( chunk.QI() ) );
  CHECK( 6.28 == Approx( chunk.reactionQValue() ) );
  CHECK( 314 == chunk.IZAP() );
  CHECK( 314 == chunk.productIdentifier() );
  CHECK( 628 == chunk.LFS() );
  CHECK( 628 == chunk.excitedLevel() );
  CHECK( 2 == chunk.NL() );
  CHECK( 2 == chunk.numberReactions() );

  auto stuff = chunk.reactionBlocks()[1];

  // ReactionBlock CONT record
  CHECK( 3.0 == Approx(stuff.XMF1() ) );
  CHECK( 1.0 == Approx(stuff.XLFS1() ) );
  CHECK( 77 == stuff.MAT1() );
  CHECK( 88 == stuff.MT1() );

  CHECK( 9 == chunk.NC() );

}
