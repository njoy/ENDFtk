// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/458.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section1458 = section::Type< 1, 458 >;
using ThermalPointComponents = section::Type< 1, 458 >::ThermalPointComponents;
using PolynomialComponents = section::Type< 1, 458 >::PolynomialComponents;
using TabulatedComponents = section::Type< 1, 458 >::TabulatedComponents;
using EnergyReleaseComponent = section::Type< 1, 458 >::EnergyReleaseComponent;

std::string chunkLFC0NPLY0();
void verifyLFC0NPLY0( const section::Type< 1, 458 >& );
std::string chunkLFC0NPLY1();
void verifyLFC0NPLY1( const section::Type< 1, 458 >& );
std::string chunkLFC1();
void verifyLFC1( const section::Type< 1, 458 >& );
std::string invalidLFC();
std::string invalidNFC();
std::string validSEND();

SCENARIO( "section::Type< 1, 458 >" ) {

  GIVEN( "valid data for a section::Type< 1, 458 > with thermal point values" ) {

    std::string sectionString = chunkLFC0NPLY0() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      ThermalPointComponents fissionq( { 1.691300e+8, 4.900000e+5 },
                                       { 4.838000e+6, 7.000000e+4 },
                                       { 7.400000e+3, 1.110000e+3 },
                                       { 6.600000e+6, 5.000000e+5 },
                                       { 6.330000e+6, 5.000000e+4 },
                                       { 6.500000e+6, 5.100000e+4 },
                                       { 8.750000e+6, 7.000000e+4 },
                                       { 1.934054e+8, 1.500000e+5 },
                                       { 2.021554e+8, 1.300000e+5 } );

      section::Type< 1, 458 > chunk( zaid, awr, std::move( fissionq ) );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 458 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 458, std::string( sectionString ) );

      section::Type< 1, 458 > chunk = section.parse< 1, 458 >();

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 458 > with polynomial values" ) {

    std::string sectionString = chunkLFC0NPLY1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      PolynomialComponents fissionq( { { 1.691300e+8, 4.900000e+5 }, { -2.66e-1, 2.66e-2 } },
                                     { { 4.838000e+6, 7.000000e+4 }, { 3.004e-1, 3.004e-2 } },
                                     { { 7.400000e+3, 1.110000e+3 }, { 0., 0. } },
                                     { { 6.600000e+6, 5.000000e+5 }, { 7.77e-2, 7.77e-3 } },
                                     { { 6.330000e+6, 5.000000e+4 }, { -7.500e-2, 7.600e-3 } },
                                     { { 6.500000e+6, 5.100000e+4 }, { -7.700e-2, 7.800e-3 } },
                                     { { 8.750000e+6, 7.000000e+4 }, { -1.00e-1, 1.00e-2 } },
                                     { { 1.934054e+8, 1.500000e+5 }, { -3.790e-2, 3.790e-3 } },
                                     { { 2.021554e+8, 1.300000e+5 }, { -1.379e-1, 1.379e-2 } } );

      section::Type< 1, 458 > chunk( zaid, awr, std::move( fissionq ) );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 458 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 458, std::string( sectionString ) );

      section::Type< 1, 458 > chunk = section.parse< 1, 458 >();

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC0NPLY1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 458 > with tabulated values" ) {

    std::string sectionString = chunkLFC1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      TabulatedComponents fissionq(

        ThermalPointComponents( { 1.691300e+8, 4.900000e+5 },
                                { 4.838000e+6, 7.000000e+4 },
                                { 7.400000e+3, 1.110000e+3 },
                                { 6.600000e+6, 5.000000e+5 },
                                { 6.330000e+6, 5.000000e+4 },
                                { 6.500000e+6, 5.100000e+4 },
                                { 8.750000e+6, 7.000000e+4 },
                                { 1.934054e+8, 1.500000e+5 },
                                { 2.021554e+8, 1.300000e+5 } ),
        { EnergyReleaseComponent( false, 1, { 3 }, { 2 },
                                  { 1.000000e-5, 2.530000e-2, 2.000000e+7 },
                                  { 1.691300e+8, 1.691000e+8, 1.690000e+8 } ),
          EnergyReleaseComponent( true, 9, { 4 }, { 2 },
                                  { 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                    2.000000e+7 },
                                  { 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                    1.500000e+8 } ) } );

      section::Type< 1, 458 > chunk( zaid, awr, std::move( fissionq ) );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 458 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 458, std::string( sectionString ) );

      section::Type< 1, 458 > chunk = section.parse< 1, 458 >();

      THEN( "a section::Type< 1, 458 > can be constructed and "
            "members can be tested" ) {

        verifyLFC1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 1, 458 >" ) {

    WHEN( "a string representation of an File 1 Section 458 "
          "with an invalid LFC" ) {

      std::string sectionString = invalidLFC() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of an File 1 Section 458 "
          "with an invalid NFC" ) {

      std::string sectionString = invalidNFC() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1458( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLFC0NPLY0() {
  return
    " 9.223500+4 2.330248+2          0          0          0          09228 1458     \n"
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

void verifyLFC0NPLY0( const section::Type< 1, 458 >& chunk ) {

  CHECK( 458 == chunk.MT() );
  CHECK( 458 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );

  CHECK( false == chunk.LFC() );
  CHECK( false == chunk.tabulatedEnergyRelease() );
  CHECK( 0 == chunk.NPLY() );
  CHECK( 0 == chunk.order() );
  CHECK( 0 == chunk.NFC() );
  CHECK( 0 == chunk.numberTabulatedComponents() );

  auto data = std::get< ThermalPointComponents >( chunk.energyRelease() );

  CHECK( false == data.LFC() );
  CHECK( false == data.tabulatedEnergyRelease() );
  CHECK( 0 == data.NPLY() );
  CHECK( 0 == data.order() );
  CHECK( 0 == data.NFC() );
  CHECK( 0 == data.numberTabulatedComponents() );

  CHECK_THAT( 1.691300e+8, WithinRel( data.E()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.E()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.E()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.E()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.E()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.E()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.E()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.E()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.E()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.E()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.E()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.E()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.E()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.E()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.E()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.E()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.E()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.E()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.energyRelease()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.energyRelease()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.energyRelease()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.energyRelease()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.energyRelease()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.energyRelease()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.energyRelease()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.energyRelease()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.energyRelease()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.energyRelease()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.energyRelease()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.energyRelease()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.energyRelease()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.energyRelease()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.energyRelease()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.energyRelease()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.energyRelease()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.energyRelease()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.EFR()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.ENP()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.END()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.EGP()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.EGD()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.EB()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.ENU()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.ER()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.ET()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.EFR()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.ENP()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.END()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.EGP()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.EGD()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.EB()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.ENU()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.ER()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.ET()[1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.fissionFragments()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.promptNeutrons()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.delayedNeutrons()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.promptGammas()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.delayedGammas()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.delayedBetas()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.neutrinos()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.totalMinusNeutrinos()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.total()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.fissionFragments()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.promptNeutrons()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.delayedNeutrons()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.promptGammas()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.delayedGammas()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.delayedBetas()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.neutrinos()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.totalMinusNeutrinos()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.total()[1] ) );

  CHECK( 5 == chunk.NC() );
}

std::string chunkLFC0NPLY1() {
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

void verifyLFC0NPLY1( const section::Type< 1, 458 >& chunk ) {

  CHECK( 458 == chunk.MT() );
  CHECK( 458 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );

  CHECK( false == chunk.LFC() );
  CHECK( false == chunk.tabulatedEnergyRelease() );
  CHECK( 1 == chunk.NPLY() );
  CHECK( 1 == chunk.order() );
  CHECK( 0 == chunk.NFC() );
  CHECK( 0 == chunk.numberTabulatedComponents() );

  auto data = std::get< PolynomialComponents >( chunk.energyRelease() );

  CHECK( false == data.LFC() );
  CHECK( false == data.tabulatedEnergyRelease() );
  CHECK( 1 == data.NPLY() );
  CHECK( 1 == data.order() );
  CHECK( 0 == data.NFC() );
  CHECK( 0 == data.numberTabulatedComponents() );

  CHECK_THAT( 1.691300e+8, WithinRel( data.E()[0][0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.E()[1][0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.E()[2][0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.E()[3][0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.E()[4][0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.E()[5][0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.E()[6][0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.E()[7][0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.E()[8][0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.E()[0][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.E()[1][0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.E()[2][0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.E()[3][0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.E()[4][0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.E()[5][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.E()[6][0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.E()[7][0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.E()[8][0][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.energyRelease()[0][0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.energyRelease()[1][0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.energyRelease()[2][0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.energyRelease()[3][0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.energyRelease()[4][0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.energyRelease()[5][0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.energyRelease()[6][0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.energyRelease()[7][0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.energyRelease()[8][0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.energyRelease()[0][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.energyRelease()[1][0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.energyRelease()[2][0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.energyRelease()[3][0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.energyRelease()[4][0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.energyRelease()[5][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.energyRelease()[6][0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.energyRelease()[7][0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.energyRelease()[8][0][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( data.E()[0][1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( data.E()[1][1][0] ) );
  CHECK_THAT( 0.0, WithinRel( data.E()[2][1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( data.E()[3][1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( data.E()[4][1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( data.E()[5][1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( data.E()[6][1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( data.E()[7][1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( data.E()[8][1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( data.E()[0][1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( data.E()[1][1][1] ) );
  CHECK_THAT( 0.0, WithinRel( data.E()[2][1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( data.E()[3][1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( data.E()[4][1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( data.E()[5][1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( data.E()[6][1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( data.E()[7][1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( data.E()[8][1][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( data.energyRelease()[0][1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( data.energyRelease()[1][1][0] ) );
  CHECK_THAT( 0.0, WithinRel( data.energyRelease()[2][1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( data.energyRelease()[3][1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( data.energyRelease()[4][1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( data.energyRelease()[5][1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( data.energyRelease()[6][1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( data.energyRelease()[7][1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( data.energyRelease()[8][1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( data.energyRelease()[0][1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( data.energyRelease()[1][1][1] ) );
  CHECK_THAT( 0.0, WithinRel( data.energyRelease()[2][1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( data.energyRelease()[3][1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( data.energyRelease()[4][1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( data.energyRelease()[5][1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( data.energyRelease()[6][1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( data.energyRelease()[7][1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( data.energyRelease()[8][1][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.EFR()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.ENP()[0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.END()[0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.EGP()[0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.EGD()[0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.EB()[0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.ENU()[0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.ER()[0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.ET()[0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.EFR()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.ENP()[0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.END()[0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.EGP()[0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.EGD()[0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.EB()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.ENU()[0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.ER()[0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.ET()[0][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.fissionFragments()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.promptNeutrons()[0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.delayedNeutrons()[0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.promptGammas()[0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.delayedGammas()[0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.delayedBetas()[0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.neutrinos()[0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.totalMinusNeutrinos()[0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.total()[0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.fissionFragments()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.promptNeutrons()[0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.delayedNeutrons()[0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.promptGammas()[0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.delayedGammas()[0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.delayedBetas()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.neutrinos()[0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.totalMinusNeutrinos()[0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.total()[0][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( data.EFR()[1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( data.ENP()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( data.END()[1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( data.EGP()[1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( data.EGD()[1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( data.EB()[1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( data.ENU()[1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( data.ER()[1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( data.ET()[1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( data.EFR()[1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( data.ENP()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( data.END()[1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( data.EGP()[1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( data.EGD()[1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( data.EB()[1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( data.ENU()[1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( data.ER()[1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( data.ET()[1][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( data.fissionFragments()[1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( data.promptNeutrons()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( data.delayedNeutrons()[1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( data.promptGammas()[1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( data.delayedGammas()[1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( data.delayedBetas()[1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( data.neutrinos()[1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( data.totalMinusNeutrinos()[1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( data.total()[1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( data.fissionFragments()[1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( data.promptNeutrons()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( data.delayedNeutrons()[1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( data.promptGammas()[1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( data.delayedGammas()[1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( data.delayedBetas()[1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( data.neutrinos()[1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( data.totalMinusNeutrinos()[1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( data.total()[1][1] ) );

  CHECK( 8 == chunk.NC() );
}

std::string chunkLFC1() {
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

void verifyLFC1( const section::Type< 1, 458 >& chunk ) {

  CHECK( 458 == chunk.MT() );
  CHECK( 458 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );

  CHECK( true == chunk.LFC() );
  CHECK( true == chunk.tabulatedEnergyRelease() );
  CHECK( 0 == chunk.NPLY() );
  CHECK( 0 == chunk.order() );
  CHECK( 2 == chunk.NFC() );
  CHECK( 2 == chunk.numberTabulatedComponents() );

  auto data = std::get< TabulatedComponents >( chunk.energyRelease() );

  CHECK( true == data.LFC() );
  CHECK( true == data.tabulatedEnergyRelease() );
  CHECK( 0 == data.NPLY() );
  CHECK( 0 == data.order() );
  CHECK( 2 == data.NFC() );
  CHECK( 2 == data.numberTabulatedComponents() );

  CHECK_THAT( 1.691300e+8, WithinRel( data.thermalPointValues().E()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.thermalPointValues().E()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.thermalPointValues().E()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.thermalPointValues().E()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.thermalPointValues().E()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.thermalPointValues().E()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.thermalPointValues().E()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.thermalPointValues().E()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.thermalPointValues().E()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.thermalPointValues().E()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().E()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.thermalPointValues().E()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.thermalPointValues().E()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.thermalPointValues().E()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.thermalPointValues().E()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().E()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.thermalPointValues().E()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.thermalPointValues().E()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.thermalPointValues().energyRelease()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.thermalPointValues().energyRelease()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.thermalPointValues().energyRelease()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.thermalPointValues().energyRelease()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.thermalPointValues().energyRelease()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.thermalPointValues().energyRelease()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.thermalPointValues().energyRelease()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.thermalPointValues().energyRelease()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.thermalPointValues().energyRelease()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.thermalPointValues().energyRelease()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().energyRelease()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.thermalPointValues().energyRelease()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.thermalPointValues().energyRelease()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.thermalPointValues().energyRelease()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.thermalPointValues().energyRelease()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().energyRelease()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.thermalPointValues().energyRelease()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.thermalPointValues().energyRelease()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.thermalPointValues().EFR()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.thermalPointValues().ENP()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.thermalPointValues().END()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.thermalPointValues().EGP()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.thermalPointValues().EGD()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.thermalPointValues().EB()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.thermalPointValues().ENU()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.thermalPointValues().ER()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.thermalPointValues().ET()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.thermalPointValues().EFR()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().ENP()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.thermalPointValues().END()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.thermalPointValues().EGP()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.thermalPointValues().EGD()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.thermalPointValues().EB()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().ENU()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.thermalPointValues().ER()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.thermalPointValues().ET()[1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( data.thermalPointValues().fissionFragments()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( data.thermalPointValues().promptNeutrons()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( data.thermalPointValues().delayedNeutrons()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( data.thermalPointValues().promptGammas()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( data.thermalPointValues().delayedGammas()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( data.thermalPointValues().delayedBetas()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( data.thermalPointValues().neutrinos()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( data.thermalPointValues().totalMinusNeutrinos()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( data.thermalPointValues().total()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( data.thermalPointValues().fissionFragments()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().promptNeutrons()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( data.thermalPointValues().delayedNeutrons()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( data.thermalPointValues().promptGammas()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( data.thermalPointValues().delayedGammas()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( data.thermalPointValues().delayedBetas()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( data.thermalPointValues().neutrinos()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( data.thermalPointValues().totalMinusNeutrinos()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( data.thermalPointValues().total()[1] ) );

  CHECK( true == bool( data.tabulatedEFR() ) );
  CHECK( false == bool( data.tabulatedENP() ) );
  CHECK( false == bool( data.tabulatedEND() ) );
  CHECK( false == bool( data.tabulatedEGP() ) );
  CHECK( false == bool( data.tabulatedEGD() ) );
  CHECK( false == bool( data.tabulatedEB() ) );
  CHECK( false == bool( data.tabulatedENU() ) );
  CHECK( false == bool( data.tabulatedER() ) );
  CHECK( true == bool( data.tabulatedET() ) );

  CHECK( true == bool( data.tabulatedFissionFragments() ) );
  CHECK( false == bool( data.tabulatedPromptNeutrons() ) );
  CHECK( false == bool( data.tabulatedDelayedNeutrons() ) );
  CHECK( false == bool( data.tabulatedPromptGammas() ) );
  CHECK( false == bool( data.tabulatedDelayedGammas() ) );
  CHECK( false == bool( data.tabulatedDelayedBetas() ) );
  CHECK( false == bool( data.tabulatedNeutrinos() ) );
  CHECK( false == bool( data.tabulatedTotalMinusNeutrinos() ) );
  CHECK( true == bool( data.tabulatedTotal() ) );

  auto component = *data.tabulatedEFR();
  CHECK( false == component.LDRV() );
  CHECK( 1 == component.IFC() );
  CHECK( 3 == component.NP() );
  CHECK( 1 == component.NR() );
  CHECK( 1 == component.interpolants().size() );
  CHECK( 1 == component.boundaries().size() );
  CHECK( 2 == component.interpolants()[0] );
  CHECK( 3 == component.boundaries()[0] );
  CHECK( 3 == component.energies().size() );
  CHECK( 3 == component.qValues().size() );
  CHECK_THAT( 1e-5, WithinRel( component.energies()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( component.energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( component.energies()[2] ) );
  CHECK_THAT( 1.6913e+8, WithinRel( component.qValues()[0] ) );
  CHECK_THAT( 1.691e+8, WithinRel( component.qValues()[1] ) );
  CHECK_THAT( 1.69e+8, WithinRel( component.qValues()[2] ) );

  component = *data.tabulatedET();
  CHECK( true == component.LDRV() );
  CHECK( 9 == component.IFC() );
  CHECK( 4 == component.NP() );
  CHECK( 1 == component.NR() );
  CHECK( 1 == component.interpolants().size() );
  CHECK( 1 == component.boundaries().size() );
  CHECK( 2 == component.interpolants()[0] );
  CHECK( 4 == component.boundaries()[0] );
  CHECK( 4 == component.energies().size() );
  CHECK( 4 == component.qValues().size() );
  CHECK_THAT( 1e-5, WithinRel( component.energies()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( component.energies()[1] ) );
  CHECK_THAT( 1e+6, WithinRel( component.energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( component.energies()[3] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( component.qValues()[0] ) );
  CHECK_THAT( 3e+8, WithinRel( component.qValues()[1] ) );
  CHECK_THAT( 2.5e+8, WithinRel( component.qValues()[2] ) );
  CHECK_THAT( 1.5e+8, WithinRel( component.qValues()[3] ) );

  CHECK( 12 == chunk.NC() );
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

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}
