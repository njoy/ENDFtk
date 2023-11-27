// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/458.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ThermalPointComponents = section::Type< 1, 458 >::ThermalPointComponents;
using EnergyReleaseComponent = section::Type< 1, 458 >::EnergyReleaseComponent;
using TabulatedComponents = section::Type< 1, 458 >::TabulatedComponents;

std::string chunk();
void verifyChunk( const TabulatedComponents& );
std::string invalidNPL();
std::string invalidIFC();
std::string duplicateIFC();

SCENARIO( "TabulatedComponents" ) {

  GIVEN( "valid data for a TabulatedComponents" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > efr = {{ 1.691300e+8, 4.900000e+5 }};
      std::array< double, 2 > enp = {{ 4.838000e+6, 7.000000e+4 }};
      std::array< double, 2 > end = {{ 7.400000e+3, 1.110000e+3 }};
      std::array< double, 2 > egp = {{ 6.600000e+6, 5.000000e+5 }};
      std::array< double, 2 > egd = {{ 6.330000e+6, 5.000000e+4 }};
      std::array< double, 2 > eb = {{ 6.500000e+6, 5.100000e+4 }};
      std::array< double, 2 > enu = {{ 8.750000e+6, 7.000000e+4 }};
      std::array< double, 2 > er = {{ 1.934054e+8, 1.500000e+5 }};
      std::array< double, 2 > et = {{ 2.021554e+8, 1.300000e+5 }};

      ThermalPointComponents thermal( std::move( efr ), std::move( enp ),
                                      std::move( end ), std::move( egp ),
                                      std::move( egd ), std::move( eb ),
                                      std::move( enu ), std::move( er ),
                                      std::move( et ) );

      std::vector< EnergyReleaseComponent > tables = {

        EnergyReleaseComponent( false, 1, { 3 }, { 2 },
                                { 1.000000e-5, 2.530000e-2, 2.000000e+7 },
                                { 1.691300e+8, 1.691000e+8, 1.690000e+8 } ),
        EnergyReleaseComponent( true, 9, { 4 }, { 2 },
                                { 1.000000e-5, 2.530000e-2, 1.000000e+6,
                                  2.000000e+7 },
                                { 2.021554e+8, 3.000000e+8, 2.500000e+8,
                                  1.500000e+8 } ) };

      TabulatedComponents chunk( std::move( thermal ), std::move( tables ) );

      THEN( "a TabulatedComponents can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 458 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TabulatedComponents chunk( begin, end, lineNumber, 9228, 1, 458, 2 );

      THEN( "a TabulatedComponents can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 458 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedComponents" ) {

    WHEN( "a string representation with an invalid NPL" ) {

      std::string string = invalidNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComponents( begin, end, lineNumber,
                                           9228, 1, 458, 2 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid IFC" ) {

      std::string string = invalidIFC();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComponents( begin, end, lineNumber,
                                           9228, 1, 458, 2 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a duplicate IFC" ) {

      std::string string = duplicateIFC();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComponents( begin, end, lineNumber,
                                           9228, 1, 458, 2 ) );
      } // THEN
    } // WHEN
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

void verifyChunk( const TabulatedComponents& chunk ) {

  CHECK( true == chunk.LFC() );
  CHECK( true == chunk.tabulatedEnergyRelease() );
  CHECK( 0 == chunk.NPLY() );
  CHECK( 0 == chunk.order() );
  CHECK( 2 == chunk.NFC() );
  CHECK( 2 == chunk.numberTabulatedComponents() );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.thermalPointValues().E()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.thermalPointValues().E()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.thermalPointValues().E()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.thermalPointValues().E()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.thermalPointValues().E()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.thermalPointValues().E()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.thermalPointValues().E()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.thermalPointValues().E()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.thermalPointValues().E()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.thermalPointValues().E()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().E()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.thermalPointValues().E()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.thermalPointValues().E()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.thermalPointValues().E()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.thermalPointValues().E()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().E()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.thermalPointValues().E()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.thermalPointValues().E()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.thermalPointValues().energyRelease()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.thermalPointValues().energyRelease()[1][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.thermalPointValues().energyRelease()[2][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.thermalPointValues().energyRelease()[3][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.thermalPointValues().energyRelease()[4][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.thermalPointValues().energyRelease()[5][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.thermalPointValues().energyRelease()[6][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.thermalPointValues().energyRelease()[7][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.thermalPointValues().energyRelease()[8][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.thermalPointValues().energyRelease()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().energyRelease()[1][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.thermalPointValues().energyRelease()[2][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.thermalPointValues().energyRelease()[3][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.thermalPointValues().energyRelease()[4][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.thermalPointValues().energyRelease()[5][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().energyRelease()[6][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.thermalPointValues().energyRelease()[7][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.thermalPointValues().energyRelease()[8][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.thermalPointValues().EFR()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.thermalPointValues().ENP()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.thermalPointValues().END()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.thermalPointValues().EGP()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.thermalPointValues().EGD()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.thermalPointValues().EB()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.thermalPointValues().ENU()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.thermalPointValues().ER()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.thermalPointValues().ET()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.thermalPointValues().EFR()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().ENP()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.thermalPointValues().END()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.thermalPointValues().EGP()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.thermalPointValues().EGD()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.thermalPointValues().EB()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().ENU()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.thermalPointValues().ER()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.thermalPointValues().ET()[1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.thermalPointValues().fissionFragments()[0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.thermalPointValues().promptNeutrons()[0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.thermalPointValues().delayedNeutrons()[0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.thermalPointValues().promptGammas()[0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.thermalPointValues().delayedGammas()[0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.thermalPointValues().delayedBetas()[0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.thermalPointValues().neutrinos()[0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.thermalPointValues().totalMinusNeutrinos()[0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.thermalPointValues().total()[0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.thermalPointValues().fissionFragments()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().promptNeutrons()[1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.thermalPointValues().delayedNeutrons()[1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.thermalPointValues().promptGammas()[1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.thermalPointValues().delayedGammas()[1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.thermalPointValues().delayedBetas()[1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.thermalPointValues().neutrinos()[1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.thermalPointValues().totalMinusNeutrinos()[1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.thermalPointValues().total()[1] ) );

  CHECK( true == bool( chunk.tabulatedEFR() ) );
  CHECK( false == bool( chunk.tabulatedENP() ) );
  CHECK( false == bool( chunk.tabulatedEND() ) );
  CHECK( false == bool( chunk.tabulatedEGP() ) );
  CHECK( false == bool( chunk.tabulatedEGD() ) );
  CHECK( false == bool( chunk.tabulatedEB() ) );
  CHECK( false == bool( chunk.tabulatedENU() ) );
  CHECK( false == bool( chunk.tabulatedER() ) );
  CHECK( true == bool( chunk.tabulatedET() ) );

  CHECK( true == bool( chunk.tabulatedFissionFragments() ) );
  CHECK( false == bool( chunk.tabulatedPromptNeutrons() ) );
  CHECK( false == bool( chunk.tabulatedDelayedNeutrons() ) );
  CHECK( false == bool( chunk.tabulatedPromptGammas() ) );
  CHECK( false == bool( chunk.tabulatedDelayedGammas() ) );
  CHECK( false == bool( chunk.tabulatedDelayedBetas() ) );
  CHECK( false == bool( chunk.tabulatedNeutrinos() ) );
  CHECK( false == bool( chunk.tabulatedTotalMinusNeutrinos() ) );
  CHECK( true == bool( chunk.tabulatedTotal() ) );

  auto component = *chunk.tabulatedEFR();
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

  component = *chunk.tabulatedET();
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

  CHECK( 11 == chunk.NC() );
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
