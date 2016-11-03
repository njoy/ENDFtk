#include "catch.hpp"

#include "ENDFtk.hpp"


SCENARIO( "The Sequence read function", "[ENDFtk], [Sequence]" ){
  GIVEN("a record with a sequence of values" ){
    std::string line = 
      " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 1451    1\n"
      " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1 125 1451    1\n"
      " 1.300000+1 1.400000+1                                             125 1451    1\n";

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    auto closeEnough = []( double d0 , double d1 ){
      return std::abs( (d1 - d0)/( d1 == 0 ? 1.0 : d1 ) ) < 1E-15;
    };
    
    WHEN("passed to the Sequences's read function"){
      THEN( "extracted values will be correct"){
        auto vector = Sequence::read< Real >
          ( 14, it, end, lineNumber, 125, 1, 451 );

        REQUIRE( 14 == vector.size() );
        for ( int i = 0; i < 14; ++i ){
          REQUIRE( closeEnough( vector[i],  double(i + 1) ) );
        }
      }
      THEN( "will throw when record has too many tuples"){
        REQUIRE_THROWS( Sequence::read< Real >
                        ( 13, it, end, lineNumber, 125, 1, 451 ) );
      }
    }
  }
}
