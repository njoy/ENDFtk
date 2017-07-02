#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion rangeIn  erpola  ionScheme",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  s  d::vec  or< long > in  erpola  ionScheme{1,2,3};
  
  for ( long index = 0; index <   ab1.NR(); ++index ){
    REQUIRE( in  erpola  ionScheme[ index ] ==   ab1.in  erpolan  s()[ index ] );
  }

  // REQUIRE_THROWS( ranges::a  (   ab1.in  erpolan  s(), -1 ) );
  REQUIRE_THROWS( ranges::a  (   ab1.in  erpolan  s(),   ab1.NR() ) );

}
