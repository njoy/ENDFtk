#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing SpecialCase (LRU=0)" ){
  GIVEN( "valid 'special case' input" ){
    std::string ENDF{
        // " 1.001000+3 9.991673-1          0          0          1          0 125 2151    1\n"
        // " 1.001000+3 1.000000+0          0          0          1          0 125 2151    2\n"
        " 1.000000-5 1.000000+5          0          0          0          0 125 2151    3\n"
        " 5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n"};
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    THEN( "a SpecialCase can be constructed" ){
      CONT cont1( begin, end, lineNumber, MAT, MF, MT );
      CONT cont2( begin, end, lineNumber, MAT, MF, MT );

      ResonanceParameters::SpecialCase SC( cont1.C1(), cont1.C2(), 
                                           cont2.C1(), cont2.C2(), cont2.N1() );

      AND_THEN( "the parameters can be checked" ){
        REQUIRE( 1E-5 == Approx( SC.lowerEnergyLimit ) );
        REQUIRE( 1E5 == SC.upperEnergyLimit );
        REQUIRE( 0.5 == SC.spin );
        REQUIRE( 1.276553 == SC.scatteringRadius );
        REQUIRE( 0 == SC.nlValues );
      }
    }
  }
}

