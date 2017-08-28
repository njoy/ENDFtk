#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string ENDF();

SCENARIO( "Energy-dependent unresolved resonances LState" ){
  GIVEN( "Valid LState" ){
    long lineNumber = 0;
    int MAT = 3843;
    int MF = 2;
    int MT = 151;
    auto endf = ENDF();
    auto begin = endf.begin();
    auto end = endf.end();

    CONT cont( begin, end, lineNumber, MAT, MF, MT );
    resonanceParameters::unresolved::Unresolved::LState lstate( 
        cont, begin, end, lineNumber, MAT, MF, MT );
    THEN( "the parameters can be verified" ){
      REQUIRE( 8.91354E1 == lstate.AWRI() );
      REQUIRE( 1 == lstate.L() );
      REQUIRE( 2 == lstate.LISTs().size() );
    }
  }
  GIVEN( "invalid ENDF, negative L-value" ){
    long lineNumber = 0;
    int MAT = 3843;
    int MF = 2;
    int MT = 151;

    auto endf = ENDF();
    auto begin = endf.begin();
    auto end = endf.end();
    CONT cont( begin, end, lineNumber, MAT, MF, MT );

    WHEN( "L value is negative" ){
      std::string sCONT = 
        " 8.913540+1 0.000000+0         -1          0          2          03843 2151   21\n";
      auto cbegin = sCONT.begin();
      auto cend = sCONT.end();
      cont = CONT( cbegin, cend, lineNumber, MAT, MF, MT );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          resonanceParameters::unresolved::Unresolved::LState( 
            cont, begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "NJS value is negative" ){
      njoy::Log::debug( "Should find negative NJS value" );
      std::string sCONT = 
        " 8.913540+1 0.000000+0          1          0         -2          03843 2151   21\n";
      auto cbegin = sCONT.begin();
      auto cend = sCONT.end();
      cont = CONT( cbegin, cend, lineNumber, MAT, MF, MT );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          resonanceParameters::unresolved::Unresolved::LState( 
            cont, begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
  }
}

std::string ENDF(){
  return
  // L=1 CONT
  " 8.913540+1 0.000000+0          1          0          2          03843 2151   21\n"
  // L=1,J=0 LIST
  " 5.000000-1 0.000000+0          5          0         84         133843 2151   22\n"
  " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+03843 2151   23\n"
  " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151   24\n"
  " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151   25\n"
  " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151   26\n"
  " 1.000000+4 1.231300+4 0.000000+0 6.673600+0 2.050000-1 0.000000+03843 2151   27\n"
  " 1.500000+4 1.226300+4 0.000000+0 6.646600+0 2.050000-1 0.000000+03843 2151   28\n"
  " 2.500000+4 1.212200+4 0.000000+0 6.569900+0 2.050000-1 0.000000+03843 2151   29\n"
  " 3.000000+4 1.205400+4 0.000000+0 6.533500+0 2.050000-1 0.000000+03843 2151   30\n"
  " 4.000000+4 1.191800+4 0.000000+0 6.459600+0 2.050000-1 0.000000+03843 2151   31\n"
  " 5.000000+4 1.181000+4 0.000000+0 6.401200+0 2.050000-1 0.000000+03843 2151   32\n"
  " 6.000000+4 1.113000+4 0.000000+0 6.032400+0 2.050000-1 0.000000+03843 2151   33\n"
  " 7.000000+4 1.077400+4 0.000000+0 5.839300+0 2.050000-1 0.000000+03843 2151   34\n"
  " 8.000000+4 1.039500+4 0.000000+0 5.634100+0 2.050000-1 0.000000+03843 2151   35\n"
  " 1.000000+5 9.669700+3 0.000000+0 5.241000+0 2.050000-1 0.000000+03843 2151   36\n"
  // L=1,J=1 LIST
  " 1.500000+0 0.000000+0          5          0         84         133843 2151   37\n"
  " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 0.000000+0 0.000000+03843 2151   38\n"
  " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151   39\n"
  " 7.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151   40\n"
  " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151   41\n"
  " 1.000000+4 6.156500+3 0.000000+0 3.336800+0 2.050000-1 0.000000+03843 2151   42\n"
  " 1.500000+4 6.131600+3 0.000000+0 3.323300+0 2.050000-1 0.000000+03843 2151   43\n"
  " 2.500000+4 6.060800+3 0.000000+0 3.285000+0 2.050000-1 0.000000+03843 2151   44\n"
  " 3.000000+4 6.027200+3 0.000000+0 3.266800+0 2.050000-1 0.000000+03843 2151   45\n"
  " 4.000000+4 5.959100+3 0.000000+0 3.229800+0 2.050000-1 0.000000+03843 2151   46\n"
  " 5.000000+4 5.905100+3 0.000000+0 3.200600+0 2.050000-1 0.000000+03843 2151   47\n"
  " 6.000000+4 5.564900+3 0.000000+0 3.016200+0 2.050000-1 0.000000+03843 2151   48\n"
  " 7.000000+4 5.386800+3 0.000000+0 2.919600+0 2.050000-1 0.000000+03843 2151   49\n"
  " 8.000000+4 5.197500+3 0.000000+0 2.817000+0 2.050000-1 0.000000+03843 2151   50\n"
  " 1.000000+5 4.834900+3 0.000000+0 2.620500+0 2.050000-1 0.000000+03843 2151   51\n";
}
