
#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

class TestBreitWigner : public resonanceParameters::resolved::BreitWigner {
public:
  template< typename... Args >
  TestBreitWigner( Args&&... args ) :
    BreitWigner( std::forward<Args>(args)... ){}
};

std::string LBreitWigner();

SCENARIO( "Testing unresolved resonance Lvalues" ){
  GIVEN( "valid ENDF paramaters without TAB1" ){
    long lineNumber = 0;
    int MAT = 1025;
    int MF = 2;
    int MT = 151;

    std::string bws = LBreitWigner();
    auto begin = bws.begin();
    auto end = bws.end();

    resonanceParameters::Base base( 1E-5, 2.201E6, 1, 2, 0, 0 );
    TestBreitWigner bw( base, begin, end, lineNumber, MAT, MF, MT );

    WHEN( "extracting the lValues" ){
      auto lValues = bw.lValues();

      THEN( "the Lvalue parameters can be verified" ){
        REQUIRE( 3 == lValues.size() );

        REQUIRE( -1.47E5 == Approx( lValues[0].resonances()[0].ER() ) );
        REQUIRE(  1.47E5 == Approx( lValues[1].resonances()[0].ER() ) );
        REQUIRE(  1.37E6 == Approx( lValues[2].resonances()[0].ER() ) );

        REQUIRE( 0.5 == Approx( lValues[0].resonances()[0].AJ() ) );
        REQUIRE( 0.5 == Approx( lValues[1].resonances()[0].AJ() ) );
        REQUIRE( 1.5 == Approx( lValues[2].resonances()[0].AJ() ) );

        REQUIRE( 5.430695E2 == Approx( lValues[0].resonances()[0].GT() ) );
        REQUIRE( 3.210160E2 == Approx( lValues[1].resonances()[0].GT() ) );
        REQUIRE( 8.175E3    == Approx( lValues[2].resonances()[0].GT() ) );

        REQUIRE( 3.680695E2 == Approx( lValues[0].resonances()[0].GN() ) );
        REQUIRE( 3.19E2     == Approx( lValues[1].resonances()[0].GN() ) );
        REQUIRE( 8.0E3      == Approx( lValues[2].resonances()[0].GN() ) );

        REQUIRE( 1.75E2     == Approx( lValues[0].resonances()[0].GG() ) );
        REQUIRE( 2.016      == Approx( lValues[1].resonances()[0].GG() ) );
        REQUIRE( 1.75E2     == Approx( lValues[2].resonances()[0].GG() ) );

        REQUIRE( 0.0        == Approx( lValues[0].resonances()[0].GF() ) );
        REQUIRE( 0.0        == Approx( lValues[1].resonances()[0].GF() ) );
        REQUIRE( 0.0        == Approx( lValues[2].resonances()[0].GF() ) );
      }
    }

  }
}

std::string LBreitWigner(){
  return
    /* HEAD Record */
    // " 1.002000+4 1.982070+1          0          0          1          01025 2151\n"
    /* CONT Record */
    // " 1.002000+4 1.000000+0          0          0          1          01025 2151\n"
    /* range CONT Record */
    // " 1.000000-5 2.201000+6          1          2          0          11025 2151\n"
    /* CONT Record */
    " 0.000000+0 5.200000-1          0          0          3          01025 2151\n"
    /* LIST Record */
    " 1.982069+1 0.000000+0          0          0         12          21025 2151\n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151\n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 0.000000+01025 2151\n"
    /* LIST Record */
    " 1.982069+1 0.000000+0          1          0         48          81025 2151\n"
    " 1.470000+5 5.000000-1 3.210160+2 3.190000+2 2.016000+0 0.000000+01025 2151\n"
    " 9.100000+5 1.500000+0 1.400202+4 1.400000+4 2.016000+0 0.000000+01025 2151\n"
    " 1.280000+6 1.500000+0 6.002016+3 6.000000+3 2.016000+0 0.000000+01025 2151\n"
    " 1.310000+6 5.000000-1 3.200202+4 3.200000+4 2.016000+0 0.000000+01025 2151\n"
    " 1.620000+6 1.500000+0 2.700202+4 2.700000+4 2.016000+0 0.000000+01025 2151\n"
    " 1.849000+6 1.500000+0 6.002016+3 6.000000+3 2.016000+0 0.000000+01025 2151\n"
    " 2.016000+6 1.500000+0 5.400202+4 5.400000+4 2.016000+0 0.000000+01025 2151\n"
    " 2.124000+6 1.500000+0 5.000202+4 5.000000+4 2.016000+0 0.000000+01025 2151\n"
    /* LIST Record */
    " 1.982069+1 0.000000+0          2          0         18          31025 2151\n"
    " 1.370000+6 1.500000+0 8.175000+3 8.000000+3 1.750000+2 0.000000+01025 2151\n"
    " 1.680000+6 1.500000+0 1.017500+4 1.000000+4 1.750000+2 0.000000+01025 2151\n"
    " 1.930000+6 1.500000+0 3.817500+4 3.800000+4 1.750000+2 0.000000+01025 2151\n"
    "                                                                  1025 2  0\n"
    "                                                                  1025 0  0\n";
}
