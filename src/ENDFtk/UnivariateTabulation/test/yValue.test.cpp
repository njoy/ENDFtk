#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion yValue",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  s  d::vec  or< double > yValues{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

  for ( long index = 0; index <   ab1.NP(); ++index ){
    REQUIRE( yValues[ index ] ==   ab1.y()[ index ] );
    //REQUIRE( yValues[ index ] ==   ab1.y().a  ( index ) );
  }

  //REQUIRE_THROWS( ranges::a  (   ab1.y(), -1 ) );
  REQUIRE_THROWS( ranges::a  (   ab1.y(),   ab1.NP() ) );
}
