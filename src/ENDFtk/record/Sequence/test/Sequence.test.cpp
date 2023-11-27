// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/record/Sequence.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk::record;

SCENARIO( "The Sequence read function", "[ENDFtk], [Sequence]" ){
  GIVEN("a record with a sequence of values" ){
    std::string line =
      " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 1451    1\n"
      " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1 125 1451    1\n"
      " 1.300000+1 1.400000+1                                             125 1451    1\n";

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    WHEN("passed to the Sequences's read function"){
      THEN( "extracted values will be correct"){
        auto vector = Sequence::read< Real >
          ( 14, it, end, lineNumber, 125, 1, 451 );

        CHECK( 14 == vector.size() );
        for ( int i = 0; i < 14; ++i ){
          CHECK_THAT( vector[i], WithinRel( double(i + 1) ) );
        }
      }
      THEN( "will throw when record has too many tuples"){
        CHECK_THROWS( Sequence::read< Real >
                        ( 13, it, end, lineNumber, 125, 1, 451 ) );
      }
    }
  }
}
