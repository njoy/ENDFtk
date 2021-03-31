#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/458.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ThermalPointComponents = section::Type< 1, 458 >::ThermalPointComponents;

std::string chunk();
void verifyChunk( const ThermalPointComponents& );
std::string invalidNPL();

SCENARIO( "ThermalPointComponents" ) {

  GIVEN( "valid data for a ThermalPointComponents" ) {

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

      ThermalPointComponents chunk( std::move( efr ), std::move( enp ),
                                    std::move( end ), std::move( egp ),
                                    std::move( egd ), std::move( eb ),
                                    std::move( enu ), std::move( er ),
                                    std::move( et ) );

      THEN( "a ThermalPointComponents can be constructed and members can be "
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

      ThermalPointComponents chunk( begin, end, lineNumber, 9228, 1, 458 );

      THEN( "a ThermalPointComponents can be constructed and members can be "
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

  GIVEN( "invalid data for a ThermalPointComponents" ) {

    WHEN( "a string representation with an invalid NPL" ) {

      std::string string = invalidNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ThermalPointComponents( begin, end, lineNumber,
                                             9228, 1, 458 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0         18          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.100000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n";
}

void verifyChunk( const ThermalPointComponents& chunk ) {

  CHECK( false == chunk.LFC() );
  CHECK( false == chunk.tabulatedEnergyRelease() );
  CHECK( 0 == chunk.NPLY() );
  CHECK( 0 == chunk.order() );
  CHECK( 0 == chunk.NFC() );
  CHECK( 0 == chunk.numberTabulatedComponents() );

  CHECK( 1.691300e+8 == Approx( chunk.E()[0][0] ) );
  CHECK( 4.838000e+6 == Approx( chunk.E()[1][0] ) );
  CHECK( 7.400000e+3 == Approx( chunk.E()[2][0] ) );
  CHECK( 6.600000e+6 == Approx( chunk.E()[3][0] ) );
  CHECK( 6.330000e+6 == Approx( chunk.E()[4][0] ) );
  CHECK( 6.500000e+6 == Approx( chunk.E()[5][0] ) );
  CHECK( 8.750000e+6 == Approx( chunk.E()[6][0] ) );
  CHECK( 1.934054e+8 == Approx( chunk.E()[7][0] ) );
  CHECK( 2.021554e+8 == Approx( chunk.E()[8][0] ) );

  CHECK( 4.900000e+5 == Approx( chunk.E()[0][1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.E()[1][1] ) );
  CHECK( 1.110000e+3 == Approx( chunk.E()[2][1] ) );
  CHECK( 5.000000e+5 == Approx( chunk.E()[3][1] ) );
  CHECK( 5.000000e+4 == Approx( chunk.E()[4][1] ) );
  CHECK( 5.100000e+4 == Approx( chunk.E()[5][1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.E()[6][1] ) );
  CHECK( 1.500000e+5 == Approx( chunk.E()[7][1] ) );
  CHECK( 1.300000e+5 == Approx( chunk.E()[8][1] ) );

  CHECK( 1.691300e+8 == Approx( chunk.energyRelease()[0][0] ) );
  CHECK( 4.838000e+6 == Approx( chunk.energyRelease()[1][0] ) );
  CHECK( 7.400000e+3 == Approx( chunk.energyRelease()[2][0] ) );
  CHECK( 6.600000e+6 == Approx( chunk.energyRelease()[3][0] ) );
  CHECK( 6.330000e+6 == Approx( chunk.energyRelease()[4][0] ) );
  CHECK( 6.500000e+6 == Approx( chunk.energyRelease()[5][0] ) );
  CHECK( 8.750000e+6 == Approx( chunk.energyRelease()[6][0] ) );
  CHECK( 1.934054e+8 == Approx( chunk.energyRelease()[7][0] ) );
  CHECK( 2.021554e+8 == Approx( chunk.energyRelease()[8][0] ) );

  CHECK( 4.900000e+5 == Approx( chunk.energyRelease()[0][1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.energyRelease()[1][1] ) );
  CHECK( 1.110000e+3 == Approx( chunk.energyRelease()[2][1] ) );
  CHECK( 5.000000e+5 == Approx( chunk.energyRelease()[3][1] ) );
  CHECK( 5.000000e+4 == Approx( chunk.energyRelease()[4][1] ) );
  CHECK( 5.100000e+4 == Approx( chunk.energyRelease()[5][1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.energyRelease()[6][1] ) );
  CHECK( 1.500000e+5 == Approx( chunk.energyRelease()[7][1] ) );
  CHECK( 1.300000e+5 == Approx( chunk.energyRelease()[8][1] ) );

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

  CHECK( 1.691300e+8 == Approx( chunk.fissionFragments()[0] ) );
  CHECK( 4.838000e+6 == Approx( chunk.promptNeutrons()[0] ) );
  CHECK( 7.400000e+3 == Approx( chunk.delayedNeutrons()[0] ) );
  CHECK( 6.600000e+6 == Approx( chunk.promptGammas()[0] ) );
  CHECK( 6.330000e+6 == Approx( chunk.delayedGammas()[0] ) );
  CHECK( 6.500000e+6 == Approx( chunk.delayedBetas()[0] ) );
  CHECK( 8.750000e+6 == Approx( chunk.neutrinos()[0] ) );
  CHECK( 1.934054e+8 == Approx( chunk.totalMinusNeutrinos()[0] ) );
  CHECK( 2.021554e+8 == Approx( chunk.total()[0] ) );

  CHECK( 4.900000e+5 == Approx( chunk.fissionFragments()[1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.promptNeutrons()[1] ) );
  CHECK( 1.110000e+3 == Approx( chunk.delayedNeutrons()[1] ) );
  CHECK( 5.000000e+5 == Approx( chunk.promptGammas()[1] ) );
  CHECK( 5.000000e+4 == Approx( chunk.delayedGammas()[1] ) );
  CHECK( 5.100000e+4 == Approx( chunk.delayedBetas()[1] ) );
  CHECK( 7.000000e+4 == Approx( chunk.neutrinos()[1] ) );
  CHECK( 1.500000e+5 == Approx( chunk.totalMinusNeutrinos()[1] ) );
  CHECK( 1.300000e+5 == Approx( chunk.total()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidNPL() {
  return
    " 0.000000+0 0.000000+0          0          0         19          99228 1458     \n"
    " 1.691300+8 4.900000+5 4.838000+6 7.000000+4 7.400000+3 1.110000+39228 1458     \n"
    " 6.600000+6 5.000000+5 6.330000+6 5.000000+4 6.500000+6 5.000000+49228 1458     \n"
    " 8.750000+6 7.000000+4 1.934054+8 1.500000+5 2.021554+8 1.300000+59228 1458     \n"
    " 1.000000+6                                                       9228 1458     \n";
}
