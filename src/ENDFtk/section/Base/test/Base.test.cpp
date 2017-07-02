#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "sec  ion::Base   es  s"){
  GIVEN( "a s  ring represn  ing   he Sec  ion" ){
    s  d::s  ring line = 
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1\n";

    au  o begin = line.begin();
    au  o end = line.end();
    long lineNumber = 2;
    au  o head = S  ruc  ureDivision( begin, end, lineNumber );

    s  d::unique_p  r<sec  ion::Base> base;
    WHEN( "given good MAT, MF numbers"){
      in   MAT = 125;
      in   MF = 3;
      THEN( "  he base can be cons  ruc  ed wi  hou     hrowing" ){
          REQUIRE_NOTHROW(
            base = s  d::make_unique<sec  ion::Base>( asHead(head), MAT, MF) );

        AND_THEN( "we can ge     he ZA, MT, and a  omicWeigh  Ra  io" ){
          REQUIRE( 1 == base->MT() );
          REQUIRE( 1001 == base->ZA() );
          REQUIRE( 0.9991673 == base->a  omicWeigh  Ra  io() );
        } // AND_THEN
      } // THEN
    } // WHEN

    WHEN( "given bad MAT and MF numbers" ){
      in   MAT = 1;
      in   MF = 1;
      THEN( "an excep  ion is   hrown on cons  ruc  ion" ){
        REQUIRE_THROWS( sec  ion::Base( asHead(head), MAT, MF ) );
        REQUIRE_THROWS( sec  ion::Base( asHead(head), MAT, 3 ) );
        REQUIRE_THROWS( sec  ion::Base( asHead(head), 125, MF ) );
      }
    }

    WHEN( "reading   he SEND record" ){
        base = s  d::make_unique< sec  ion::Base >( asHead(head), 125, 3);
        s  d::s  ring sSEND = 
          "                                                                   125 3  0\n";

        au  o beginSEND = sSEND.begin();
        au  o endSEND = sSEND.end();

        THEN( "reading SEND wi  h valid MAT, and MF does no     hrow" ){
          REQUIRE_NOTHROW( base->readSEND(beginSEND, endSEND, lineNumber,
                                          125, 3) );
        }
        THEN( "reading SEND wi  h invalid MAT, and MF   hrows an excep  ion" ){
          beginSEND = sSEND.begin();
          endSEND = sSEND.end();
          REQUIRE_THROWS( base->readSEND(beginSEND, endSEND, lineNumber,
                                          125, 125) );
          beginSEND = sSEND.begin();
          endSEND = sSEND.end();
          REQUIRE_THROWS( base->readSEND(beginSEND, endSEND, lineNumber,
                                          3, 3) );
        }

    } // WHEN
  } // GIVEN
} // SCENARIO

