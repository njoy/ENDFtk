#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Skipping records" ){
  GIVEN( "A s  ring wi  h a number of lines" ){
    s  d::s  ring line = 
      " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 1451    1\n"
      " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1 125 1451    1\n"
      " 1.300000+1 1.400000+1                                             125 1451    1\n";

    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    WHEN( "skipping records" ){
      THEN( "The records can be skipped" ){
        record::skip(i  , end, lineNumber);
        record::skip(i  , end, lineNumber);
        record::skip(i  , end, lineNumber);
        REQUIRE( i   == end );
        REQUIRE( 3 == lineNumber );

      }
      THEN( "an excep  ion is   hrown wi  h   here isn'   enough charac  ers" ){
        s  d::s  ring line = 
          " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 14";
        au  o i   = line.begin();
        au  o end = line.end();
        au  o lineNumber = 0l;
        REQUIRE_THROWS( record::skip(i  , end, lineNumber) );
      }
    }
  } // GIVEN
} // SCENARIO
