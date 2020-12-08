#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/458.hpp"

#include "ENDFtk/tree/Section.hpp"

using namespace njoy::ENDFtk;

using section1458 = section::Type< 1, 458 >;

std::string baseLFC0NPLY0();
std::string baseLFC0NPLY1();
std::string baseLFC1();
std::string invalidLFC();
std::string invalidNFC();
std::string invalidNPLLFC0();
std::string invalidNPLLFC1();
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
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::ThermalPointComponents >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::ThermalPointComponents >( MF1MT458.energyRelease() );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[1] ) );

        REQUIRE( 5 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLFC0NPLY0() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );


        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::ThermalPointComponents >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::ThermalPointComponents >( MF1MT458.energyRelease() );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[1] ) );

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
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 1 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::PolynomialComponents >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::PolynomialComponents >( MF1MT458.energyRelease() );

        CHECK( false == data.LFC() );
        CHECK( false == data.tabulatedEnergyRelease() );
        CHECK( 1 == data.NPLY() );
        CHECK( 1 == data.order() );
        CHECK( 0 == data.NFC() );
        CHECK( 0 == data.numberTabulatedComponents() );

        CHECK( 1.691300e+8 == Approx( data.E()[0][0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.E()[1][0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.E()[2][0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.E()[3][0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.E()[4][0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.E()[5][0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.E()[6][0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.E()[7][0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.E()[8][0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.E()[0][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.E()[1][0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.E()[2][0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.E()[3][0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.E()[4][0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.E()[5][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.E()[6][0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.E()[7][0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.E()[8][0][1] ) );

        CHECK( 1.691300e+8 == Approx( data.energyRelease()[0][0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.energyRelease()[1][0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.energyRelease()[2][0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.energyRelease()[3][0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.energyRelease()[4][0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.energyRelease()[5][0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.energyRelease()[6][0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.energyRelease()[7][0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.energyRelease()[8][0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.energyRelease()[0][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.energyRelease()[1][0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.energyRelease()[2][0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.energyRelease()[3][0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.energyRelease()[4][0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.energyRelease()[5][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.energyRelease()[6][0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.energyRelease()[7][0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.energyRelease()[8][0][1] ) );

        CHECK( -2.660000e-1 == Approx( data.E()[0][1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.E()[1][1][0] ) );
        CHECK( 0.0 == Approx( data.E()[2][1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.E()[3][1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.E()[4][1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.E()[5][1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.E()[6][1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.E()[7][1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.E()[8][1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.E()[0][1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.E()[1][1][1] ) );
        CHECK( 0.0 == Approx( data.E()[2][1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.E()[3][1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.E()[4][1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.E()[5][1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.E()[6][1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.E()[7][1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.E()[8][1][1] ) );

        CHECK( -2.660000e-1 == Approx( data.energyRelease()[0][1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.energyRelease()[1][1][0] ) );
        CHECK( 0.0 == Approx( data.energyRelease()[2][1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.energyRelease()[3][1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.energyRelease()[4][1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.energyRelease()[5][1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.energyRelease()[6][1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.energyRelease()[7][1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.energyRelease()[8][1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.energyRelease()[0][1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.energyRelease()[1][1][1] ) );
        CHECK( 0.0 == Approx( data.energyRelease()[2][1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.energyRelease()[3][1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.energyRelease()[4][1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.energyRelease()[5][1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.energyRelease()[6][1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.energyRelease()[7][1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.energyRelease()[8][1][1] ) );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[0][1] ) );

        CHECK( 1.691300e+8 == Approx( data.fissionFragments()[0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.promptNeutrons()[0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.delayedNeutrons()[0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.promptGammas()[0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.delayedGammas()[0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.delayedBetas()[0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.neutrinos()[0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.totalMinusNeutrinos()[0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.total()[0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.fissionFragments()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.promptNeutrons()[0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.delayedNeutrons()[0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.promptGammas()[0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.delayedGammas()[0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.delayedBetas()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.neutrinos()[0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.totalMinusNeutrinos()[0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.total()[0][1] ) );

        CHECK( -2.660000e-1 == Approx( data.EFR()[1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.ENP()[1][0] ) );
        CHECK( 0.0 == Approx( data.END()[1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.EGP()[1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.EGD()[1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.EB()[1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.ENU()[1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.ER()[1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.ET()[1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.EFR()[1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.ENP()[1][1] ) );
        CHECK( 0.0 == Approx( data.END()[1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.EGP()[1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.EGD()[1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.EB()[1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.ENU()[1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.ER()[1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.ET()[1][1] ) );

        CHECK( -2.660000e-1 == Approx( data.fissionFragments()[1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.promptNeutrons()[1][0] ) );
        CHECK( 0.0 == Approx( data.delayedNeutrons()[1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.promptGammas()[1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.delayedGammas()[1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.delayedBetas()[1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.neutrinos()[1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.totalMinusNeutrinos()[1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.total()[1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.fissionFragments()[1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.promptNeutrons()[1][1] ) );
        CHECK( 0.0 == Approx( data.delayedNeutrons()[1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.promptGammas()[1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.delayedGammas()[1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.delayedBetas()[1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.neutrinos()[1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.totalMinusNeutrinos()[1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.total()[1][1] ) );

        REQUIRE( 8 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLFC0NPLY1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );


        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 0 == MF1MT458.LFC() );
        REQUIRE( 1 == MF1MT458.NPLY() );
        REQUIRE( 0 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::PolynomialComponents >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::PolynomialComponents >( MF1MT458.energyRelease() );

        CHECK( false == data.LFC() );
        CHECK( false == data.tabulatedEnergyRelease() );
        CHECK( 1 == data.NPLY() );
        CHECK( 1 == data.order() );
        CHECK( 0 == data.NFC() );
        CHECK( 0 == data.numberTabulatedComponents() );

        CHECK( 1.691300e+8 == Approx( data.E()[0][0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.E()[1][0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.E()[2][0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.E()[3][0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.E()[4][0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.E()[5][0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.E()[6][0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.E()[7][0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.E()[8][0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.E()[0][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.E()[1][0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.E()[2][0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.E()[3][0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.E()[4][0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.E()[5][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.E()[6][0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.E()[7][0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.E()[8][0][1] ) );

        CHECK( 1.691300e+8 == Approx( data.energyRelease()[0][0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.energyRelease()[1][0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.energyRelease()[2][0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.energyRelease()[3][0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.energyRelease()[4][0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.energyRelease()[5][0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.energyRelease()[6][0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.energyRelease()[7][0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.energyRelease()[8][0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.energyRelease()[0][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.energyRelease()[1][0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.energyRelease()[2][0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.energyRelease()[3][0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.energyRelease()[4][0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.energyRelease()[5][0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.energyRelease()[6][0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.energyRelease()[7][0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.energyRelease()[8][0][1] ) );

        CHECK( -2.660000e-1 == Approx( data.E()[0][1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.E()[1][1][0] ) );
        CHECK( 0.0 == Approx( data.E()[2][1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.E()[3][1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.E()[4][1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.E()[5][1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.E()[6][1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.E()[7][1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.E()[8][1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.E()[0][1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.E()[1][1][1] ) );
        CHECK( 0.0 == Approx( data.E()[2][1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.E()[3][1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.E()[4][1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.E()[5][1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.E()[6][1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.E()[7][1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.E()[8][1][1] ) );

        CHECK( -2.660000e-1 == Approx( data.energyRelease()[0][1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.energyRelease()[1][1][0] ) );
        CHECK( 0.0 == Approx( data.energyRelease()[2][1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.energyRelease()[3][1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.energyRelease()[4][1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.energyRelease()[5][1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.energyRelease()[6][1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.energyRelease()[7][1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.energyRelease()[8][1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.energyRelease()[0][1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.energyRelease()[1][1][1] ) );
        CHECK( 0.0 == Approx( data.energyRelease()[2][1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.energyRelease()[3][1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.energyRelease()[4][1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.energyRelease()[5][1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.energyRelease()[6][1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.energyRelease()[7][1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.energyRelease()[8][1][1] ) );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[0][1] ) );

        CHECK( 1.691300e+8 == Approx( data.fissionFragments()[0][0] ) );
        CHECK( 4.838000e+6 == Approx( data.promptNeutrons()[0][0] ) );
        CHECK( 7.400000e+3 == Approx( data.delayedNeutrons()[0][0] ) );
        CHECK( 6.600000e+6 == Approx( data.promptGammas()[0][0] ) );
        CHECK( 6.330000e+6 == Approx( data.delayedGammas()[0][0] ) );
        CHECK( 6.500000e+6 == Approx( data.delayedBetas()[0][0] ) );
        CHECK( 8.750000e+6 == Approx( data.neutrinos()[0][0] ) );
        CHECK( 1.934054e+8 == Approx( data.totalMinusNeutrinos()[0][0] ) );
        CHECK( 2.021554e+8 == Approx( data.total()[0][0] ) );

        CHECK( 4.900000e+5 == Approx( data.fissionFragments()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.promptNeutrons()[0][1] ) );
        CHECK( 1.110000e+3 == Approx( data.delayedNeutrons()[0][1] ) );
        CHECK( 5.000000e+5 == Approx( data.promptGammas()[0][1] ) );
        CHECK( 5.000000e+4 == Approx( data.delayedGammas()[0][1] ) );
        CHECK( 5.100000e+4 == Approx( data.delayedBetas()[0][1] ) );
        CHECK( 7.000000e+4 == Approx( data.neutrinos()[0][1] ) );
        CHECK( 1.500000e+5 == Approx( data.totalMinusNeutrinos()[0][1] ) );
        CHECK( 1.300000e+5 == Approx( data.total()[0][1] ) );

        CHECK( -2.660000e-1 == Approx( data.EFR()[1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.ENP()[1][0] ) );
        CHECK( 0.0 == Approx( data.END()[1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.EGP()[1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.EGD()[1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.EB()[1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.ENU()[1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.ER()[1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.ET()[1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.EFR()[1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.ENP()[1][1] ) );
        CHECK( 0.0 == Approx( data.END()[1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.EGP()[1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.EGD()[1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.EB()[1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.ENU()[1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.ER()[1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.ET()[1][1] ) );

        CHECK( -2.660000e-1 == Approx( data.fissionFragments()[1][0] ) );
        CHECK( 3.004000e-1 ==  Approx( data.promptNeutrons()[1][0] ) );
        CHECK( 0.0 == Approx( data.delayedNeutrons()[1][0] ) );
        CHECK( 7.770000e-2 ==  Approx( data.promptGammas()[1][0] ) );
        CHECK( -7.500000e-2 == Approx( data.delayedGammas()[1][0] ) );
        CHECK( -7.700000e-2 == Approx( data.delayedBetas()[1][0] ) );
        CHECK( -1.000000e-1 == Approx( data.neutrinos()[1][0] ) );
        CHECK( -3.790000e-2 == Approx( data.totalMinusNeutrinos()[1][0] ) );
        CHECK( -1.379000e-1 == Approx( data.total()[1][0] ) );

        CHECK( 2.660000e-2 == Approx( data.fissionFragments()[1][1] ) );
        CHECK( 3.004000e-2 == Approx( data.promptNeutrons()[1][1] ) );
        CHECK( 0.0 == Approx( data.delayedNeutrons()[1][1] ) );
        CHECK( 7.770000e-3 == Approx( data.promptGammas()[1][1] ) );
        CHECK( 7.600000e-3 == Approx( data.delayedGammas()[1][1] ) );
        CHECK( 7.800000e-3 == Approx( data.delayedBetas()[1][1] ) );
        CHECK( 1.000000e-2 == Approx( data.neutrinos()[1][1] ) );
        CHECK( 3.790000e-3 == Approx( data.totalMinusNeutrinos()[1][1] ) );
        CHECK( 1.379000e-2 == Approx( data.total()[1][1] ) );

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
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 1 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 2 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::Tabulated >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::Tabulated >( MF1MT458.energyRelease() );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[1] ) );

        REQUIRE( true == bool( data.tableEFR() ) );
        REQUIRE( false == bool( data.tableENP() ) );
        REQUIRE( false == bool( data.tableEND() ) );
        REQUIRE( false == bool( data.tableEGP() ) );
        REQUIRE( false == bool( data.tableEGD() ) );
        REQUIRE( false == bool( data.tableEB() ) );
        REQUIRE( false == bool( data.tableENU() ) );
        REQUIRE( false == bool( data.tableER() ) );
        REQUIRE( true == bool( data.tableET() ) );

        auto component = *data.tableEFR();
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

        component = *data.tableET();
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

        REQUIRE( 12 == MF1MT458.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLFC1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 458 > can be constructed and members can be tested" ){
        section::Type< 1, 458 > MF1MT458 = section.parse< 1, 458 >( lineNumber );

        REQUIRE( 458 == MF1MT458.MT() );
        REQUIRE( 458 == MF1MT458.sectionNumber() );
        REQUIRE( 92235 == MF1MT458.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT458.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT458.AWR() ) );

        REQUIRE( 1 == MF1MT458.LFC() );
        REQUIRE( 0 == MF1MT458.NPLY() );
        REQUIRE( 2 == MF1MT458.NFC() );

        REQUIRE_NOTHROW( std::get< section1458::Tabulated >
                         ( MF1MT458.energyRelease() ) );
        auto data = std::get< section1458::Tabulated >( MF1MT458.energyRelease() );

        CHECK( 1.691300e+8 == Approx( data.EFR()[0] ) );
        CHECK( 4.838000e+6 == Approx( data.ENP()[0] ) );
        CHECK( 7.400000e+3 == Approx( data.END()[0] ) );
        CHECK( 6.600000e+6 == Approx( data.EGP()[0] ) );
        CHECK( 6.330000e+6 == Approx( data.EGD()[0] ) );
        CHECK( 6.500000e+6 == Approx( data.EB()[0] ) );
        CHECK( 8.750000e+6 == Approx( data.ENU()[0] ) );
        CHECK( 1.934054e+8 == Approx( data.ER()[0] ) );
        CHECK( 2.021554e+8 == Approx( data.ET()[0] ) );

        CHECK( 4.900000e+5 == Approx( data.EFR()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENP()[1] ) );
        CHECK( 1.110000e+3 == Approx( data.END()[1] ) );
        CHECK( 5.000000e+5 == Approx( data.EGP()[1] ) );
        CHECK( 5.000000e+4 == Approx( data.EGD()[1] ) );
        CHECK( 5.100000e+4 == Approx( data.EB()[1] ) );
        CHECK( 7.000000e+4 == Approx( data.ENU()[1] ) );
        CHECK( 1.500000e+5 == Approx( data.ER()[1] ) );
        CHECK( 1.300000e+5 == Approx( data.ET()[1] ) );

        REQUIRE( true == bool( data.tableEFR() ) );
        REQUIRE( false == bool( data.tableENP() ) );
        REQUIRE( false == bool( data.tableEND() ) );
        REQUIRE( false == bool( data.tableEGP() ) );
        REQUIRE( false == bool( data.tableEGD() ) );
        REQUIRE( false == bool( data.tableEB() ) );
        REQUIRE( false == bool( data.tableENU() ) );
        REQUIRE( false == bool( data.tableER() ) );
        REQUIRE( true == bool( data.tableET() ) );

        auto component = *data.tableEFR();
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

        component = *data.tableET();
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
         " with an invalid NPL for LFC=0" ){
    std::string sectionString = invalidNPLLFC0() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 458"
         " with an invalid NPL for LFC=1" ){
    std::string sectionString = invalidNPLLFC1() + validSEND();
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

std::string invalidNPLLFC0() {
  return
    " 9.223500+4 2.330248+2          0          0          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         19          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n";
}

std::string invalidNPLLFC1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1458     \n"
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

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}
