// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/458.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using PolynomialComponents = section::Type< 1, 458 >::PolynomialComponents;

std::string chunk();
void verifyChunk( const PolynomialComponents& );
std::string invalidNPL();

SCENARIO( "PolynomialComponents" ) {

  GIVEN( "valid data for a PolynomialComponents" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::array< double, 2 > > efr = { {{ 1.691300e+8, 4.900000e+5 }},
                                                     {{ -2.66e-1, 2.66e-2 }} };
      std::vector< std::array< double, 2 > > enp = { {{ 4.838000e+6, 7.000000e+4 }},
                                                     {{ 3.004e-1, 3.004e-2 }} };
      std::vector< std::array< double, 2 > > end = { {{ 7.400000e+3, 1.110000e+3 }},
                                                     {{ 0., 0. }} };
      std::vector< std::array< double, 2 > > egp = { {{ 6.600000e+6, 5.000000e+5 }},
                                                     {{ 7.77e-2, 7.77e-3 }} };
      std::vector< std::array< double, 2 > > egd = { {{ 6.330000e+6, 5.000000e+4 }},
                                                     {{ -7.500e-2, 7.600e-3 }} };
      std::vector< std::array< double, 2 > > eb  = { {{ 6.500000e+6, 5.100000e+4 }},
                                                     {{ -7.700e-2, 7.800e-3 }} };
      std::vector< std::array< double, 2 > > enu = { {{ 8.750000e+6, 7.000000e+4 }},
                                                     {{ -1.00e-1, 1.00e-2 }} };
      std::vector< std::array< double, 2 > > er  = { {{ 1.934054e+8, 1.500000e+5 }},
                                                     {{ -3.790e-2, 3.790e-3 }} };
      std::vector< std::array< double, 2 > > et  = { {{ 2.021554e+8, 1.300000e+5 }},
                                                     {{ -1.379e-1, 1.379e-2 }} };

      PolynomialComponents chunk( std::move( efr ), std::move( enp ),
                                  std::move( end ), std::move( egp ),
                                  std::move( egd ), std::move( eb ),
                                  std::move( enu ), std::move( er ),
                                  std::move( et ) );

      THEN( "a PolynomialComponents can be constructed and members can be "
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

      PolynomialComponents chunk( begin, end, lineNumber, 9228, 1, 458 );

      THEN( "a PolynomialComponents can be constructed and members can be "
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

  GIVEN( "invalid data for a PolynomialComponents" ) {

    WHEN( "inconsistent sizes are used" ) {

      std::vector< std::array< double, 2 > > invalid = { {{ 1.691300e+8, 4.900000e+5 }} };
      std::vector< std::array< double, 2 > > enp = { {{ 4.838000e+6, 7.000000e+4 }},
                                                     {{ 3.004e-1, 3.004e-2 }} };
      std::vector< std::array< double, 2 > > end = { {{ 7.400000e+3, 1.110000e+3 }},
                                                     {{ 0., 0. }} };
      std::vector< std::array< double, 2 > > egp = { {{ 6.600000e+6, 5.000000e+5 }},
                                                     {{ 7.77e-2, 7.77e-3 }} };
      std::vector< std::array< double, 2 > > egd = { {{ 6.330000e+6, 5.000000e+4 }},
                                                     {{ -7.500e-2, 7.600e-3 }} };
      std::vector< std::array< double, 2 > > eb  = { {{ 6.500000e+6, 5.100000e+4 }},
                                                     {{ -7.700e-2, 7.800e-3 }} };
      std::vector< std::array< double, 2 > > enu = { {{ 8.750000e+6, 7.000000e+4 }},
                                                     {{ -1.00e-1, 1.00e-2 }} };
      std::vector< std::array< double, 2 > > er  = { {{ 1.934054e+8, 1.500000e+5 }},
                                                     {{ -3.790e-2, 3.790e-3 }} };
      std::vector< std::array< double, 2 > > et  = { {{ 2.021554e+8, 1.300000e+5 }},
                                                     {{ -1.379e-1, 1.379e-2 }} };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialComponents( std::move( invalid ), std::move( enp ),
                                            std::move( end ), std::move( egp ),
                                            std::move( egd ), std::move( eb ),
                                            std::move( enu ), std::move( er ),
                                            std::move( et ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid NPL" ) {

      std::string string = invalidNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialComponents( begin, end, lineNumber,
                                             9228, 1, 458 ) );
      } // THEN
    } // WHEN
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

void verifyChunk( const PolynomialComponents& chunk ) {

  CHECK( false == chunk.LFC() );
  CHECK( false == chunk.tabulatedEnergyRelease() );
  CHECK( 1 == chunk.NPLY() );
  CHECK( 1 == chunk.order() );
  CHECK( 0 == chunk.NFC() );
  CHECK( 0 == chunk.numberTabulatedComponents() );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.E()[0][0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.E()[1][0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.E()[2][0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.E()[3][0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.E()[4][0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.E()[5][0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.E()[6][0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.E()[7][0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.E()[8][0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.E()[0][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.E()[1][0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.E()[2][0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.E()[3][0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.E()[4][0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.E()[5][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.E()[6][0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.E()[7][0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.E()[8][0][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.energyRelease()[0][0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.energyRelease()[1][0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.energyRelease()[2][0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.energyRelease()[3][0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.energyRelease()[4][0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.energyRelease()[5][0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.energyRelease()[6][0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.energyRelease()[7][0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.energyRelease()[8][0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.energyRelease()[0][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.energyRelease()[1][0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.energyRelease()[2][0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.energyRelease()[3][0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.energyRelease()[4][0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.energyRelease()[5][0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.energyRelease()[6][0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.energyRelease()[7][0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.energyRelease()[8][0][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( chunk.E()[0][1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( chunk.E()[1][1][0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.E()[2][1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( chunk.E()[3][1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( chunk.E()[4][1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( chunk.E()[5][1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( chunk.E()[6][1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( chunk.E()[7][1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( chunk.E()[8][1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( chunk.E()[0][1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( chunk.E()[1][1][1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.E()[2][1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( chunk.E()[3][1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( chunk.E()[4][1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( chunk.E()[5][1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( chunk.E()[6][1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( chunk.E()[7][1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( chunk.E()[8][1][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( chunk.energyRelease()[0][1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( chunk.energyRelease()[1][1][0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energyRelease()[2][1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( chunk.energyRelease()[3][1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( chunk.energyRelease()[4][1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( chunk.energyRelease()[5][1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( chunk.energyRelease()[6][1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( chunk.energyRelease()[7][1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( chunk.energyRelease()[8][1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( chunk.energyRelease()[0][1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( chunk.energyRelease()[1][1][1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energyRelease()[2][1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( chunk.energyRelease()[3][1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( chunk.energyRelease()[4][1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( chunk.energyRelease()[5][1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( chunk.energyRelease()[6][1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( chunk.energyRelease()[7][1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( chunk.energyRelease()[8][1][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.EFR()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.ENP()[0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.END()[0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.EGP()[0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.EGD()[0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.EB()[0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.ENU()[0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.ER()[0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.ET()[0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.EFR()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.ENP()[0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.END()[0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.EGP()[0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.EGD()[0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.EB()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.ENU()[0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.ER()[0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.ET()[0][1] ) );

  CHECK_THAT( 1.691300e+8, WithinRel( chunk.fissionFragments()[0][0] ) );
  CHECK_THAT( 4.838000e+6, WithinRel( chunk.promptNeutrons()[0][0] ) );
  CHECK_THAT( 7.400000e+3, WithinRel( chunk.delayedNeutrons()[0][0] ) );
  CHECK_THAT( 6.600000e+6, WithinRel( chunk.promptGammas()[0][0] ) );
  CHECK_THAT( 6.330000e+6, WithinRel( chunk.delayedGammas()[0][0] ) );
  CHECK_THAT( 6.500000e+6, WithinRel( chunk.delayedBetas()[0][0] ) );
  CHECK_THAT( 8.750000e+6, WithinRel( chunk.neutrinos()[0][0] ) );
  CHECK_THAT( 1.934054e+8, WithinRel( chunk.totalMinusNeutrinos()[0][0] ) );
  CHECK_THAT( 2.021554e+8, WithinRel( chunk.total()[0][0] ) );

  CHECK_THAT( 4.900000e+5, WithinRel( chunk.fissionFragments()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.promptNeutrons()[0][1] ) );
  CHECK_THAT( 1.110000e+3, WithinRel( chunk.delayedNeutrons()[0][1] ) );
  CHECK_THAT( 5.000000e+5, WithinRel( chunk.promptGammas()[0][1] ) );
  CHECK_THAT( 5.000000e+4, WithinRel( chunk.delayedGammas()[0][1] ) );
  CHECK_THAT( 5.100000e+4, WithinRel( chunk.delayedBetas()[0][1] ) );
  CHECK_THAT( 7.000000e+4, WithinRel( chunk.neutrinos()[0][1] ) );
  CHECK_THAT( 1.500000e+5, WithinRel( chunk.totalMinusNeutrinos()[0][1] ) );
  CHECK_THAT( 1.300000e+5, WithinRel( chunk.total()[0][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( chunk.EFR()[1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( chunk.ENP()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.END()[1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( chunk.EGP()[1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( chunk.EGD()[1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( chunk.EB()[1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( chunk.ENU()[1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( chunk.ER()[1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( chunk.ET()[1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( chunk.EFR()[1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( chunk.ENP()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.END()[1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( chunk.EGP()[1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( chunk.EGD()[1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( chunk.EB()[1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( chunk.ENU()[1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( chunk.ER()[1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( chunk.ET()[1][1] ) );

  CHECK_THAT( -2.660000e-1, WithinRel( chunk.fissionFragments()[1][0] ) );
  CHECK_THAT( 3.004000e-1, WithinRel( chunk.promptNeutrons()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.delayedNeutrons()[1][0] ) );
  CHECK_THAT( 7.770000e-2, WithinRel( chunk.promptGammas()[1][0] ) );
  CHECK_THAT( -7.500000e-2, WithinRel( chunk.delayedGammas()[1][0] ) );
  CHECK_THAT( -7.700000e-2, WithinRel( chunk.delayedBetas()[1][0] ) );
  CHECK_THAT( -1.000000e-1, WithinRel( chunk.neutrinos()[1][0] ) );
  CHECK_THAT( -3.790000e-2, WithinRel( chunk.totalMinusNeutrinos()[1][0] ) );
  CHECK_THAT( -1.379000e-1, WithinRel( chunk.total()[1][0] ) );

  CHECK_THAT( 2.660000e-2, WithinRel( chunk.fissionFragments()[1][1] ) );
  CHECK_THAT( 3.004000e-2, WithinRel( chunk.promptNeutrons()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.delayedNeutrons()[1][1] ) );
  CHECK_THAT( 7.770000e-3, WithinRel( chunk.promptGammas()[1][1] ) );
  CHECK_THAT( 7.600000e-3, WithinRel( chunk.delayedGammas()[1][1] ) );
  CHECK_THAT( 7.800000e-3, WithinRel( chunk.delayedBetas()[1][1] ) );
  CHECK_THAT( 1.000000e-2, WithinRel( chunk.neutrinos()[1][1] ) );
  CHECK_THAT( 3.790000e-3, WithinRel( chunk.totalMinusNeutrinos()[1][1] ) );
  CHECK_THAT( 1.379000e-2, WithinRel( chunk.total()[1][1] ) );

  CHECK( 7 == chunk.NC() );
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
