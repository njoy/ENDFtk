#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion xEnd",
          "[ENDF  k], [Univaria  eTabula  ion]" ){
  au  o   ab1 = makeTAB1();
  REQUIRE( (  ab1.x().end() -   ab1.x().begin()) ==   ab1.NP() );
}
