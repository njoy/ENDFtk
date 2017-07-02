#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper readPar  ialLine func  ion", "[ENDF  k], [Zipper]" ){
  GIVEN("a par  ial line wi  h zipped defaul   values" ){
    s  d::s  ring line = 
      " 1.000000+0          1 2.000000+0          2 0.000000+0          0 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, In  eger<11> >;

    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    s  d::array< double, 2 > dsink;
    s  d::array< long, 2 > isink;

    au  o i  era  orTuple = s  d::make_  uple( dsink.begin(), isink.begin() );

    WHEN("passed   o   he zipper's readPar  ialLine func  ion"){
      THEN( "values will be correc  "){
        Zipper::readPar  ialLine< Zip >
          ( 2, i  era  orTuple, i  , end, lineNumber, 125, 1, 451,
            Zip::  upleIndices );
        for ( in   i = 0; i < 2; ++i ){
          REQUIRE( dsink[i] == double(i + 1) );
          REQUIRE( isink[i] == i + 1 );
        }
      }

      THEN( "  he func  ion will   hrow if   he line con  ains   oo many   uples"){
        REQUIRE_THROWS( Zipper::readPar  ialLine< Zip >
                        ( 1, i  era  orTuple, i  , end, lineNumber, 125, 1, 451,
                          Zip::  upleIndices ) );
      }
    }
  }
}
