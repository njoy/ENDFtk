#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string chunk();
std::string invalidNPL();

SCENARIO( "section::Type< 1, 458 >::ThermalPoint" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 458 >::ThermalPoint" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 1, 458 >::ThermalPoint can be constructed and members can be tested" ) {
      section::Type< 1, 458 >::ThermalPoint chunk(begin, end, lineNumber, 9228, 1, 458 );

      REQUIRE( 0 == chunk.LFC() );
      REQUIRE( 0 == chunk.NPLY() );
      REQUIRE( 0 == chunk.NFC() );

      REQUIRE( 1.691300e+8 == Approx( chunk.EFR() ) );
      REQUIRE( 4.838000e+6 == Approx( chunk.ENP() ) );
      REQUIRE( 7.400000e+3 == Approx( chunk.END() ) );
      REQUIRE( 6.600000e+6 == Approx( chunk.EGP() ) );
      REQUIRE( 6.330000e+6 == Approx( chunk.EGD() ) );
      REQUIRE( 6.500000e+6 == Approx( chunk.EB() ) );
      REQUIRE( 8.750000e+6 == Approx( chunk.ENU() ) );
      REQUIRE( 1.934054e+8 == Approx( chunk.ER() ) );
      REQUIRE( 2.021554e+8 == Approx( chunk.ET() ) );

      REQUIRE( 4.900000e+5 == Approx( chunk.DEFR() ) );
      REQUIRE( 7.000000e+4 == Approx( chunk.DENP() ) );
      REQUIRE( 1.110000e+3 == Approx( chunk.DEND() ) );
      REQUIRE( 5.000000e+5 == Approx( chunk.DEGP() ) );
      REQUIRE( 5.000000e+4 == Approx( chunk.DEGD() ) );
      REQUIRE( 5.100000e+4 == Approx( chunk.DEB() ) );
      REQUIRE( 7.000000e+4 == Approx( chunk.DENU() ) );
      REQUIRE( 1.500000e+5 == Approx( chunk.DER() ) );
      REQUIRE( 1.300000e+5 == Approx( chunk.DET() ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 >::ThermalPoint" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 1, 458 >::ThermalPoint chunk(begin, end, lineNumber, 9228, 1, 458 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 458 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 1, 458 >::ThermalPoint"
         " with an invalid NPL" ){
    std::string string = invalidNPL();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458::ThermalPoint( begin, end, lineNumber, 9228, 1, 458 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

std::string invalidNPL() {
  return
    " 0.000000+0 0.000000+0          0          0         19          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n";
}

