#define CATCH_CONFIG_MAIN

#include <unordered_map>

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::unordered_map< int, std::string> sLRU0 = { };

std::unordered_map< int, std::string> sLRU1 = {
  { 1, // From ENDF/B-VII.1 Pm=148m1
      " 6.114800+4 1.466500+2          0          0          1          06153 2151    1\n"
      " 6.114800+4 1.000000+0          0          0          1          06153 2151    2\n"
      " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
      " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
      " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
      " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n"
      " 0.000000+0 0.000000+0          0          0          0          06153 2  099999\n"
      " 0.000000+0 0.000000+0          0          0          0          06153 0  0    0\n" }
};

std::unordered_map< int, std::string> sLRU2 = { };
SCENARIO( "section::Type<2>" ){
  GIVEN( "a string representation of a valid File 2 Section" ){
    WHEN( "reading LRU=1, LRF=1" ){
      std::string& sMF2 = sLRU1[1];
      auto begin = sMF2.begin();
      auto end = sMF2.end();
      long lineNumber = 0;
      int MAT = 6153;
      HeadRecord HEAD( begin, end, lineNumber );

      THEN( "a section::Type<2> can be constructed" ){
        section::Type<2> MF2( HEAD, begin, end, lineNumber, MAT );
        REQUIRE( 151 == MF2.MT() );
        REQUIRE( 61148 == MF2.ZA() );
        REQUIRE( 146.65 == MF2.atomicWeightRatio() );
      }
    }
  } // GIVEN
} // SCENARIO

