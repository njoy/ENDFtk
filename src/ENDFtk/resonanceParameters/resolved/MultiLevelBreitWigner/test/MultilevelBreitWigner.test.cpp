#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string Tab1();
std::string BreitWigner();

SCENARIO( "Testing resolved Resonance MLBW" ){
  GIVEN( "valid ENDF parameters with TAB1" ){

    long lineNumber = 0;
    int MAT = 6922;
    int MF = 2;
    int MT = 151;

    WHEN( "NRO == 1" ){
      auto bws = Tab1() + BreitWigner();
      auto begin = bws.begin();
      auto end = bws.end();
      
      resonanceParameters::Base base( 1E-5, 3.2, 1, 2, 1, 0 );

      std::string baseString =
        " 1.000000-5 3.200000+0          1          2          1          06922 2151     \n";
      
      resonanceParameters::resolved::MultilevelBreitWigner
        mlbw( base, begin, end, lineNumber, MAT, MF, MT );
      
      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == mlbw.EL() );
        REQUIRE( 3.2 == mlbw.EH() );
        REQUIRE( 1 == mlbw.NRO() );
        REQUIRE( 0 == mlbw.NAPS() );
        REQUIRE( 26 == mlbw.NC() );
        
        REQUIRE( 3.0 == mlbw.SPI() );
        REQUIRE( 0.0 == Approx( mlbw.AP() ) );
        REQUIRE( 1 == mlbw.NLS() );

        REQUIRE( 166.492 == Approx( mlbw.LISTS().front().C1() ) );
        REQUIRE( 0.0 == mlbw.LISTS().front().C2() );
        REQUIRE( 0 == mlbw.LISTS().front().L1() );
        REQUIRE( 0 == mlbw.LISTS().front().L2() );
        REQUIRE( 24 == mlbw.LISTS().front().NPL() );
        REQUIRE( 4 == mlbw.LISTS().front().N2() );

        REQUIRE( 0.0 == mlbw.APE().C1() );
        REQUIRE( 0.0 == mlbw.APE().C2() );
        REQUIRE( 0 == mlbw.APE().L1() );
        REQUIRE( 0 == mlbw.APE().L2() );
        REQUIRE( 1 == mlbw.APE().NR() );
        REQUIRE( 50 == mlbw.APE().NP() );
        REQUIRE( 50 == mlbw.APE().x().size() );
        REQUIRE( 50 == mlbw.APE().y().size() );
        REQUIRE( 1.0E-5 == Approx( mlbw.APE().x().front() ) );
        REQUIRE( 1.2381 == Approx( mlbw.APE().y().front() ) );
        REQUIRE( 2.0E5 == Approx( mlbw.APE().x().back() ) );
        REQUIRE( 0.5803 == Approx( mlbw.APE().y().back() ) );
      }

      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        mlbw.print( output, MAT, MF, MT );

        REQUIRE( buffer == baseString + Tab1() + BreitWigner() );

      }
    }

    WHEN( "NRO == 0" ){
      auto bws = BreitWigner();
      auto begin = bws.begin();
      auto end = bws.end();
      
      resonanceParameters::Base base( 1E-5, 3.2, 1, 2, 0, 0 );
      std::string baseString =
        " 1.000000-5 3.200000+0          1          2          0          06922 2151     \n";
      
      resonanceParameters::resolved::MultilevelBreitWigner
        mlbw( base, begin, end, lineNumber, MAT, MF, MT);

      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == mlbw.EL() );
        REQUIRE( 3.2 == mlbw.EH() );
        REQUIRE( 0 == mlbw.NRO() );
        REQUIRE( 0 == mlbw.NAPS() );
        REQUIRE( 7 == mlbw.NC() );

        REQUIRE( 3.0 == mlbw.SPI() );
        REQUIRE( 0.0 == Approx( mlbw.AP() ) );
        REQUIRE( 1 == mlbw.NLS() );

        REQUIRE( 166.492 == Approx( mlbw.LISTS().front().C1() ) );
        REQUIRE( 0.0 == mlbw.LISTS().front().C2() );
        REQUIRE( 0 == mlbw.LISTS().front().L1() );
        REQUIRE( 0 == mlbw.LISTS().front().L2() );
        REQUIRE( 24 == mlbw.LISTS().front().NPL() );
        REQUIRE( 4 == mlbw.LISTS().front().N2() );
      }

      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        mlbw.print( output, MAT, MF, MT );

        REQUIRE( buffer == baseString + BreitWigner() );

      }
    }
  }
  GIVEN( "invalid ENDF parameters" ){
    long lineNumber = 0;
    int MAT = 7922;
    int MF = 2;
    int MT = 151;

    auto bws = Tab1() + BreitWigner();
    auto begin = bws.begin();
    auto end = bws.end();
    
    resonanceParameters::Base base( 1E-5, 3.2, 1, 2, 1, 0 );
    THEN( "an exception is thrown" ){

      REQUIRE_THROWS(
        resonanceParameters::resolved::MultilevelBreitWigner( 
            base, begin, end, lineNumber, MAT, MF, MT ) );
    }
  }
}

