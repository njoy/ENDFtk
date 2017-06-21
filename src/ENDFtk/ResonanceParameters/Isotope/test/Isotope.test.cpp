#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string sRange{
  " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
  " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
  " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n"};
std::string sCONTRange{
  " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"};
SCENARIO( "Resolved Resonance Isotope" ){
  GIVEN( "valid isotope input" ){
    WHEN( "LRU=0" ){
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
    WHEN( "LRU=1" ){
      WHEN( "there is only one range in the Isotope" ){
        std::string ENDF = sCONTRange + sRange;
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        CONT cont( 6.1148E4, 1.0, 0, 0, 1, 0 );
        ResonanceParameters::Isotope iso( cont, begin, end, lineNumber, 
                                          MAT, MF, MT );

        THEN( "the Isotope can be verified" ){
          REQUIRE( 1 == iso.ranges.size() );
        }
      }

      WHEN( "there is more than one range in the Isotope" ){
        std::string ENDF = sCONTRange + sRange + sCONTRange + sRange;
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        CONT cont( 6.1148E4, 1.0, 0, 0, 2, 0 );
        ResonanceParameters::Isotope iso( cont, begin, end, lineNumber, 
                                          MAT, MF, MT );
        THEN( "the Isotope can be verified" ){
          REQUIRE( 2 == iso.ranges.size() );
        }
      }
    }
  }

  GIVEN( "not implemented input" ){
    WHEN( "LRU=2" ){
      THEN( "an exception is thrown" ){
        std::string badCONT{
          " 1.000000-5 1.000000+0          2          1          0          06153 2151    3\n"};
        std::string ENDF = badCONT + sRange;
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;
        CONT cont( 6.1148E4, 1.0,  0, 0, 1, 0 );
        REQUIRE_THROWS( ResonanceParameters::Isotope( cont, begin, end, lineNumber, 
                                          MAT, MF, MT ) );
      }
    }
  }

  GIVEN( "invalid input" ){
    WHEN( "invalid LRU number" ){
      THEN( "an exception is thrown" ){
        std::string badCONT{
          " 1.000000-5 1.000000+0          3          1          0          06153 2151    3\n"};
        std::string ENDF = badCONT + sRange;
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        CONT cont( 6.1148E4, 1.0,  0, 0, 1, 0 );
        REQUIRE_THROWS( ResonanceParameters::Isotope( cont, begin, end, lineNumber, 
                                          MAT, MF, MT ) );
      }
      THEN( "an exception is thrown" ){
        std::string badCONT{
          " 1.000000-5 1.000000+0         -1          1          0          06153 2151    3\n"};
        std::string ENDF = badCONT + sRange;
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;
        CONT cont( 6.1148E4, 1.0,  0, 0, 1, 0 );
        REQUIRE_THROWS( ResonanceParameters::Isotope( cont, begin, end, lineNumber, 
                                          MAT, MF, MT ) );
      }
    }
  }
}
