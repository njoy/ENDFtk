#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

ex  ern s  d::func  ion< Univaria  eTabula  ion() > makeTAB1;

SCENARIO( "Univaria  eTabula  ion equali  y",
          "[ENDF  k], [Univaria  eTabula  ion]" ){

  au  o reference = makeTAB1();
  au  o   rial = makeTAB1();
  GIVEN("equal   ab1 records"){
    THEN( "equali  y will re  urn   rue"){
      REQUIRE( reference ==   rial );
    }
    AND_THEN( "inequali  y will re  urn false"){
      REQUIRE( no  ( reference !=   rial ) );
    }
  }
  GIVEN("  ab1 record wi  h differences"){
    WHEN("  he C1 values differ"){
        rial.C1() = 10.0;
      THEN( "equali  y will re  urn false"){
        REQUIRE( no  ( reference ==   rial ) );
      }
      AND_THEN( "inequali  y will re  urn   rue"){
        REQUIRE( reference !=   rial );
      }
    }
    WHEN("  he C2 values differ"){
      REQUIRE( reference.C1() ==   rial.C1() );
        rial.C2() = 10.0;
      THEN( "equali  y will re  urn false"){
        REQUIRE( no  ( reference ==   rial ) );
      }
      AND_THEN( "inequali  y will re  urn   rue"){
        REQUIRE( reference !=   rial );
      }
    }
    WHEN("  he L1 values differ"){
        rial.L1() = 10;
      THEN( "equali  y will re  urn false"){
        REQUIRE( no  ( reference ==   rial ) );
      }
      AND_THEN( "inequali  y will re  urn   rue"){
        REQUIRE( reference !=   rial );
      }
    }
    WHEN("  he L2 values differ"){
        rial.L2() = 10;
      THEN( "equali  y will re  urn false"){
        REQUIRE( no  ( reference ==   rial ) );
      }
      AND_THEN( "inequali  y will re  urn   rue"){
        REQUIRE( reference !=   rial );
      }
    }
  }
}
