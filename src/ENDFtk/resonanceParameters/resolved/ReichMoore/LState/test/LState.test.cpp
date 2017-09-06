#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string sLState();

class TestLState : public resonanceParameters::resolved::ReichMoore::LState {
public:
  using resonanceParameters::resolved::ReichMoore::LState::stride;
  using resonanceParameters::resolved::ReichMoore::LState::LState;

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
        REQUIRE( 0.0 == lstate.APL() );
        REQUIRE( 0 == lstate.L() );
        REQUIRE( 2 == lstate.NRS() );

        REQUIRE( -1.47E5 == lstate.stride(0)[0] );
        REQUIRE( 4.73E5  == lstate.stride(0)[1] );
        REQUIRE( -1.47E5 == lstate.resonanceEnergies()[0] );
        REQUIRE( 4.73E5  == lstate.resonanceEnergies()[1] );

        REQUIRE( 5.0E-1  == lstate.stride(1)[0] );
        REQUIRE( 5.0E-1  == lstate.stride(1)[1] );
        REQUIRE( 5.0E-1  == lstate.AJs()[0] );
        REQUIRE( 5.0E-1  == lstate.AJs()[1] );

        REQUIRE( 5.430695E2 == Approx( lstate.stride(2)[0] ) );
        REQUIRE( 1.072906E5 == Approx( lstate.stride(2)[1] ) );
        REQUIRE( 5.430695E2 == Approx( lstate.neutronWidths()[0] ) );
        REQUIRE( 1.072906E5 == Approx( lstate.neutronWidths()[1] ) );

        REQUIRE( 3.680695E2 == Approx( lstate.stride(3)[0] ) );
        REQUIRE( 1.072900E5 == Approx( lstate.stride(3)[1] ) );
        REQUIRE( 3.680695E2 == Approx( lstate.radiationWidths()[0] ) );
        REQUIRE( 1.072900E5 == Approx( lstate.radiationWidths()[1] ) );

        REQUIRE( 1.75E2 == Approx( lstate.stride(4)[0] ) );
        REQUIRE( 5.6E-1 == Approx( lstate.stride(4)[1] ) );
        REQUIRE( 1.75E2 == Approx( lstate.firstPartialFissionWidths()[0] ) );
        REQUIRE( 5.6E-1 == Approx( lstate.firstPartialFissionWidths()[1] ) );

        REQUIRE( 0.0 == Approx( lstate.stride(5)[0] ) );
        REQUIRE( 0.0 == Approx( lstate.stride(5)[1] ) );
        REQUIRE( 0.0 == Approx( lstate.secondPartialFissionWidths()[0] ) );
        REQUIRE( 0.0 == Approx( lstate.secondPartialFissionWidths()[1] ) );
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
