#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ThermalScatteringData =
section::Type< 6 >::ContinuumEnergyAngle::ThermalScatteringData;

std::string chunkForLTT5();
void verifyChunkForLTT5( const ThermalScatteringData& );
std::string chunkForLTT6();
void verifyChunkForLTT6( const ThermalScatteringData& );

SCENARIO( "ThermalScatteringData" ) {

  GIVEN( "valid data for a ThermalScatteringData with LTT=5" ) {

    std::string string = chunkForLTT5();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int n2 = 6;
      std::vector< double > data = { 0., 0., 0., 0., 0., 0.,
                                     9.999999e-6, 9.477167e+1, -5.379121e-1,
                                     0.21062848, 0.70490082, 9.552579e-1,
                                     1.265100e-1, 0., 0., 0., 0., 0. };

      ThermalScatteringData chunk( energy, n2, std::move( data ) );

      THEN( "a ThermalScatteringData can be constructed and members can be "
            "tested" ) {

        verifyChunkForLTT5( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ThermalScatteringData chunk( begin, end, lineNumber, 1301, 6, 222 );

      THEN( "a ThermalScatteringData can be constructed and members can be "
            "tested" ) {

        verifyChunkForLTT5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ThermalScatteringData with LTT=6" ) {

    std::string string = chunkForLTT6();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > cosines = { -5.379121e-1, 0.21062848,
                                         0.70490082, 9.552579e-1 };

      ThermalScatteringData chunk( energy, std::move( cosines ) );

      THEN( "a ThermalScatteringData can be constructed and members can be "
            "tested" ) {

        verifyChunkForLTT6( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ThermalScatteringData chunk( begin, end, lineNumber, 1301, 6, 222 );

      THEN( "a ThermalScatteringData can be constructed and members can be "
            "tested" ) {

        verifyChunkForLTT6( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkForLTT5() {
  return
    " 0.000000+0 1.000000-5          0          0         18          61301 6222     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n"
    " 9.999999-6 9.477167+1-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n"
    " 1.265100-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n";
}

void verifyChunkForLTT5( const ThermalScatteringData& chunk ) {

  CHECK( 3 == chunk.LANG() );
  CHECK( 3 == chunk.representation() );
  CHECK( 5 == chunk.LTT() );
  CHECK( 1e-5 == Approx( chunk.E() ) );
  CHECK( 1e-5 == Approx( chunk.incidentEnergy() ) );

  CHECK( 18 == chunk.NW() );
  CHECK( 6 == chunk.N2() );

  auto data = chunk.data();
  CHECK( 18 == data.size() );
  CHECK( 0. == Approx( data[0] ) );
  CHECK( 0. == Approx( data[1] ) );
  CHECK( 0. == Approx( data[2] ) );
  CHECK( 0. == Approx( data[3] ) );
  CHECK( 0. == Approx( data[4] ) );
  CHECK( 0. == Approx( data[5] ) );
  CHECK( 9.999999e-6 == Approx( data[6] ) );
  CHECK( 9.477167e+1 == Approx( data[7] ) );
  CHECK( -5.379121e-1 == Approx( data[8] ) );
  CHECK( 0.21062848 == Approx( data[9] ) );
  CHECK( 0.70490082 == Approx( data[10] ) );
  CHECK( 9.552579e-1 == Approx( data[11] ) );
  CHECK( 1.265100e-1 == Approx( data[12] ) );
  CHECK( 0. == Approx( data[13] ) );
  CHECK( 0. == Approx( data[14] ) );
  CHECK( 0. == Approx( data[15] ) );
  CHECK( 0. == Approx( data[16] ) );
  CHECK( 0. == Approx( data[17] ) );

  CHECK( 3 == chunk.NEP() );
  CHECK( 3 == chunk.numberSecondaryEnergies() );

  CHECK( 3 == chunk.EP().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 0. == Approx( chunk.EP()[0] ) );
  CHECK( 9.999999e-6 == Approx( chunk.EP()[1] ) );
  CHECK( 1.265100e-1 == Approx( chunk.EP()[2] ) );
  CHECK( 0. == Approx( chunk.energies()[0] ) );
  CHECK( 9.999999e-6 == Approx( chunk.energies()[1] ) );
  CHECK( 1.265100e-1 == Approx( chunk.energies()[2] ) );

  auto pp = chunk.PP();
  CHECK( 3 == pp.size() );
  CHECK( 0. == Approx( pp[0] ) );
  CHECK( 9.477167e+1 == Approx( pp[1] ) );
  CHECK( 0. == Approx( pp[2] ) );

  CHECK( 3 == chunk.MU().size() );
  CHECK( 3 == chunk.cosines().size() );
  CHECK( 4 == chunk.MU()[0].size() );
  CHECK( 0. == Approx( chunk.MU()[0][0] ) );
  CHECK( 0. == Approx( chunk.MU()[0][1] ) );
  CHECK( 0. == Approx( chunk.MU()[0][2] ) );
  CHECK( 0. == Approx( chunk.MU()[0][3] ) );
  CHECK( 4 == chunk.MU()[1].size() );
  CHECK( -5.379121e-1 == Approx( chunk.MU()[1][0] ) );
  CHECK( 0.21062848 == Approx( chunk.MU()[1][1] ) );
  CHECK( 0.70490082 == Approx( chunk.MU()[1][2] ) );
  CHECK( 9.552579e-1 == Approx( chunk.MU()[1][3] ) );
  CHECK( 4 == chunk.MU()[2].size() );
  CHECK( 0. == Approx( chunk.MU()[2][0] ) );
  CHECK( 0. == Approx( chunk.MU()[2][1] ) );
  CHECK( 0. == Approx( chunk.MU()[2][2] ) );
  CHECK( 0. == Approx( chunk.MU()[2][3] ) );
  CHECK( 4 == chunk.cosines()[0].size() );
  CHECK( 0. == Approx( chunk.cosines()[0][0] ) );
  CHECK( 0. == Approx( chunk.cosines()[0][1] ) );
  CHECK( 0. == Approx( chunk.cosines()[0][2] ) );
  CHECK( 0. == Approx( chunk.cosines()[0][3] ) );
  CHECK( 4 == chunk.cosines()[1].size() );
  CHECK( -5.379121e-1 == Approx( chunk.cosines()[1][0] ) );
  CHECK( 0.21062848 == Approx( chunk.cosines()[1][1] ) );
  CHECK( 0.70490082 == Approx( chunk.cosines()[1][2] ) );
  CHECK( 9.552579e-1 == Approx( chunk.cosines()[1][3] ) );
  CHECK( 4 == chunk.cosines()[2].size() );
  CHECK( 0. == Approx( chunk.cosines()[2][0] ) );
  CHECK( 0. == Approx( chunk.cosines()[2][1] ) );
  CHECK( 0. == Approx( chunk.cosines()[2][2] ) );
  CHECK( 0. == Approx( chunk.cosines()[2][3] ) );

  CHECK( 4 == chunk.NC() );
}

std::string chunkForLTT6() {
  return
    " 0.000000+0 1.000000-5          0          0          6          61301 6222     \n"
    " 1.000000-5 1.000000+0-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n";
}

void verifyChunkForLTT6( const ThermalScatteringData& chunk ) {

  CHECK( 3 == chunk.LANG() );
  CHECK( 3 == chunk.representation() );
  CHECK( 6 == chunk.LTT() );
  CHECK( 1e-5 == Approx( chunk.E() ) );
  CHECK( 1e-5 == Approx( chunk.incidentEnergy() ) );

  CHECK( 6 == chunk.NW() );
  CHECK( 6 == chunk.N2() );

  auto data = chunk.data();
  CHECK( 6 == data.size() );
  CHECK( 1e-5 == Approx( data[0] ) );
  CHECK( 1. == Approx( data[1] ) );
  CHECK( -5.379121e-1 == Approx( data[2] ) );
  CHECK( 0.21062848 == Approx( data[3] ) );
  CHECK( 0.70490082 == Approx( data[4] ) );
  CHECK( 9.552579e-1 == Approx( data[5] ) );

  CHECK( 1 == chunk.NEP() );
  CHECK( 1 == chunk.numberSecondaryEnergies() );

  CHECK( 1 == chunk.EP().size() );
  CHECK( 1 == chunk.energies().size() );
  CHECK( 1e-5 == Approx( chunk.EP()[0] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );

  CHECK( 1 == chunk.PP().size() );
  CHECK( 1. == Approx( chunk.PP()[0] ) );

  CHECK( 1 == chunk.MU().size() );
  CHECK( 1 == chunk.cosines().size() );
  CHECK( 4 == chunk.MU()[0].size() );
  CHECK( -5.379121e-1 == Approx( chunk.MU()[0][0] ) );
  CHECK( 0.21062848 == Approx( chunk.MU()[0][1] ) );
  CHECK( 0.70490082 == Approx( chunk.MU()[0][2] ) );
  CHECK( 9.552579e-1 == Approx( chunk.MU()[0][3] ) );
  CHECK( 4 == chunk.cosines()[0].size() );
  CHECK( -5.379121e-1 == Approx( chunk.cosines()[0][0] ) );
  CHECK( 0.21062848 == Approx( chunk.cosines()[0][1] ) );
  CHECK( 0.70490082 == Approx( chunk.cosines()[0][2] ) );
  CHECK( 9.552579e-1 == Approx( chunk.cosines()[0][3] ) );

  CHECK( 2 == chunk.NC() );
}
