#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing Resolved Resonance Base" ){
  GIVEN( "valid Base input parameters" ){

    ResonanceParameters::Resolved::Base base(1E-5, 1.0, 0, 1);
    THEN( "the Base parameters can be verified" ){

      REQUIRE( 1E-5 == base.lowerEnergyLimit );
      REQUIRE( 1.0 == base.upperEnergyLimit );
      REQUIRE( 0 == base.NRO );
      REQUIRE( 1 == base.NAPS );
    }
    WHEN( "verifying combinations of valid input parameters" ){
      THEN( "no exception is thrown" ){
        REQUIRE_NOTHROW( ResonanceParameters::Resolved::Base(1E-5, 1.0, 0, 0) );
        REQUIRE_NOTHROW( ResonanceParameters::Resolved::Base(1E-5, 1.0, 0, 1) );
        REQUIRE_NOTHROW( ResonanceParameters::Resolved::Base(1E-5, 1.0, 1, 0) );
        REQUIRE_NOTHROW( ResonanceParameters::Resolved::Base(1E-5, 1.0, 1, 1) );
        REQUIRE_NOTHROW( ResonanceParameters::Resolved::Base(1E-5, 1.0, 1, 2) );
      }
    }

  }
  GIVEN( "invalid Base input parameters" ){
    WHEN( "invalid lowerEnergyLimit" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(-0.1, 1.0, 0, 1) );
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1.1, 1.0, 0, 1) );
      }
    }
    WHEN( "invalid NRO parameter" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, -1, 1) );
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, 2, 1) );
      }
    }
    WHEN( "invalid NAPS parameter" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, 0, -1) );
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, 0, 2) );
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, 1, -1) );
        REQUIRE_THROWS( ResonanceParameters::Resolved::Base(1E-5, 1.0, 1, 3) );
      }
    }
  }

}
