#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper unzip func  ion", "[ENDF  k], [Zipper]" ){
  GIVEN("a record wi  h zipped values" ){
    s  d::s  ring line = 
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n"
      " 4.000000+0          4 5.000000+0          5 6.000000+0          6 125 1451    1\n"
      " 7.000000+0          7                                             125 1451    1\n";

    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;

    WHEN("passed   o   he zipper's unzip func  ion"){
      THEN( "ex  rac  ed values will be correc  "){
        au  o vec  ors = Zipper::unzip< Real, In  eger<11> >
          ( 7, i  , end, lineNumber, 125, 1, 451 );
        for ( in   i = 0; i < 7; ++i ){
          REQUIRE( s  d::ge  < 0 >( vec  ors )[i] == double(i + 1) );
          REQUIRE( s  d::ge  < 1 >( vec  ors )[i] == i + 1 );
        }
      }
    }
  }
}
