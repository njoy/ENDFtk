#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string BreitWigner();
std::string ReichMoore();

SCENARIO( "getting energy values from resonance parameters" ){
  GIVEN( "valid ENDF parameters" ){
    long lineNumber = 0;
    int MAT = 6922;
    int MF = 2;
    int MT = 151;
    auto bws = BreitWigner();
    auto begin = bws.begin();
    auto end = bws.end();
    
    resonanceParameters::Base base( 1E-5, 3.2, 1, 1, 0, 0 );

    WHEN( "creating SLBW" ){
      resonanceParameters::resolved::SingleLevelBreitWigner
        slbw( base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the energy values can be verified" ){
        auto energies = resonanceParameters::ER( slbw ) | ranges::to_vector;
        REQUIRE( 4 == energies.size() );
        REQUIRE( -2.9747 == Approx( energies[0] ) );
        REQUIRE( -0.9747 == Approx( energies[1] ) );
        REQUIRE( 1.0253  == Approx( energies[2] ) );
        REQUIRE( 3.0253  == Approx( energies[3] ) );
      }
    }

    WHEN( "creating MLBW" ){
      resonanceParameters::resolved::MultilevelBreitWigner
        mlbw( base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the energy values can be verified" ){
        auto energies = resonanceParameters::ER( mlbw ) | ranges::to_vector;
        REQUIRE( 4 == energies.size() );
        REQUIRE( -2.9747 == Approx( energies[0] ) );
        REQUIRE( -0.9747 == Approx( energies[1] ) );
        REQUIRE( 1.0253  == Approx( energies[2] ) );
        REQUIRE( 3.0253  == Approx( energies[3] ) );
      }
    }

    WHEN( "creating ReichMoore" ){
      auto RM = ReichMoore();
      auto begin = RM.begin();
      auto end = RM.end();
      resonanceParameters::resolved::ReichMoore
        rm( base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the energy values can be verified" ){
        auto energies = resonanceParameters::ER( rm ) | ranges::to_vector;
        REQUIRE( 4 == energies.size() );
        REQUIRE( -2.9747 == Approx( energies[0] ) );
        REQUIRE( -0.9747 == Approx( energies[1] ) );
        REQUIRE( 1.0253  == Approx( energies[2] ) );
        REQUIRE( 3.0253  == Approx( energies[3] ) );
      }
    }
  }
}

std::string BreitWigner(){
  return
    /* cont record */
  " 3.000000+0 0.000000+0          0          0          1          06922 2151   23\n"
    /* list record */
  " 1.664920+2 0.000000+0          0          0         24          46922 2151   24\n"
  "-2.974700+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   25\n"
  "-9.747000-1 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   26\n"
  " 1.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   27\n"
  " 3.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   28\n"
  " 0.000000+0 0.000000+0          0          0          0          06922 2  099999\n";
}

std::string ReichMoore(){
  return
    /* cont record */
  " 3.000000+0 0.000000+0          0          0          1          16922 2151   23\n"
    /* list record */
  " 1.664920+2 0.000000+0          0          0         24          46922 2151   24\n"
  "-2.974700+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   25\n"
  "-9.747000-1 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   26\n"
  " 1.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   27\n"
  " 3.025300+0 2.500000+0 7.846160-2 4.616000-4 7.800000-2 0.000000+06922 2151   28\n"
  " 0.000000+0 0.000000+0          0          0          0          06922 2  099999\n";
}

