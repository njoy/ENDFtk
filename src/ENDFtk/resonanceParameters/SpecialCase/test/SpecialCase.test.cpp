#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing SpecialCase (LRU=0)" ){
  GIVEN( "valid 'special case' input" ){
    std::string ENDF = 
      " 5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n";
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    resonanceParameters::Base base( 1.0, 2.0, 0, 0, 0, 0 );
    THEN( "a SpecialCase can be constructed" ){
      resonanceParameters::SpecialCase
        sc( base, begin, end, lineNumber, MAT, MF, MT );

      REQUIRE( 1.0 == Approx( sc.EL() ) );
      REQUIRE( 2.0 == sc.EH() );
      REQUIRE( 0.5 == sc.SPI() );
      REQUIRE( 1.276553 == sc.AP() );
    }
  }
  GIVEN( "invalid ENDF input" ){
    std::string ENDF = 
      "-5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n";
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    resonanceParameters::Base base( 1.0, 2.0, 0, 0, 0, 0 );
    THEN( "an exception is thrown" ){
      REQUIRE_THROWS( 
          resonanceParameters::SpecialCase( 
              base, begin, end, lineNumber, MAT, MF, MT ) );
    }
  }
}

