#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Resolved Resonance Isotope" ){
  GIVEN( "valid isotope input" ){
    WHEN( "there is only one range in the Isotope" ){
      std::string ENDF{
        // " 6.114800+4 1.466500+2          0          0          1          06153 2151    1\n"
        " 6.114800+4 1.000000+0          0          0          1          06153 2151    2\n"
        " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
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

      CONT cont( begin, end, lineNumber, MAT, MF, MT );
      ResonanceParameters::Isotope iso( cont, begin, end, lineNumber, 
                                        MAT, MF, MT );

      THEN( "the Isotope can be verified" ){
        REQUIRE( 1 == iso.ranges.size() );
      }
    }
    WHEN( "there is more than one range in the Isotope" ){
      // std::string ENDF{ };
      // auto begin = ENDF.begin();
      // auto end = ENDF.end();
      // long lineNumber = 0;
      // int MAT = 6153;
      // int MF = 2;
      // int MT = 151;
    }
  }
}
