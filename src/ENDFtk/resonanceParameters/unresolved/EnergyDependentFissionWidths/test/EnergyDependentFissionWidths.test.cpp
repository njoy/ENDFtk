#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string LRF2();
std::string Tab1();

SCENARIO( "Testing energy-dependent fission width unresolved resonances" ){
  GIVEN( "valid ENDF parameters" ){
    long lineNumber = 0;
    int MAT = 9440;
    int MF = 2;
    int MT = 151;

    WHEN( "NRO == 0" ){
      std::string ENDF = LRF2();
      auto begin = ENDF.begin();
      auto end = ENDF.end();

      resonanceParameters::Base base( 5.7E3, 4.0E4, 2, 1, 0, 0 );
      std::string baseString =
        " 5.700000+3 4.000000+4          2          1          0          09440 2151     \n";
      resonanceParameters::unresolved::EnergyDependentFissionWidths edfw( 
          base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the parameters can be verified" ){
        REQUIRE( 5.7E3 == edfw.EL() );
        REQUIRE( 4.0E4 == edfw.EH() );
        REQUIRE( 0 == edfw.NRO() );
        REQUIRE( 0 == edfw.NAPS() );
        REQUIRE( 33 == edfw.NC() );

        REQUIRE( 0.0 == edfw.SPI() );
        REQUIRE( 8.88E-1 == Approx( edfw.AP() ) );
        REQUIRE( 0 == edfw.LSSF() );
        REQUIRE( 14 == edfw.NE() );
        REQUIRE( 3 == edfw.NLS() );
        REQUIRE( 3 == edfw.lValues().size() );
      }

      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        edfw.print( output, MAT, MF, MT );

        REQUIRE( buffer == baseString + LRF2() );
      }
    }
    
    WHEN( "NRO != 0" ){
      std::string ENDF = Tab1() + LRF2();
      auto begin = ENDF.begin();
      auto end = ENDF.end();

      resonanceParameters::Base base( 5.7E3, 4.0E4, 2, 1, 1, 0 );
      resonanceParameters::unresolved::EnergyDependentFissionWidths edfw( 
          base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the parameters can be verified" ){
        REQUIRE( Approx(5.7E3) == edfw.EL() );
        REQUIRE( Approx(4.0E4) == edfw.EH() );
        REQUIRE( 1 == edfw.NRO() );
        REQUIRE( 0 == edfw.NAPS() );

        REQUIRE( 0.0 == edfw.SPI() );
        REQUIRE( 8.88E-1 == Approx( edfw.AP() ) );
        REQUIRE( 0 == edfw.LSSF() );
        REQUIRE( 14 == edfw.NE() );
        REQUIRE( 3 == edfw.NLS() );
        REQUIRE( 3 == edfw.lValues().size() );
        SECTION( "L == 0"){
          auto lValue = edfw.lValues()[0];
          REQUIRE( Approx(2.37992E2) == lValue.AWRI() );
          REQUIRE( 0 == lValue.L() );
          REQUIRE( 1 == lValue.NJS() );
          REQUIRE( 1 == lValue.jValues().size() );
          auto jValue = lValue.jValues()[0];
          REQUIRE( 0 == jValue.L() );
          REQUIRE( 1 == jValue.MUF() );
          REQUIRE( Approx(1.31E1) == jValue.D() );
          REQUIRE( Approx(0.5) == jValue.AJ() );
          REQUIRE( Approx(1.0) == jValue.AMUN() );
          REQUIRE( Approx(1.572E-3) == jValue.GNO() );
          REQUIRE( Approx(3.1E-2) == jValue.GG() );
          REQUIRE( Approx(1.256E-3) == jValue.GF().front() );
          REQUIRE( Approx(1.403E-3) == jValue.GF().back() );
          REQUIRE( 14 == jValue.GF().size() );
        }

        SECTION( "L == 1"){
          auto lValue =  edfw.lValues()[1];
          REQUIRE( Approx(2.37992E2) == lValue.AWRI() );
          REQUIRE( 1 == lValue.L() );
          REQUIRE( 2 == lValue.NJS() );
          REQUIRE( 2 == lValue.jValues().size() );
        }

        REQUIRE( 1 == edfw.APE().NR() );
        REQUIRE( 50 == edfw.APE().NP() );
        REQUIRE( 50 == edfw.APE().x().size() );
        REQUIRE( 50 == edfw.APE().y().size() );
        REQUIRE( 1.0E-5 == Approx( edfw.APE().x().front() ) );
        REQUIRE( 1.2381 == Approx( edfw.APE().y().front() ) );
        REQUIRE( 2.0E5 == Approx( edfw.APE().x().back() ) );
        REQUIRE( 0.5803 == Approx( edfw.APE().y().back() ) );
      }
    }
  }
  
  GIVEN( "invalid ENDF parameteters:" ){
    long lineNumber = 0;
    int MAT = 9235;
    int MF = 2;
    int MT = 151;

    std::string ENDF = Tab1() + LRF2();
    auto begin = ENDF.begin();
    auto end = ENDF.end();

    THEN( "an exception is thrown" ){
      resonanceParameters::Base base( 5.7E3, 4.0E4, 2, 1, 1, 0 );
      REQUIRE_THROWS(
        resonanceParameters::unresolved::EnergyDependentFissionWidths( 
            base, begin, end, lineNumber, MAT, MF, MT ) );
    }
  }
}

