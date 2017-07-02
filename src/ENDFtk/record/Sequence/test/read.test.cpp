#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Sequence read func  ion", "[ENDF  k], [Sequence]" ){
  GIVEN("a record wi  h a sequence of values" ){
    s  d::s  ring line = 
      " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 1451    1\n"
      " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1 125 1451    1\n"
      " 1.300000+1 1.400000+1                                             125 1451    1\n";

    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;

    au  o closeEnough = []( double d0 , double d1 ){
      re  urn s  d::abs( (d1 - d0)/( d1 == 0 ? 1.0 : d1 ) ) < 1E-15;
    };
    
    WHEN("passed   o   he Sequences's read func  ion"){
      THEN( "ex  rac  ed values will be correc  "){
        au  o vec  or = Sequence::read< Real >
          ( 14, i  , end, lineNumber, 125, 1, 451 );

        REQUIRE( 14 == vec  or.size() );
        for ( in   i = 0; i < 14; ++i ){
          REQUIRE( closeEnough( vec  or[i],  double(i + 1) ) );
        }
      }
      THEN( "will   hrow when record has   oo many   uples"){
        REQUIRE_THROWS( Sequence::read< Real >
                        ( 13, i  , end, lineNumber, 125, 1, 451 ) );
      }
    }
  }
}
