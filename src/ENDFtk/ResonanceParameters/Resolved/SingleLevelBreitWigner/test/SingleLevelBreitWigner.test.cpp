#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing Resolved Resonance SLBW" ){
  GIVEN( "valid SLBW input parameters" ){
    std::string ENDF{
//    " 6.114800+4 1.466500+2          0          0          1          06153 2151    1\n"
//    " 6.114800+4 1.000000+0          0          0          1          06153 2151    2\n"
//    " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
      " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
      " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
      " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n"
      " 0.000000+0 0.000000+0          0          0          0          06153 2  099999\n"
      " 0.000000+0 0.000000+0          0          0          0          06153 0  0    0\n" };
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 6153;
    int MF = 2;
    int MT = 151;

    WHEN( "an object is successfully instantiated" ){
      ResonanceParameters::Resolved::Base base(1E-5, 1.0, 0, 0);
      ResonanceParameters::Resolved::SLBW slbw(std::move(base), begin, end, lineNumber, MAT, MF, MT);
      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == slbw.lowerEnergyLimit );
        REQUIRE( 1.0 == slbw.upperEnergyLimit );
        REQUIRE( 0 == slbw.NRO );
        REQUIRE( 0 == slbw.NAPS );
        REQUIRE( 6.0 == slbw.cont.C1() );

        {
        REQUIRE( 0.63809 == Approx( slbw.cont.C2() ) );
        REQUIRE( 0 == slbw.cont.L1() );
        REQUIRE( 0 == slbw.cont.L2() );
        REQUIRE( 1 == slbw.cont.N1() );
        REQUIRE( 0 == slbw.cont.N2() );
        }

        {
        REQUIRE( 146.6470 == Approx( slbw.list.C1() ) );
        REQUIRE( 0.0 == slbw.list.C2() );
        REQUIRE( 0 == slbw.list.L1() );
        REQUIRE( 0 == slbw.list.L2() );
        REQUIRE( 6 == slbw.list.NPL() );
        REQUIRE( 1 == slbw.list.N2() );
        }
      }
    }
  }
}
