#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing Resolved Resonance SLSLBW" ){
  GIVEN( "valid ENDF parameters with TAB1" ){
    std::string ENDF{
      // " 6.916800+4 1.664920+2          0          0          1          06922 2151    1\n"
      // " 6.916800+4 1.000000+0          0          0          1          06922 2151    2\n"
      // " 1.000000-5 3.200000+0          1          2          1          06922 2151    3\n"
      " 0.000000+0 0.000000+0          0          0          1         506922 2151    4\n"
      "         50          2                                            6922 2151    5\n"
      " 1.000000-5 1.238100+0 4.000000+1 1.188400+0 5.000000+1 1.153200+06922 2151    6\n"
      " 6.000000+1 1.126500+0 7.000000+1 1.105300+0 8.000000+1 1.087800+06922 2151    7\n"
      " 9.000000+1 1.073100+0 1.000000+2 1.060500+0 2.000000+2 9.888000-16922 2151    8\n"
      " 3.000000+2 9.547000-1 4.000000+2 9.334000-1 5.000000+2 9.184000-16922 2151    9\n"
      " 6.000000+2 9.069000-1 7.000000+2 8.978000-1 8.000000+2 8.903000-16922 2151   10\n"
      " 9.000000+2 8.839000-1 1.000000+3 8.783000-1 2.000000+3 8.456000-16922 2151   11\n"
      " 3.000000+3 8.286000-1 4.000000+3 8.170000-1 5.000000+3 8.081000-16922 2151   12\n"
      " 6.000000+3 8.008000-1 7.000000+3 7.946000-1 8.000000+3 7.892000-16922 2151   13\n"
      " 9.000000+3 7.844000-1 1.000000+4 7.800000-1 1.200000+4 7.721000-16922 2151   14\n"
      " 1.400000+4 7.653000-1 1.600000+4 7.592000-1 1.800000+4 7.536000-16922 2151   15\n"
      " 2.000000+4 7.484000-1 2.500000+4 7.369000-1 3.000000+4 7.269000-16922 2151   16\n"
      " 3.500000+4 7.180000-1 4.000000+4 7.098000-1 4.200000+4 7.067000-16922 2151   17\n"
      " 4.400000+4 7.038000-1 4.600000+4 7.009000-1 4.800000+4 6.980000-16922 2151   18\n"
      " 5.000000+4 6.953000-1 5.500000+4 6.888000-1 6.000000+4 6.826000-16922 2151   19\n"
      " 6.500000+4 6.767000-1 7.000000+4 6.712000-1 7.500000+4 6.659000-16922 2151   20\n"
      " 8.000000+4 6.608000-1 8.500000+4 6.560000-1 9.000000+4 6.513000-16922 2151   21\n"
      " 9.500000+4 6.469000-1 2.000000+5 5.803000-1                      6922 2151   22\n"
      " 3.000000+0 0.000000+0          0          0          1          06922 2151   23\n"
      " 1.664920+2 0.000000+0          0          0         24          46922 2151   24\n"
      "-2.974700+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   25\n"
      "-9.747000-1 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   26\n"
      " 1.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   27\n"
      " 3.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   28\n"
      " 0.000000+0 0.000000+0          0          0          0          06922 2  099999\n"};
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 6922;
    int MF = 2;
    int MT = 151;

    WHEN( "NRO != 0" ){
      ResonanceParameters::Resolved::Base base(1E-5, 3.2, 1, 0);

      ResonanceParameters::Resolved::BreitWigner SLBW(
          std::move(base), TAB1( begin, end, lineNumber, MAT, MF, MT ), 
          begin, end, lineNumber, MAT, MF, MT);
      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == SLBW.lowerEnergyLimit );
        REQUIRE( 3.2 == SLBW.upperEnergyLimit );
        REQUIRE( 1 == SLBW.NRO );
        REQUIRE( 0 == SLBW.NAPS );

        {
        REQUIRE( 3.0 == SLBW.cont.C1() );
        REQUIRE( 0.0 == Approx( SLBW.cont.C2() ) );
        REQUIRE( 0 == SLBW.cont.L1() );
        REQUIRE( 0 == SLBW.cont.L2() );
        REQUIRE( 1 == SLBW.cont.N1() );
        REQUIRE( 0 == SLBW.cont.N2() );
        }

        {
        REQUIRE( 166.492 == Approx( SLBW.list.C1() ) );
        REQUIRE( 0.0 == SLBW.list.C2() );
        REQUIRE( 0 == SLBW.list.L1() );
        REQUIRE( 0 == SLBW.list.L2() );
        REQUIRE( 24 == SLBW.list.NPL() );
        REQUIRE( 4 == SLBW.list.N2() );
        }

        {
          REQUIRE( 0.0 == SLBW.tab1->C1() );
          REQUIRE( 0.0 == SLBW.tab1->C2() );
          REQUIRE( 0 == SLBW.tab1->L1() );
          REQUIRE( 0 == SLBW.tab1->L2() );
          REQUIRE( 1 == SLBW.tab1->NR() );
          REQUIRE( 50 == SLBW.tab1->NP() );
          REQUIRE( 50 == SLBW.tab1->xValues.size() );
          REQUIRE( 50 == SLBW.tab1->yValues.size() );
          REQUIRE( 1.0E-5 == Approx( SLBW.tab1->xValues.front() ) );
          REQUIRE( 1.2381 == Approx( SLBW.tab1->yValues.front() ) );
          REQUIRE( 2.0E5 == Approx( SLBW.tab1->xValues.back() ) );
          REQUIRE( 0.5803 == Approx( SLBW.tab1->yValues.back() ) );
        }
      }
    }
    WHEN( "NRO == 0" ){
      TAB1 throwAway( begin, end, lineNumber, MAT, MF, MT );

      ResonanceParameters::Resolved::Base base(1E-5, 3.2, 0, 0);
      ResonanceParameters::Resolved::BreitWigner SLBW(
          std::move(base), 
          begin, end, lineNumber, MAT, MF, MT);

      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == SLBW.lowerEnergyLimit );
        REQUIRE( 3.2 == SLBW.upperEnergyLimit );
        REQUIRE( 0 == SLBW.NRO );
        REQUIRE( 0 == SLBW.NAPS );

        {
        REQUIRE( 3.0 == SLBW.cont.C1() );
        REQUIRE( 0.0 == Approx( SLBW.cont.C2() ) );
        REQUIRE( 0 == SLBW.cont.L1() );
        REQUIRE( 0 == SLBW.cont.L2() );
        REQUIRE( 1 == SLBW.cont.N1() );
        REQUIRE( 0 == SLBW.cont.N2() );
        }

        {
        REQUIRE( 166.492 == Approx( SLBW.list.C1() ) );
        REQUIRE( 0.0 == SLBW.list.C2() );
        REQUIRE( 0 == SLBW.list.L1() );
        REQUIRE( 0 == SLBW.list.L2() );
        REQUIRE( 24 == SLBW.list.NPL() );
        REQUIRE( 4 == SLBW.list.N2() );
        }
        

        // Make sure there is no TAB1 Record
        REQUIRE( not SLBW.tab1 );
      }
    }
  }
}
