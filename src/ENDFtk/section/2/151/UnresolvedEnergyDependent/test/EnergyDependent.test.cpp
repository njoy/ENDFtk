#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using UnresolvedEnergyDependent = section::Type< 2, 151 >::UnresolvedEnergyDependent;
using JValue = section::Type< 2, 151 >::UnresolvedEnergyDependent::JValue;
using LValue = section::Type< 2, 151 >::UnresolvedEnergyDependent::LValue;

std::string chunk();
void verifyChunk( const UnresolvedEnergyDependent& );
std::string chunkWithNoLValues();

SCENARIO( "UnresolvedEnergyDependent" ) {

  GIVEN( "valid data for an UnresolvedEnergyDependent" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spin = 0.0;
      double ap = 0.67959;
      bool lssf = false;

      std::vector< LValue > lvalues =
        { { 89.13540, 0,
            { { 0.5, 2, 3, 4, 1, 5,
                { 6000., 8000. }, { 12406., 12406. },
                { 0.45901, 0.45901 }, { 0.205, 0.2051 },
                { 0., 0. }, { 0., 0.1 } } } },
          { 89.13540, 1,
            { { 0.5, 3, 2, 1, 4, 5,
                { 6000., 7000., 8000. }, { 12406., 12406., 12406. },
                { 6.7238, 6.7238, 6.7238 }, { 0.205, 0.205, 0.205 },
                { 0., 0., 0. }, { 0., 0., 0. } },
              { 1.5, 1, 4, 2, 0, 5,
                { 6000., 8000. }, { 6202.8, 6202.8 },
                { 3.3619, 3.3619 }, { 0.205, 0.205 },
                { 0., 0. }, { 0., 0. } } } } };

      UnresolvedEnergyDependent chunk( spin, ap, lssf, std::move( lvalues ) );

      THEN( "a UnresolvedEnergyDependent can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      UnresolvedEnergyDependent chunk( begin, end, lineNumber, 3843, 2, 151 );

      THEN( "a UnresolvedEnergyDependent can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "no l values are given" ) {

      double spin = 0.0;
      double ap = 0.67959;
      bool lssf = false;

      std::vector< LValue > lvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependent( spin, ap, lssf, std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no l values is used" ) {

      std::string string = chunkWithNoLValues();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependent( begin, end, lineNumber, 3843, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 6.795900-1          0          0          2          03843 2151     \n"
    // L=0
    " 8.913540+1 0.000000+0          0          0          1          03843 2151     \n"
    // L=0 J=0.5
    " 5.000000-1 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 4.590100-1 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 1.000000-1 4.590100-1 2.051000-1 0.000000+03843 2151     \n"
    // L=1
    " 8.913540+1 0.000000+0          1          0          2          03843 2151     \n"
    // L=1 J=0.5
    " 5.000000-1 0.000000+0          5          0         24          33843 2151     \n"
    " 0.000000+0 0.000000+0 4.000000+0 3.000000+0 2.000000+0 1.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    // L=1 J=1.5
    " 1.500000+0 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 4.000000+0 2.000000+03843 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n";
}

void verifyChunk( const UnresolvedEnergyDependent& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 2 == chunk.LRF() );
  CHECK( 2 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK( 0.0 == Approx( chunk.SPI() ) );
  CHECK( 0.0 == Approx( chunk.spin() ) );
  CHECK( 0.67959 == Approx( chunk.AP() ) );
  CHECK( 0.67959 == Approx( chunk.scatteringRadius() ) );
  CHECK( false == Approx( chunk.LSSF() ) );
  CHECK( false == Approx( chunk.selfShieldingOnly() ) );

  CHECK( 2 == chunk.NLS() );

  auto lvalue0 = chunk.lValues()[0];
  CHECK( 89.1354 == Approx( lvalue0.AWRI() ) );
  CHECK( 89.1354 == Approx( lvalue0.atomicWeightRatio() ) );
  CHECK( 0 == lvalue0.L() );
  CHECK( 0 == lvalue0.orbitalMomentum() );
  CHECK( 1 == lvalue0.NJS() );
  CHECK( 1 == lvalue0.numberSpinValues() );

  auto jvalue00 = lvalue0.jValues()[0];
  CHECK( 0.5 == Approx( jvalue00.AJ() ) );
  CHECK( 0.5 == Approx( jvalue00.spin() ) );

  CHECK( 2 == jvalue00.AMUN() );
  CHECK( 2 == jvalue00.neutronWidthDegreesFreedom() );
  CHECK( 3 == jvalue00.AMUG() );
  CHECK( 3 == jvalue00.gammaWidthDegreesFreedom() );
  CHECK( 4 == jvalue00.AMUF() );
  CHECK( 4 == jvalue00.fissionWidthDegreesFreedom() );
  CHECK( 1 == jvalue00.AMUX() );
  CHECK( 1 == jvalue00.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue00.INT() );

  CHECK( 1 == jvalue00.NR() );
  CHECK( 1 == jvalue00.interpolants().size() );
  CHECK( 1 == jvalue00.boundaries().size() );
  CHECK( 5 == jvalue00.interpolants()[0] );
  CHECK( 2 == jvalue00.boundaries()[0] );

  CHECK( 2 == jvalue00.NE() );
  CHECK( 2 == jvalue00.ES().size() );
  CHECK( 2 == jvalue00.energies().size() );
  CHECK( 2 == jvalue00.D().size() );
  CHECK( 2 == jvalue00.averageLevelSpacings().size() );
  CHECK( 2 == jvalue00.GN().size() );
  CHECK( 2 == jvalue00.averageNeutronWidths().size() );
  CHECK( 2 == jvalue00.GG().size() );
  CHECK( 2 == jvalue00.averageGammaWidths().size() );
  CHECK( 2 == jvalue00.GF().size() );
  CHECK( 2 == jvalue00.averageFissionWidths().size() );
  CHECK( 2 == jvalue00.GX().size() );
  CHECK( 2 == jvalue00.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue00.ES()[0] ) );
  CHECK( 8000. == Approx( jvalue00.ES()[1] ) );
  CHECK( 6000. == Approx( jvalue00.energies()[0] ) );
  CHECK( 8000. == Approx( jvalue00.energies()[1] ) );
  CHECK( 12406 == Approx( jvalue00.D()[0] ) );
  CHECK( 12406 == Approx( jvalue00.D()[1] ) );
  CHECK( 12406 == Approx( jvalue00.averageLevelSpacings()[0] ) );
  CHECK( 12406 == Approx( jvalue00.averageLevelSpacings()[1] ) );
  CHECK( 0.45901 == Approx( jvalue00.GN()[0] ) );
  CHECK( 0.45901 == Approx( jvalue00.GN()[1] ) );
  CHECK( 0.45901 == Approx( jvalue00.averageNeutronWidths()[0] ) );
  CHECK( 0.45901 == Approx( jvalue00.averageNeutronWidths()[1] ) );
  CHECK( 0.2050 == Approx( jvalue00.GG()[0] ) );
  CHECK( 0.2051 == Approx( jvalue00.GG()[1] ) );
  CHECK( 0.2050 == Approx( jvalue00.averageGammaWidths()[0] ) );
  CHECK( 0.2051 == Approx( jvalue00.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( jvalue00.GF()[0] ) );
  CHECK( 0. == Approx( jvalue00.GF()[1] ) );
  CHECK( 0. == Approx( jvalue00.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue00.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue00.GX()[0] ) );
  CHECK( .1 == Approx( jvalue00.GX()[1] ) );
  CHECK( 0. == Approx( jvalue00.averageCompetitiveWidths()[0] ) );
  CHECK( .1 == Approx( jvalue00.averageCompetitiveWidths()[1] ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK( 89.1354 == Approx( lvalue1.AWRI() ) );
  CHECK( 89.1354 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 1 == lvalue1.L() );
  CHECK( 1 == lvalue1.orbitalMomentum() );
  CHECK( 2 == lvalue1.NJS() );
  CHECK( 2 == lvalue1.numberSpinValues() );

  auto jvalue10 = lvalue1.jValues()[0];
  CHECK( 0.5 == Approx( jvalue10.AJ() ) );
  CHECK( 0.5 == Approx( jvalue10.spin() ) );

  CHECK( 3 == jvalue10.AMUN() );
  CHECK( 3 == jvalue10.neutronWidthDegreesFreedom() );
  CHECK( 2 == jvalue10.AMUG() );
  CHECK( 2 == jvalue10.gammaWidthDegreesFreedom() );
  CHECK( 1 == jvalue10.AMUF() );
  CHECK( 1 == jvalue10.fissionWidthDegreesFreedom() );
  CHECK( 4 == jvalue10.AMUX() );
  CHECK( 4 == jvalue10.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue10.INT() );

  CHECK( 1 == jvalue10.NR() );
  CHECK( 1 == jvalue10.interpolants().size() );
  CHECK( 1 == jvalue10.boundaries().size() );
  CHECK( 5 == jvalue10.interpolants()[0] );
  CHECK( 3 == jvalue10.boundaries()[0] );

  CHECK( 3 == jvalue10.NE() );
  CHECK( 3 == jvalue10.ES().size() );
  CHECK( 3 == jvalue10.energies().size() );
  CHECK( 3 == jvalue10.D().size() );
  CHECK( 3 == jvalue10.averageLevelSpacings().size() );
  CHECK( 3 == jvalue10.GN().size() );
  CHECK( 3 == jvalue10.averageNeutronWidths().size() );
  CHECK( 3 == jvalue10.GG().size() );
  CHECK( 3 == jvalue10.averageGammaWidths().size() );
  CHECK( 3 == jvalue10.GF().size() );
  CHECK( 3 == jvalue10.averageFissionWidths().size() );
  CHECK( 3 == jvalue10.GX().size() );
  CHECK( 3 == jvalue10.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue10.ES()[0] ) );
  CHECK( 7000. == Approx( jvalue10.ES()[1] ) );
  CHECK( 8000. == Approx( jvalue10.ES()[2] ) );
  CHECK( 6000. == Approx( jvalue10.energies()[0] ) );
  CHECK( 7000. == Approx( jvalue10.energies()[1] ) );
  CHECK( 8000. == Approx( jvalue10.energies()[2] ) );
  CHECK( 12406. == Approx( jvalue10.D()[0] ) );
  CHECK( 12406. == Approx( jvalue10.D()[1] ) );
  CHECK( 12406. == Approx( jvalue10.D()[2] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[0] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[1] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[2] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[0] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[1] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[2] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[0] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[1] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[2] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[0] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[1] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[2] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[0] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[1] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[2] ) );
  CHECK( 0. == Approx( jvalue10.GF()[0] ) );
  CHECK( 0. == Approx( jvalue10.GF()[1] ) );
  CHECK( 0. == Approx( jvalue10.GF()[2] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[2] ) );
  CHECK( 0. == Approx( jvalue10.GX()[0] ) );
  CHECK( 0. == Approx( jvalue10.GX()[1] ) );
  CHECK( 0. == Approx( jvalue10.GX()[2] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[1] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[2] ) );

  auto jvalue11 = lvalue1.jValues()[1];
  CHECK( 1.5 == Approx( jvalue11.AJ() ) );
  CHECK( 1.5 == Approx( jvalue11.spin() ) );

  CHECK( 1 == jvalue11.AMUN() );
  CHECK( 1 == jvalue11.neutronWidthDegreesFreedom() );
  CHECK( 4 == jvalue11.AMUG() );
  CHECK( 4 == jvalue11.gammaWidthDegreesFreedom() );
  CHECK( 2 == jvalue11.AMUF() );
  CHECK( 2 == jvalue11.fissionWidthDegreesFreedom() );
  CHECK( 0 == jvalue11.AMUX() );
  CHECK( 0 == jvalue11.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue11.INT() );

  CHECK( 1 == jvalue11.NR() );
  CHECK( 1 == jvalue11.interpolants().size() );
  CHECK( 1 == jvalue11.boundaries().size() );
  CHECK( 5 == jvalue11.interpolants()[0] );
  CHECK( 2 == jvalue11.boundaries()[0] );

  CHECK( 2 == jvalue11.NE() );
  CHECK( 2 == jvalue11.ES().size() );
  CHECK( 2 == jvalue11.energies().size() );
  CHECK( 2 == jvalue11.D().size() );
  CHECK( 2 == jvalue11.averageLevelSpacings().size() );
  CHECK( 2 == jvalue11.GN().size() );
  CHECK( 2 == jvalue11.averageNeutronWidths().size() );
  CHECK( 2 == jvalue11.GG().size() );
  CHECK( 2 == jvalue11.averageGammaWidths().size() );
  CHECK( 2 == jvalue11.GF().size() );
  CHECK( 2 == jvalue11.averageFissionWidths().size() );
  CHECK( 2 == jvalue11.GX().size() );
  CHECK( 2 == jvalue11.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue11.ES()[0] ) );
  CHECK( 8000. == Approx( jvalue11.ES()[1] ) );
  CHECK( 6000. == Approx( jvalue11.energies()[0] ) );
  CHECK( 8000. == Approx( jvalue11.energies()[1] ) );
  CHECK( 6202.8 == Approx( jvalue11.D()[0] ) );
  CHECK( 6202.8 == Approx( jvalue11.D()[1] ) );
  CHECK( 6202.8 == Approx( jvalue11.averageLevelSpacings()[0] ) );
  CHECK( 6202.8 == Approx( jvalue11.averageLevelSpacings()[1] ) );
  CHECK( 3.3619 == Approx( jvalue11.GN()[0] ) );
  CHECK( 3.3619 == Approx( jvalue11.GN()[1] ) );
  CHECK( 3.3619 == Approx( jvalue11.averageNeutronWidths()[0] ) );
  CHECK( 3.3619 == Approx( jvalue11.averageNeutronWidths()[1] ) );
  CHECK( 0.205 == Approx( jvalue11.GG()[0] ) );
  CHECK( 0.205 == Approx( jvalue11.GG()[1] ) );
  CHECK( 0.205 == Approx( jvalue11.averageGammaWidths()[0] ) );
  CHECK( 0.205 == Approx( jvalue11.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( jvalue11.GF()[0] ) );
  CHECK( 0. == Approx( jvalue11.GF()[1] ) );
  CHECK( 0. == Approx( jvalue11.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue11.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue11.GX()[0] ) );
  CHECK( 0. == Approx( jvalue11.GX()[1] ) );
  CHECK( 0. == Approx( jvalue11.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( jvalue11.averageCompetitiveWidths()[1] ) );

  CHECK( 16 == chunk.NC() );
}

std::string chunkWithNoLValues() {
  return
    " 0.000000+0 6.795900-1          0          0          0          03843 2151     \n";
}
