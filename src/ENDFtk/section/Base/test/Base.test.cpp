// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/Base.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

class TestBase : public section::Base {

public:

  TestBase( double ZA, double AWR, int MT ) : Base( ZA, AWR, MT ) {};
  TestBase( const HEAD& head, int MAT, int MF ) : Base( head, MAT, MF ) {};
};

std::string chunk();
void verifyChunk( const TestBase& );

SCENARIO( "HeadRecord" ) {

  GIVEN( "valid data for a HeadRecord" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 2;
    auto head = StructureDivision( begin, end, lineNumber );

    WHEN( "the data is given explicitly" ) {

      int ZA = 1001;
      double AWR = 0.9991673;
      int MT = 1;

      TestBase chunk( ZA, AWR, MT );

      THEN( "a Base can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given using a HeadRecord" ) {

      int MAT = 125;
      int MF = 3;

      TestBase chunk( asHead( head ), MAT, MF );

      THEN( "a Base can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Base class" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 2;
    auto head = StructureDivision( begin, end, lineNumber );

    WHEN( "given bad MAT and MF numbers when using a HEAD record" ) {

      int MAT = 1;
      int MF = 1;

      THEN( "an exception is thrown on construction" ) {

        CHECK_THROWS( TestBase( asHead( head ), MAT, MF ) );
        CHECK_THROWS( TestBase( asHead( head ), MAT, 3 ) );
        CHECK_THROWS( TestBase( asHead( head ), 125, MF ) );
      } // THEN
    } // WHEN

    WHEN( "the input arguments are negative" ) {

      THEN( "an exception is thrown on construction" ) {

        CHECK_THROWS( TestBase( -1, 2.0, 3 ) );
        CHECK_THROWS( TestBase( 1, -2.0, 3 ) );
        CHECK_THROWS( TestBase( 1, 2.0, -3 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk(){

  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n";
}

void verifyChunk( const TestBase& chunk ) {

  CHECK( 1 == chunk.MT() );
  CHECK( 1 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK( 0.9991673 == chunk.AWR() );
  CHECK( 0.9991673 == chunk.atomicWeightRatio() );
}
