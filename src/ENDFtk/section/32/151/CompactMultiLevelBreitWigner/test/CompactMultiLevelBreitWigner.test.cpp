// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactMultiLevelBreitWigner =
section::Type< 32, 151 >::CompactMultiLevelBreitWigner;
using CompactBreitWignerUncertainties =
section::Type< 32, 151 >::CompactBreitWignerUncertainties;
using CompactCorrelationMatrix =
section::Type< 32, 151 >::CompactCorrelationMatrix;

std::string chunk();
void verifyChunk( const CompactMultiLevelBreitWigner& );

SCENARIO( "CompactCorrelationMatrix" ) {

  GIVEN( "valid data for a CompactCorrelationMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 2.5;
      double ap = 7.945990e-1;
      double dap = 7.945990e-2;

      CompactBreitWignerUncertainties parameters(
          203.2137, 0., false,
          { -8.684388e+3, -5.815640e+3 }, { 1., 2. },
          { 7.761335e-1, 3.788054e+0 }, { 1.005949e-1, 2.995726e+0 },
          { 6.755386e-1, 7.923275e-1 }, { 0., 0. },
          { 8.684390e-3, 5.815640e-3 },
          { 1.005950e-6, 2.995730e-5 }, { 6.755390e-2, 7.923280e-2 },
          { 0., 0. } );

      CompactCorrelationMatrix matrix( 87, {}, {}, {}, 2 );

      CompactMultiLevelBreitWigner chunk( spi, ap, dap,
                                          std::move( parameters ),
                                          std::move( matrix ) );

      THEN( "a CompactMultiLevelBreitWigner can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 8228, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CompactMultiLevelBreitWigner chunk( begin, end, lineNumber, 8228, 32, 151 );

      THEN( "a CompactCorrelationMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 8228, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 2.500000+0 7.945990-1          0          2          0          1822832151     \n"
    " 0.000000+0 7.945990-2          0          0          0          0822832151     \n"
    " 2.032137+2 0.000000+0          0          0         24          2822832151     \n"
    "-8.684388+3 1.000000+0 7.761335-1 1.005949-1 6.755386-1 0.000000+0822832151     \n"
    " 8.684390-3 0.000000+0 0.000000+0 1.005950-6 6.755390-2 0.000000+0822832151     \n"
    "-5.815640+3 2.000000+0 3.788054+0 2.995726+0 7.923275-1 0.000000+0822832151     \n"
    " 5.815640-3 0.000000+0 0.000000+0 2.995730-5 7.923280-2 0.000000+0822832151     \n"
    " 0.000000+0 0.000000+0          2         87          0          0822832151     \n";
}

void verifyChunk( const CompactMultiLevelBreitWigner& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 2 == chunk.LRF() );
  CHECK( 2 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 2 == chunk.LCOMP() );
  CHECK( 2 == chunk.covarianceRepresentation() );

  CHECK_THAT( 2.5, WithinRel( chunk.SPI() ) );
  CHECK_THAT( 2.5, WithinRel( chunk.spin() ) );
  CHECK_THAT( .7945990, WithinRel( chunk.AP() ) );
  CHECK_THAT( .7945990, WithinRel( chunk.scatteringRadius() ) );

  CHECK( 7.945990e-2 == chunk.DAP() );
  CHECK( 7.945990e-2 == chunk.scatteringRadiusUncertainty() );
  CHECK( true == chunk.ISR() );
  CHECK( true == chunk.scatteringRadiusUncertaintyFlag() );

  CHECK_THAT( 203.2137, WithinRel( chunk.uncertainties().AWRI() ) );
  CHECK_THAT( 203.2137, WithinRel( chunk.uncertainties().atomicWeightRatio() ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().QX() ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().competitiveQValue() ) );
  CHECK( false == chunk.uncertainties().LRX() );
  CHECK( false == chunk.uncertainties().competitiveWidthFlag() );

  CHECK( 2 == chunk.uncertainties().NRSA() );
  CHECK( 2 == chunk.uncertainties().numberResonances() );
  CHECK( 2 == chunk.uncertainties().ER().size() );
  CHECK( 2 == chunk.uncertainties().resonanceEnergies().size() );
  CHECK( 2 == chunk.uncertainties().AJ().size() );
  CHECK( 2 == chunk.uncertainties().spinValues().size() );
  CHECK( 2 == chunk.uncertainties().GT().size() );
  CHECK( 2 == chunk.uncertainties().totalWidths().size() );
  CHECK( 2 == chunk.uncertainties().GN().size() );
  CHECK( 2 == chunk.uncertainties().neutronWidths().size() );
  CHECK( 2 == chunk.uncertainties().GG().size() );
  CHECK( 2 == chunk.uncertainties().gammaWidths().size() );
  CHECK( 2 == chunk.uncertainties().GF().size() );
  CHECK( 2 == chunk.uncertainties().fissionWidths().size() );
  CHECK( 2 == chunk.uncertainties().DER().size() );
  CHECK( 2 == chunk.uncertainties().resonanceEnergyUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGN().size() );
  CHECK( 2 == chunk.uncertainties().neutronWidthUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGG().size() );
  CHECK( 2 == chunk.uncertainties().gammaWidthUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGF().size() );
  CHECK( 2 == chunk.uncertainties().fissionWidthUncertainties().size() );

  CHECK_THAT( -8.684388e+3, WithinRel( chunk.uncertainties().ER()[0] ) );
  CHECK_THAT( -5.815640e+3, WithinRel( chunk.uncertainties().ER()[1] ) );
  CHECK_THAT( -8.684388e+3, WithinRel( chunk.uncertainties().resonanceEnergies()[0] ) );
  CHECK_THAT( -5.815640e+3, WithinRel( chunk.uncertainties().resonanceEnergies()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.uncertainties().AJ()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.uncertainties().AJ()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.uncertainties().spinValues()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.uncertainties().spinValues()[1] ) );
  CHECK_THAT( 7.761335e-1, WithinRel( chunk.uncertainties().GT()[0] ) );
  CHECK_THAT( 3.788054e+0, WithinRel( chunk.uncertainties().GT()[1] ) );
  CHECK_THAT( 7.761335e-1, WithinRel( chunk.uncertainties().totalWidths()[0] ) );
  CHECK_THAT( 3.788054e+0, WithinRel( chunk.uncertainties().totalWidths()[1] ) );
  CHECK_THAT( 1.005949e-1, WithinRel( chunk.uncertainties().GN()[0] ) );
  CHECK_THAT( 2.995726e+0, WithinRel( chunk.uncertainties().GN()[1] ) );
  CHECK_THAT( 1.005949e-1, WithinRel( chunk.uncertainties().neutronWidths()[0] ) );
  CHECK_THAT( 2.995726e+0, WithinRel( chunk.uncertainties().neutronWidths()[1] ) );
  CHECK_THAT( 6.755386e-1, WithinRel( chunk.uncertainties().GG()[0] ) );
  CHECK_THAT( 7.923275e-1, WithinRel( chunk.uncertainties().GG()[1] ) );
  CHECK_THAT( 6.755386e-1, WithinRel( chunk.uncertainties().gammaWidths()[0] ) );
  CHECK_THAT( 7.923275e-1, WithinRel( chunk.uncertainties().gammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().GF()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().GF()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().fissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().fissionWidths()[1] ) );

  CHECK_THAT( 8.684390e-3, WithinRel( chunk.uncertainties().DER()[0] ) );
  CHECK_THAT( 5.815640e-3, WithinRel( chunk.uncertainties().DER()[1] ) );
  CHECK_THAT( 8.684390e-3, WithinRel( chunk.uncertainties().resonanceEnergyUncertainties()[0] ) );
  CHECK_THAT( 5.815640e-3, WithinRel( chunk.uncertainties().resonanceEnergyUncertainties()[1] ) );
  CHECK_THAT( 1.005950e-6, WithinRel( chunk.uncertainties().DGN()[0] ) );
  CHECK_THAT( 2.995730e-5, WithinRel( chunk.uncertainties().DGN()[1] ) );
  CHECK_THAT( 1.005950e-6, WithinRel( chunk.uncertainties().neutronWidthUncertainties()[0] ) );
  CHECK_THAT( 2.995730e-5, WithinRel( chunk.uncertainties().neutronWidthUncertainties()[1] ) );
  CHECK_THAT( 6.755390e-2, WithinRel( chunk.uncertainties().DGG()[0] ) );
  CHECK_THAT( 7.923280e-2, WithinRel( chunk.uncertainties().DGG()[1] ) );
  CHECK_THAT( 6.755390e-2, WithinRel( chunk.uncertainties().gammaWidthUncertainties()[0] ) );
  CHECK_THAT( 7.923280e-2, WithinRel( chunk.uncertainties().gammaWidthUncertainties()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().DGF()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().DGF()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().fissionWidthUncertainties()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.uncertainties().fissionWidthUncertainties()[1] ) );

  CHECK( 2 == chunk.correlationMatrix().NDIGIT() );
  CHECK( 2 == chunk.correlationMatrix().numberDigits() );
  CHECK( 87 == chunk.correlationMatrix().NNN() );
  CHECK( 87 == chunk.correlationMatrix().order() );
  CHECK( 0 == chunk.correlationMatrix().I().size() );
  CHECK( 0 == chunk.correlationMatrix().J().size() );
  CHECK( 0 == chunk.correlationMatrix().correlations().size() );

  CHECK( 8 == chunk.NC() );
}
