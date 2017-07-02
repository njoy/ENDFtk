#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion yEnd",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  REQUIRE( (  ab1.y().end() -   ab1.y().begin()) ==   ab1.NP() );
}