std::string BreitWigner(){
  return
    /* cont record */
    " 3.000000+0 0.000000+0          0          0          1          06922 2151     \n"
    /* list record */                                                                
    " 1.664920+2 0.000000+0          0          0         24          46922 2151     \n"
    "-2.974700+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151     \n"
    "-9.747000-1 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151     \n"
    " 1.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151     \n"
    " 3.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151     \n";
}

std::string Tab1(){
  return
    " 0.000000+0 0.000000+0          0          0          1         506922 2151     \n"
    "         50          2                                            6922 2151     \n"
    " 1.000000-5 1.238100+0 4.000000+1 1.188400+0 5.000000+1 1.153200+06922 2151     \n"
    " 6.000000+1 1.126500+0 7.000000+1 1.105300+0 8.000000+1 1.087800+06922 2151     \n"
    " 9.000000+1 1.073100+0 1.000000+2 1.060500+0 2.000000+2 9.888000-16922 2151     \n"
    " 3.000000+2 9.547000-1 4.000000+2 9.334000-1 5.000000+2 9.184000-16922 2151     \n"
    " 6.000000+2 9.069000-1 7.000000+2 8.978000-1 8.000000+2 8.903000-16922 2151     \n"
    " 9.000000+2 8.839000-1 1.000000+3 8.783000-1 2.000000+3 8.456000-16922 2151     \n"
    " 3.000000+3 8.286000-1 4.000000+3 8.170000-1 5.000000+3 8.081000-16922 2151     \n"
    " 6.000000+3 8.008000-1 7.000000+3 7.946000-1 8.000000+3 7.892000-16922 2151     \n"
    " 9.000000+3 7.844000-1 1.000000+4 7.800000-1 1.200000+4 7.721000-16922 2151     \n"
    " 1.400000+4 7.653000-1 1.600000+4 7.592000-1 1.800000+4 7.536000-16922 2151     \n"
    " 2.000000+4 7.484000-1 2.500000+4 7.369000-1 3.000000+4 7.269000-16922 2151     \n"
    " 3.500000+4 7.180000-1 4.000000+4 7.098000-1 4.200000+4 7.067000-16922 2151     \n"
    " 4.400000+4 7.038000-1 4.600000+4 7.009000-1 4.800000+4 6.980000-16922 2151     \n"
    " 5.000000+4 6.953000-1 5.500000+4 6.888000-1 6.000000+4 6.826000-16922 2151     \n"
    " 6.500000+4 6.767000-1 7.000000+4 6.712000-1 7.500000+4 6.659000-16922 2151     \n"
    " 8.000000+4 6.608000-1 8.500000+4 6.560000-1 9.000000+4 6.513000-16922 2151     \n"
    " 9.500000+4 6.469000-1 2.000000+5 5.803000-1                      6922 2151     \n";
}
