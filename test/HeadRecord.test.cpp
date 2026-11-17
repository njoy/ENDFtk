// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/HeadRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const HeadRecord& );
std::string invalidChunk();

SCENARIO( "HeadRecord" ) {

  GIVEN( "valid data for a HeadRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int zaid = 1001;
      double c2 = 0.9991673;
      int l1 = 1;
      int l2 = 2;
      int n1 = 3;
      int n2 = 4;
      int mat = 125;
      int mf = 1;
      int mt = 451;

      HeadRecord chunk( zaid, c2, l1, l2, n1, n2, mat, mf, mt );

      THEN( "a HeadRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      HeadRecord chunk( begin, end, lineNumber );

      THEN( "a HeadRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a HeadRecord" ) {

    WHEN( "a string representation with an error is given" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( HeadRecord( begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.001000+3 9.991673-1          1          2          3          4 125 1451     \n";
}

void verifyChunk( const HeadRecord& chunk ) {

  CHECK( 1001 == chunk.ZA() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L1() );
  CHECK( 2 == chunk.L2() );
  CHECK( 3 == chunk.N1() );
  CHECK( 4 == chunk.N2() );

  CHECK( 125 == chunk.MAT() );
  CHECK( 125 == chunk.material() );
  CHECK( 1 == chunk.MF() );
  CHECK( 1 == chunk.file() );
  CHECK( 451 == chunk.MT() );
  CHECK( 451 == chunk.section() );
}

std::string invalidChunk() {

  return
    " 1.0010z0+3 9.991673-1          1          2          3          4 125 1451     \n";
}
