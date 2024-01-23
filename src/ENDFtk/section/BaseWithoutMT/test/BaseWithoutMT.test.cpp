// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/Base.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

class TestBaseWithoutMT : public section::BaseWithoutMT < TestBaseWithoutMT > {

public:

  TestBaseWithoutMT( double ZA, double AWR ) : BaseWithoutMT( ZA, AWR ) {};
  TestBaseWithoutMT( const HEAD& head, int MAT, int MF ) :
    BaseWithoutMT( head, MAT, MF ) {};

  int sectionNumber() const { return 451; }
};

std::string chunk();
void verifyChunk( const TestBaseWithoutMT& );

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

      TestBaseWithoutMT chunk( ZA, AWR );

      THEN( "a Base can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given using a HeadRecord" ) {

      int MAT = 125;
      int MF = 3;

      TestBaseWithoutMT chunk( asHead( head ), MAT, MF );

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

        CHECK_THROWS( TestBaseWithoutMT( asHead( head ), MAT, MF ) );
        CHECK_THROWS( TestBaseWithoutMT( asHead( head ), MAT, 3 ) );
        CHECK_THROWS( TestBaseWithoutMT( asHead( head ), 125, MF ) );
      } // THEN
    } // WHEN

    WHEN( "the input arguments are negative" ) {

      THEN( "an exception is thrown on construction" ) {

        CHECK_THROWS( TestBaseWithoutMT( -1, 2.0 ) );
        CHECK_THROWS( TestBaseWithoutMT( 1, -2.0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk(){

  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n";
}

void verifyChunk( const TestBaseWithoutMT& chunk ) {

  CHECK( 451 == chunk.MT() );
  CHECK( 451 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 0.9991673 == chunk.atomicWeightRatio() );
}
