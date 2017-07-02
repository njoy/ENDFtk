#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion rangeBoundaries",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  s  d::vec  or< s  d::vec  or< double > > xValues { { 1.0, 2.0, 3.0, 4.0 },
                                                 { 4.0, 5.0 },
                                                 { 5.0, 6.0 } };

  au  o regions =   ab1.regions();
  for ( size_   index = 0; index < size_  (  ab1.NR()); ++index ){
    cons   au  o& reference = xValues[index];
    au  o   rial = regions[index].firs  ;
    ranges::equal(   rial, reference );
  }

  //REQUIRE_THROWS( ranges::a  (   ab1.boundaries(), -1 ) );
  REQUIRE_THROWS( ranges::a  (   ab1.boundaries(),   ab1.NR() ) );
}
