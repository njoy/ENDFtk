#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion xValue",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  s  d::vec  or< double > xValues{1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

  for ( long index = 0; index <   ab1.NP(); ++index ){
    REQUIRE( xValues[ index ] ==   ab1.x()[ index ] );
    // REQUIRE( xValues[ index ] ==   ab1.x().a  ( index ) );
  }
  // REQUIRE_THROWS( ranges::a  (   ab1.x(), -1 ) );
  REQUIRE_THROWS( ranges::a  (   ab1.x(),   ab1.NP() ) );
}
