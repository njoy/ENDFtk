// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/section/34.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionBlock = section::Type< 34 >::ReactionBlock;
using LegendreBlock = section::Type< 34 >::LegendreBlock;
using SquareMatrix = section::SquareMatrix;

std::string chunk();
void verifyChunk( const ReactionBlock& );
std::string chunk1();
void verifyChunk1( const ReactionBlock& );


SCENARIO( "ReactionBlock" ) {

  GIVEN( "valid data for a ReactionBlock for MT==MT1" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      auto chunk = ReactionBlock( 51, 51, 2, 2, {
          LegendreBlock( 1, 1, 0,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
          LegendreBlock( 1, 2, 0,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
          LegendreBlock( 2, 2, 0,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34, 51 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionBlock chunk( begin, end, lineNumber, 9437, 34, 51 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34, 51 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN

  GIVEN( "valid data for a ReactionBlock for MT!=MT1" ) {

    std::string string = chunk1();

    WHEN( "the data is given explicitly" ) {

      auto chunk = ReactionBlock( 2, 51, 1, 2, {
          LegendreBlock( 1, 1, 0,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
          LegendreBlock( 1, 2, 0,
              { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionBlock chunk( begin, end, lineNumber, 9437, 34, 2 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunk1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 34, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN

  GIVEN( "invalid data for a ReactionBlock" ) {

    WHEN( "the data is given explicitly" ) {

      THEN( "an exception is thrown" ) {

        // should be 4 blocks, only 2 given
        CHECK_THROWS( ReactionBlock( 2, 51, 2, 2, {
           LegendreBlock( 1, 1, 0,
               { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
           LegendreBlock( 1, 2, 0,
               { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } ) );

        // should be 3 blocks, only 2 given
        CHECK_THROWS( ReactionBlock( 51, 51, 2, 2, {
           LegendreBlock( 1, 1, 0,
               { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ),
           LegendreBlock( 1, 2, 0,
               { SquareMatrix( 0, { 0, 100, 200 }, { 1, 2, 3, 4 } ) } ) } ) );

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0         51          2          2943734 51     \n"
    " 0.000000+0 0.000000+0          1          1          0          1943734 51     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
    " 4.000000+0                                                       943734 51     \n"
    " 0.000000+0 0.000000+0          1          2          0          1943734 51     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
    " 4.000000+0                                                       943734 51     \n"
    " 0.000000+0 0.000000+0          2          2          0          1943734 51     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
    " 4.000000+0                                                       943734 51     \n";
}
std::string chunk1() {
  return
    " 0.000000+0 0.000000+0          0         51          1          2943734  2     \n"
    " 0.000000+0 0.000000+0          1          1          0          1943734  2     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
    " 4.000000+0                                                       943734  2     \n"
    " 0.000000+0 0.000000+0          1          2          0          1943734  2     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
    " 4.000000+0                                                       943734  2     \n";
}

void verifyChunk( const ReactionBlock& chunk ) {

  // ReactionBlock CONT record
  CHECK( 0 == chunk.MAT1() );
  CHECK( 0 == chunk.secondMaterialNumber() );
  CHECK( 51 == chunk.MT1() );
  CHECK( 51 == chunk.secondSectionNumber() );
  CHECK( 2 == chunk.NL() );
  CHECK( 2 == chunk.firstNumberLegendre() );
  CHECK( 2 == chunk.NL1() );
  CHECK( 2 == chunk.secondNumberLegendre() );
  CHECK( 3 == chunk.NSS() );
  CHECK( 3 == chunk.numberLegendreBlocks() );
  CHECK( 3 == chunk.legendreBlocks().size() );

  auto stuff = chunk.legendreBlocks()[1];

  // LegendreBlock CONT record
  CHECK( 1 == stuff.L() );
  CHECK( 1 == stuff.firstLegendreOrder() );
  CHECK( 2 == stuff.L1() );
  CHECK( 2 == stuff.secondLegendreOrder() );
  CHECK( 0 == stuff.LCT() );
  CHECK( 0 == stuff.referenceFrame() );
  CHECK( 1 == stuff.NI() );
  CHECK( 1 == stuff.numberDataBlocks() );
  CHECK( 1 == stuff.data().size() );

  CHECK( 13 == chunk.NC() );

}

void verifyChunk1( const ReactionBlock& chunk ) {

  // ReactionBlock CONT record
  CHECK( 0 == chunk.MAT1() );
  CHECK( 0 == chunk.secondMaterialNumber() );
  CHECK( 51 == chunk.MT1() );
  CHECK( 51 == chunk.secondSectionNumber() );
  CHECK( 1 == chunk.NL() );
  CHECK( 1 == chunk.firstNumberLegendre() );
  CHECK( 2 == chunk.NL1() );
  CHECK( 2 == chunk.secondNumberLegendre() );
  CHECK( 2 == chunk.NSS() );
  CHECK( 2 == chunk.numberLegendreBlocks() );
  CHECK( 2 == chunk.legendreBlocks().size() );

  auto stuff = chunk.legendreBlocks()[1];

  // LegendreBlock CONT record
  CHECK( 1 == stuff.L() );
  CHECK( 1 == stuff.firstLegendreOrder() );
  CHECK( 2 == stuff.L1() );
  CHECK( 2 == stuff.secondLegendreOrder() );
  CHECK( 0 == stuff.LCT() );
  CHECK( 0 == stuff.referenceFrame() );
  CHECK( 1 == stuff.NI() );
  CHECK( 1 == stuff.numberDataBlocks() );
  CHECK( 1 == stuff.data().size() );

  CHECK( 9 == chunk.NC() );

}
