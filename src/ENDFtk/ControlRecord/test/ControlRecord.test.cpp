// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/ControlRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const ControlRecord& );
std::string invalidChunk();

SCENARIO( "ControlRecord" ) {

  GIVEN( "valid data for a TabulatedMultiplicity" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double c1 = 1001;
      double c2 = 0.9991673;
      int l1 = 1;
      int l2 = 2;
      int n1 = 3;
      int n2 = 4;

      ControlRecord chunk( c1, c2, l1, l2, n1, n2 );

      THEN( "a ControlRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ControlRecord chunk( begin, end, lineNumber, 125, 1, 451 );

      THEN( "a ControlRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ControlRecord" ) {

    WHEN( "a string representation with an error is given" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ControlRecord( begin, end, lineNumber, 125, 1, 451 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has a mismatch in tha MAT, MF or MT number" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ControlRecord( begin, end, lineNumber, 5, 1, 451 ) ); // MAT
        CHECK_THROWS( ControlRecord( begin, end, lineNumber, 125, 2, 451 ) ); // MF
        CHECK_THROWS( ControlRecord( begin, end, lineNumber, 125, 1, 452 ) ); // MT
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.001000+3 9.991673-1          1          2          3          4 125 1451     \n";
}

void verifyChunk( const ControlRecord& chunk ) {

  CHECK_THAT( 1001., WithinRel( chunk.C1() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.C2() ) );
  CHECK( 1 == chunk.L1() );
  CHECK( 2 == chunk.L2() );
  CHECK( 3 == chunk.N1() );
  CHECK( 4 == chunk.N2() );

  CHECK( 1 == chunk.NC() );
}

std::string invalidChunk() {

  return
    " 1.0010z0+3 9.991673-1          1          2          3          4 125 1451     \n";
}
