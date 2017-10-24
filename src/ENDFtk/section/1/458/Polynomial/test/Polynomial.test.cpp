#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string chunk();
std::string invalidNPL();

SCENARIO( "section::Type< 1, 458 >::Polynomial" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 458 >::Polynomial" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 1, 458 >::Polynomial can be constructed and members can be tested" ) {
      section::Type< 1, 458 >::Polynomial chunk(begin, end, lineNumber, 9228, 1, 458 );

      REQUIRE( 0 == chunk.LFC() );
      REQUIRE( 1 == chunk.NPLY() );
      REQUIRE( 0 == chunk.NFC() );

      auto efr = chunk.EFR();
      auto enp = chunk.ENP();
      auto end = chunk.END();
      auto egp = chunk.EGP();
      auto egd = chunk.EGD();
      auto eb  = chunk.EB();
      auto enu = chunk.ENU();
      auto er  = chunk.ER();
      auto et  = chunk.ET();
      REQUIRE( 2 == efr.size() );
      REQUIRE( 2 == enp.size() );
      REQUIRE( 2 == end.size() );
      REQUIRE( 2 == egp.size() );
      REQUIRE( 2 == egd.size() );
      REQUIRE( 2 == eb.size() );
      REQUIRE( 2 == enu.size() );
      REQUIRE( 2 == er.size() );
      REQUIRE( 2 == et.size() );
      REQUIRE( 1.691300e+8 == Approx( efr[0] ) );
      REQUIRE( 4.838000e+6 == Approx( enp[0] ) );
      REQUIRE( 7.400000e+3 == Approx( end[0] ) );
      REQUIRE( 6.600000e+6 == Approx( egp[0] ) );
      REQUIRE( 6.330000e+6 == Approx( egd[0] ) );
      REQUIRE( 6.500000e+6 == Approx( eb[0] ) );
      REQUIRE( 8.750000e+6 == Approx( enu[0] ) );
      REQUIRE( 1.934054e+8 == Approx( er[0] ) );
      REQUIRE( 2.021554e+8 == Approx( et[0] ) );
      REQUIRE( -2.660000e-1 == Approx( efr[1] ) );
      REQUIRE( 3.004000e-1 == Approx( enp[1] ) );
      REQUIRE( 0.0 == Approx( end[1] ) );
      REQUIRE( 7.770000e-2 == Approx( egp[1] ) );
      REQUIRE( -7.500000e-2 == Approx( egd[1] ) );
      REQUIRE( -7.700000e-2 == Approx( eb[1] ) );
      REQUIRE( -1.000000e-1 == Approx( enu[1] ) );
      REQUIRE( -3.790000e-2 == Approx( er[1] ) );
      REQUIRE( -1.379000e-1 == Approx( et[1] ) );

      auto defr = chunk.DEFR();
      auto denp = chunk.DENP();
      auto dend = chunk.DEND();
      auto degp = chunk.DEGP();
      auto degd = chunk.DEGD();
      auto deb  = chunk.DEB();
      auto denu = chunk.DENU();
      auto der  = chunk.DER();
      auto det  = chunk.DET();
      REQUIRE( 2 == defr.size() );
      REQUIRE( 2 == denp.size() );
      REQUIRE( 2 == dend.size() );
      REQUIRE( 2 == degp.size() );
      REQUIRE( 2 == degd.size() );
      REQUIRE( 2 == deb.size() );
      REQUIRE( 2 == denu.size() );
      REQUIRE( 2 == der.size() );
      REQUIRE( 2 == det.size() );
      REQUIRE( 4.900000e+5 == Approx( defr[0] ) );
      REQUIRE( 7.000000e+4 == Approx( denp[0] ) );
      REQUIRE( 1.110000e+3 == Approx( dend[0] ) );
      REQUIRE( 5.000000e+5 == Approx( degp[0] ) );
      REQUIRE( 5.000000e+4 == Approx( degd[0] ) );
      REQUIRE( 5.100000e+4 == Approx( deb[0] ) );
      REQUIRE( 7.000000e+4 == Approx( denu[0] ) );
      REQUIRE( 1.500000e+5 == Approx( der[0] ) );
      REQUIRE( 1.300000e+5 == Approx( det[0] ) );
      REQUIRE( 2.660000e-2 == Approx( defr[1] ) );
      REQUIRE( 3.004000e-2 == Approx( denp[1] ) );
      REQUIRE( 0.0 == Approx( dend[1] ) );
      REQUIRE( 7.770000e-3 == Approx( degp[1] ) );
      REQUIRE( 7.600000e-3 == Approx( degd[1] ) );
      REQUIRE( 7.800000e-3 == Approx( deb[1] ) );
      REQUIRE( 1.000000e-2 == Approx( denu[1] ) );
      REQUIRE( 3.790000e-3 == Approx( der[1] ) );
      REQUIRE( 1.379000e-2 == Approx( det[1] ) );
      REQUIRE( 7 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 >::Polynomial" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 1, 458 >::Polynomial chunk(begin, end, lineNumber, 9228, 1, 458 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 458 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 1, 458 >::Polynomial"
         " with an invalid NPL" ){
    std::string string = invalidNPL();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458::Polynomial( begin, end, lineNumber, 9228, 1, 458 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          1         36         189228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    "-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n"
    " 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n"
    "-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n";
}

std::string invalidNPL() {
  return
    " 0.000000+0 0.000000+0          0          1         37         189228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    "-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n"
    " 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n"
    "-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n";
}

