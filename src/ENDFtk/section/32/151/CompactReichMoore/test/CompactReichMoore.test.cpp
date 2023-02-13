#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactReichMoore =
section::Type< 32, 151 >::CompactReichMoore;
using CompactReichMooreUncertainties =
section::Type< 32, 151 >::CompactReichMooreUncertainties;
using CompactCorrelationMatrix =
section::Type< 32, 151 >::CompactCorrelationMatrix;

std::string chunk();
void verifyChunk( const CompactReichMoore& );

SCENARIO( "CompactCorrelationMatrix" ) {

  GIVEN( "valid data for a CompactCorrelationMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 2.5;
      double ap = 0.962;
      bool lad = false;

      CompactReichMooreUncertainties parameters(
          231.0377, 0.,
          { -1.060000e+3, -8.000000e+2 }, { 3., 2. },
          { 1.524000e+0, 1.315000e+0 }, { 0.04, 0.04 },
          { 2.600000e-1, 3.120000e-1 }, {  2.370000e-1, -2.250000e-1 },
          { 2.061000e+0, 1.891999e+0 },
          { 1.453063e+0, 1.268267e+0 }, { 3.999991e-2, 3.999987e-2 },
          { 2.592466e-1, 3.106125e-1 }, { 2.362210e-1, 2.241766e-1 } );

      CompactCorrelationMatrix matrix(
          10,
          { 2, 4, 4, 5, 5, 5, 6, 7, 7, 7,
            7, 7, 8, 9, 9, 9, 9, 9 },
          { 1, 1, 2, 1, 2, 4, 2, 1, 2, 4,
            5, 6, 2, 2, 4, 5, 6, 7 },
          { -1205e-6,   -25e-6, -9375e-6,   -25e-6, -6215e-6,
             -385e-6,  -105e-6,   -95e-6, -61345e-6, -2095e-6,
             1145e-6, -1395e-6,    25e-6,  3245e-6,   175e-6,
               35e-6,   -35e-6, -7485e-6 }, 5 );

      CompactReichMoore chunk( spi, ap, lad,
                               std::move( parameters ),
                               std::move( matrix ) );

      THEN( "a CompactReichMoore can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CompactReichMoore chunk( begin, end, lineNumber, 9222, 32, 151 );

      THEN( "a CompactCorrelationMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 2.500000+0 9.620000-1          0          2          0          0922232151     \n"
    " 2.310377+2 0.000000+0          0          0         24          2922232151     \n"
    "-1.060000+3 3.000000+0 1.524000+0 4.000000-2 2.600000-1 2.370000-1922232151     \n"
    " 2.061000+0 0.000000+0 1.453063+0 3.999991-2 2.592466-1 2.362210-1922232151     \n"
    "-8.000000+2 2.000000+0 1.315000+0 4.000000-2 3.120000-1-2.250000-1922232151     \n"
    " 1.891999+0 0.000000+0 1.268267+0 3.999987-2 3.106125-1 2.241766-1922232151     \n"
    " 0.000000+0 0.000000+0          5         10          7          0922232151     \n"
    "    2    1   -120                                                 922232151     \n"
    "    4    1     -2  -937                                           922232151     \n"
    "    5    1     -2  -621     0   -38                               922232151     \n"
    "    6    2    -10                                                 922232151     \n"
    "    7    1     -9 -6134     0  -209   114  -139                   922232151     \n"
    "    8    2      2                                                 922232151     \n"
    "    9    2    324     0    17     3    -3  -748                   922232151     \n";
}

void verifyChunk( const CompactReichMoore& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 3 == chunk.LRF() );
  CHECK( 3 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 2 == chunk.LCOMP() );
  CHECK( 2 == chunk.covarianceRepresentation() );

  CHECK( 2.5 == Approx( chunk.SPI() ) );
  CHECK( 2.5 == Approx( chunk.spin() ) );
  CHECK( 0.962 == Approx( chunk.AP() ) );
  CHECK( 0.962 == Approx( chunk.scatteringRadius() ) );
  CHECK( false == chunk.LAD() );
  CHECK( false == chunk.scatteringRadiusUncertainty() );

  CHECK( std::nullopt == chunk.DAP() );
  CHECK( std::nullopt == chunk.scatteringRadiusUncertainty() );

  CHECK( 231.0377 == Approx( chunk.uncertainties().AWRI() ) );
  CHECK( 231.0377 == Approx( chunk.uncertainties().atomicWeightRatio() ) );
  CHECK( 0. == Approx( chunk.uncertainties().APL() ) );
  CHECK( 0. == Approx( chunk.uncertainties().lDependentScatteringRadius() ) );

  CHECK( 2 == chunk.uncertainties().NRSA() );
  CHECK( 2 == chunk.uncertainties().numberResonances() );
  CHECK( 2 == chunk.uncertainties().ER().size() );
  CHECK( 2 == chunk.uncertainties().resonanceEnergies().size() );
  CHECK( 2 == chunk.uncertainties().AJ().size() );
  CHECK( 2 == chunk.uncertainties().spinValues().size() );
  CHECK( 2 == chunk.uncertainties().GN().size() );
  CHECK( 2 == chunk.uncertainties().neutronWidths().size() );
  CHECK( 2 == chunk.uncertainties().GG().size() );
  CHECK( 2 == chunk.uncertainties().gammaWidths().size() );
  CHECK( 2 == chunk.uncertainties().GFA().size() );
  CHECK( 2 == chunk.uncertainties().firstFissionWidths().size() );
  CHECK( 2 == chunk.uncertainties().GFB().size() );
  CHECK( 2 == chunk.uncertainties().secondFissionWidths().size() );
  CHECK( 2 == chunk.uncertainties().DER().size() );
  CHECK( 2 == chunk.uncertainties().resonanceEnergyUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGN().size() );
  CHECK( 2 == chunk.uncertainties().neutronWidthUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGG().size() );
  CHECK( 2 == chunk.uncertainties().gammaWidthUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGFA().size() );
  CHECK( 2 == chunk.uncertainties().firstFissionWidthUncertainties().size() );
  CHECK( 2 == chunk.uncertainties().DGFB().size() );
  CHECK( 2 == chunk.uncertainties().secondFissionWidthUncertainties().size() );

  CHECK( -1.060000e+3 == Approx( chunk.uncertainties().ER()[0] ) );
  CHECK( -8.000000e+2 == Approx( chunk.uncertainties().ER()[1] ) );
  CHECK( -1.060000e+3 == Approx( chunk.uncertainties().resonanceEnergies()[0] ) );
  CHECK( -8.000000e+2 == Approx( chunk.uncertainties().resonanceEnergies()[1] ) );
  CHECK( 3. == Approx( chunk.uncertainties().AJ()[0] ) );
  CHECK( 2. == Approx( chunk.uncertainties().AJ()[1] ) );
  CHECK( 3. == Approx( chunk.uncertainties().spinValues()[0] ) );
  CHECK( 2. == Approx( chunk.uncertainties().spinValues()[1] ) );
  CHECK( 1.524000e+0 == Approx( chunk.uncertainties().GN()[0] ) );
  CHECK( 1.315000e+0 == Approx( chunk.uncertainties().GN()[1] ) );
  CHECK( 1.524000e+0 == Approx( chunk.uncertainties().neutronWidths()[0] ) );
  CHECK( 1.315000e+0 == Approx( chunk.uncertainties().neutronWidths()[1] ) );
  CHECK( 0.04 == Approx( chunk.uncertainties().GG()[0] ) );
  CHECK( 0.04 == Approx( chunk.uncertainties().GG()[1] ) );
  CHECK( 0.04 == Approx( chunk.uncertainties().gammaWidths()[0] ) );
  CHECK( 0.04 == Approx( chunk.uncertainties().gammaWidths()[1] ) );
  CHECK( 2.600000e-1 == Approx( chunk.uncertainties().GFA()[0] ) );
  CHECK( 3.120000e-1 == Approx( chunk.uncertainties().GFA()[1] ) );
  CHECK( 2.600000e-1 == Approx( chunk.uncertainties().firstFissionWidths()[0] ) );
  CHECK( 3.120000e-1 == Approx( chunk.uncertainties().firstFissionWidths()[1] ) );
  CHECK(  2.370000e-1 == Approx( chunk.uncertainties().GFB()[0] ) );
  CHECK( -2.250000e-1 == Approx( chunk.uncertainties().GFB()[1] ) );
  CHECK(  2.370000e-1 == Approx( chunk.uncertainties().secondFissionWidths()[0] ) );
  CHECK( -2.250000e-1 == Approx( chunk.uncertainties().secondFissionWidths()[1] ) );

  CHECK( 2.061000e+0 == Approx( chunk.uncertainties().DER()[0] ) );
  CHECK( 1.891999e+0 == Approx( chunk.uncertainties().DER()[1] ) );
  CHECK( 2.061000e+0 == Approx( chunk.uncertainties().resonanceEnergyUncertainties()[0] ) );
  CHECK( 1.891999e+0 == Approx( chunk.uncertainties().resonanceEnergyUncertainties()[1] ) );
  CHECK( 1.453063e+0 == Approx( chunk.uncertainties().DGN()[0] ) );
  CHECK( 1.268267e+0 == Approx( chunk.uncertainties().DGN()[1] ) );
  CHECK( 1.453063e+0 == Approx( chunk.uncertainties().neutronWidthUncertainties()[0] ) );
  CHECK( 1.268267e+0 == Approx( chunk.uncertainties().neutronWidthUncertainties()[1] ) );
  CHECK( 3.999991e-2 == Approx( chunk.uncertainties().DGG()[0] ) );
  CHECK( 3.999987e-2 == Approx( chunk.uncertainties().DGG()[1] ) );
  CHECK( 3.999991e-2 == Approx( chunk.uncertainties().gammaWidthUncertainties()[0] ) );
  CHECK( 3.999987e-2 == Approx( chunk.uncertainties().gammaWidthUncertainties()[1] ) );
  CHECK( 2.592466e-1 == Approx( chunk.uncertainties().DGFA()[0] ) );
  CHECK( 3.106125e-1 == Approx( chunk.uncertainties().DGFA()[1] ) );
  CHECK( 2.592466e-1 == Approx( chunk.uncertainties().firstFissionWidthUncertainties()[0] ) );
  CHECK( 3.106125e-1 == Approx( chunk.uncertainties().firstFissionWidthUncertainties()[1] ) );
  CHECK( 2.362210e-1 == Approx( chunk.uncertainties().DGFB()[0] ) );
  CHECK( 2.241766e-1 == Approx( chunk.uncertainties().DGFB()[1] ) );
  CHECK( 2.362210e-1 == Approx( chunk.uncertainties().secondFissionWidthUncertainties()[0] ) );
  CHECK( 2.241766e-1 == Approx( chunk.uncertainties().secondFissionWidthUncertainties()[1] ) );

  CHECK( 5 == chunk.correlationMatrix().NDIGIT() );
  CHECK( 5 == chunk.correlationMatrix().numberDigits() );
  CHECK( 10 == chunk.correlationMatrix().NNN() );
  CHECK( 10 == chunk.correlationMatrix().order() );
  CHECK( 18 == chunk.correlationMatrix().I().size() );
  CHECK( 18 == chunk.correlationMatrix().J().size() );
  CHECK( 18 == chunk.correlationMatrix().correlations().size() );

  CHECK( 2 == chunk.correlationMatrix().I()[0] );
  CHECK( 4 == chunk.correlationMatrix().I()[1] );
  CHECK( 4 == chunk.correlationMatrix().I()[2] );
  CHECK( 5 == chunk.correlationMatrix().I()[3] );
  CHECK( 5 == chunk.correlationMatrix().I()[4] );
  CHECK( 5 == chunk.correlationMatrix().I()[5] );
  CHECK( 6 == chunk.correlationMatrix().I()[6] );
  CHECK( 7 == chunk.correlationMatrix().I()[7] );
  CHECK( 7 == chunk.correlationMatrix().I()[8] );
  CHECK( 7 == chunk.correlationMatrix().I()[9] );
  CHECK( 7 == chunk.correlationMatrix().I()[10] );
  CHECK( 7 == chunk.correlationMatrix().I()[11] );
  CHECK( 8 == chunk.correlationMatrix().I()[12] );
  CHECK( 9 == chunk.correlationMatrix().I()[13] );
  CHECK( 9 == chunk.correlationMatrix().I()[14] );
  CHECK( 9 == chunk.correlationMatrix().I()[15] );
  CHECK( 9 == chunk.correlationMatrix().I()[16] );
  CHECK( 9 == chunk.correlationMatrix().I()[17] );

  CHECK( 1 == chunk.correlationMatrix().J()[0] );
  CHECK( 1 == chunk.correlationMatrix().J()[1] );
  CHECK( 2 == chunk.correlationMatrix().J()[2] );
  CHECK( 1 == chunk.correlationMatrix().J()[3] );
  CHECK( 2 == chunk.correlationMatrix().J()[4] );
  CHECK( 4 == chunk.correlationMatrix().J()[5] );
  CHECK( 2 == chunk.correlationMatrix().J()[6] );
  CHECK( 1 == chunk.correlationMatrix().J()[7] );
  CHECK( 2 == chunk.correlationMatrix().J()[8] );
  CHECK( 4 == chunk.correlationMatrix().J()[9] );
  CHECK( 5 == chunk.correlationMatrix().J()[10] );
  CHECK( 6 == chunk.correlationMatrix().J()[11] );
  CHECK( 2 == chunk.correlationMatrix().J()[12] );
  CHECK( 2 == chunk.correlationMatrix().J()[13] );
  CHECK( 4 == chunk.correlationMatrix().J()[14] );
  CHECK( 5 == chunk.correlationMatrix().J()[15] );
  CHECK( 6 == chunk.correlationMatrix().J()[16] );
  CHECK( 7 == chunk.correlationMatrix().J()[17] );

  CHECK(  -1205e-6 == Approx( chunk.correlationMatrix().correlations()[0] ) );
  CHECK(    -25e-6 == Approx( chunk.correlationMatrix().correlations()[1] ) );
  CHECK(  -9375e-6 == Approx( chunk.correlationMatrix().correlations()[2] ) );
  CHECK(    -25e-6 == Approx( chunk.correlationMatrix().correlations()[3] ) );
  CHECK(  -6215e-6 == Approx( chunk.correlationMatrix().correlations()[4] ) );
  CHECK(   -385e-6 == Approx( chunk.correlationMatrix().correlations()[5] ) );
  CHECK(   -105e-6 == Approx( chunk.correlationMatrix().correlations()[6] ) );
  CHECK(    -95e-6 == Approx( chunk.correlationMatrix().correlations()[7] ) );
  CHECK( -61345e-6 == Approx( chunk.correlationMatrix().correlations()[8] ) );
  CHECK(  -2095e-6 == Approx( chunk.correlationMatrix().correlations()[9] ) );
  CHECK(   1145e-6 == Approx( chunk.correlationMatrix().correlations()[10] ) );
  CHECK(  -1395e-6 == Approx( chunk.correlationMatrix().correlations()[11] ) );
  CHECK(     25e-6 == Approx( chunk.correlationMatrix().correlations()[12] ) );
  CHECK(   3245e-6 == Approx( chunk.correlationMatrix().correlations()[13] ) );
  CHECK(    175e-6 == Approx( chunk.correlationMatrix().correlations()[14] ) );
  CHECK(     35e-6 == Approx( chunk.correlationMatrix().correlations()[15] ) );
  CHECK(    -35e-6 == Approx( chunk.correlationMatrix().correlations()[16] ) );
  CHECK(  -7485e-6 == Approx( chunk.correlationMatrix().correlations()[17] ) );

  CHECK( 14 == chunk.NC() );
}
