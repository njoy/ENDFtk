#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing Resolved Resonance ReichMoore" ){
  GIVEN( "valid ReichMoore input parameters when NRO=0" ){
    std::string ENDF{
      // " 1.402800+4 2.773700+1          0          0          1          01425 2151    1\n"
      // " 1.402800+4 1.000000+0          0          0          1          01425 2151    2\n"
      // " 1.000000-5 1.750000+6          1          3          0          11425 2151    3\n"
      " 0.000000+0 4.136400-1          1          0          3          31425 2151    4\n"
      " 2.773700+1 4.136400-1          0          0         96         161425 2151    5\n"
      "-3.622100+6 5.000000-1 3.936200+6 1.453600+2 0.000000+0 0.000000+01425 2151    6\n"
      "-8.737300+5 5.000000-1 1.015100-1 1.025300+0 0.000000+0 0.000000+01425 2151    7\n"
      "-3.652900+5 5.000000-1 3.040600-2 1.000000+0 0.000000+0 0.000000+01425 2151    8\n"
      "-6.315900+4 5.000000-1 4.689400-2 1.000000+0 0.000000+0 0.000000+01425 2151    9\n"
      "-4.880100+4 5.000000-1 9.249600-3 1.000000+0 0.000000+0 0.000000+01425 2151   10\n"
      " 5.567700+4 5.000000-1 6.533100+2 1.580300+0 0.000000+0 0.000000+01425 2151   11\n"
      " 1.816200+5 5.000000-1 3.489400+4 5.600000+0 0.000000+0 0.000000+01425 2151   12\n"
      " 3.013100+5 5.000000-1 2.354800+0 3.600000+0 0.000000+0 0.000000+01425 2151   13\n"
      " 5.902900+5 5.000000-1 5.236600+2 3.600000+0 0.000000+0 0.000000+01425 2151   14\n"
      " 1.085200+6 5.000000-1 7.279400+1 3.600000+0 0.000000+0 0.000000+01425 2151   15\n"
      " 1.162700+6 5.000000-1 3.013600+3 3.800000+0 0.000000+0 0.000000+01425 2151   16\n"
      " 1.201200+6 5.000000-1 4.601200+3 3.600000+0 0.000000+0 0.000000+01425 2151   17\n"
      " 1.256400+6 5.000000-1 1.738300+4 3.600000+0 0.000000+0 0.000000+01425 2151   18\n"
      " 2.248700+6 5.000000-1 4.447600+5 3.600000+0 0.000000+0 0.000000+01425 2151   19\n"
      " 3.007300+6 5.000000-1 2.899600+2 3.600000+0 0.000000+0 0.000000+01425 2151   20\n"
      " 3.067800+6 5.000000-1 4.222900+2 3.600000+0 0.000000+0 0.000000+01425 2151   21\n"
      " 2.773700+1 4.943700-1          1          0        102         171425 2151   22\n"
      " 6.773300+4 1.500000+0 2.658900+0 2.500000+0 0.000000+0 0.000000+01425 2151   23\n"
      " 8.679700+4 1.500000+0 7.261800-1 2.500000+0 0.000000+0 0.000000+01425 2151   24\n"
      " 3.996800+5 1.500000+0 8.136100-1 6.600000-1 0.000000+0 0.000000+01425 2151   25\n"
      " 5.326600+5 1.500000+0 5.328100+2 2.500000+0 0.000000+0 0.000000+01425 2151   26\n"
      " 5.655800+5 1.500000+0 1.095300+4 2.900000+0 0.000000+0 0.000000+01425 2151   27\n"
      " 5.871700+5 5.000000-1 1.991600+2 8.800000+0 0.000000+0 0.000000+01425 2151   28\n"
      " 7.140400+5 1.500000+0 1.216500+0 2.500000+0 0.000000+0 0.000000+01425 2151   29\n"
      " 8.124900+5 1.500000+0 3.010000+4 9.700000+0 0.000000+0 0.000000+01425 2151   30\n"
      " 9.100400+5 1.500000+0 3.673300+3 1.130000+0 0.000000+0 0.000000+01425 2151   31\n"
      " 9.622300+5 5.000000-1 7.661400+4 1.600000+1 0.000000+0 0.000000+01425 2151   32\n"
      " 1.199500+6 5.000000-1 1.491400+4 7.600000+0 0.000000+0 0.000000+01425 2151   33\n"
      " 1.408300+6 1.500000+0 5.198300+3 2.700000+0 0.000000+0 0.000000+01425 2151   34\n"
      " 1.482400+6 5.000000-1 8.869400-1 8.800000+0 0.000000+0 0.000000+01425 2151   35\n"
      " 1.592800+6 5.000000-1 1.119900+4 8.800000+0 0.000000+0 0.000000+01425 2151   36\n"
      " 1.658600+6 5.000000-1 1.555300+3 8.800000+0 0.000000+0 0.000000+01425 2151   37\n"
      " 1.805700+6 1.500000+0 1.299100+3 2.500000+0 0.000000+0 0.000000+01425 2151   38\n"
      " 1.852400+6 1.500000+0 7.070700+4 2.500000+0 0.000000+0 0.000000+01425 2151   39\n"
      " 2.773700+1 4.136400-1          2          0        150         251425 2151   40\n"
      " 3.174000+4 2.500000+0 1.566700-2 1.000000+0 0.000000+0 0.000000+01425 2151   41\n"
      " 7.080000+4 2.500000+0 2.961700-2 1.000000+0 0.000000+0 0.000000+01425 2151   42\n"
      " 2.987000+5 2.500000+0 9.886000+0 1.000000+0 0.000000+0 0.000000+01425 2151   43\n"
      " 3.545900+5 2.500000+0 1.446000+1 1.000000+0 0.000000+0 0.000000+01425 2151   44\n"
      " 6.024700+5 1.500000+0 5.049100+1 3.400000+0 0.000000+0 0.000000+01425 2151   45\n"
      " 7.717100+5 2.500000+0 5.313900+1 1.000000+0 0.000000+0 0.000000+01425 2151   46\n"
      " 8.452300+5 1.500000+0 3.979100+2 2.000000+0 0.000000+0 0.000000+01425 2151   47\n"
      " 8.723100+5 2.500000+0 3.214000+1 1.300000+0 0.000000+0 0.000000+01425 2151   48\n"
      " 1.017800+6 2.500000+0 7.619200+1 1.000000+0 0.000000+0 0.000000+01425 2151   49\n"
      " 1.042900+6 2.500000+0 9.337000+2 1.000000+0 0.000000+0 0.000000+01425 2151   50\n"
      " 1.148100+6 2.500000+0 3.146900+0 1.000000+0 0.000000+0 0.000000+01425 2151   51\n"
      " 1.264400+6 2.500000+0 8.436400+2 1.000000+0 0.000000+0 0.000000+01425 2151   52\n"
      " 1.379900+6 1.500000+0 6.529900+1 2.400000+0 0.000000+0 0.000000+01425 2151   53\n"
      " 1.479900+6 1.500000+0 3.502500+3 1.650000+0 0.000000+0 0.000000+01425 2151   54\n"
      " 1.512300+6 2.500000+0 9.149300+1 1.000000+0 0.000000+0 0.000000+01425 2151   55\n"
      " 1.528700+6 1.500000+0 2.922500+3 2.400000+0 0.000000+0 0.000000+01425 2151   56\n"
      " 1.580600+6 1.500000+0 1.495500+3 2.400000+0 0.000000+0 0.000000+01425 2151   57\n"
      " 1.597200+6 1.500000+0 4.017200+3 2.400000+0 0.000000+0 0.000000+01425 2151   58\n"
      " 1.639600+6 2.500000+0 1.529300+4 1.000000+0 0.000000+0 0.000000+01425 2151   59\n"
      " 1.651100+6 2.500000+0 2.155500+4 1.000000+0 0.000000+0 0.000000+01425 2151   60\n"
      " 1.665000+6 1.500000+0 2.159000+2 2.400000+0 0.000000+0 0.000000+01425 2151   61\n"
      " 1.785000+6 1.500000+0 1.929400+2 2.400000+0 0.000000+0 0.000000+01425 2151   62\n"
      " 1.850700+6 2.500000+0 3.551500+4 1.000000+0 0.000000+0 0.000000+01425 2151   63\n"
      " 1.923700+6 2.500000+0 1.017100+3 1.000000+0 0.000000+0 0.000000+01425 2151   64\n"
      " 1.968900+6 2.500000+0 5.734100+3 1.000000+0 0.000000+0 0.000000+01425 2151   65\n"
      " 0.000000+0 0.000000+0          0          0          0          01425 2  099999\n"};
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 1425;
    int MF = 2;
    int MT = 151;

    WHEN( "an object is successfully instantiated" ){
      ResonanceParameters::Resolved::Base base(1E-5, 1.75E6, 0, 1);
      ResonanceParameters::Resolved::ReichMoore rm(
          std::move(base), begin, end, lineNumber, MAT, MF, MT);
      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == rm.lowerEnergyLimit );
        REQUIRE( 1.75E6 == rm.upperEnergyLimit );
        REQUIRE( 0 == rm.NRO );
        REQUIRE( 1 == rm.NAPS );

        {
        REQUIRE( 0.0 == rm.cont.C1() );
        REQUIRE( 0.41364 == Approx( rm.cont.C2() ) );
        REQUIRE( 1 == rm.cont.L1() );
        REQUIRE( 0 == rm.cont.L2() );
        REQUIRE( 3 == rm.cont.N1() );
        REQUIRE( 3 == rm.cont.N2() );
        }

        {
        REQUIRE( 27.737 == Approx( rm.list.C1() ) );
        REQUIRE( 0.41364 == rm.list.C2() );
        REQUIRE( 0 == rm.list.L1() );
        REQUIRE( 0 == rm.list.L2() );
        REQUIRE( 96 == rm.list.NPL() );
        REQUIRE( 16 == rm.list.N2() );
        }
        

        // Make sure there is no TAB1 Record
        REQUIRE( not rm.tab1 );
      }
    }
  }
}