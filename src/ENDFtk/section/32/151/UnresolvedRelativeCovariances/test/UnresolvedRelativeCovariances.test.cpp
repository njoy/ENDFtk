#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LValue =
section::Type< 32, 151 >::UnresolvedRelativeCovariances::LValue;
using CovarianceMatrix =
section::Type< 32, 151 >::UnresolvedRelativeCovariances::CovarianceMatrix;
using UnresolvedRelativeCovariances =
section::Type< 32, 151 >::UnresolvedRelativeCovariances;

std::string chunk();
void verifyChunk( const UnresolvedRelativeCovariances& );

SCENARIO( "UnresolvedRelativeCovariances" ) {

  GIVEN( "valid data for a UnresolvedRelativeCovariances" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spin = 1.5;
      double ap = 0.51;

      std::vector< LValue > lvalues =
        { { 20.8135, 0,
            { 1., 2. }, { 4.737450e+4, 4.004950e+4 },
            { 1.43931, 1.21677 }, { 9.325340e-1, 3.312740e-1 },
            { 0., 0. }, { 0., 0. } },
          { 20.8135, 1,
            { 0., 1., 2., 3. },
            { 1.197338e+5, 4.737450e+4, 4.004950e+4, 4.784325e+4 },
            { 1.115620e+1, 3.543470e+0, 2.995580e+0, 4.457810e+0 },
            { 8.083210e-2, 1.048490e+0, 3.577760e-1, 4.728190e-1 },
            { 0., 0., 0., 0. }, { 0., 0., 0., 0. } } };

      CovarianceMatrix matrix(
            2,
            {  1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               1.000000e-2, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-4,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0,
               0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0,
               1.000000e-2, 0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 1.000000e-2 } );

      UnresolvedRelativeCovariances chunk( spin, ap,
                                           std::move( lvalues ),
                                           std::move( matrix ) );

      THEN( "a UnresolvedRelativeCovariances can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1028, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      UnresolvedRelativeCovariances chunk( begin, end, lineNumber, 1028, 32, 151 );

      THEN( "a UnresolvedRelativeCovariances can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1028, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.500000+0 5.100000-1          0          0          2          0102832151     \n"
    " 2.081350+1 0.000000+0          0          0         12          2102832151     \n"
    " 4.737450+4 1.000000+0 1.439310+0 9.325340-1 0.000000+0 0.000000+0102832151     \n"
    " 4.004950+4 2.000000+0 1.216770+0 3.312740-1 0.000000+0 0.000000+0102832151     \n"
    " 2.081350+1 0.000000+0          1          0         24          4102832151     \n"
    " 1.197338+5 0.000000+0 1.115620+1 8.083210-2 0.000000+0 0.000000+0102832151     \n"
    " 4.737450+4 1.000000+0 3.543470+0 1.048490+0 0.000000+0 0.000000+0102832151     \n"
    " 4.004950+4 2.000000+0 2.995580+0 3.577760-1 0.000000+0 0.000000+0102832151     \n"
    " 4.784325+4 3.000000+0 4.457810+0 4.728190-1 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0          2          0         78         12102832151     \n"
    " 1.000000-4 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 1.000000-2 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 1.000000-4102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 1.000000-4 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000-4 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0102832151     \n"
    " 0.000000+0 0.000000+0 1.000000-4 0.000000+0 0.000000+0 0.000000+0102832151     \n"
    " 1.000000-2 0.000000+0 0.000000+0 1.000000-4 0.000000+0 1.000000-2102832151     \n";
}

void verifyChunk( const UnresolvedRelativeCovariances& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK( 1.5 == Approx( chunk.SPI() ) );
  CHECK( 1.5 == Approx( chunk.spin() ) );
  CHECK( 0.51 == Approx( chunk.AP() ) );
  CHECK( 0.51 == Approx( chunk.scatteringRadius() ) );

  CHECK( 2 == chunk.NLS() );

  auto lvalue0 = chunk.lValues()[0];
  CHECK( 20.8135 == Approx( lvalue0.AWRI() ) );
  CHECK( 20.8135 == Approx( lvalue0.atomicWeightRatio() ) );
  CHECK( 0 == lvalue0.L() );
  CHECK( 0 == lvalue0.orbitalMomentum() );

  CHECK( 2 == lvalue0.NJS() );
  CHECK( 2 == lvalue0.numberSpinValues() );
  CHECK( 2 == lvalue0.AJ().size() );
  CHECK( 2 == lvalue0.spinValues().size() );
  CHECK( 2 == lvalue0.D().size() );
  CHECK( 2 == lvalue0.averageLevelSpacings().size() );
  CHECK( 2 == lvalue0.GNO().size() );
  CHECK( 2 == lvalue0.averageNeutronWidths().size() );
  CHECK( 2 == lvalue0.GG().size() );
  CHECK( 2 == lvalue0.averageGammaWidths().size() );
  CHECK( 2 == lvalue0.GF().size() );
  CHECK( 2 == lvalue0.averageFissionWidths().size() );
  CHECK( 2 == lvalue0.GX().size() );
  CHECK( 2 == lvalue0.averageCompetitiveWidths().size() );
  CHECK( 2 == lvalue0.jValues().size() );

  CHECK( 1. == Approx( lvalue0.AJ()[0] ) );
  CHECK( 2. == Approx( lvalue0.AJ()[1] ) );
  CHECK( 1. == Approx( lvalue0.spinValues()[0] ) );
  CHECK( 2. == Approx( lvalue0.spinValues()[1] ) );
  CHECK( 4.737450e+4 == Approx( lvalue0.D()[0] ) );
  CHECK( 4.004950e+4 == Approx( lvalue0.D()[1] ) );
  CHECK( 4.737450e+4 == Approx( lvalue0.averageLevelSpacings()[0] ) );
  CHECK( 4.004950e+4 == Approx( lvalue0.averageLevelSpacings()[1] ) );
  CHECK( 1.43931 == Approx( lvalue0.GNO()[0] ) );
  CHECK( 1.21677 == Approx( lvalue0.GNO()[1] ) );
  CHECK( 1.43931 == Approx( lvalue0.averageNeutronWidths()[0] ) );
  CHECK( 1.21677 == Approx( lvalue0.averageNeutronWidths()[1] ) );
  CHECK( 9.325340e-1 == Approx( lvalue0.GG()[0] ) );
  CHECK( 3.312740e-1 == Approx( lvalue0.GG()[1] ) );
  CHECK( 9.325340e-1 == Approx( lvalue0.averageGammaWidths()[0] ) );
  CHECK( 3.312740e-1 == Approx( lvalue0.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( lvalue0.GF()[0] ) );
  CHECK( 0. == Approx( lvalue0.GF()[1] ) );
  CHECK( 0. == Approx( lvalue0.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( lvalue0.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( lvalue0.GX()[0] ) );
  CHECK( 0. == Approx( lvalue0.GX()[1] ) );
  CHECK( 0. == Approx( lvalue0.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( lvalue0.averageCompetitiveWidths()[1] ) );

  CHECK( 1. == Approx( lvalue0.jValues()[0].AJ() ) );
  CHECK( 2. == Approx( lvalue0.jValues()[1].AJ() ) );
  CHECK( 1. == Approx( lvalue0.jValues()[0].spin() ) );
  CHECK( 2. == Approx( lvalue0.jValues()[1].spin() ) );
  CHECK( 4.737450e+4 == Approx( lvalue0.jValues()[0].D() ) );
  CHECK( 4.004950e+4 == Approx( lvalue0.jValues()[1].D() ) );
  CHECK( 4.737450e+4 == Approx( lvalue0.jValues()[0].averageLevelSpacing() ) );
  CHECK( 4.004950e+4 == Approx( lvalue0.jValues()[1].averageLevelSpacing() ) );
  CHECK( 1.43931 == Approx( lvalue0.jValues()[0].GNO() ) );
  CHECK( 1.21677 == Approx( lvalue0.jValues()[1].GNO() ) );
  CHECK( 1.43931 == Approx( lvalue0.jValues()[0].averageNeutronWidth() ) );
  CHECK( 1.21677 == Approx( lvalue0.jValues()[1].averageNeutronWidth() ) );
  CHECK( 9.325340e-1 == Approx( lvalue0.jValues()[0].GG() ) );
  CHECK( 3.312740e-1 == Approx( lvalue0.jValues()[1].GG() ) );
  CHECK( 9.325340e-1 == Approx( lvalue0.jValues()[0].averageGammaWidth() ) );
  CHECK( 3.312740e-1 == Approx( lvalue0.jValues()[1].averageGammaWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].GF() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[1].GF() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[1].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].GX() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[1].GX() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue0.jValues()[1].averageCompetitiveWidth() ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK( 20.8135 == Approx( lvalue1.AWRI() ) );
  CHECK( 20.8135 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 1 == lvalue1.L() );
  CHECK( 1 == lvalue1.orbitalMomentum() );

  CHECK( 4 == lvalue1.NJS() );
  CHECK( 4 == lvalue1.numberSpinValues() );
  CHECK( 4 == lvalue1.AJ().size() );
  CHECK( 4 == lvalue1.spinValues().size() );
  CHECK( 4 == lvalue1.D().size() );
  CHECK( 4 == lvalue1.averageLevelSpacings().size() );
  CHECK( 4 == lvalue1.GNO().size() );
  CHECK( 4 == lvalue1.averageNeutronWidths().size() );
  CHECK( 4 == lvalue1.GG().size() );
  CHECK( 4 == lvalue1.averageGammaWidths().size() );
  CHECK( 4 == lvalue1.GF().size() );
  CHECK( 4 == lvalue1.averageFissionWidths().size() );
  CHECK( 4 == lvalue1.GX().size() );
  CHECK( 4 == lvalue1.averageCompetitiveWidths().size() );
  CHECK( 4 == lvalue1.jValues().size() );

  CHECK( 0. == Approx( lvalue1.AJ()[0] ) );
  CHECK( 1. == Approx( lvalue1.AJ()[1] ) );
  CHECK( 2. == Approx( lvalue1.AJ()[2] ) );
  CHECK( 3. == Approx( lvalue1.AJ()[3] ) );
  CHECK( 0. == Approx( lvalue1.spinValues()[0] ) );
  CHECK( 1. == Approx( lvalue1.spinValues()[1] ) );
  CHECK( 2. == Approx( lvalue1.spinValues()[2] ) );
  CHECK( 3. == Approx( lvalue1.spinValues()[3] ) );
  CHECK( 1.197338e+5 == Approx( lvalue1.D()[0] ) );
  CHECK( 4.737450e+4 == Approx( lvalue1.D()[1] ) );
  CHECK( 4.004950e+4 == Approx( lvalue1.D()[2] ) );
  CHECK( 4.784325e+4 == Approx( lvalue1.D()[3] ) );
  CHECK( 1.197338e+5 == Approx( lvalue1.averageLevelSpacings()[0] ) );
  CHECK( 4.737450e+4 == Approx( lvalue1.averageLevelSpacings()[1] ) );
  CHECK( 4.004950e+4 == Approx( lvalue1.averageLevelSpacings()[2] ) );
  CHECK( 4.784325e+4 == Approx( lvalue1.averageLevelSpacings()[3] ) );
  CHECK( 1.115620e+1 == Approx( lvalue1.GNO()[0] ) );
  CHECK( 3.543470e+0 == Approx( lvalue1.GNO()[1] ) );
  CHECK( 2.995580e+0 == Approx( lvalue1.GNO()[2] ) );
  CHECK( 4.457810e+0 == Approx( lvalue1.GNO()[3] ) );
  CHECK( 1.115620e+1 == Approx( lvalue1.averageNeutronWidths()[0] ) );
  CHECK( 3.543470e+0 == Approx( lvalue1.averageNeutronWidths()[1] ) );
  CHECK( 2.995580e+0 == Approx( lvalue1.averageNeutronWidths()[2] ) );
  CHECK( 4.457810e+0 == Approx( lvalue1.averageNeutronWidths()[3] ) );
  CHECK( 8.083210e-2 == Approx( lvalue1.GG()[0] ) );
  CHECK( 1.048490e+0 == Approx( lvalue1.GG()[1] ) );
  CHECK( 3.577760e-1 == Approx( lvalue1.GG()[2] ) );
  CHECK( 4.728190e-1 == Approx( lvalue1.GG()[3] ) );
  CHECK( 8.083210e-2 == Approx( lvalue1.averageGammaWidths()[0] ) );
  CHECK( 1.048490e+0 == Approx( lvalue1.averageGammaWidths()[1] ) );
  CHECK( 3.577760e-1 == Approx( lvalue1.averageGammaWidths()[2] ) );
  CHECK( 4.728190e-1 == Approx( lvalue1.averageGammaWidths()[3] ) );
  CHECK( 0. == Approx( lvalue1.GF()[0] ) );
  CHECK( 0. == Approx( lvalue1.GF()[1] ) );
  CHECK( 0. == Approx( lvalue1.GF()[2] ) );
  CHECK( 0. == Approx( lvalue1.GF()[3] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[2] ) );
  CHECK( 0. == Approx( lvalue1.averageFissionWidths()[3] ) );
  CHECK( 0. == Approx( lvalue1.GX()[0] ) );
  CHECK( 0. == Approx( lvalue1.GX()[1] ) );
  CHECK( 0. == Approx( lvalue1.GX()[2] ) );
  CHECK( 0. == Approx( lvalue1.GX()[3] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[1] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[2] ) );
  CHECK( 0. == Approx( lvalue1.averageCompetitiveWidths()[3] ) );

  CHECK( 0. == Approx( lvalue1.jValues()[0].AJ() ) );
  CHECK( 1. == Approx( lvalue1.jValues()[1].AJ() ) );
  CHECK( 2. == Approx( lvalue1.jValues()[2].AJ() ) );
  CHECK( 3. == Approx( lvalue1.jValues()[3].AJ() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].spin() ) );
  CHECK( 1. == Approx( lvalue1.jValues()[1].spin() ) );
  CHECK( 2. == Approx( lvalue1.jValues()[2].spin() ) );
  CHECK( 3. == Approx( lvalue1.jValues()[3].spin() ) );
  CHECK( 1.197338e+5 == Approx( lvalue1.jValues()[0].D() ) );
  CHECK( 4.737450e+4 == Approx( lvalue1.jValues()[1].D() ) );
  CHECK( 4.004950e+4 == Approx( lvalue1.jValues()[2].D() ) );
  CHECK( 4.784325e+4 == Approx( lvalue1.jValues()[3].D() ) );
  CHECK( 1.197338e+5 == Approx( lvalue1.jValues()[0].averageLevelSpacing() ) );
  CHECK( 4.737450e+4 == Approx( lvalue1.jValues()[1].averageLevelSpacing() ) );
  CHECK( 4.004950e+4 == Approx( lvalue1.jValues()[2].averageLevelSpacing() ) );
  CHECK( 4.784325e+4 == Approx( lvalue1.jValues()[3].averageLevelSpacing() ) );
  CHECK( 1.115620e+1 == Approx( lvalue1.jValues()[0].GNO() ) );
  CHECK( 3.543470e+0 == Approx( lvalue1.jValues()[1].GNO() ) );
  CHECK( 2.995580e+0 == Approx( lvalue1.jValues()[2].GNO() ) );
  CHECK( 4.457810e+0 == Approx( lvalue1.jValues()[3].GNO() ) );
  CHECK( 1.115620e+1 == Approx( lvalue1.jValues()[0].averageNeutronWidth() ) );
  CHECK( 3.543470e+0 == Approx( lvalue1.jValues()[1].averageNeutronWidth() ) );
  CHECK( 2.995580e+0 == Approx( lvalue1.jValues()[2].averageNeutronWidth() ) );
  CHECK( 4.457810e+0 == Approx( lvalue1.jValues()[3].averageNeutronWidth() ) );
  CHECK( 8.083210e-2 == Approx( lvalue1.jValues()[0].GG() ) );
  CHECK( 1.048490e+0 == Approx( lvalue1.jValues()[1].GG() ) );
  CHECK( 3.577760e-1 == Approx( lvalue1.jValues()[2].GG() ) );
  CHECK( 4.728190e-1 == Approx( lvalue1.jValues()[3].GG() ) );
  CHECK( 8.083210e-2 == Approx( lvalue1.jValues()[0].averageGammaWidth() ) );
  CHECK( 1.048490e+0 == Approx( lvalue1.jValues()[1].averageGammaWidth() ) );
  CHECK( 3.577760e-1 == Approx( lvalue1.jValues()[2].averageGammaWidth() ) );
  CHECK( 4.728190e-1 == Approx( lvalue1.jValues()[3].averageGammaWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[2].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[3].GF() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[2].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[3].averageFissionWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[2].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[3].GX() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[1].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[2].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( lvalue1.jValues()[3].averageCompetitiveWidth() ) );

  auto matrix = chunk.covarianceMatrix();
  CHECK( 2 == matrix.MPAR() );
  CHECK( 2 == matrix.numberAverageParameters() );

  CHECK( 12 == matrix.NPAR() );
  CHECK( 12 == matrix.covarianceMatrixOrder() );

  CHECK( 78 == matrix.covarianceMatrix().size() );
  CHECK( 78 == matrix.NVS() );
  CHECK( 78 == matrix.numberValues() );

  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[ 0] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 1] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 2] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 3] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 4] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 5] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 6] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 7] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 8] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[ 9] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[10] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[11] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[12] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[13] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[14] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[15] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[16] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[17] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[18] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[19] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[20] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[21] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[22] ) );
  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[23] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[24] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[25] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[26] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[27] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[28] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[29] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[30] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[31] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[32] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[33] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[34] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[35] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[36] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[37] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[38] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[39] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[40] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[41] ) );
  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[42] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[43] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[44] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[45] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[46] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[47] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[48] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[49] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[50] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[51] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[52] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[53] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[54] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[55] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[56] ) );
  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[57] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[58] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[59] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[60] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[61] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[62] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[63] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[64] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[65] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[66] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[67] ) );
  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[68] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[69] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[70] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[71] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[72] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[73] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[74] ) );
  CHECK( 1.000000e-4 == Approx( matrix.covarianceMatrix()[75] ) );
  CHECK( 0. == Approx( matrix.covarianceMatrix()[76] ) );
  CHECK( 1.000000e-2 == Approx( matrix.covarianceMatrix()[77] ) );

  CHECK( 23 == chunk.NC() );
}
