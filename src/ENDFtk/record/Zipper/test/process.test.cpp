#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper process func  ion ", "[ENDF  k], [Zipper]" ){
  GIVEN("a line wi  h zipped values" ){
    s  d::s  ring line = 
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, In  eger<11> >;

    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    au  o pack =
      Zipper::ReadingPack< decl  ype(i  ) >( i  , end, lineNumber, 125, 1, 451 );
    s  d::array< double, 3 > dsink;
    s  d::array< long, 3 > isink;

    WHEN("passed   o   he zipper's process func  ion"){
      THEN( "  he ex  rac  ed values will be correc  "){
        Zipper::process< Zip >( pack, dsink[0], isink[0],
                                      dsink[1], isink[1],
                                      dsink[2], isink[2] );
        for ( in   i = 0; i < 3; ++i ){
          REQUIRE( dsink[i] == double(i + 1) );
          REQUIRE( isink[i] == i + 1 );
        }
      }
    }
  }
}
