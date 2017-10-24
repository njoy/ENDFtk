#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string baseLFC0NPLY0();
std::string baseLFC0NPLY1();
std::string baseLFC1();
std::string invalidLFC();
std::string invalidNFC();
std::string invalidNPL();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 458 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 458 with LFC=0 and NPLY=0" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLFC0NPLY0() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ) {
        section::Type< 1, 458 > MF1MT458( head, begin, end, lineNumber, 9228 );

        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::ThermalPoint >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::ThermalPoint >( MF1MT458.energyRelease() );

        REQUIRE( 1.691300e+8 == Approx( data.EFR() ) );
        REQUIRE( 4.838000e+6 == Approx( data.ENP() ) );
        REQUIRE( 7.400000e+3 == Approx( data.END() ) );
        REQUIRE( 6.600000e+6 == Approx( data.EGP() ) );
        REQUIRE( 6.330000e+6 == Approx( data.EGD() ) );
        REQUIRE( 6.500000e+6 == Approx( data.EB() ) );
        REQUIRE( 8.750000e+6 == Approx( data.ENU() ) );
        REQUIRE( 1.934054e+8 == Approx( data.ER() ) );
        REQUIRE( 2.021554e+8 == Approx( data.ET() ) );

        REQUIRE( 4.900000e+5 == Approx( data.DEFR() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENP() ) );
        REQUIRE( 1.110000e+3 == Approx( data.DEND() ) );
        REQUIRE( 5.000000e+5 == Approx( data.DEGP() ) );
        REQUIRE( 5.000000e+4 == Approx( data.DEGD() ) );
        REQUIRE( 5.100000e+4 == Approx( data.DEB() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENU() ) );
        REQUIRE( 1.500000e+5 == Approx( data.DER() ) );
        REQUIRE( 1.300000e+5 == Approx( data.DET() ) );

        REQUIRE( 5 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLFC0NPLY0() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );


        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::ThermalPoint >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::ThermalPoint >( MF1MT458.energyRelease() );

        REQUIRE( 1.691300e+8 == Approx( data.EFR() ) );
        REQUIRE( 4.838000e+6 == Approx( data.ENP() ) );
        REQUIRE( 7.400000e+3 == Approx( data.END() ) );
        REQUIRE( 6.600000e+6 == Approx( data.EGP() ) );
        REQUIRE( 6.330000e+6 == Approx( data.EGD() ) );
        REQUIRE( 6.500000e+6 == Approx( data.EB() ) );
        REQUIRE( 8.750000e+6 == Approx( data.ENU() ) );
        REQUIRE( 1.934054e+8 == Approx( data.ER() ) );
        REQUIRE( 2.021554e+8 == Approx( data.ET() ) );

        REQUIRE( 4.900000e+5 == Approx( data.DEFR() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENP() ) );
        REQUIRE( 1.110000e+3 == Approx( data.DEND() ) );
        REQUIRE( 5.000000e+5 == Approx( data.DEGP() ) );
        REQUIRE( 5.000000e+4 == Approx( data.DEGD() ) );
        REQUIRE( 5.100000e+4 == Approx( data.DEB() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENU() ) );
        REQUIRE( 1.500000e+5 == Approx( data.DER() ) );
        REQUIRE( 1.300000e+5 == Approx( data.DET() ) );

        REQUIRE( 5 == MF1MT458.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLFC0NPLY0() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 458 with LFC=0 and NPLY!=0" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLFC0NPLY1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ) {
        section::Type< 1, 458 > MF1MT458( head, begin, end, lineNumber, 9228 );

        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 1 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::Polynomial >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::Polynomial >( MF1MT458.energyRelease() );

        auto efr = data.EFR();
        auto enp = data.ENP();
        auto end = data.END();
        auto egp = data.EGP();
        auto egd = data.EGD();
        auto eb  = data.EB();
        auto enu = data.ENU();
        auto er  = data.ER();
        auto et  = data.ET();
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

        auto defr = data.DEFR();
        auto denp = data.DENP();
        auto dend = data.DEND();
        auto degp = data.DEGP();
        auto degd = data.DEGD();
        auto deb  = data.DEB();
        auto denu = data.DENU();
        auto der  = data.DER();
        auto det  = data.DET();
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

        REQUIRE( 8 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLFC0NPLY1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );


        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 1 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::Polynomial >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::Polynomial >( MF1MT458.energyRelease() );

        auto efr = data.EFR();
        auto enp = data.ENP();
        auto end = data.END();
        auto egp = data.EGP();
        auto egd = data.EGD();
        auto eb  = data.EB();
        auto enu = data.ENU();
        auto er  = data.ER();
        auto et  = data.ET();
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

        auto defr = data.DEFR();
        auto denp = data.DENP();
        auto dend = data.DEND();
        auto degp = data.DEGP();
        auto degd = data.DEGD();
        auto deb  = data.DEB();
        auto denu = data.DENU();
        auto der  = data.DER();
        auto det  = data.DET();
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

        REQUIRE( 8 == MF1MT458.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLFC0NPLY1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 458 with LFC=1" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLFC1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ) {
        section::Type< 1, 458 > MF1MT458( head, begin, end, lineNumber, 9228 );

        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 1 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 2 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::Tabulated >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::Tabulated >( MF1MT458.energyRelease() );

        REQUIRE( 1.691300e+8 == Approx( data.EFR() ) );
        REQUIRE( 4.838000e+6 == Approx( data.ENP() ) );
        REQUIRE( 7.400000e+3 == Approx( data.END() ) );
        REQUIRE( 6.600000e+6 == Approx( data.EGP() ) );
        REQUIRE( 6.330000e+6 == Approx( data.EGD() ) );
        REQUIRE( 6.500000e+6 == Approx( data.EB() ) );
        REQUIRE( 8.750000e+6 == Approx( data.ENU() ) );
        REQUIRE( 1.934054e+8 == Approx( data.ER() ) );
        REQUIRE( 2.021554e+8 == Approx( data.ET() ) );

        REQUIRE( 4.900000e+5 == Approx( data.DEFR() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENP() ) );
        REQUIRE( 1.110000e+3 == Approx( data.DEND() ) );
        REQUIRE( 5.000000e+5 == Approx( data.DEGP() ) );
        REQUIRE( 5.000000e+4 == Approx( data.DEGD() ) );
        REQUIRE( 5.100000e+4 == Approx( data.DEB() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENU() ) );
        REQUIRE( 1.500000e+5 == Approx( data.DER() ) );
        REQUIRE( 1.300000e+5 == Approx( data.DET() ) );

        REQUIRE( true == bool( data.tableEFR() ) );
        REQUIRE( false == bool( data.tableENP() ) );
        REQUIRE( false == bool( data.tableEND() ) );
        REQUIRE( false == bool( data.tableEGP() ) );
        REQUIRE( false == bool( data.tableEGD() ) );
        REQUIRE( false == bool( data.tableEB() ) );
        REQUIRE( false == bool( data.tableENU() ) );
        REQUIRE( false == bool( data.tableER() ) );
        REQUIRE( true == bool( data.tableET() ) );

        auto component = data.tableEFR().value();
        REQUIRE( 1 == component.LDRV() );
        REQUIRE( 1 == component.IFC() );
        REQUIRE( 3 == component.NP() );
        REQUIRE( 1 == component.NR() );
        REQUIRE( 1 == component.interpolants().size() );
        REQUIRE( 1 == component.boundaries().size() );
        REQUIRE( 2 == component.interpolants()[0] );
        REQUIRE( 3 == component.boundaries()[0] );
        REQUIRE( 3 == component.energy().size() );
        REQUIRE( 3 == component.release().size() );
        REQUIRE( 1e-5 == Approx( component.energy()[0] ) );
        REQUIRE( 0.0253 == Approx( component.energy()[1] ) );
        REQUIRE( 2e+7 == Approx( component.energy()[2] ) );
        REQUIRE( 1.6913e+8 == Approx( component.release()[0] ) );
        REQUIRE( 1.691e+8 == Approx( component.release()[1] ) );
        REQUIRE( 1.69e+8 == Approx( component.release()[2] ) );

        component = data.tableET().value();
        REQUIRE( 2 == component.LDRV() );
        REQUIRE( 9 == component.IFC() );
        REQUIRE( 4 == component.NP() );
        REQUIRE( 1 == component.NR() );
        REQUIRE( 1 == component.interpolants().size() );
        REQUIRE( 1 == component.boundaries().size() );
        REQUIRE( 2 == component.interpolants()[0] );
        REQUIRE( 4 == component.boundaries()[0] );
        REQUIRE( 4 == component.energy().size() );
        REQUIRE( 4 == component.release().size() );
        REQUIRE( 1e-5 == Approx( component.energy()[0] ) );
        REQUIRE( 0.0253 == Approx( component.energy()[1] ) );
        REQUIRE( 1e+6 == Approx( component.energy()[2] ) );
        REQUIRE( 2e+7 == Approx( component.energy()[3] ) );
        REQUIRE( 2.021554e+8 == Approx( component.release()[0] ) );
        REQUIRE( 3e+8 == Approx( component.release()[1] ) );
        REQUIRE( 2.5e+8 == Approx( component.release()[2] ) );
        REQUIRE( 1.5e+8 == Approx( component.release()[3] ) );

        REQUIRE( 12 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLFC1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );

        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 1 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 2 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::experimental::get< section1458::Tabulated >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::experimental::get< section1458::Tabulated >( MF1MT458.energyRelease() );

        REQUIRE( 1.691300e+8 == Approx( data.EFR() ) );
        REQUIRE( 4.838000e+6 == Approx( data.ENP() ) );
        REQUIRE( 7.400000e+3 == Approx( data.END() ) );
        REQUIRE( 6.600000e+6 == Approx( data.EGP() ) );
        REQUIRE( 6.330000e+6 == Approx( data.EGD() ) );
        REQUIRE( 6.500000e+6 == Approx( data.EB() ) );
        REQUIRE( 8.750000e+6 == Approx( data.ENU() ) );
        REQUIRE( 1.934054e+8 == Approx( data.ER() ) );
        REQUIRE( 2.021554e+8 == Approx( data.ET() ) );

        REQUIRE( 4.900000e+5 == Approx( data.DEFR() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENP() ) );
        REQUIRE( 1.110000e+3 == Approx( data.DEND() ) );
        REQUIRE( 5.000000e+5 == Approx( data.DEGP() ) );
        REQUIRE( 5.000000e+4 == Approx( data.DEGD() ) );
        REQUIRE( 5.100000e+4 == Approx( data.DEB() ) );
        REQUIRE( 7.000000e+4 == Approx( data.DENU() ) );
        REQUIRE( 1.500000e+5 == Approx( data.DER() ) );
        REQUIRE( 1.300000e+5 == Approx( data.DET() ) );

        REQUIRE( true == bool( data.tableEFR() ) );
        REQUIRE( false == bool( data.tableENP() ) );
        REQUIRE( false == bool( data.tableEND() ) );
        REQUIRE( false == bool( data.tableEGP() ) );
        REQUIRE( false == bool( data.tableEGD() ) );
        REQUIRE( false == bool( data.tableEB() ) );
        REQUIRE( false == bool( data.tableENU() ) );
        REQUIRE( false == bool( data.tableER() ) );
        REQUIRE( true == bool( data.tableET() ) );

        auto component = data.tableEFR().value();
        REQUIRE( 1 == component.LDRV() );
        REQUIRE( 1 == component.IFC() );
        REQUIRE( 3 == component.NP() );
        REQUIRE( 1 == component.NR() );
        REQUIRE( 1 == component.interpolants().size() );
        REQUIRE( 1 == component.boundaries().size() );
        REQUIRE( 2 == component.interpolants()[0] );
        REQUIRE( 3 == component.boundaries()[0] );
        REQUIRE( 3 == component.energy().size() );
        REQUIRE( 3 == component.release().size() );
        REQUIRE( 1e-5 == Approx( component.energy()[0] ) );
        REQUIRE( 0.0253 == Approx( component.energy()[1] ) );
        REQUIRE( 2e+7 == Approx( component.energy()[2] ) );
        REQUIRE( 1.6913e+8 == Approx( component.release()[0] ) );
        REQUIRE( 1.691e+8 == Approx( component.release()[1] ) );
        REQUIRE( 1.69e+8 == Approx( component.release()[2] ) );

        component = data.tableET().value();
        REQUIRE( 2 == component.LDRV() );
        REQUIRE( 9 == component.IFC() );
        REQUIRE( 4 == component.NP() );
        REQUIRE( 1 == component.NR() );
        REQUIRE( 1 == component.interpolants().size() );
        REQUIRE( 1 == component.boundaries().size() );
        REQUIRE( 2 == component.interpolants()[0] );
        REQUIRE( 4 == component.boundaries()[0] );
        REQUIRE( 4 == component.energy().size() );
        REQUIRE( 4 == component.release().size() );
        REQUIRE( 1e-5 == Approx( component.energy()[0] ) );
        REQUIRE( 0.0253 == Approx( component.energy()[1] ) );
        REQUIRE( 1e+6 == Approx( component.energy()[2] ) );
        REQUIRE( 2e+7 == Approx( component.energy()[3] ) );
        REQUIRE( 2.021554e+8 == Approx( component.release()[0] ) );
        REQUIRE( 3e+8 == Approx( component.release()[1] ) );
        REQUIRE( 2.5e+8 == Approx( component.release()[2] ) );
        REQUIRE( 1.5e+8 == Approx( component.release()[3] ) );

        REQUIRE( 12 == MF1MT458.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLFC1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 > with LFC=0 and NPLY=0" ) {
    std::string string = baseLFC0NPLY0() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 458 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 > with LFC=0 and NPLY!=0" ) {
    std::string string = baseLFC0NPLY1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 458 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 458 > with LFC=1" ) {
    std::string string = baseLFC1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 458 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 458"
         " with an invalid LFC" ){
    std::string sectionString = invalidLFC() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 458"
         " with an invalid NFC" ){
    std::string sectionString = invalidNFC() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 458"
         " with an invalid NPL" ){
    std::string sectionString = invalidNPL() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseLFC0NPLY0() {
  return
    " 9.223500+4 2.330248+2          0          0          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

std::string baseLFC0NPLY1() {
  return
    " 9.223500+4 2.330248+2          0          0          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          1         36         189228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    "-2.660000-1 2.660000-2 3.004000-1 3.004000-2 0.000000+0 0.000000+09228 1458     \n"
    " 7.770000-2 7.770000-3-7.500000-2 7.600000-3-7.700000-2 7.800000-39228 1458     \n"
    "-1.000000-1 1.000000-2-3.790000-2 3.790000-3-1.379000-1 1.379000-29228 1458     \n";
}

std::string baseLFC1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          29228 1458     \n"
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

std::string invalidLFC() {
  return
    " 9.223500+4 2.330248+2          0          3          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

std::string invalidNFC() {
  return
    " 9.223500+4 2.330248+2          0          1          0         -19228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

std::string invalidNPL() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         19          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}

