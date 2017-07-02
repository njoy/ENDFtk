#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion xBegin",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  REQUIRE( *(  ab1.x().begin()) == 1.0 );
}
