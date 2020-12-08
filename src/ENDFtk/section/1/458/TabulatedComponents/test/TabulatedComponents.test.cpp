#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/458.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string chunk();
std::string invalidNPL();
std::string invalidIFC();
std::string duplicateIFC();

SCENARIO( "section::Type< 1, 458 >::Tabulated" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 458 >::Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 1, 458 >::Tabulated can be constructed and members can be tested" ) {
      section::Type< 1, 458 >::Tabulated chunk(begin, end, lineNumber, 9228, 1, 458, 2 );

      REQUIRE( 1 == chunk.LFC() );
      REQUIRE( 0 == chunk.NPLY() );
      REQUIRE( 2 == chunk.NFC() );

      CHECK( 1.691300e+8 == Approx( chunk.EFR()[0] ) );
      CHECK( 4.838000e+6 == Approx( chunk.ENP()[0] ) );
      CHECK( 7.400000e+3 == Approx( chunk.END()[0] ) );
      CHECK( 6.600000e+6 == Approx( chunk.EGP()[0] ) );
      CHECK( 6.330000e+6 == Approx( chunk.EGD()[0] ) );
      CHECK( 6.500000e+6 == Approx( chunk.EB()[0] ) );
      CHECK( 8.750000e+6 == Approx( chunk.ENU()[0] ) );
      CHECK( 1.934054e+8 == Approx( chunk.ER()[0] ) );
      CHECK( 2.021554e+8 == Approx( chunk.ET()[0] ) );

      CHECK( 4.900000e+5 == Approx( chunk.EFR()[1] ) );
      CHECK( 7.000000e+4 == Approx( chunk.ENP()[1] ) );
      CHECK( 1.110000e+3 == Approx( chunk.END()[1] ) );
      CHECK( 5.000000e+5 == Approx( chunk.EGP()[1] ) );
      CHECK( 5.000000e+4 == Approx( chunk.EGD()[1] ) );
      CHECK( 5.100000e+4 == Approx( chunk.EB()[1] ) );
      CHECK( 7.000000e+4 == Approx( chunk.ENU()[1] ) );
      CHECK( 1.500000e+5 == Approx( chunk.ER()[1] ) );
      CHECK( 1.300000e+5 == Approx( chunk.ET()[1] ) );

      REQUIRE( true == bool( chunk.tableEFR() ) );
      REQUIRE( false == bool( chunk.tableENP() ) );
      REQUIRE( false == bool( chunk.tableEND() ) );
      REQUIRE( false == bool( chunk.tableEGP() ) );
      REQUIRE( false == bool( chunk.tableEGD() ) );
      REQUIRE( false == bool( chunk.tableEB() ) );
      REQUIRE( false == bool( chunk.tableENU() ) );
      REQUIRE( false == bool( chunk.tableER() ) );
      REQUIRE( true == bool( chunk.tableET() ) );

      auto component = *chunk.tableEFR();
      REQUIRE( false == component.LDRV() );
      REQUIRE( 1 == component.IFC() );
      REQUIRE( 3 == component.NP() );
      REQUIRE( 1 == component.NR() );
      REQUIRE( 1 == component.interpolants().size() );
      REQUIRE( 1 == component.boundaries().size() );
      REQUIRE( 2 == component.interpolants()[0] );
      REQUIRE( 3 == component.boundaries()[0] );
      REQUIRE( 3 == component.energies().size() );
      REQUIRE( 3 == component.qValues().size() );
      REQUIRE( 1e-5 == Approx( component.energies()[0] ) );
      REQUIRE( 0.0253 == Approx( component.energies()[1] ) );
      REQUIRE( 2e+7 == Approx( component.energies()[2] ) );
      REQUIRE( 1.6913e+8 == Approx( component.qValues()[0] ) );
      REQUIRE( 1.691e+8 == Approx( component.qValues()[1] ) );
      REQUIRE( 1.69e+8 == Approx( component.qValues()[2] ) );

      component = *chunk.tableET();
      REQUIRE( true == component.LDRV() );
      REQUIRE( 9 == component.IFC() );
      REQUIRE( 4 == component.NP() );
      REQUIRE( 1 == component.NR() );
      REQUIRE( 1 == component.interpolants().size() );
      REQUIRE( 1 == component.boundaries().size() );
      REQUIRE( 2 == component.interpolants()[0] );
      REQUIRE( 4 == component.boundaries()[0] );
      REQUIRE( 4 == component.energies().size() );
      REQUIRE( 4 == component.qValues().size() );
      REQUIRE( 1e-5 == Approx( component.energies()[0] ) );
      REQUIRE( 0.0253 == Approx( component.energies()[1] ) );
      REQUIRE( 1e+6 == Approx( component.energies()[2] ) );
      REQUIRE( 2e+7 == Approx( component.energies()[3] ) );
      REQUIRE( 2.021554e+8 == Approx( component.qValues()[0] ) );
      REQUIRE( 3e+8 == Approx( component.qValues()[1] ) );
      REQUIRE( 2.5e+8 == Approx( component.qValues()[2] ) );
      REQUIRE( 1.5e+8 == Approx( component.qValues()[3] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 >::Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 1, 458 >::Tabulated chunk(begin, end, lineNumber, 9228, 1, 458, 2 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 458 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 1, 458 >::Tabulated"
         " with an invalid NPL" ){
    std::string string = invalidNPL();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458::Tabulated( begin, end, lineNumber, 9228, 1, 458, 2 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 1, 458 >::Tabulated"
         " with an invalid IFC" ){
    std::string string = invalidIFC();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458::Tabulated( begin, end, lineNumber, 9228, 1, 458, 2 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 1, 458 >::Tabulated"
         " with a duplicate IFC" ){
    std::string string = duplicateIFC();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458::Tabulated( begin, end, lineNumber, 9228, 1, 458, 2 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 0.000000+0 0.000000+0          1          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n"
    " 0.000000+0 0.000000+0          2          9          1          49228 1458     \n"
    "          4          2                                            9228 1458     \n"
    " 1.000000-5 2.021554+8 2.530000-2 3.000000+8 1.000000+6 2.500000+89228 1458     \n"
    " 2.000000+7 1.500000+8                                            9228 1458     \n";
}

std::string invalidNPL() {
  return
    " 0.000000+0 0.000000+0          0          0         19          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n"
    " 0.000000+0 0.000000+0          1          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n"
    " 0.000000+0 0.000000+0          2          9          1          49228 1458     \n"
    "          4          2                                            9228 1458     \n"
    " 1.000000-5 2.021554+8 2.530000-2 3.000000+8 1.000000+6 2.500000+89228 1458     \n"
    " 2.000000+7 1.500000+8                                            9228 1458     \n";
}

std::string invalidIFC() {
  return
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 0.000000+0 0.000000+0          1          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n"
    " 0.000000+0 0.000000+0          2         10          1          49228 1458     \n"
    "          4          2                                            9228 1458     \n"
    " 1.000000-5 2.021554+8 2.530000-2 3.000000+8 1.000000+6 2.500000+89228 1458     \n"
    " 2.000000+7 1.500000+8                                            9228 1458     \n";
}

std::string duplicateIFC() {
  return
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 0.000000+0 0.000000+0          1          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n"
    " 0.000000+0 0.000000+0          2          1          1          49228 1458     \n"
    "          4          2                                            9228 1458     \n"
    " 1.000000-5 2.021554+8 2.530000-2 3.000000+8 1.000000+6 2.500000+89228 1458     \n"
    " 2.000000+7 1.500000+8                                            9228 1458     \n";
}