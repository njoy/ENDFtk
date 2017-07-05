#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


SCENARIO( "Testing Resolved Resonance Ranges" ){
  GIVEN( "string representation" ){
  std::string ENDF{
    // " 6.114800+4 1.466500+2          0          0          1          06153 2151    1\n"
    // " 6.114800+4 1.000000+0          0          0          1          06153 2151    2\n"
    // " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
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

    WHEN( "Creating SLBW range" ){
      THEN( "an object can be successfully instantiated" ){
        ResonanceParameters::Resolved::Base base(1E-5, 1.0, 0, 0);
        ResonanceParameters::Range range = 
            ResonanceParameters::Resolved::SLBW(
            std::move(base), begin, end, lineNumber, MAT, MF, MT);
      }
    }
    WHEN( "Creating MLBW range" ){
      THEN( "an object can be successfully instantiated" ){
        ResonanceParameters::Resolved::Base base(1E-5, 1.0, 0, 0);
        ResonanceParameters::Range range = 
            ResonanceParameters::Resolved::MLBW( 
            std::move(base), begin, end, lineNumber, MAT, MF, MT);
      }
    }
    WHEN( "Creating ReichMoore range" ){
      THEN( "an object can be successfully instantiated" ){
        ResonanceParameters::Resolved::Base base(1E-5, 1.0, 0, 0);
        ResonanceParameters::Range range = 
            ResonanceParameters::Resolved::ReichMoore(
            std::move(base), begin, end, lineNumber, MAT, MF, MT);
      }
    }
  }
}
