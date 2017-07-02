#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion C2",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  REQUIRE(   ab1.C2() == 2.0 );
}