std::string LRF2(){
  return 
    // " 5.700000+3 4.000000+4          2          1          0          09440 2151\n"
    // LIST
    " 0.000000+0 8.880000-1          0          0         14          39440 2151     \n"
    " 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n"
    " 1.400000+4 1.600000+4 1.800000+4 2.000000+4 2.500000+4 3.000000+49440 2151     \n"
    " 3.500000+4 4.000000+4                                            9440 2151     \n"
    // L=0 CONT                                                                      
    " 2.379920+2 0.000000+0          0          0          1          09440 2151     \n"
    // L=0 LIST                                                                      
    " 0.000000+0 0.000000+0          0          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+09440 2151     \n"
    " 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-39440 2151     \n"
    " 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-39440 2151     \n"
    " 1.481000-3 1.403000-3                                            9440 2151     \n"
    // L=1 CONT                                                                      
    " 2.379920+2 0.000000+0          1          0          2          09440 2151     \n"
    // L=1,J=0 LIST                                                                  
    " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n"
    // L=1,J=1 LIST                                                                  
    " 0.000000+0 0.000000+0          1          2         20          09440 2151     \n"
    " 6.697000+0 1.500000+0 1.000000+0 1.540000-3 3.100000-2 0.000000+09440 2151     \n"
    " 1.207000-3 1.299000-3 1.326000-3 1.397000-3 1.544000-3 1.973000-39440 2151     \n"
    " 2.317000-3 2.581000-3 2.811000-3 3.075000-3 3.494000-3 3.887000-39440 2151     \n"
    " 4.290000-3 4.586000-3                                            9440 2151     \n"
    // L=2 CONT                                                                      
    " 2.379920+2 0.000000+0          2          0          2          09440 2151     \n"
    // L=2,J=0 LIST                                                                  
    " 0.000000+0 0.000000+0          2          1         20          09440 2151     \n"
    " 6.697000+0 1.500000+0 1.000000+0 8.304300-4 3.100000-2 0.000000+09440 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-99440 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-99440 2151     \n"
    " 1.000000-9 1.000000-9                                            9440 2151     \n"
    // L=2,J=1 LIST                                                                  
    " 0.000000+0 0.000000+0          2          2         20          09440 2151     \n"
    " 4.633000+0 2.500000+0 1.000000+0 5.744900-4 3.100000-2 0.000000+09440 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-99440 2151     \n"
    " 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-9 1.000000-99440 2151     \n"
    " 1.000000-9 1.000000-9                                            9440 2151     \n";
}

std::string Tab1(){
  return
  " 0.000000+0 0.000000+0          0          0          1         509440 2151     \n"
  "         50          2                                            9440 2151     \n"
  " 1.000000-5 1.238100+0 4.000000+1 1.188400+0 5.000000+1 1.153200+09440 2151     \n"
  " 6.000000+1 1.126500+0 7.000000+1 1.105300+0 8.000000+1 1.087800+09440 2151     \n"
  " 9.000000+1 1.073100+0 1.000000+2 1.060500+0 2.000000+2 9.888000-19440 2151     \n"
  " 3.000000+2 9.547000-1 4.000000+2 9.334000-1 5.000000+2 9.184000-19440 2151     \n"
  " 6.000000+2 9.069000-1 7.000000+2 8.978000-1 8.000000+2 8.903000-19440 2151     \n"
  " 9.000000+2 8.839000-1 1.000000+3 8.783000-1 2.000000+3 8.456000-19440 2151     \n"
  " 3.000000+3 8.286000-1 4.000000+3 8.170000-1 5.000000+3 8.081000-19440 2151     \n"
  " 6.000000+3 8.008000-1 7.000000+3 7.946000-1 8.000000+3 7.892000-19440 2151     \n"
  " 9.000000+3 7.844000-1 1.000000+4 7.800000-1 1.200000+4 7.721000-19440 2151     \n"
  " 1.400000+4 7.653000-1 1.600000+4 7.592000-1 1.800000+4 7.536000-19440 2151     \n"
  " 2.000000+4 7.484000-1 2.500000+4 7.369000-1 3.000000+4 7.269000-19440 2151     \n"
  " 3.500000+4 7.180000-1 4.000000+4 7.098000-1 4.200000+4 7.067000-19440 2151     \n"
  " 4.400000+4 7.038000-1 4.600000+4 7.009000-1 4.800000+4 6.980000-19440 2151     \n"
  " 5.000000+4 6.953000-1 5.500000+4 6.888000-1 6.000000+4 6.826000-19440 2151     \n"
  " 6.500000+4 6.767000-1 7.000000+4 6.712000-1 7.500000+4 6.659000-19440 2151     \n"
  " 8.000000+4 6.608000-1 8.500000+4 6.560000-1 9.000000+4 6.513000-19440 2151     \n"
  " 9.500000+4 6.469000-1 2.000000+5 5.803000-1                      9440 2151     \n";
}

