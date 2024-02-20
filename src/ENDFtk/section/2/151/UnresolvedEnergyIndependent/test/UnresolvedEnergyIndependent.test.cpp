// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using UnresolvedEnergyIndependent = section::Type< 2, 151 >::UnresolvedEnergyIndependent;
using LValue = section::Type< 2, 151 >::UnresolvedEnergyIndependent::LValue;

std::string chunk();
void verifyChunk( const UnresolvedEnergyIndependent& );
std::string chunkWithNoLValues();

SCENARIO( "UnresolvedEnergyIndependent" ) {

  GIVEN( "valid data for an UnresolvedEnergyIndependent" ) {

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

      UnresolvedEnergyIndependent chunk( spin, ap, lssf, std::move( lvalues ) );

      THEN( "a UnresolvedEnergyIndependent can be constructed and members can be "
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

      UnresolvedEnergyIndependent chunk( begin, end, lineNumber, 5655, 2, 151 );

      THEN( "a UnresolvedEnergyIndependent can be constructed and members can be tested" ) {

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

  GIVEN( "invalid data" ) {

    WHEN( "no l values are given" ) {

      double spin = 0.0;
      double ap = 0.6233;
      bool lssf = false;

      std::vector< LValue > lvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyIndependent( spin, ap, lssf,
                                         std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no l values is used" ) {

      std::string string = chunkWithNoLValues();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyIndependent( begin, end, lineNumber, 1025, 2, 151 ) );
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

void verifyChunk( const UnresolvedEnergyIndependent& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK_THAT( 0.0, WithinRel( chunk.SPI() ) );
  CHECK_THAT( 0.0, WithinRel( chunk.spin() ) );
  CHECK_THAT( 0.6233, WithinRel( chunk.AP() ) );
  CHECK_THAT( 0.6233, WithinRel( chunk.scatteringRadius() ) );
  CHECK( false == chunk.LSSF() );
  CHECK( false == chunk.selfShieldingOnly() );

  CHECK( 3 == chunk.NLS() );

  auto lvalue0 = chunk.lValues()[0];
  CHECK_THAT( 138.709, WithinRel( lvalue0.AWRI() ) );
  CHECK_THAT( 138.709, WithinRel( lvalue0.atomicWeightRatio() ) );
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

  CHECK_THAT( 0.5, WithinRel( lvalue0.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue0.spinValues()[0] ) );
  CHECK_THAT( 4400., WithinRel( lvalue0.D()[0] ) );
  CHECK_THAT( 4400., WithinRel( lvalue0.averageLevelSpacings()[0] ) );
  CHECK( 1 == lvalue0.AMUN()[0] );
  CHECK( 1 == lvalue0.neutronWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUG()[0] );
  CHECK( 0 == lvalue0.gammaWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUF()[0] );
  CHECK( 0 == lvalue0.fissionWidthDegreesFreedom()[0] );
  CHECK( 0 == lvalue0.AMUX()[0] );
  CHECK( 0 == lvalue0.competitiveWidthDegreesFreedom()[0] );
  CHECK_THAT( 0.44, WithinRel( lvalue0.GN()[0] ) );
  CHECK_THAT( 0.44, WithinRel( lvalue0.averageNeutronWidths()[0] ) );
  CHECK_THAT( 0.05, WithinRel( lvalue0.GG()[0] ) );
  CHECK_THAT( 0.05, WithinRel( lvalue0.averageGammaWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue0.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue0.averageFissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue0.GX()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue0.averageCompetitiveWidths()[0] ) );

  CHECK_THAT( 0.5, WithinRel( lvalue0.jValues()[0].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( lvalue0.jValues()[0].spin() ) );
  CHECK_THAT( 4400., WithinRel( lvalue0.jValues()[0].D() ) );
  CHECK_THAT( 4400., WithinRel( lvalue0.jValues()[0].averageLevelSpacing() ) );
  CHECK( 1 == lvalue0.jValues()[0].AMUN() );
  CHECK( 1 == lvalue0.jValues()[0].neutronWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUG() );
  CHECK( 0 == lvalue0.jValues()[0].gammaWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUF() );
  CHECK( 0 == lvalue0.jValues()[0].fissionWidthDegreesFreedom() );
  CHECK( 0 == lvalue0.jValues()[0].AMUX() );
  CHECK( 0 == lvalue0.jValues()[0].competitiveWidthDegreesFreedom() );
  CHECK_THAT( 0.44, WithinRel( lvalue0.jValues()[0].GN() ) );
  CHECK_THAT( 0.44, WithinRel( lvalue0.jValues()[0].averageNeutronWidth() ) );
  CHECK_THAT( 0.05, WithinRel( lvalue0.jValues()[0].GG() ) );
  CHECK_THAT( 0.05, WithinRel( lvalue0.jValues()[0].averageGammaWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue0.jValues()[0].GF() ) );
  CHECK_THAT( 0., WithinRel( lvalue0.jValues()[0].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue0.jValues()[0].GX() ) );
  CHECK_THAT( 0., WithinRel( lvalue0.jValues()[0].averageCompetitiveWidth() ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK_THAT( 138.709, WithinRel( lvalue1.AWRI() ) );
  CHECK_THAT( 138.709, WithinRel( lvalue1.atomicWeightRatio() ) );
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

  CHECK_THAT( 0.5, WithinRel( lvalue1.AJ()[0] ) );
  CHECK_THAT( 1.5, WithinRel( lvalue1.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.spinValues()[0] ) );
  CHECK_THAT( 1.5, WithinRel( lvalue1.spinValues()[1] ) );
  CHECK_THAT( 4400., WithinRel( lvalue1.D()[0] ) );
  CHECK_THAT( 2200., WithinRel( lvalue1.D()[1] ) );
  CHECK_THAT( 4400., WithinRel( lvalue1.averageLevelSpacings()[0] ) );
  CHECK_THAT( 2200., WithinRel( lvalue1.averageLevelSpacings()[1] ) );
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
  CHECK_THAT( 0.528, WithinRel( lvalue1.GN()[0] ) );
  CHECK_THAT( 0.264, WithinRel( lvalue1.GN()[1] ) );
  CHECK_THAT( 0.528, WithinRel( lvalue1.averageNeutronWidths()[0] ) );
  CHECK_THAT( 0.264, WithinRel( lvalue1.averageNeutronWidths()[1] ) );
  CHECK_THAT( 0.090, WithinRel( lvalue1.GG()[0] ) );
  CHECK_THAT( 0.091, WithinRel( lvalue1.GG()[1] ) );
  CHECK_THAT( 0.090, WithinRel( lvalue1.averageGammaWidths()[0] ) );
  CHECK_THAT( 0.091, WithinRel( lvalue1.averageGammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.averageFissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.averageFissionWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GX()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GX()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.averageCompetitiveWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.averageCompetitiveWidths()[1] ) );

  CHECK_THAT( 0.5, WithinRel( lvalue1.jValues()[0].AJ() ) );
  CHECK_THAT( 1.5, WithinRel( lvalue1.jValues()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.jValues()[0].spin() ) );
  CHECK_THAT( 1.5, WithinRel( lvalue1.jValues()[1].spin() ) );
  CHECK_THAT( 4400., WithinRel( lvalue1.jValues()[0].D() ) );
  CHECK_THAT( 2200., WithinRel( lvalue1.jValues()[1].D() ) );
  CHECK_THAT( 4400., WithinRel( lvalue1.jValues()[0].averageLevelSpacing() ) );
  CHECK_THAT( 2200., WithinRel( lvalue1.jValues()[1].averageLevelSpacing() ) );
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
  CHECK_THAT( 0.528, WithinRel( lvalue1.jValues()[0].GN() ) );
  CHECK_THAT( 0.264, WithinRel( lvalue1.jValues()[1].GN() ) );
  CHECK_THAT( 0.528, WithinRel( lvalue1.jValues()[0].averageNeutronWidth() ) );
  CHECK_THAT( 0.264, WithinRel( lvalue1.jValues()[1].averageNeutronWidth() ) );
  CHECK_THAT( 0.090, WithinRel( lvalue1.jValues()[0].GG() ) );
  CHECK_THAT( 0.091, WithinRel( lvalue1.jValues()[1].GG() ) );
  CHECK_THAT( 0.090, WithinRel( lvalue1.jValues()[0].averageGammaWidth() ) );
  CHECK_THAT( 0.091, WithinRel( lvalue1.jValues()[1].averageGammaWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[0].GF() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[1].GF() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[0].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[1].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[0].GX() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[1].GX() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[0].averageCompetitiveWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.jValues()[1].averageCompetitiveWidth() ) );

  auto lvalue2 = chunk.lValues()[2];
  CHECK_THAT( 138.709, WithinRel( lvalue2.AWRI() ) );
  CHECK_THAT( 138.709, WithinRel( lvalue2.atomicWeightRatio() ) );
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

  CHECK_THAT( 1.5, WithinRel( lvalue2.AJ()[0] ) );
  CHECK_THAT( 2.5, WithinRel( lvalue2.AJ()[1] ) );
  CHECK_THAT( 1.5, WithinRel( lvalue2.spinValues()[0] ) );
  CHECK_THAT( 2.5, WithinRel( lvalue2.spinValues()[1] ) );
  CHECK_THAT( 2200., WithinRel( lvalue2.D()[0] ) );
  CHECK_THAT( 1466.67, WithinRel( lvalue2.D()[1] ) );
  CHECK_THAT( 2200., WithinRel( lvalue2.averageLevelSpacings()[0] ) );
  CHECK_THAT( 1466.67, WithinRel( lvalue2.averageLevelSpacings()[1] ) );
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
  CHECK_THAT( 0.033, WithinRel( lvalue2.GN()[0] ) );
  CHECK_THAT( 0.022, WithinRel( lvalue2.GN()[1] ) );
  CHECK_THAT( 0.033, WithinRel( lvalue2.averageNeutronWidths()[0] ) );
  CHECK_THAT( 0.022, WithinRel( lvalue2.averageNeutronWidths()[1] ) );
  CHECK_THAT( 0.050, WithinRel( lvalue2.GG()[0] ) );
  CHECK_THAT( 0.051, WithinRel( lvalue2.GG()[1] ) );
  CHECK_THAT( 0.050, WithinRel( lvalue2.averageGammaWidths()[0] ) );
  CHECK_THAT( 0.051, WithinRel( lvalue2.averageGammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.averageFissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.averageFissionWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GX()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GX()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.averageCompetitiveWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.averageCompetitiveWidths()[1] ) );

  CHECK_THAT( 1.5, WithinRel( lvalue2.jValues()[0].AJ() ) );
  CHECK_THAT( 2.5, WithinRel( lvalue2.jValues()[1].AJ() ) );
  CHECK_THAT( 1.5, WithinRel( lvalue2.jValues()[0].spin() ) );
  CHECK_THAT( 2.5, WithinRel( lvalue2.jValues()[1].spin() ) );
  CHECK_THAT( 2200., WithinRel( lvalue2.jValues()[0].D() ) );
  CHECK_THAT( 1466.67, WithinRel( lvalue2.jValues()[1].D() ) );
  CHECK_THAT( 2200., WithinRel( lvalue2.jValues()[0].averageLevelSpacing() ) );
  CHECK_THAT( 1466.67, WithinRel( lvalue2.jValues()[1].averageLevelSpacing() ) );
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
  CHECK_THAT( 0.033, WithinRel( lvalue2.jValues()[0].GN() ) );
  CHECK_THAT( 0.022, WithinRel( lvalue2.jValues()[1].GN() ) );
  CHECK_THAT( 0.033, WithinRel( lvalue2.jValues()[0].averageNeutronWidth() ) );
  CHECK_THAT( 0.022, WithinRel( lvalue2.jValues()[1].averageNeutronWidth() ) );
  CHECK_THAT( 0.050, WithinRel( lvalue2.jValues()[0].GG() ) );
  CHECK_THAT( 0.051, WithinRel( lvalue2.jValues()[1].GG() ) );
  CHECK_THAT( 0.050, WithinRel( lvalue2.jValues()[0].averageGammaWidth() ) );
  CHECK_THAT( 0.051, WithinRel( lvalue2.jValues()[1].averageGammaWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[0].GF() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[1].GF() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[0].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[1].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[0].GX() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[1].GX() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[0].averageCompetitiveWidth() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 9 == chunk.NC() );
}

std::string chunkWithNoLValues() {
  return
    " 0.000000+0 6.233000-1          0          0          0          05655 2151     \n";
}
