#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string sLState();

class TestLState : public resonanceParameters::resolved::BreitWigner::LState {
public:
  using resonanceParameters::resolved::BreitWigner::LState::LState;

};

SCENARIO( "Testing BreitWigner LState" ){
  GIVEN( "LIST Record" ){
    long lineNumber = 0;
    int MAT = 1025;
    int MF = 2;
    int MT = 151;

    std::string sLIST = sLState();
    auto begin = sLIST.begin();
    auto end = sLIST.end();

    LIST list( begin, end, lineNumber, MAT, MF, MT );

    THEN( "an LState can be construted" ){
      TestLState lstate( list );

      AND_THEN( "it's parameters can be verified" ){
        REQUIRE( 19.82069 == Approx( lstate.AWRI() ) );
        REQUIRE( 0.0 == lstate.QX() );
        REQUIRE( 0 == lstate.L() );
        REQUIRE( 0 == lstate.LRX() );
        REQUIRE( 2 == lstate.NRS() );
      }
      AND_THEN( "it's resonances can be extracted" ){
        auto resonances = lstate.resonances();
        REQUIRE( 2 == resonances.size() );

        auto res0 = resonances[0];
        REQUIRE( -1.47E5    == Approx( res0.ER() ) );
        REQUIRE( 0.5        == Approx( res0.AJ() ) );
        REQUIRE( 5.430695E2 == Approx( res0.GT() ) );
        REQUIRE( 3.680695E2 == Approx( res0.GN() ) );
        REQUIRE( 1.75E2     == Approx( res0.GG() ) );
        REQUIRE( 0.0        == Approx( res0.GF() ) );

        auto res1 = resonances[1];
        REQUIRE( 4.73E5     == Approx( res1.ER() ) );
        REQUIRE( 0.5        == Approx( res1.AJ() ) );
        REQUIRE( 1.072906E5 == Approx( res1.GT() ) );
        REQUIRE( 1.0729E5   == Approx( res1.GN() ) );
        REQUIRE( 0.56       == Approx( res1.GG() ) );
        REQUIRE( 0.0        == Approx( res1.GF() ) );
      }
    }
  }
}

std::string sLState(){
  return
    /* LIST Record */
    " 1.982069+1 0.000000+0          0          0         12          21025 2151\n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151\n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 0.000000+01025 2151\n";
}
