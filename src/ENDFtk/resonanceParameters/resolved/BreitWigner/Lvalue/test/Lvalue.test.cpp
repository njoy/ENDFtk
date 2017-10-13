#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string sLvalue();

class TestLvalue : public resonanceParameters::resolved::BreitWigner::Lvalue {
public:
  using resonanceParameters::resolved::BreitWigner::Lvalue::Lvalue;
};

SCENARIO( "Testing BreitWigner Lvalue" ){
  GIVEN( "LIST Record" ){
    long lineNumber = 0;
    int MAT = 1025;
    int MF = 2;
    int MT = 151;

    std::string sLIST = sLvalue();
    auto begin = sLIST.begin();
    auto end = sLIST.end();

    LIST list( begin, end, lineNumber, MAT, MF, MT );

    THEN( "an Lvalue can be constructed" ){
      TestLvalue lValue( list );

      AND_THEN( "its parameters can be verified" ){
        REQUIRE( 19.82069 == Approx( lValue.AWRI() ) );
        REQUIRE( 1.0 == Approx( lValue.QX() ) );
        REQUIRE( 0 == lValue.L() );
        REQUIRE( 1 == lValue.LRX() );
        REQUIRE( 2 == lValue.NRS() );

        auto resonances = lValue.resonances();
        
        REQUIRE( Approx(-1.47E5) == resonances[0].ER() );
        REQUIRE( Approx(4.73E5)  == resonances[1].ER() );
        REQUIRE( Approx(0.5)  == resonances[0].AJ() );
        REQUIRE( Approx(1.5)  == resonances[1].AJ() );

        REQUIRE( 5.430695E2 == Approx( resonances[0].GT() ) );
        REQUIRE( 1.072906E5 == Approx( resonances[1].GT() ) );

        REQUIRE( 3.680695E2 == Approx( resonances[0].GN() ) );
        REQUIRE( 1.072900E5 == Approx( resonances[1].GN() ) );

        REQUIRE( 1.75E2 == Approx( resonances[0].GG() ) );
        REQUIRE( 5.6E-1 == Approx( resonances[1].GG() ) );

        REQUIRE( 0.0 == Approx( resonances[0].GF() ) );
        REQUIRE( 0.0 == Approx( resonances[1].GF() ) );
      }
    }
  }
}

std::string sLvalue(){
  return
    /* LIST Record */
    " 1.982069+1 1.000000+0          0          1         12          21025 2151\n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151\n"
    " 4.730000+5 1.500000+0 1.072906+5 1.072900+5 5.600000-1 0.000000+01025 2151\n";

}