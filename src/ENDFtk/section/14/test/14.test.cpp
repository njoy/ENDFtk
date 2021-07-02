#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/14.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using PhotonDistribution = section::Type< 14 >::PhotonDistribution;
using AnisotropicPhotonDistribution = section::Type< 14 >::AnisotropicPhotonDistribution;
using LegendreDistributions = section::Type< 14 >::LegendreDistributions;
using LegendreCoefficients = section::Type< 14 >::LegendreCoefficients;
using TabulatedDistributions = section::Type< 14 >::TabulatedDistributions;
using TabulatedDistribution = section::Type< 14 >::TabulatedDistribution;
using IsotropicDiscretePhoton = section::Type< 14 >::IsotropicDiscretePhoton;

std::string chunkWithLTT0();
void verifyChunkWithLTT0( const section::Type< 14 >& );
std::string chunkWithLTT1();
void verifyChunkWithLTT1( const section::Type< 14 >& );
std::string chunkWithInvalidLTT();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 14 >" ) {

  GIVEN( "valid data for a section::Type< 14 > with LTT=0" ) {

    std::string sectionString = chunkWithLTT0() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 2;
      double za = 92235.;
      double awr = 2.330248e+2;
      unsigned int nk = 2;

      section::Type< 14 > chunk( mt, za, awr, nk );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 14 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 14, 2, std::string( sectionString ) );

      section::Type< 14 > chunk = section.parse< 14 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT0( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 14 > with LTT=1" ) {

    std::string sectionString = chunkWithLTT1() + validSEND();

    WHEN( "the data is given explicitly using PhotonDistribution" ) {

      int mt = 2;
      double za = 92235.;
      double awr = 2.330248e+2;

      std::vector< PhotonDistribution > photons =
        { IsotropicDiscretePhoton( 1.5e+6, 2e+6 ),
          LegendreDistributions( 4.438900e+6, 4.438900e+6,
                                 { 2 }, { 3 },
                                 { { 4.812998e+6, { 0., 0.04076 } },
                                   { 15e+7, { 0., 0. } } } ) };

      section::Type< 14 > chunk( mt, za, awr, std::move( photons ) );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using AnisotropicPhotonDistribution "
          "and pairs of energy values" ) {

      int mt = 2;
      double za = 92235.;
      double awr = 2.330248e+2;

      std::vector< std::array< double, 2 > > isotropic = { {{ 1.5e+6, 2e+6 }} };

      std::vector< AnisotropicPhotonDistribution > anisotropic =
        { LegendreDistributions( 4.438900e+6, 4.438900e+6,
                                 { 2 }, { 3 },
                                 { { 4.812998e+6, { 0., 0.04076 } },
                                   { 15e+7, { 0., 0. } } } ) };

      section::Type< 14 > chunk( mt, za, awr,
                                 std::move( isotropic ),
                                 std::move( anisotropic ) );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using AnisotropicPhotonDistribution "
          "and vectors of energies and levels" ) {

      int mt = 2;
      double za = 92235.;
      double awr = 2.330248e+2;

      std::vector< double > energies = { 1.5e+6 };
      std::vector< double > levels = { 2.0e+6 };

      std::vector< AnisotropicPhotonDistribution > anisotropic =
        { LegendreDistributions( 4.438900e+6, 4.438900e+6,
                                 { 2 }, { 3 },
                                 { { 4.812998e+6, { 0., 0.04076 } },
                                   { 15e+7, { 0., 0. } } } ) };

      section::Type< 14 > chunk( mt, za, awr,
                                 std::move( energies ),
                                 std::move( levels ),
                                 std::move( anisotropic ) );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 14 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 14 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 14, 2, std::string( sectionString ) );

      section::Type< 14 > chunk = section.parse< 14 >();

      THEN( "a section::Type< 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLTT1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 14 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 14 >" ) {

    WHEN( "a string representation of a section::Type< 14 > with an "
          "invalid LTT" ) {

      std::string sectionString = chunkWithInvalidLTT() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 14 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 14 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunkWithLTT0() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 14 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLTT0() {
  return
    " 9.223500+4 2.330248+2          1          0          2          0922814  2     \n";
}

void verifyChunkWithLTT0( const section::Type< 14 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 92235. == Approx( chunk.ZA() ) );
  CHECK( 2.330248e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.330248e+2 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( 0 == chunk.NI() );
  CHECK( 0 == chunk.numberIsotropicPhotons() );
  CHECK( 2 == chunk.NK() );
  CHECK( 2 == chunk.numberPhotons() );

  CHECK( 0 == chunk.LTT() );
  CHECK( 0 == chunk.LAW() );
  CHECK( true == chunk.LI() );
  CHECK( true == chunk.isotropicDistributions() );

  CHECK( 0 == chunk.photonAngularDistributions().size() );

  CHECK( 1 == chunk.NC() );
}

std::string chunkWithLTT1() {
  return
    " 9.223500+4 2.330248+2          0          1          2          1922814  2     \n"
    " 1.500000+6 2.000000+6          0          0          0          0922814  2     \n"
    " 4.438900+6 4.438900+6          0          0          1          2922814  2     \n"
    "          2          3                                            922814  2     \n"
    " 0.000000+0 4.812998+6          0          0          2          0922814  2     \n"
    " 0.000000+0 4.076000-2                                            922814  2     \n"
    " 0.000000+0 1.500000+8          0          0          2          0922814  2     \n"
    " 0.000000+0 0.000000+0                                            922814  2     \n";
}

void verifyChunkWithLTT1( const section::Type< 14 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 92235. == Approx( chunk.ZA() ) );
  CHECK( 2.330248e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.330248e+2 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.NI() );
  CHECK( 1 == chunk.numberIsotropicPhotons() );
  CHECK( 2 == chunk.NK() );
  CHECK( 2 == chunk.numberPhotons() );

  CHECK( 1 == chunk.LTT() );
  CHECK( 1 == chunk.LAW() );
  CHECK( false == chunk.LI() );
  CHECK( false == chunk.isotropicDistributions() );

  CHECK( 2 == chunk.photonAngularDistributions().size() );

  auto isotropic = std::get< IsotropicDiscretePhoton >( chunk.photonAngularDistributions()[0] );

  CHECK( true == isotropic.LI() );
  CHECK( true == isotropic.isotropicDistributions() );
  CHECK( 0 == isotropic.LTT() );
  CHECK( 0 == isotropic.LAW() );

  CHECK( 1.5e+6 == Approx( isotropic.EG() ) );
  CHECK( 1.5e+6 == Approx( isotropic.photonEnergy() ) );
  CHECK( 2e+6 == Approx( isotropic.ES() ) );
  CHECK( 2e+6 == Approx( isotropic.levelEnergy() ) );

  auto photon = std::get< LegendreDistributions >( chunk.photonAngularDistributions()[1] );

  CHECK( false == photon.LI() );
  CHECK( false == photon.isotropicDistributions() );
  CHECK( 1 == photon.LTT() );
  CHECK( 1 == photon.LAW() );

  CHECK( 4.438900e+6 == Approx( photon.EG() ) );
  CHECK( 4.438900e+6 == Approx( photon.photonEnergy() ) );
  CHECK( 4.438900e+6 == Approx( photon.ES() ) );
  CHECK( 4.438900e+6 == Approx( photon.levelEnergy() ) );

  CHECK( 2 == photon.NE() );
  CHECK( 1 == photon.NR() );
  CHECK( 1 == photon.interpolants().size() );
  CHECK( 1 == photon.boundaries().size() );
  CHECK( 3 == photon.interpolants()[0] );
  CHECK( 2 == photon.boundaries()[0] );

  CHECK( 2 == photon.incidentEnergies().size() );
  CHECK( 2 == photon.angularDistributions().size() );

  CHECK( 4.812998e+6 == Approx( photon.incidentEnergies()[0] ) );
  CHECK( 15e+7 == Approx( photon.incidentEnergies()[1] ) );

  auto distributions = photon.angularDistributions();

  auto d = distributions[0];
  CHECK( 4.812998e+6 == Approx( d.E() ) );
  CHECK( 4.812998e+6 == Approx( d.incidentEnergy() ) );
  CHECK( 2 == d.NL() );
  CHECK( 2 == d.legendreOrder() );
  CHECK( 2 == d.coefficients().size() );
  CHECK( 0.  == Approx( d.coefficients()[0] ) );
  CHECK( 4.076000e-2 == Approx( d.coefficients()[1] ) );

  d = distributions[1];
  CHECK( 15e+7 == Approx( d.E() ) );
  CHECK( 15e+7 == Approx( d.incidentEnergy() ) );
  CHECK( 2 == d.NL() );
  CHECK( 2 == d.legendreOrder() );
  CHECK( 2 == d.coefficients().size() );
  CHECK( 0. == Approx( d.coefficients()[0] ) );
  CHECK( 0. == Approx( d.coefficients()[1] ) );

  CHECK( 8 == chunk.NC() );
}

std::string chunkWithInvalidLTT() {
  return
    " 9.223500+4 2.330250+2          0          4          1          0922814  2     \n";
}

std::string validSEND() {
  return
    "                                                                  922814  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  922814  4     \n";
}
