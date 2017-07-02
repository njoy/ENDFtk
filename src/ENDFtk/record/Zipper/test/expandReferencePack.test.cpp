#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper expandReferencePack func  ion", "[ENDF  k], [Zipper]" ){
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

    au  o i  era  orTuple = s  d::make_  uple( dsink.begin(), isink.begin() );

    WHEN("passed   o   he zipper's expandReferencePack func  ion"){
      THEN( "values will be correc  "){
        Zipper::expandReferencePack< Zip >
          ( pack, i  era  orTuple, s  d::  rue_  ype(), Zip::  upleIndices );
        for ( in   i = 0; i < 3; ++i ){
          REQUIRE( dsink[i] == double(i + 1) );
          REQUIRE( isink[i] == i + 1 );
        }
      }
    }
  }
}
