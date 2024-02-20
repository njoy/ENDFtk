// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LimitedMultiLevelBreitWigner =
section::Type< 32, 151 >::LimitedMultiLevelBreitWigner;
using LValue = section::Type< 32, 151 >::LimitedMultiLevelBreitWigner::LValue;

std::string chunk();
void verifyChunk( const LimitedMultiLevelBreitWigner& );
std::string invalidSize();

SCENARIO( "LimitedMultiLevelBreitWigner" ) {

  GIVEN( "valid data for a LimitedMultiLevelBreitWigner" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 1.5;
      double ap = .541;
      std::vector< LValue > lvalues =
        { { 22.792, 0,
            { 2810., 242970., 298320. }, { 1., 1., 2. },
            { 376.35, 329.5, 2039. }, { 376., 328., 2038. },
            { .353, 1.50, 1.02 }, { 0., 0., 0. },
            { 1600., 1100., 1400. }, { 225., 340., 710. },
            { 0., 0., 0. }, { 2.5e-3, 6.1e-2, 8.3e-3 },
            { 0., 0., 0. }, { 0., 0., 0. }, { 0., 0., 0. },
            { 0., 0., 0. }, { 0., 0., 0. }, { 0., 0., 0. },
            { 0., 0., 0. } },
          { 22.792, 1,
            { 7617., 392320. }, { 2., 1. },
            { 6.058e-1, 2.277e+4 }, { 5.800e-3, 2.276e+4 },
            { .6, 9.87 }, { 0., 0. },
            { 100., 130000. }, { 9.0e-6, 6.1e+4 },
            { 0., 0. }, { .09, 2.4 },
            { 0., 0. }, { 0., 0. }, { 0., 0. },
            { 0., 0. }, { 0., 0. }, { 0., 0. },
            { 0., 0. } } };

      LimitedMultiLevelBreitWigner chunk( spi, ap, std::move( lvalues ) );

      THEN( "a LimitedMultiLevelBreitWigner can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1125, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LimitedMultiLevelBreitWigner chunk( begin, end, lineNumber, 1125, 32, 151 );

      THEN( "a LimitedMultiLevelBreitWigner can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1125, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "no l values are given" ) {

      double spi = 1.0;
      double ap = 0.893;
      std::vector< LValue > lvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LimitedMultiLevelBreitWigner( spi, ap, std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no l values is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LimitedMultiLevelBreitWigner( begin, end, lineNumber, 1125, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.500000+0 5.410000-1          0          0          2          0112532151     \n"
    " 2.279200+1 0.000000+0          0          0         54          3112532151     \n"
    " 2.810000+3 1.000000+0 3.763500+2 3.760000+2 3.530000-1 0.000000+0112532151     \n"
    " 1.600000+3 2.250000+2 0.000000+0 2.500000-3 0.000000+0 0.000000+0112532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n"
    " 2.429700+5 1.000000+0 3.295000+2 3.280000+2 1.500000+0 0.000000+0112532151     \n"
    " 1.100000+3 3.400000+2 0.000000+0 6.100000-2 0.000000+0 0.000000+0112532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n"
    " 2.983200+5 2.000000+0 2.039000+3 2.038000+3 1.020000+0 0.000000+0112532151     \n"
    " 1.400000+3 7.100000+2 0.000000+0 8.300000-3 0.000000+0 0.000000+0112532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n"
    " 2.279200+1 0.000000+0          1          0         36          2112532151     \n"
    " 7.617000+3 2.000000+0 6.058000-1 5.800000-3 6.000000-1 0.000000+0112532151     \n"
    " 1.000000+2 9.000000-6 0.000000+0 9.000000-2 0.000000+0 0.000000+0112532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n"
    " 3.923200+5 1.000000+0 2.277000+4 2.276000+4 9.870000+0 0.000000+0112532151     \n"
    " 1.300000+5 6.100000+4 0.000000+0 2.400000+0 0.000000+0 0.000000+0112532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n";
}

void verifyChunk( const LimitedMultiLevelBreitWigner& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 2 == chunk.LRF() );
  CHECK( 2 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 0 == chunk.LCOMP() );
  CHECK( 0 == chunk.covarianceRepresentation() );

  CHECK_THAT( 1.5, WithinRel( chunk.SPI() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.spin() ) );
  CHECK_THAT( 0.541, WithinRel( chunk.AP() ) );
  CHECK_THAT( 0.541, WithinRel( chunk.scatteringRadius() ) );

  CHECK( std::nullopt == chunk.DAP() );
  CHECK( std::nullopt == chunk.scatteringRadiusUncertainty() );
  CHECK( false == chunk.ISR() );
  CHECK( false == chunk.scatteringRadiusUncertaintyFlag() );

  CHECK( 2 == chunk.NLS() );
  CHECK( 2 == chunk.numberLValues() );

  CHECK( 2 == chunk.lValues().size() );

  auto lvalue1 = chunk.lValues()[0];
  CHECK_THAT( 22.792, WithinRel( lvalue1.AWRI() ) );
  CHECK_THAT( 22.792, WithinRel( lvalue1.atomicWeightRatio() ) );
  CHECK( 0 == lvalue1.L() );
  CHECK( 0 == lvalue1.orbitalMomentum() );

  CHECK( 3 == lvalue1.NRS() );
  CHECK( 3 == lvalue1.numberResonances() );
  CHECK( 3 == lvalue1.ER().size() );
  CHECK( 3 == lvalue1.resonanceEnergies().size() );
  CHECK( 3 == lvalue1.AJ().size() );
  CHECK( 3 == lvalue1.spinValues().size() );
  CHECK( 3 == lvalue1.GT().size() );
  CHECK( 3 == lvalue1.totalWidths().size() );
  CHECK( 3 == lvalue1.GN().size() );
  CHECK( 3 == lvalue1.neutronWidths().size() );
  CHECK( 3 == lvalue1.GG().size() );
  CHECK( 3 == lvalue1.gammaWidths().size() );
  CHECK( 3 == lvalue1.GF().size() );
  CHECK( 3 == lvalue1.fissionWidths().size() );
  CHECK( 3 == lvalue1.DE2().size() );
  CHECK( 3 == lvalue1.resonanceEnergyVariances().size() );
  CHECK( 3 == lvalue1.DJ2().size() );
  CHECK( 3 == lvalue1.spinVariances().size() );
  CHECK( 3 == lvalue1.DN2().size() );
  CHECK( 3 == lvalue1.neutronWidthVariances().size() );
  CHECK( 3 == lvalue1.DG2().size() );
  CHECK( 3 == lvalue1.gammaWidthVariances().size() );
  CHECK( 3 == lvalue1.DF2().size() );
  CHECK( 3 == lvalue1.fissionWidthVariances().size() );
  CHECK( 3 == lvalue1.DJDN().size() );
  CHECK( 3 == lvalue1.spinAndNeutronWidthCovariances().size() );
  CHECK( 3 == lvalue1.DJDG().size() );
  CHECK( 3 == lvalue1.spinAndGammaWidthCovariances().size() );
  CHECK( 3 == lvalue1.DJDF().size() );
  CHECK( 3 == lvalue1.spinAndFissionWidthCovariances().size() );
  CHECK( 3 == lvalue1.DNDG().size() );
  CHECK( 3 == lvalue1.neutronAndGammaWidthCovariances().size() );
  CHECK( 3 == lvalue1.DNDF().size() );
  CHECK( 3 == lvalue1.neutronAndFissionWidthCovariances().size() );
  CHECK( 3 == lvalue1.DGDF().size() );
  CHECK( 3 == lvalue1.gammaAndFissionWidthCovariances().size() );
  CHECK( 3 == lvalue1.resonances().size() );

  CHECK_THAT( 2810., WithinRel( lvalue1.ER()[0] ) );
  CHECK_THAT( 242970., WithinRel( lvalue1.ER()[1] ) );
  CHECK_THAT( 298320., WithinRel( lvalue1.ER()[2] ) );
  CHECK_THAT( 2810., WithinRel( lvalue1.resonanceEnergies()[0] ) );
  CHECK_THAT( 242970., WithinRel( lvalue1.resonanceEnergies()[1] ) );
  CHECK_THAT( 298320., WithinRel( lvalue1.resonanceEnergies()[2] ) );
  CHECK_THAT( 1.0, WithinRel( lvalue1.AJ()[0] ) );
  CHECK_THAT( 1.0, WithinRel( lvalue1.AJ()[1] ) );
  CHECK_THAT( 2.0, WithinRel( lvalue1.AJ()[2] ) );
  CHECK_THAT( 1.0, WithinRel( lvalue1.spinValues()[0] ) );
  CHECK_THAT( 1.0, WithinRel( lvalue1.spinValues()[1] ) );
  CHECK_THAT( 2.0, WithinRel( lvalue1.spinValues()[2] ) );
  CHECK_THAT( 376.35, WithinRel( lvalue1.GT()[0] ) );
  CHECK_THAT( 329.5, WithinRel( lvalue1.GT()[1] ) );
  CHECK_THAT( 2039., WithinRel( lvalue1.GT()[2] ) );
  CHECK_THAT( 376.35, WithinRel( lvalue1.totalWidths()[0] ) );
  CHECK_THAT( 329.5, WithinRel( lvalue1.totalWidths()[1] ) );
  CHECK_THAT( 2039., WithinRel( lvalue1.totalWidths()[2] ) );
  CHECK_THAT( 376., WithinRel( lvalue1.GN()[0] ) );
  CHECK_THAT( 328., WithinRel( lvalue1.GN()[1] ) );
  CHECK_THAT( 2038., WithinRel( lvalue1.GN()[2] ) );
  CHECK_THAT( 376., WithinRel( lvalue1.neutronWidths()[0] ) );
  CHECK_THAT( 328., WithinRel( lvalue1.neutronWidths()[1] ) );
  CHECK_THAT( 2038., WithinRel( lvalue1.neutronWidths()[2] ) );
  CHECK_THAT( .353, WithinRel( lvalue1.GG()[0] ) );
  CHECK_THAT( 1.50, WithinRel( lvalue1.GG()[1] ) );
  CHECK_THAT( 1.02, WithinRel( lvalue1.GG()[2] ) );
  CHECK_THAT( .353, WithinRel( lvalue1.gammaWidths()[0] ) );
  CHECK_THAT( 1.50, WithinRel( lvalue1.gammaWidths()[1] ) );
  CHECK_THAT( 1.02, WithinRel( lvalue1.gammaWidths()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidths()[2] ) );
  CHECK_THAT( 1600., WithinRel( lvalue1.DE2()[0] ) );
  CHECK_THAT( 1100., WithinRel( lvalue1.DE2()[1] ) );
  CHECK_THAT( 1400., WithinRel( lvalue1.DE2()[2] ) );
  CHECK_THAT( 1600., WithinRel( lvalue1.resonanceEnergyVariances()[0] ) );
  CHECK_THAT( 1100., WithinRel( lvalue1.resonanceEnergyVariances()[1] ) );
  CHECK_THAT( 1400., WithinRel( lvalue1.resonanceEnergyVariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJ2()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJ2()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJ2()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinVariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinVariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinVariances()[2] ) );
  CHECK_THAT( 225., WithinRel( lvalue1.DN2()[0] ) );
  CHECK_THAT( 340., WithinRel( lvalue1.DN2()[1] ) );
  CHECK_THAT( 710., WithinRel( lvalue1.DN2()[2] ) );
  CHECK_THAT( 225., WithinRel( lvalue1.neutronWidthVariances()[0] ) );
  CHECK_THAT( 340., WithinRel( lvalue1.neutronWidthVariances()[1] ) );
  CHECK_THAT( 710., WithinRel( lvalue1.neutronWidthVariances()[2] ) );
  CHECK_THAT( 2.5e-3, WithinRel( lvalue1.DG2()[0] ) );
  CHECK_THAT( 6.1e-2, WithinRel( lvalue1.DG2()[1] ) );
  CHECK_THAT( 8.3e-3, WithinRel( lvalue1.DG2()[2] ) );
  CHECK_THAT( 2.5e-3, WithinRel( lvalue1.gammaWidthVariances()[0] ) );
  CHECK_THAT( 6.1e-2, WithinRel( lvalue1.gammaWidthVariances()[1] ) );
  CHECK_THAT( 8.3e-3, WithinRel( lvalue1.gammaWidthVariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DF2()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DF2()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DF2()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidthVariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidthVariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidthVariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDN()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDN()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDN()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndNeutronWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndNeutronWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndNeutronWidthCovariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDG()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDG()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDG()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndGammaWidthCovariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DJDF()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.spinAndFissionWidthCovariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDG()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDG()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDG()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndGammaWidthCovariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DNDF()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.neutronAndFissionWidthCovariances()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DGDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DGDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.DGDF()[2] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.gammaAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.gammaAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.gammaAndFissionWidthCovariances()[2] ) );

  auto lvalue2 = chunk.lValues()[1];
  CHECK_THAT( 22.792, WithinRel( lvalue2.AWRI() ) );
  CHECK_THAT( 22.792, WithinRel( lvalue2.atomicWeightRatio() ) );
  CHECK( 1 == lvalue2.L() );
  CHECK( 1 == lvalue2.orbitalMomentum() );

  CHECK( 2 == lvalue2.NRS() );
  CHECK( 2 == lvalue2.numberResonances() );
  CHECK( 2 == lvalue2.ER().size() );
  CHECK( 2 == lvalue2.resonanceEnergies().size() );
  CHECK( 2 == lvalue2.AJ().size() );
  CHECK( 2 == lvalue2.spinValues().size() );
  CHECK( 2 == lvalue2.GT().size() );
  CHECK( 2 == lvalue2.totalWidths().size() );
  CHECK( 2 == lvalue2.GN().size() );
  CHECK( 2 == lvalue2.neutronWidths().size() );
  CHECK( 2 == lvalue2.GG().size() );
  CHECK( 2 == lvalue2.gammaWidths().size() );
  CHECK( 2 == lvalue2.GF().size() );
  CHECK( 2 == lvalue2.fissionWidths().size() );
  CHECK( 2 == lvalue2.DE2().size() );
  CHECK( 2 == lvalue2.resonanceEnergyVariances().size() );
  CHECK( 2 == lvalue2.DJ2().size() );
  CHECK( 2 == lvalue2.spinVariances().size() );
  CHECK( 2 == lvalue2.DN2().size() );
  CHECK( 2 == lvalue2.neutronWidthVariances().size() );
  CHECK( 2 == lvalue2.DG2().size() );
  CHECK( 2 == lvalue2.gammaWidthVariances().size() );
  CHECK( 2 == lvalue2.DF2().size() );
  CHECK( 2 == lvalue2.fissionWidthVariances().size() );
  CHECK( 2 == lvalue2.DJDN().size() );
  CHECK( 2 == lvalue2.spinAndNeutronWidthCovariances().size() );
  CHECK( 2 == lvalue2.DJDG().size() );
  CHECK( 2 == lvalue2.spinAndGammaWidthCovariances().size() );
  CHECK( 2 == lvalue2.DJDF().size() );
  CHECK( 2 == lvalue2.spinAndFissionWidthCovariances().size() );
  CHECK( 2 == lvalue2.DNDG().size() );
  CHECK( 2 == lvalue2.neutronAndGammaWidthCovariances().size() );
  CHECK( 2 == lvalue2.DNDF().size() );
  CHECK( 2 == lvalue2.neutronAndFissionWidthCovariances().size() );
  CHECK( 2 == lvalue2.DGDF().size() );
  CHECK( 2 == lvalue2.gammaAndFissionWidthCovariances().size() );
  CHECK( 2 == lvalue2.resonances().size() );

  CHECK_THAT( 7617., WithinRel( lvalue2.ER()[0] ) );
  CHECK_THAT( 392320., WithinRel( lvalue2.ER()[1] ) );
  CHECK_THAT( 7617., WithinRel( lvalue2.resonanceEnergies()[0] ) );
  CHECK_THAT( 392320., WithinRel( lvalue2.resonanceEnergies()[1] ) );
  CHECK_THAT( 2., WithinRel( lvalue2.AJ()[0] ) );
  CHECK_THAT( 1., WithinRel( lvalue2.AJ()[1] ) );
  CHECK_THAT( 2., WithinRel( lvalue2.spinValues()[0] ) );
  CHECK_THAT( 1., WithinRel( lvalue2.spinValues()[1] ) );
  CHECK_THAT( 6.058e-1, WithinRel( lvalue2.GT()[0] ) );
  CHECK_THAT( 2.277e+4, WithinRel( lvalue2.GT()[1] ) );
  CHECK_THAT( 6.058e-1, WithinRel( lvalue2.totalWidths()[0] ) );
  CHECK_THAT( 2.277e+4, WithinRel( lvalue2.totalWidths()[1] ) );
  CHECK_THAT( 5.800e-3, WithinRel( lvalue2.GN()[0] ) );
  CHECK_THAT( 2.276e+4, WithinRel( lvalue2.GN()[1] ) );
  CHECK_THAT( 5.800e-3, WithinRel( lvalue2.neutronWidths()[0] ) );
  CHECK_THAT( 2.276e+4, WithinRel( lvalue2.neutronWidths()[1] ) );
  CHECK_THAT( .6, WithinRel( lvalue2.GG()[0] ) );
  CHECK_THAT( 9.87, WithinRel( lvalue2.GG()[1] ) );
  CHECK_THAT( .6, WithinRel( lvalue2.gammaWidths()[0] ) );
  CHECK_THAT( 9.87, WithinRel( lvalue2.gammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.fissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.fissionWidths()[1] ) );
  CHECK_THAT( 100., WithinRel( lvalue2.DE2()[0] ) );
  CHECK_THAT( 130000., WithinRel( lvalue2.DE2()[1] ) );
  CHECK_THAT( 100., WithinRel( lvalue2.resonanceEnergyVariances()[0] ) );
  CHECK_THAT( 130000., WithinRel( lvalue2.resonanceEnergyVariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJ2()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJ2()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinVariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinVariances()[1] ) );
  CHECK_THAT( 9.0e-6, WithinRel( lvalue2.DN2()[0] ) );
  CHECK_THAT( 6.1e+4, WithinRel( lvalue2.DN2()[1] ) );
  CHECK_THAT( 9.0e-6, WithinRel( lvalue2.neutronWidthVariances()[0] ) );
  CHECK_THAT( 6.1e+4, WithinRel( lvalue2.neutronWidthVariances()[1] ) );
  CHECK_THAT( .09, WithinRel( lvalue2.DG2()[0] ) );
  CHECK_THAT( 2.4, WithinRel( lvalue2.DG2()[1] ) );
  CHECK_THAT( .09, WithinRel( lvalue2.gammaWidthVariances()[0] ) );
  CHECK_THAT( 2.4, WithinRel( lvalue2.gammaWidthVariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DF2()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DF2()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.fissionWidthVariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.fissionWidthVariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDN()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDN()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndNeutronWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndNeutronWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDG()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDG()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DJDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.spinAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DNDG()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DNDG()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.neutronAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.neutronAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DNDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DNDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.neutronAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.neutronAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DGDF()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.DGDF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.gammaAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 0., WithinRel( lvalue2.gammaAndFissionWidthCovariances()[1] ) );

  CHECK( 18 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.000000+0 8.930000-1          0          0          0          01025 2151     \n";
}
