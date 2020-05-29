#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ReichMoore =
resonanceParameters::resolved::ReichMoore;
using LValue =
resonanceParameters::resolved::ReichMoore::LValue;

std::string chunk();
void verifyChunk( const ReichMoore& );
std::string invalidNLSC();

SCENARIO( "ReichMoore" ) {

  GIVEN( "valid data for a ReichMoore" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 1.0;
      double ap = 0.893;
      bool lad = false;
      int nlsc = 3;
      std::vector< LValue > lvalues =
        { { 1.982069e+1, 0.0, 0,
            { -1.470000e+5, 4.730000e+5 }, { 0.5, 0.5 },
            { 5.430695e+2, 1.072906e+5 }, { 3.680695e+2, 1.072900e+5 },
            { 1.750000e+2, 5.600000e-1 }, { 3., 4. } },
          { 1.982069e+1, 0.0, 1,
            { -2.060000e+0, 5.160000+0 }, { 0.5, 0.5 },
            { 3.006610e-2, 3.393822e-2 }, { 5.750000e-3, 3.920000e-3 },
            { 2.430000e-2, 3.000000e-2 }, { 1.610000e-5, 1.822000e-5 } } };

      ReichMoore chunk( spi, ap, lad, nlsc, std::move( lvalues ) );

      THEN( "a ReichMoore can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReichMoore chunk( begin, end, lineNumber, 1025, 2, 151 );

      THEN( "a ReichMoore can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "data with an illegal nlsc is used" ) {

      double spi = 1.0;
      double ap = 0.893;
      bool lad = false;
      int nlsc = 1; // should be larger than or equal to 2
      std::vector< LValue > lvalues =
        { { 1.982069e+1, 0.0, 0,
            { -1.470000e+5, 4.730000e+5 }, { 0.5, 0.5 },
            { 5.430695e+2, 1.072906e+5 }, { 3.680695e+2, 1.072900e+5 },
            { 1.750000e+2, 5.600000e-1 }, { 3., 4. } },
          { 1.982069e+1, 0.0, 1,
            { -2.060000e+0, 5.160000+0 }, { 0.5, 0.5 },
            { 3.006610e-2, 3.393822e-2 }, { 5.750000e-3, 3.920000e-3 },
            { 2.430000e-2, 3.000000e-2 }, { 1.610000e-5, 1.822000e-5 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMoore( spi, ap, lad, nlsc, std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with an illegal nlsc is used" ) {

      std::string string = invalidNLSC();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMoore( begin, end, lineNumber, 1025, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 8.930000-1          0          0          2          31025 2151     \n"
    " 1.982069+1 0.000000+0          0          0         12          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n"
    " 1.982069+1 0.000000+0          1          0         12          21025 2151     \n"
    "-2.060000+0 5.000000-1 3.006610-2 5.750000-3 2.430000-2 1.610000-51025 2151     \n"
    " 5.160000+0 5.000000-1 3.393822-2 3.920000-3 3.000000-2 1.822000-51025 2151     \n";
}

void verifyChunk( const ReichMoore& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 3 == chunk.LRF() );
  CHECK( 3 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK( 1. == Approx( chunk.SPI() ) );
  CHECK( 1. == Approx( chunk.spin() ) );
  CHECK( 0.893 == Approx( chunk.AP() ) );
  CHECK( 0.893 == Approx( chunk.scatteringRadius() ) );

  CHECK( false == chunk.LAD() );
  CHECK( false == chunk.angularDistributionsFlag() );
  CHECK( 2 == chunk.NLS() );
  CHECK( 2 == chunk.numberLValues() );
  CHECK( 3 == chunk.NLSC() );
  CHECK( 3 == chunk.numberLValuesForConvergence() );

  CHECK( 2 == chunk.lValues().size() );

  auto lvalue1 = chunk.lValues()[0];
  CHECK( 1.982069e+1 == Approx( lvalue1.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 0. == Approx( lvalue1.APL() ) );
  CHECK( 0. == Approx( lvalue1.lDependentScatteringRadius() ) );
  CHECK( 0 == lvalue1.L() );
  CHECK( 0 == lvalue1.orbitalMomentum() );

  CHECK( 2 == lvalue1.NRS() );
  CHECK( 2 == lvalue1.numberResonances() );
  CHECK( 2 == lvalue1.ER().size() );
  CHECK( 2 == lvalue1.resonanceEnergies().size() );
  CHECK( 2 == lvalue1.AJ().size() );
  CHECK( 2 == lvalue1.spinValues().size() );
  CHECK( 2 == lvalue1.GN().size() );
  CHECK( 2 == lvalue1.neutronWidths().size() );
  CHECK( 2 == lvalue1.GG().size() );
  CHECK( 2 == lvalue1.gammaWidths().size() );
  CHECK( 2 == lvalue1.GFA().size() );
  CHECK( 2 == lvalue1.firstFissionWidths().size() );
  CHECK( 2 == lvalue1.GFB().size() );
  CHECK( 2 == lvalue1.secondFissionWidths().size() );
  CHECK( 2 == lvalue1.resonances().size() );

  CHECK( -1.470000e+5 == Approx( lvalue1.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( lvalue1.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( lvalue1.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( lvalue1.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( lvalue1.AJ()[0] ) );
  CHECK( 0.5 == Approx( lvalue1.AJ()[1] ) );
  CHECK( 0.5 == Approx( lvalue1.spinValues()[0] ) );
  CHECK( 0.5 == Approx( lvalue1.spinValues()[1] ) );
  CHECK( 5.430695e+2 == Approx( lvalue1.GN()[0] ) );
  CHECK( 1.072906e+5 == Approx( lvalue1.GN()[1] ) );
  CHECK( 5.430695e+2 == Approx( lvalue1.neutronWidths()[0] ) );
  CHECK( 1.072906e+5 == Approx( lvalue1.neutronWidths()[1] ) );
  CHECK( 3.680695e+2 == Approx( lvalue1.GG()[0] ) );
  CHECK( 1.072900e+5 == Approx( lvalue1.GG()[1] ) );
  CHECK( 3.680695e+2 == Approx( lvalue1.gammaWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( lvalue1.gammaWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( lvalue1.GFA()[0] ) );
  CHECK( 0.56 == Approx( lvalue1.GFA()[1] ) );
  CHECK( 1.750000e+2 == Approx( lvalue1.firstFissionWidths()[0] ) );
  CHECK( 0.56 == Approx( lvalue1.firstFissionWidths()[1] ) );
  CHECK( 3. == Approx( lvalue1.GFB()[0] ) );
  CHECK( 4. == Approx( lvalue1.GFB()[1] ) );
  CHECK( 3. == Approx( lvalue1.secondFissionWidths()[0] ) );
  CHECK( 4. == Approx( lvalue1.secondFissionWidths()[1] ) );

  auto lvalue2 = chunk.lValues()[1];
  CHECK( 1.982069e+1 == Approx( lvalue2.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( lvalue2.atomicWeightRatio() ) );
  CHECK( 0. == Approx( lvalue2.APL() ) );
  CHECK( 0. == Approx( lvalue2.lDependentScatteringRadius() ) );
  CHECK( 1 == lvalue2.L() );
  CHECK( 1 == lvalue2.orbitalMomentum() );

  CHECK( 2 == lvalue2.NRS() );
  CHECK( 2 == lvalue2.numberResonances() );
  CHECK( 2 == lvalue2.ER().size() );
  CHECK( 2 == lvalue2.resonanceEnergies().size() );
  CHECK( 2 == lvalue2.AJ().size() );
  CHECK( 2 == lvalue2.spinValues().size() );
  CHECK( 2 == lvalue2.GN().size() );
  CHECK( 2 == lvalue2.neutronWidths().size() );
  CHECK( 2 == lvalue2.GG().size() );
  CHECK( 2 == lvalue2.gammaWidths().size() );
  CHECK( 2 == lvalue2.GFA().size() );
  CHECK( 2 == lvalue2.firstFissionWidths().size() );
  CHECK( 2 == lvalue2.GFB().size() );
  CHECK( 2 == lvalue2.secondFissionWidths().size() );
  CHECK( 2 == lvalue2.resonances().size() );

  CHECK( -2.060000e+0 == Approx( lvalue2.ER()[0] ) );
  CHECK(  5.160000e+0 == Approx( lvalue2.ER()[1] ) );
  CHECK( -2.060000e+0 == Approx( lvalue2.resonanceEnergies()[0] ) );
  CHECK(  5.160000e+0 == Approx( lvalue2.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( lvalue2.AJ()[0] ) );
  CHECK( 0.5 == Approx( lvalue2.AJ()[1] ) );
  CHECK( 0.5 == Approx( lvalue2.spinValues()[0] ) );
  CHECK( 0.5 == Approx( lvalue2.spinValues()[1] ) );
  CHECK( 3.006610e-2 == Approx( lvalue2.GN()[0] ) );
  CHECK( 3.393822e-2 == Approx( lvalue2.GN()[1] ) );
  CHECK( 3.006610e-2 == Approx( lvalue2.neutronWidths()[0] ) );
  CHECK( 3.393822e-2 == Approx( lvalue2.neutronWidths()[1] ) );
  CHECK( 5.750000e-3 == Approx( lvalue2.GG()[0] ) );
  CHECK( 3.920000e-3 == Approx( lvalue2.GG()[1] ) );
  CHECK( 5.750000e-3 == Approx( lvalue2.gammaWidths()[0] ) );
  CHECK( 3.920000e-3 == Approx( lvalue2.gammaWidths()[1] ) );
  CHECK( 2.430000e-2 == Approx( lvalue2.GFA()[0] ) );
  CHECK( 3.000000e-2 == Approx( lvalue2.GFA()[1] ) );
  CHECK( 2.430000e-2 == Approx( lvalue2.firstFissionWidths()[0] ) );
  CHECK( 3.000000e-2 == Approx( lvalue2.firstFissionWidths()[1] ) );
  CHECK( 1.610000e-5 == Approx( lvalue2.GFB()[0] ) );
  CHECK( 1.822000e-5 == Approx( lvalue2.GFB()[1] ) );
  CHECK( 1.610000e-5 == Approx( lvalue2.secondFissionWidths()[0] ) );
  CHECK( 1.822000e-5 == Approx( lvalue2.secondFissionWidths()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidNLSC() {
  return
    " 1.000000+0 8.930000-1          0          0          2          11025 2151     \n"
    " 1.982069+1 0.000000+0          0          0         12          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n"
    " 1.982069+1 0.000000+0          1          0         12          21025 2151     \n"
    "-2.060000+0 5.000000-1 3.006610-2 5.750000-3 2.430000-2 1.610000-51025 2151     \n"
    " 5.160000+0 5.000000-1 3.393822-2 3.920000-3 3.000000-2 1.822000-51025 2151     \n";
}
