#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing resolved Resonance Base" ){
  GIVEN( "valid Base input parameters" ){

    resonanceParameters::Base base(1E-5, 1.0, 1, 7, 1, 2);
    THEN( "the Base parameters can be verified" ){
      REQUIRE( 1E-5 == base.EL() );
      REQUIRE( 1.0 == base.EH() );
      REQUIRE( 1 == base.LRU() );
      REQUIRE( 7 == base.LRF() );
      REQUIRE( 1 == base.NRO() );
      REQUIRE( 2 == base.NAPS() );
    }
  }
  
  GIVEN( "invalid Base input parameters" ){
    WHEN( "invalid lowerEnergyLimit" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( resonanceParameters::Base(-0.1, 1.0, 1, 1, 0, 1) );
        REQUIRE_THROWS( resonanceParameters::Base(1.1, 1.0, 1, 1, 0, 1) );
      }
    }

    WHEN( "invalid LRU" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, -1, 1, 0, 1) );
        REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 3, 1, 0, 1) );
      }
    }
    
    WHEN("LRU is zero"){
      WHEN( "and nonzero LRF" ){
        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 0, -1, 0, 1) );
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 0, 1, 0, 1) );
        }
      }
    }
    
    WHEN("LRU is one"){
      WHEN( "and illegal LRF" ){
        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 1, 0, 0, 1) );
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 1, 5, 0, 1) );
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 1, 6, 0, 1) );
          REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 1, 8, 0, 1) );
        }
      }
      
      WHEN( "and legal LRF" ){
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 1, 1, 0, 1) );
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 1, 2, 0, 1) );
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 1, 3, 0, 1) );
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 1, 4, 0, 1) );
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 1, 7, 0, 1) );
      }
    }
    
    WHEN("LRU is two"){
      WHEN( "and illegal LRF" ){
        REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 2, 0, 0, 1) );
        REQUIRE_THROWS( resonanceParameters::Base(0.1, 1.0, 2, 3, 0, 1) );
      }
      
      WHEN( "and legal LRF" ){
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 2, 1, 0, 1) );
        REQUIRE_NOTHROW( resonanceParameters::Base(0.1, 1.0, 2, 2, 0, 1) );
      }      
    }
    
    WHEN( "invalid NRO parameter" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, -1, 1) );
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, 2, 1) );
      }
    }
    
    WHEN( "invalid NAPS parameter" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, 0, -1) );
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, 0, 2) );
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, 1, -1) );
        REQUIRE_THROWS( resonanceParameters::Base(1E-5, 1.0, 1, 1, 1, 3) );
      }
    }
  }
}
