#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string sLState(){
  return
    /* LIST Record */
    " 1.982069+1 0.000000+0          0          0         12          21025 2151\n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151\n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 0.000000+01025 2151\n";
}

SCENARIO( "Testing BreitWigner LState Resonance" ){
  GIVEN( "LIST Record" ){
    long lineNumber = 0;
    int MAT = 1025;
    int MF = 2;
    int MT = 151;

    std::string sLIST = sLState();
    auto begin = sLIST.begin();
    auto end = sLIST.end();

    LIST list( begin, end, lineNumber, MAT, MF, MT );

    WHEN( "converting the LIST Record into 'chunks'" ){
      auto chunks = list.B() | ranges::view::chunk( 6 );

      THEN( "the parameters can be verified" ){
        resonanceParameters::resolved::ReichMoore::LState::Resonance R0( chunks[0] );
        REQUIRE( -1.47E5    == Approx( R0.ER() ) );
        REQUIRE( 0.5        == Approx( R0.AJ() ) );
        REQUIRE( 5.43069E2  == Approx( R0.GN() ) );
        REQUIRE( 3.680695E2 == Approx( R0.GG() ) );
        REQUIRE( 1.75E2     == Approx( R0.GFA() ) );
        REQUIRE( 0.0        == Approx( R0.GFB() ) );

        resonanceParameters::resolved::ReichMoore::LState::Resonance R1( chunks[1] );
        REQUIRE( 4.73E5     == Approx( R1.ER() ) );
        REQUIRE( 0.5        == Approx( R1.AJ() ) );
        REQUIRE( 1.072906E5 == Approx( R1.GN() ) );
        REQUIRE( 1.0729E5   == Approx( R1.GG() ) );
        REQUIRE( 5.6E-1     == Approx( R1.GFA() ) );
        REQUIRE( 0.0        == Approx( R1.GFB() ) );
      }
    }
  }
}
