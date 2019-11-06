#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using EnergyIndependent = resonanceParameters::unresolved::EnergyIndependent;
using LValue = resonanceParameters::unresolved::EnergyIndependent::LValue;

std::string chunk();
void verifyChunk( const EnergyIndependent& );

SCENARIO( "EnergyIndependent" ) {

  GIVEN( "valid data for an EnergyIndependent" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spin = 0.0;
      double ap = 0.6233;
      bool lssf = false;

      std::vector< LValue > lvalues =
        { { 138.709, 0,
            { 0.5 }, { 4400. }, { 1 }, { 0.44 }, { 0.05 } },
          { 138.709, 1,
            { 0.5, 1.5 }, { 4400., 2200. }, { 1, 1 }, { 0.528, 0.264 },
            { 0.09, 0.091 } },
          { 138.709, 2,
            { 1.5, 2.5 }, { 2200., 1466.67 }, { 1, 1 }, { 0.033, 0.022 },
            { 0.05, 0.051 } } };

      EnergyIndependent chunk( spin, ap, lssf, std::move( lvalues ) );

      THEN( "a EnergyIndependent can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 5655, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyIndependent chunk( begin, end, lineNumber, 5655, 2, 151 );

      THEN( "a EnergyIndependent can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 5655, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 6.233000-1          0          0          3          05655 2151     \n"
    " 1.387090+2 0.000000+0          0          0          6          15655 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 4.400000-1 5.000000-2 0.000000+05655 2151     \n"
    " 1.387090+2 0.000000+0          1          0         12          25655 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 1.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n"
    " 1.387090+2 0.000000+0          2          0         12          25655 2151     \n"
    " 2.200000+3 1.500000+0 1.000000+0 3.300000-2 5.000000-2 0.000000+05655 2151     \n"
    " 1.466670+3 2.500000+0 1.000000+0 2.200000-2 5.100000-2 0.000000+05655 2151     \n";
}

void verifyChunk( const EnergyIndependent& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK( 0.0 == Approx( chunk.SPI() ) );
  CHECK( 0.0 == Approx( chunk.spin() ) );
  CHECK( 0.6233 == Approx( chunk.AP() ) );
  CHECK( 0.6233 == Approx( chunk.scatteringRadius() ) );
  CHECK( false == Approx( chunk.LSSF() ) );
  CHECK( false == Approx( chunk.selfShieldingOnly() ) );

  CHECK( 3 == chunk.NLS() );

  auto lvalue0 = chunk.lValues()[0];
  CHECK( 138.709 == Approx( lvalue0.AWRI() ) );
  CHECK( 138.709 == Approx( lvalue0.atomicWeightRatio() ) );
  CHECK( 0 == lvalue0.L() );
  CHECK( 0 == lvalue0.orbitalMomentum() );

  CHECK( 1 == lvalue0.NJS() );
  CHECK( 1 == lvalue0.numberSpinValues() );
  CHECK( 1 == lvalue0.AJ().size() );
  CHECK( 1 == lvalue0.spinValues().size() );
  CHECK( 1 == lvalue0.D().size() );
  CHECK( 1 == lvalue0.averageLevelSpacings().size() );
  CHECK( 1 == lvalue0.AMUN().size() );
  CHECK( 1 == lvalue0.neutronWidthDegreesFreedom().size() );
  CHECK( 1 == lvalue0.AMUG().size() );
  CHECK( 1 == lvalue0.gammaWidthDegreesFreedom().size() );
  CHECK( 1 == lvalue0.AMUF().size() );
  CHECK( 1 == lvalue0.fissionWidthDegreesFreedom().size() );
  CHECK( 1 == lvalue0.AMUX().size() );
  CHECK( 1 == lvalue0.competitiveWidthDegreesFreedom().size() );
  CHECK( 1 == lvalue0.GN().size() );
  CHECK( 1 == lvalue0.averageNeutronWidths().size() );
  CHECK( 1 == lvalue0.GG().size() );
  CHECK( 1 == lvalue0.averageGammaWidths().size() );
  CHECK( 1 == lvalue0.GF().size() );
  CHECK( 1 == lvalue0.averageFissionWidths().size() );
  CHECK( 1 == lvalue0.GX().size() );
  CHECK( 1 == lvalue0.averageCompetitiveWidths().size() );
  CHECK( 1 == lvalue0.jValues().size() );

  CHECK( 0.5 == Approx( lvalue0.AJ()[0] ) );
  CHECK( 0.5 == Approx( lvalue0.spinValues()[0] ) );
  CHECK( 4400. == Approx( lvalue0.D()[0] ) );
  CHECK( 4400. == Approx( lvalue0.averageLevelSpacings()[0] ) );
  CHECK( 1 == lvalue0.AMUN()[0] );
  CHECK( 1 == lvalue0.neutronWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUG()[0] );
  CHECK( 0 == lvalue0.gammaWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUF()[0] );
  CHECK( 0 == lvalue0.fissionWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUX()[0] );
  CHECK( 0 == lvalue0.competitiveWidthDegreesFreedom()[0] );
  CHECK( 0.44 == Approx( lvalue0.GN()[0] ) );
  CHECK( 0.44 == Approx( lvalue0.averageNeutronWidths()[0] ) );
  CHECK( 0.05 == Approx( lvalue0.GG()[0] ) );
  CHECK( 0.05 == Approx( lvalue0.averageGammaWidths()[0] ) );
  CHECK( 0. == Approx( lvalue0.GF()[0] ) );
  CHECK( 0. == Approx( lvalue0.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( lvalue0.GX()[0] ) );
  CHECK( 0. == Approx( lvalue0.averageCompetitiveWidths()[0] ) );

  CHECK( 0.5 == Approx( lvalue0.jValues()[0].AJ() ) );
  CHECK( 0.5 == Approx( lvalue0.jValues()[0].spin() ) );
  CHECK( 4400. == Approx( lvalue0.jValues()[0].D() ) );
  CHECK( 4400. == Approx( lvalue0.jValues()[0].averageLevelSpacing() ) );
  CHECK( 1 == lvalue0.jValues()[0].AMUN() );
  CHECK( 1 == lvalue0.jValues()[0].neutronWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUG() );
  CHECK( 0 == lvalue0.jValues()[0].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUF() );
  CHECK( 0 == lvalue0.jValues()[0].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUX() );
  CHECK( 0 == lvalue0.jValues()[0].competitiveWidthDegreesFreedom() );
  CHECK( 0.44 == Approx( lvalue0.jValues()[0].GN() ) );
  CHECK( 0.44 == Approx( lvalue0.jValues()[0].averageNeutronWidth() ) );
  CHECK( 0.05 == Approx( lvalue0.jValues()[0].GG() ) );
  CHECK( 0.05 == Approx( lvalue0.jValues()[0].averageGammaWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].GF() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].GX() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].averageCompetitiveWidth() ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK( 138.709 == Approx( lvalue1.AWRI() ) );
  CHECK( 138.709 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 1 == lvalue1.L() );
  CHECK( 1 == lvalue1.orbitalMomentum() );

  CHECK( 2 == lvalue1.NJS() );
  CHECK( 2 == lvalue1.numberSpinValues() );
  CHECK( 2 == lvalue1.AJ().size() );
  CHECK( 2 == lvalue1.spinValues().size() );
  CHECK( 2 == lvalue1.D().size() );
  CHECK( 2 == lvalue1.averageLevelSpacings().size() );
  CHECK( 2 == lvalue1.AMUN().size() );
  CHECK( 2 == lvalue1.neutronWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue1.AMUG().size() );
  CHECK( 2 == lvalue1.gammaWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue1.AMUF().size() );
  CHECK( 2 == lvalue1.fissionWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue1.AMUX().size() );
  CHECK( 2 == lvalue1.competitiveWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue1.GN().size() );
  CHECK( 2 == lvalue1.averageNeutronWidths().size() );
  CHECK( 2 == lvalue1.GG().size() );
  CHECK( 2 == lvalue1.averageGammaWidths().size() );
  CHECK( 2 == lvalue1.GF().size() );
  CHECK( 2 == lvalue1.averageFissionWidths().size() );
  CHECK( 2 == lvalue1.GX().size() );
  CHECK( 2 == lvalue1.averageCompetitiveWidths().size() );
  CHECK( 2 == lvalue1.jValues().size() );

  CHECK( 0.5 == Approx( lvalue1.AJ()[0] ) );
  CHECK( 1.5 == Approx( lvalue1.AJ()[1] ) );
  CHECK( 0.5 == Approx( lvalue1.spinValues()[0] ) );
  CHECK( 1.5 == Approx( lvalue1.spinValues()[1] ) );
  CHECK( 4400. == Approx( lvalue1.D()[0] ) );
  CHECK( 2200. == Approx( lvalue1.D()[1] ) );
  CHECK( 4400. == Approx( lvalue1.averageLevelSpacings()[0] ) );
  CHECK( 2200. == Approx( lvalue1.averageLevelSpacings()[1] ) );
  CHECK( 1 == lvalue1.AMUN()[0] );
  CHECK( 1 == lvalue1.AMUN()[1] );
  CHECK( 1 == lvalue1.neutronWidthDegreesFreedom()[0] );
  CHECK( 1 == lvalue1.neutronWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue1.AMUG()[0] );
  CHECK( 0 == lvalue1.AMUG()[1] );
  CHECK( 0 == lvalue1.gammaWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue1.gammaWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue1.AMUF()[0] );
  CHECK( 0 == lvalue1.AMUF()[1] );
  CHECK( 0 == lvalue1.fissionWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue1.fissionWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue1.AMUX()[0] );
  CHECK( 0 == lvalue1.AMUX()[1] );
  CHECK( 0 == lvalue1.competitiveWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue1.competitiveWidthDegreesFreedom()[1] );
  CHECK( 0.528 == Approx( lvalue1.GN()[0] ) );
  CHECK( 0.264 == Approx( lvalue1.GN()[1] ) );
  CHECK( 0.528 == Approx( lvalue1.averageNeutronWidths()[0] ) );
  CHECK( 0.264 == Approx( lvalue1.averageNeutronWidths()[1] ) );
  CHECK( 0.090 == Approx( lvalue1.GG()[0] ) );
  CHECK( 0.091 == Approx( lvalue1.GG()[1] ) );
  CHECK( 0.090 == Approx( lvalue1.averageGammaWidths()[0] ) );
  CHECK( 0.091 == Approx( lvalue1.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( lvalue1.GF()[0] ) );
  CHECK( 0. == Approx( lvalue1.GF()[1] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( lvalue1.GX()[0] ) );
  CHECK( 0. == Approx( lvalue1.GX()[1] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[1] ) );

  CHECK( 0.5 == Approx( lvalue1.jValues()[0].AJ() ) );
  CHECK( 1.5 == Approx( lvalue1.jValues()[1].AJ() ) );
  CHECK( 0.5 == Approx( lvalue1.jValues()[0].spin() ) );
  CHECK( 1.5 == Approx( lvalue1.jValues()[1].spin() ) );
  CHECK( 4400. == Approx( lvalue1.jValues()[0].D() ) );
  CHECK( 2200. == Approx( lvalue1.jValues()[1].D() ) );
  CHECK( 4400. == Approx( lvalue1.jValues()[0].averageLevelSpacing() ) );
  CHECK( 2200. == Approx( lvalue1.jValues()[1].averageLevelSpacing() ) );
  CHECK( 1 == lvalue1.jValues()[0].AMUN() );
  CHECK( 1 == lvalue1.jValues()[1].AMUN() );
  CHECK( 1 == lvalue1.jValues()[0].neutronWidthDegreesFreedom() );
  CHECK( 1 == lvalue1.jValues()[1].neutronWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[0].AMUG() );
  CHECK( 0 == lvalue1.jValues()[1].AMUG() );
  CHECK( 0 == lvalue1.jValues()[0].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[1].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[0].AMUF() );
  CHECK( 0 == lvalue1.jValues()[1].AMUF() );
  CHECK( 0 == lvalue1.jValues()[0].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[1].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[0].AMUX() );
  CHECK( 0 == lvalue1.jValues()[1].AMUX() );
  CHECK( 0 == lvalue1.jValues()[0].competitiveWidthDegreesFreedom() );
  CHECK( 0 == lvalue1.jValues()[1].competitiveWidthDegreesFreedom() );
  CHECK( 0.528 == Approx( lvalue1.jValues()[0].GN() ) );
  CHECK( 0.264 == Approx( lvalue1.jValues()[1].GN() ) );
  CHECK( 0.528 == Approx( lvalue1.jValues()[0].averageNeutronWidth() ) );
  CHECK( 0.264 == Approx( lvalue1.jValues()[1].averageNeutronWidth() ) );
  CHECK( 0.090 == Approx( lvalue1.jValues()[0].GG() ) );
  CHECK( 0.091 == Approx( lvalue1.jValues()[1].GG() ) );
  CHECK( 0.090 == Approx( lvalue1.jValues()[0].averageGammaWidth() ) );
  CHECK( 0.091 == Approx( lvalue1.jValues()[1].averageGammaWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].averageCompetitiveWidth() ) );

  auto lvalue2 = chunk.lValues()[2];
  CHECK( 138.709 == Approx( lvalue2.AWRI() ) );
  CHECK( 138.709 == Approx( lvalue2.atomicWeightRatio() ) );
  CHECK( 2 == lvalue2.L() );
  CHECK( 2 == lvalue2.orbitalMomentum() );

  CHECK( 2 == lvalue2.NJS() );
  CHECK( 2 == lvalue2.numberSpinValues() );
  CHECK( 2 == lvalue2.AJ().size() );
  CHECK( 2 == lvalue2.spinValues().size() );
  CHECK( 2 == lvalue2.D().size() );
  CHECK( 2 == lvalue2.averageLevelSpacings().size() );
  CHECK( 2 == lvalue2.AMUN().size() );
  CHECK( 2 == lvalue2.neutronWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue2.AMUG().size() );
  CHECK( 2 == lvalue2.gammaWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue2.AMUF().size() );
  CHECK( 2 == lvalue2.fissionWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue2.AMUX().size() );
  CHECK( 2 == lvalue2.competitiveWidthDegreesFreedom().size() );
  CHECK( 2 == lvalue2.GN().size() );
  CHECK( 2 == lvalue2.averageNeutronWidths().size() );
  CHECK( 2 == lvalue2.GG().size() );
  CHECK( 2 == lvalue2.averageGammaWidths().size() );
  CHECK( 2 == lvalue2.GF().size() );
  CHECK( 2 == lvalue2.averageFissionWidths().size() );
  CHECK( 2 == lvalue2.GX().size() );
  CHECK( 2 == lvalue2.averageCompetitiveWidths().size() );
  CHECK( 2 == lvalue2.jValues().size() );

  CHECK( 1.5 == Approx( lvalue2.AJ()[0] ) );
  CHECK( 2.5 == Approx( lvalue2.AJ()[1] ) );
  CHECK( 1.5 == Approx( lvalue2.spinValues()[0] ) );
  CHECK( 2.5 == Approx( lvalue2.spinValues()[1] ) );
  CHECK( 2200. == Approx( lvalue2.D()[0] ) );
  CHECK( 1466.67 == Approx( lvalue2.D()[1] ) );
  CHECK( 2200. == Approx( lvalue2.averageLevelSpacings()[0] ) );
  CHECK( 1466.67 == Approx( lvalue2.averageLevelSpacings()[1] ) );
  CHECK( 1 == lvalue2.AMUN()[0] );
  CHECK( 1 == lvalue2.AMUN()[1] );
  CHECK( 1 == lvalue2.neutronWidthDegreesFreedom()[0] );
  CHECK( 1 == lvalue2.neutronWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue2.AMUG()[0] );
  CHECK( 0 == lvalue2.AMUG()[1] );
  CHECK( 0 == lvalue2.gammaWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue2.gammaWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue2.AMUF()[0] );
  CHECK( 0 == lvalue2.AMUF()[1] );
  CHECK( 0 == lvalue2.fissionWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue2.fissionWidthDegreesFreedom()[1] );
  CHECK( 0 == lvalue2.AMUX()[0] );
  CHECK( 0 == lvalue2.AMUX()[1] );
  CHECK( 0 == lvalue2.competitiveWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue2.competitiveWidthDegreesFreedom()[1] );
  CHECK( 0.033 == Approx( lvalue2.GN()[0] ) );
  CHECK( 0.022 == Approx( lvalue2.GN()[1] ) );
  CHECK( 0.033 == Approx( lvalue2.averageNeutronWidths()[0] ) );
  CHECK( 0.022 == Approx( lvalue2.averageNeutronWidths()[1] ) );
  CHECK( 0.050 == Approx( lvalue2.GG()[0] ) );
  CHECK( 0.051 == Approx( lvalue2.GG()[1] ) );
  CHECK( 0.050 == Approx( lvalue2.averageGammaWidths()[0] ) );
  CHECK( 0.051 == Approx( lvalue2.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( lvalue2.GF()[0] ) );
  CHECK( 0. == Approx( lvalue2.GF()[1] ) );
  CHECK( 0. == Approx( lvalue2.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( lvalue2.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( lvalue2.GX()[0] ) );
  CHECK( 0. == Approx( lvalue2.GX()[1] ) );
  CHECK( 0. == Approx( lvalue2.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( lvalue2.averageCompetitiveWidths()[1] ) );

  CHECK( 1.5 == Approx( lvalue2.jValues()[0].AJ() ) );
  CHECK( 2.5 == Approx( lvalue2.jValues()[1].AJ() ) );
  CHECK( 1.5 == Approx( lvalue2.jValues()[0].spin() ) );
  CHECK( 2.5 == Approx( lvalue2.jValues()[1].spin() ) );
  CHECK( 2200. == Approx( lvalue2.jValues()[0].D() ) );
  CHECK( 1466.67 == Approx( lvalue2.jValues()[1].D() ) );
  CHECK( 2200. == Approx( lvalue2.jValues()[0].averageLevelSpacing() ) );
  CHECK( 1466.67 == Approx( lvalue2.jValues()[1].averageLevelSpacing() ) );
  CHECK( 1 == lvalue2.jValues()[0].AMUN() );
  CHECK( 1 == lvalue2.jValues()[1].AMUN() );
  CHECK( 1 == lvalue2.jValues()[0].neutronWidthDegreesFreedom() );
  CHECK( 1 == lvalue2.jValues()[1].neutronWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[0].AMUG() );
  CHECK( 0 == lvalue2.jValues()[1].AMUG() );
  CHECK( 0 == lvalue2.jValues()[0].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[1].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[0].AMUF() );
  CHECK( 0 == lvalue2.jValues()[1].AMUF() );
  CHECK( 0 == lvalue2.jValues()[0].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[1].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[0].AMUX() );
  CHECK( 0 == lvalue2.jValues()[1].AMUX() );
  CHECK( 0 == lvalue2.jValues()[0].competitiveWidthDegreesFreedom() );
  CHECK( 0 == lvalue2.jValues()[1].competitiveWidthDegreesFreedom() );
  CHECK( 0.033 == Approx( lvalue2.jValues()[0].GN() ) );
  CHECK( 0.022 == Approx( lvalue2.jValues()[1].GN() ) );
  CHECK( 0.033 == Approx( lvalue2.jValues()[0].averageNeutronWidth() ) );
  CHECK( 0.022 == Approx( lvalue2.jValues()[1].averageNeutronWidth() ) );
  CHECK( 0.050 == Approx( lvalue2.jValues()[0].GG() ) );
  CHECK( 0.051 == Approx( lvalue2.jValues()[1].GG() ) );
  CHECK( 0.050 == Approx( lvalue2.jValues()[0].averageGammaWidth() ) );
  CHECK( 0.051 == Approx( lvalue2.jValues()[1].averageGammaWidth() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[0].GF() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[1].GF() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[1].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[0].GX() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[1].GX() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue2.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 9 == chunk.NC() );
}
