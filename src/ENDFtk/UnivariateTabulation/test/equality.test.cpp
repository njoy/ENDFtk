#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation equality",
          "[ENDFtk], [UnivariateTabulation]" ){

  auto reference = makeTAB1();
  auto trial = makeTAB1();
  GIVEN("equal tab1 records"){
    THEN( "equality will return true"){
      REQUIRE( reference == trial );
    }
    AND_THEN( "inequality will return false"){
      REQUIRE( not( reference != trial ) );
    }
  }
  GIVEN("tab1 record with differences"){
    WHEN("the C1 values differ"){
      trial.C1() = 10.0;
      THEN( "equality will return false"){
        REQUIRE( not( reference == trial ) );
      }
      AND_THEN( "inequality will return true"){
        REQUIRE( reference != trial );
      }
    }
    WHEN("the C2 values differ"){
      REQUIRE( reference.C1() == trial.C1() );
      trial.C2() = 10.0;
      THEN( "equality will return false"){
        REQUIRE( not( reference == trial ) );
      }
      AND_THEN( "inequality will return true"){
        REQUIRE( reference != trial );
      }
    }
    WHEN("the L1 values differ"){
      trial.L1() = 10;
      THEN( "equality will return false"){
        REQUIRE( not( reference == trial ) );
      }
      AND_THEN( "inequality will return true"){
        REQUIRE( reference != trial );
      }
    }
    WHEN("the L2 values differ"){
      trial.L2() = 10;
      THEN( "equality will return false"){
        REQUIRE( not( reference == trial ) );
      }
      AND_THEN( "inequality will return true"){
        REQUIRE( reference != trial );
      }
    }
  }
}
