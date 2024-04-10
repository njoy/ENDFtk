// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/ListRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const ListRecord& );
std::string chunkWithSmallerNPL();
std::string chunkWithNegativeNPL();

SCENARIO( "ListRecord" ) {

  GIVEN( "valid data for a ListRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      int N2 = 5;
      std::vector< double > list = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

      ListRecord chunk( C1, C2, L1, L2, N2, std::move( list ) );

      THEN( "a ListRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ListRecord chunk( begin, end, lineNumber, 125, 3, 102 );

      THEN( "a ListRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "different ListRecord" ) {

    GIVEN( "they can be compared" ) {

      ListRecord chunk( 1., 2., 3, 4, 5, { 4., 3., 2., 1. } );
      ListRecord equal( 1., 2., 3, 4, 5, { 4., 3., 2., 1. } );
      ListRecord c1( 2., 2., 3, 4, 5, { 4., 3., 2., 1. } );
      ListRecord c2( 1., 1., 3, 4, 5, { 4., 3., 2., 1. } );
      ListRecord l1( 1., 2., 4, 4, 5, { 4., 3., 2., 1. } );
      ListRecord l2( 1., 2., 3, 5, 5, { 4., 3., 2., 1. } );
      ListRecord n2( 1., 2., 3, 4, 6, { 4., 3., 2., 1. } );
      ListRecord list( 1., 2., 3, 4, 5, { 6., 7., 8., 9. } );

      CHECK( chunk == equal );
      CHECK( chunk != c1 );
      CHECK( chunk != c2 );
      CHECK( chunk != l1 );
      CHECK( chunk != l2 );
      CHECK( chunk != n2 );
      CHECK( chunk != list );
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data for a ListRecord" ) {

    WHEN( "a string representation with a smaller NPL value is given" ) {

      std::string string = chunkWithSmallerNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ListRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a negative NPL value is given" ) {

      std::string string = chunkWithNegativeNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ListRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has a mismatch in the tail values" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ListRecord( begin, end, lineNumber, 5, 3, 102 ) ); // MAT
        CHECK_THROWS( ListRecord( begin, end, lineNumber, 125, 1, 102 ) ); // MF
        CHECK_THROWS( ListRecord( begin, end, lineNumber, 125, 3, 103 ) ); // MT
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+0 2.000000+0          3          4         10          5 125 3102     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 3102     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                       125 3102     \n";
}

void verifyChunk( const ListRecord& chunk ) {

  CHECK_THAT( 1.0, WithinRel( chunk.C1() ) );
  CHECK_THAT( 2.0, WithinRel( chunk.C2() ) );
  CHECK( 3 == chunk.L1() );
  CHECK( 4 == chunk.L2() );
  CHECK( 5 == chunk.N2() );

  CHECK( 10 == chunk.NPL() );
  CHECK( 10 == chunk.numberValues() );

  CHECK( 10 == chunk.list().size() );
  CHECK_THAT(  1., WithinRel( chunk.list()[0] ) );
  CHECK_THAT(  2., WithinRel( chunk.list()[1] ) );
  CHECK_THAT(  3., WithinRel( chunk.list()[2] ) );
  CHECK_THAT(  4., WithinRel( chunk.list()[3] ) );
  CHECK_THAT(  5., WithinRel( chunk.list()[4] ) );
  CHECK_THAT(  6., WithinRel( chunk.list()[5] ) );
  CHECK_THAT(  7., WithinRel( chunk.list()[6] ) );
  CHECK_THAT(  8., WithinRel( chunk.list()[7] ) );
  CHECK_THAT(  9., WithinRel( chunk.list()[8] ) );
  CHECK_THAT( 10., WithinRel( chunk.list()[9] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithSmallerNPL() {

  return
    " 1.000000+0 2.000000+0          3          4          9          5 125 3102     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 3102     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithNegativeNPL() {

  return
    " 1.000000+0 2.000000+0          3          4         -1          5 125 3102     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 3102     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                       125 3102     \n";
}
