// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactRMatrixLimited =
section::Type< 32, 151 >::CompactRMatrixLimited;
using CompactRMatrixLimitedUncertainties =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties;
using ParticlePairs =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ParticlePairs;
using ResonanceParameters =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ResonanceParameters;
using ResonanceChannels =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ResonanceChannels;
using SpinGroup =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::SpinGroup;
using CompactCorrelationMatrix =
section::Type< 32, 151 >::CompactCorrelationMatrix;

std::string chunk();
void verifyChunk( const CompactRMatrixLimited& );

SCENARIO( "CompactCorrelationMatrix" ) {

  GIVEN( "valid data for a CompactCorrelationMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      bool ifg = false;

      CompactRMatrixLimitedUncertainties parameters(
          ParticlePairs( 1,
                         { 0., 1. }, { 65.37, 64.37 }, { 0., 0. }, { 0., 0. },
                         { 1., 0.5 }, { 0., -1.5 }, { 0., 0. }, { 0., 0. },
                         { 0., 0. }, { 0, 1 }, { 0, 0 }, { 102, 2 } ),
          { SpinGroup(
              ResonanceChannels( -1., 0.,
                                 { 1, 2 }, { 0, 0 }, { 0., 1. },
                                 { 0., 0. }, { 0., 0.67 } ),
              ResonanceParameters( { -1.535904e+3, 1.363096e+3,
                                      2.648648e+3, 3.585385e+3 },
                                   { { 3.950000e-1, 2.943392e+2 },
                                     { 3.950000e-1, 2.778162e-2 },
                                     { 3.950000e-1, 2.358290e-3 },
                                     { 3.950000e-1, 5.706056e-2 } },
                                   { 1.377556e+1, 4.389417e+0,
                                     1.889408e+1, 6.799781e+0 },
                                   { { 8.403206e-6, 1.026766e-3 },
                                     { 2.802750e-3, 1.169698e-4 },
                                     { 4.333117e-3, 2.987095e-5 },
                                     { 4.163289e-2, 3.271682e-4 } } ) ) } );

      CompactCorrelationMatrix matrix(
          12,
          { 2, 3, 3, 5, 5, 5, 6, 6, 6, 8,
            8, 8, 8, 9, 9, 9, 9 },
          { 1, 1, 2, 1, 2, 4, 3, 4, 5, 1,
            2, 3, 7, 1, 2, 7, 8 },
          { -795e-3, -945e-3, 665e-3, 15e-3, -25e-3, -25e-3, -15e-3,
              25e-3, -595e-3, -15e-3, 25e-3, 15e-3, -55e-3, -15e-3,
              15e-3, -65e-3, 165e-3 }, 2 );

      CompactRMatrixLimited chunk( ifg,
                                   std::move( parameters ),
                                   std::move( matrix ) );

      THEN( "a CompactRMatrixLimited can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2931, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CompactRMatrixLimited chunk( begin, end, lineNumber, 2931, 32, 151 );

      THEN( "a CompactCorrelationMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2931, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          2          1          0293132151     \n"
    " 0.000000+0 0.000000+0          2          1         24          4293132151     \n"
    " 0.000000+0 6.537000+1 0.000000+0 0.000000+0 1.000000+0 0.000000+0293132151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0293132151     \n"
    " 1.000000+0 6.437000+1 0.000000+0 0.000000+0 5.000000-1-1.500000+0293132151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 0.000000+0293132151     \n"
    "-1.000000+0 0.000000+0          0          0         12          2293132151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 2.000000+0 0.000000+0 1.000000+0 0.000000+0 6.700000-1 6.700000-1293132151     \n"
    " 0.000000+0 0.000000+0          0          4         48          4293132151     \n"
    "-1.535904+3 3.950000-1 2.943392+2 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 1.377556+1 8.403206-6 1.026766-3 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 1.363096+3 3.950000-1 2.778162-2 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 4.389417+0 2.802750-3 1.169698-4 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 2.648648+3 3.950000-1 2.358290-3 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 1.889408+1 4.333117-3 2.987095-5 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 3.585385+3 3.950000-1 5.706056-2 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 6.799781+0 4.163289-2 3.271682-4 0.000000+0 0.000000+0 0.000000+0293132151     \n"
    " 0.000000+0 0.000000+0          2         12          6          0293132151     \n"
    "    2    1 -79                                                    293132151     \n"
    "    3    1 -94 66                                                 293132151     \n"
    "    5    1   1 -2  0 -2                                           293132151     \n"
    "    6    3  -1  2-59                                              293132151     \n"
    "    8    1  -1  2  1  0  0  0 -5                                  293132151     \n"
    "    9    1  -1  1  0  0  0  0 -6 16                               293132151     \n";
}

void verifyChunk( const CompactRMatrixLimited& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 7 == chunk.LRF() );
  CHECK( 7 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 2 == chunk.LCOMP() );
  CHECK( 2 == chunk.covarianceRepresentation() );

  CHECK( false == chunk.IFG() );
  CHECK( false == chunk.reducedWidths() );

  CHECK( std::nullopt == chunk.DAP() );
  CHECK( std::nullopt == chunk.scatteringRadiusUncertainty() );

  auto pairs = chunk.uncertainties().particlePairs();
  CHECK( 1 == pairs.NJSX() );
  CHECK( 1 == pairs.numberSpinGroups() );
  CHECK( 2 == pairs.NPP() );
  CHECK( 2 == pairs.numberParticlePairs() );
  CHECK( 2 == pairs.MA().size() );
  CHECK( 2 == pairs.massParticleA().size() );
  CHECK( 2 == pairs.MB().size() );
  CHECK( 2 == pairs.massParticleB().size() );
  CHECK( 2 == pairs.ZA().size() );
  CHECK( 2 == pairs.chargeParticleA().size() );
  CHECK( 2 == pairs.ZB().size() );
  CHECK( 2 == pairs.chargeParticleB().size() );
  CHECK( 2 == pairs.IA().size() );
  CHECK( 2 == pairs.spinParticleA().size() );
  CHECK( 2 == pairs.IB().size() );
  CHECK( 2 == pairs.spinParticleB().size() );
  CHECK( 2 == pairs.PA().size() );
  CHECK( 2 == pairs.parityParticleA().size() );
  CHECK( 2 == pairs.PB().size() );
  CHECK( 2 == pairs.parityParticleB().size() );
  CHECK( 2 == pairs.Q().size() );
  CHECK( 2 == pairs.PNT().size() );
  CHECK( 2 == pairs.penetrabilityFlag().size() );
  CHECK( 2 == pairs.SHF().size() );
  CHECK( 2 == pairs.shiftFactorFlag().size() );
  CHECK( 2 == pairs.MT().size() );

  CHECK_THAT( 0., WithinRel( pairs.MA()[0] ) );
  CHECK_THAT( 1., WithinRel( pairs.MA()[1] ) );
  CHECK_THAT( 0, WithinRel( pairs.massParticleA()[0] ) );
  CHECK_THAT( 1, WithinRel( pairs.massParticleA()[1] ) );
  CHECK_THAT( 65.37, WithinRel( pairs.MB()[0] ) );
  CHECK_THAT( 64.37, WithinRel( pairs.MB()[1] ) );
  CHECK_THAT( 65.37, WithinRel( pairs.massParticleB()[0] ) );
  CHECK_THAT( 64.37, WithinRel( pairs.massParticleB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleB()[1] ) );
  CHECK_THAT( 1., WithinRel( pairs.IA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pairs.IA()[1] ) );
  CHECK_THAT( 1., WithinRel( pairs.spinParticleA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pairs.spinParticleA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.IB()[0] ) );
  CHECK_THAT( -1.5, WithinRel( pairs.IB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.spinParticleB()[0] ) );
  CHECK_THAT( -1.5, WithinRel( pairs.spinParticleB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.PA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.PA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.PB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.PB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.Q()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.Q()[1] ) );
  CHECK( 0 == pairs.PNT()[0] );
  CHECK( 1 == pairs.PNT()[1] );
  CHECK( 0 == pairs.penetrabilityFlag()[0] );
  CHECK( 1 == pairs.penetrabilityFlag()[1] );
  CHECK( 0 == pairs.SHF()[0] );
  CHECK( 0 == pairs.SHF()[1] );
  CHECK( 0 == pairs.shiftFactorFlag()[0] );
  CHECK( 0 == pairs.shiftFactorFlag()[1] );
  CHECK( 102 == pairs.MT()[0] );
  CHECK( 2 == pairs.MT()[1] );
  CHECK( 1 == chunk.uncertainties().NJSX() );
  CHECK( 1 == chunk.uncertainties().numberSpinGroups() );
  CHECK( 1 == chunk.uncertainties().spinGroups().size() );

  auto group1 = chunk.uncertainties().spinGroups()[0];
  CHECK_THAT( -1., WithinRel( group1.AJ() ) );
  CHECK_THAT( -1., WithinRel( group1.spin() ) );
  CHECK_THAT( 0., WithinRel( group1.PJ() ) );
  CHECK_THAT( 0., WithinRel( group1.parity() ) );
  CHECK( 2 == group1.NCH() );
  CHECK( 2 == group1.numberChannels() );
  CHECK( 4 == group1.NRSA() );
  CHECK( 4 == group1.numberResonances() );

  auto channels1 = group1.channels();
  CHECK_THAT( -1., WithinRel( channels1.AJ() ) );
  CHECK_THAT( -1., WithinRel( channels1.spin() ) );
  CHECK_THAT( 0., WithinRel( channels1.PJ() ) );
  CHECK_THAT( 0., WithinRel( channels1.parity() ) );
  CHECK( 2 == channels1.NCH() );
  CHECK( 2 == channels1.numberChannels() );

  CHECK( 2 == channels1.PPI().size() );
  CHECK( 2 == channels1.particlePairNumbers().size() );
  CHECK( 2 == channels1.L().size() );
  CHECK( 2 == channels1.orbitalMomentumValues().size() );
  CHECK( 2 == channels1.SCH().size() );
  CHECK( 2 == channels1.channelSpinValues().size() );
  CHECK( 2 == channels1.BND().size() );
  CHECK( 2 == channels1.boundaryConditionValues().size() );
  CHECK( 2 == channels1.APT().size() );
  CHECK( 2 == channels1.trueChannelRadii().size() );
  CHECK( 2 == channels1.APE().size() );
  CHECK( 2 == channels1.effectiveChannelRadii().size() );

  CHECK( 1 == channels1.PPI()[0] );
  CHECK( 2 == channels1.PPI()[1] );
  CHECK( 1 == channels1.particlePairNumbers()[0] );
  CHECK( 2 == channels1.particlePairNumbers()[1] );
  CHECK( 0 == channels1.L()[0] );
  CHECK( 0 == channels1.L()[1] );
  CHECK( 0. == channels1.orbitalMomentumValues()[0] );
  CHECK( 0. == channels1.orbitalMomentumValues()[1] );
  CHECK_THAT( 0., WithinRel( channels1.SCH()[0] ) );
  CHECK_THAT( 1., WithinRel( channels1.SCH()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.channelSpinValues()[0] ) );
  CHECK_THAT( 1., WithinRel( channels1.channelSpinValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.BND()[0] ) );
  CHECK_THAT( 0., WithinRel( channels1.BND()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.boundaryConditionValues()[0] ) );
  CHECK_THAT( 0., WithinRel( channels1.boundaryConditionValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.APT()[0] ) );
  CHECK_THAT( 0.67, WithinRel( channels1.APT()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.trueChannelRadii()[0] ) );
  CHECK_THAT( 0.67, WithinRel( channels1.trueChannelRadii()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.APE()[0] ) );
  CHECK_THAT( 0.67, WithinRel( channels1.APE()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.effectiveChannelRadii()[0] ) );
  CHECK_THAT( 0.67, WithinRel( channels1.effectiveChannelRadii()[1] ) );

  auto parameters1 = group1.parameters();
  CHECK( 4 == parameters1.NRSA() );
  CHECK( 4 == parameters1.numberResonances() );
  CHECK( 4 == parameters1.NX() );
  CHECK( 4 == parameters1.numberLines() );

  CHECK( 4 == parameters1.ER().size() );
  CHECK( 4 == parameters1.resonanceEnergies().size() );
  CHECK( 4 == parameters1.GAM().size() );
  CHECK( 4 == parameters1.resonanceParameters().size() );
  CHECK( 4 == parameters1.DER().size() );
  CHECK( 4 == parameters1.resonanceEnergyUncertainties().size() );
  CHECK( 4 == parameters1.DGAM().size() );
  CHECK( 4 == parameters1.resonanceParameterUncertainties().size() );

  CHECK_THAT( -1.535904e+3, WithinRel( parameters1.ER()[0] ) );
  CHECK_THAT(  1.363096e+3, WithinRel( parameters1.ER()[1] ) );
  CHECK_THAT(  2.648648e+3, WithinRel( parameters1.ER()[2] ) );
  CHECK_THAT(  3.585385e+3, WithinRel( parameters1.ER()[3] ) );
  CHECK_THAT( -1.535904e+3, WithinRel( parameters1.resonanceEnergies()[0] ) );
  CHECK_THAT(  1.363096e+3, WithinRel( parameters1.resonanceEnergies()[1] ) );
  CHECK_THAT(  2.648648e+3, WithinRel( parameters1.resonanceEnergies()[2] ) );
  CHECK_THAT(  3.585385e+3, WithinRel( parameters1.resonanceEnergies()[3] ) );
  CHECK( 5 == parameters1.GAM()[0].size() );
  CHECK( 5 == parameters1.GAM()[1].size() );
  CHECK( 5 == parameters1.GAM()[2].size() );
  CHECK( 5 == parameters1.GAM()[3].size() );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.GAM()[0][0] ) );
  CHECK_THAT( 2.943392e+2, WithinRel( parameters1.GAM()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.GAM()[1][0] ) );
  CHECK_THAT( 2.778162e-2, WithinRel( parameters1.GAM()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.GAM()[2][0] ) );
  CHECK_THAT( 2.358290e-3, WithinRel( parameters1.GAM()[2][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[2][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[2][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[2][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.GAM()[3][0] ) );
  CHECK_THAT( 5.706056e-2, WithinRel( parameters1.GAM()[3][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[3][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[3][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[3][4] ) );
  CHECK( 5 == parameters1.resonanceParameters()[0].size() );
  CHECK( 5 == parameters1.resonanceParameters()[1].size() );
  CHECK( 5 == parameters1.resonanceParameters()[2].size() );
  CHECK( 5 == parameters1.resonanceParameters()[3].size() );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.resonanceParameters()[0][0] ) );
  CHECK_THAT( 2.943392e+2, WithinRel( parameters1.resonanceParameters()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.resonanceParameters()[1][0] ) );
  CHECK_THAT( 2.778162e-2, WithinRel( parameters1.resonanceParameters()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.resonanceParameters()[2][0] ) );
  CHECK_THAT( 2.358290e-3, WithinRel( parameters1.resonanceParameters()[2][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[2][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[2][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[2][4] ) );
  CHECK_THAT( 3.950000e-1, WithinRel( parameters1.resonanceParameters()[3][0] ) );
  CHECK_THAT( 5.706056e-2, WithinRel( parameters1.resonanceParameters()[3][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[3][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[3][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[3][4] ) );

  CHECK_THAT( 1.377556e+1, WithinRel( parameters1.DER()[0] ) );
  CHECK_THAT( 4.389417e+0, WithinRel( parameters1.DER()[1] ) );
  CHECK_THAT( 1.889408e+1, WithinRel( parameters1.DER()[2] ) );
  CHECK_THAT( 6.799781e+0, WithinRel( parameters1.DER()[3] ) );
  CHECK_THAT( 1.377556e+1, WithinRel( parameters1.resonanceEnergyUncertainties()[0] ) );
  CHECK_THAT( 4.389417e+0, WithinRel( parameters1.resonanceEnergyUncertainties()[1] ) );
  CHECK_THAT( 1.889408e+1, WithinRel( parameters1.resonanceEnergyUncertainties()[2] ) );
  CHECK_THAT( 6.799781e+0, WithinRel( parameters1.resonanceEnergyUncertainties()[3] ) );
  CHECK( 5 == parameters1.DGAM()[0].size() );
  CHECK( 5 == parameters1.DGAM()[1].size() );
  CHECK( 5 == parameters1.DGAM()[2].size() );
  CHECK( 5 == parameters1.DGAM()[3].size() );
  CHECK_THAT( 8.403206e-6, WithinRel( parameters1.DGAM()[0][0] ) );
  CHECK_THAT( 1.026766e-3, WithinRel( parameters1.DGAM()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][4] ) );
  CHECK_THAT( 2.802750e-3, WithinRel( parameters1.DGAM()[1][0] ) );
  CHECK_THAT( 1.169698e-4, WithinRel( parameters1.DGAM()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][4] ) );
  CHECK_THAT( 4.333117e-3, WithinRel( parameters1.DGAM()[2][0] ) );
  CHECK_THAT( 2.987095e-5, WithinRel( parameters1.DGAM()[2][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[2][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[2][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[2][4] ) );
  CHECK_THAT( 4.163289e-2, WithinRel( parameters1.DGAM()[3][0] ) );
  CHECK_THAT( 3.271682e-4, WithinRel( parameters1.DGAM()[3][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[3][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[3][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[3][4] ) );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[0].size() );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[1].size() );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[2].size() );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[3].size() );
  CHECK_THAT( 8.403206e-6, WithinRel( parameters1.resonanceParameterUncertainties()[0][0] ) );
  CHECK_THAT( 1.026766e-3, WithinRel( parameters1.resonanceParameterUncertainties()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][4] ) );
  CHECK_THAT( 2.802750e-3, WithinRel( parameters1.resonanceParameterUncertainties()[1][0] ) );
  CHECK_THAT( 1.169698e-4, WithinRel( parameters1.resonanceParameterUncertainties()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][4] ) );
  CHECK_THAT( 4.333117e-3, WithinRel( parameters1.resonanceParameterUncertainties()[2][0] ) );
  CHECK_THAT( 2.987095e-5, WithinRel( parameters1.resonanceParameterUncertainties()[2][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[2][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[2][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[2][4] ) );
  CHECK_THAT( 4.163289e-2, WithinRel( parameters1.resonanceParameterUncertainties()[3][0] ) );
  CHECK_THAT( 3.271682e-4, WithinRel( parameters1.resonanceParameterUncertainties()[3][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[3][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[3][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[3][4] ) );

  CHECK( 2 == chunk.correlationMatrix().NDIGIT() );
  CHECK( 2 == chunk.correlationMatrix().numberDigits() );
  CHECK( 12 == chunk.correlationMatrix().NNN() );
  CHECK( 12 == chunk.correlationMatrix().order() );
  CHECK( 17 == chunk.correlationMatrix().I().size() );
  CHECK( 17 == chunk.correlationMatrix().J().size() );
  CHECK( 17 == chunk.correlationMatrix().correlations().size() );

  CHECK( 2 == chunk.correlationMatrix().I()[0] );
  CHECK( 3 == chunk.correlationMatrix().I()[1] );
  CHECK( 3 == chunk.correlationMatrix().I()[2] );
  CHECK( 5 == chunk.correlationMatrix().I()[3] );
  CHECK( 5 == chunk.correlationMatrix().I()[4] );
  CHECK( 5 == chunk.correlationMatrix().I()[5] );
  CHECK( 6 == chunk.correlationMatrix().I()[6] );
  CHECK( 6 == chunk.correlationMatrix().I()[7] );
  CHECK( 6 == chunk.correlationMatrix().I()[8] );
  CHECK( 8 == chunk.correlationMatrix().I()[9] );
  CHECK( 8 == chunk.correlationMatrix().I()[10] );
  CHECK( 8 == chunk.correlationMatrix().I()[11] );
  CHECK( 8 == chunk.correlationMatrix().I()[12] );
  CHECK( 9 == chunk.correlationMatrix().I()[13] );
  CHECK( 9 == chunk.correlationMatrix().I()[14] );
  CHECK( 9 == chunk.correlationMatrix().I()[15] );
  CHECK( 9 == chunk.correlationMatrix().I()[16] );

  CHECK( 1 == chunk.correlationMatrix().J()[0] );
  CHECK( 1 == chunk.correlationMatrix().J()[1] );
  CHECK( 2 == chunk.correlationMatrix().J()[2] );
  CHECK( 1 == chunk.correlationMatrix().J()[3] );
  CHECK( 2 == chunk.correlationMatrix().J()[4] );
  CHECK( 4 == chunk.correlationMatrix().J()[5] );
  CHECK( 3 == chunk.correlationMatrix().J()[6] );
  CHECK( 4 == chunk.correlationMatrix().J()[7] );
  CHECK( 5 == chunk.correlationMatrix().J()[8] );
  CHECK( 1 == chunk.correlationMatrix().J()[9] );
  CHECK( 2 == chunk.correlationMatrix().J()[10] );
  CHECK( 3 == chunk.correlationMatrix().J()[11] );
  CHECK( 7 == chunk.correlationMatrix().J()[12] );
  CHECK( 1 == chunk.correlationMatrix().J()[13] );
  CHECK( 2 == chunk.correlationMatrix().J()[14] );
  CHECK( 7 == chunk.correlationMatrix().J()[15] );
  CHECK( 8 == chunk.correlationMatrix().J()[16] );

  CHECK_THAT( -795e-3, WithinRel( chunk.correlationMatrix().correlations()[0] ) );
  CHECK_THAT( -945e-3, WithinRel( chunk.correlationMatrix().correlations()[1] ) );
  CHECK_THAT(  665e-3, WithinRel( chunk.correlationMatrix().correlations()[2] ) );
  CHECK_THAT(   15e-3, WithinRel( chunk.correlationMatrix().correlations()[3] ) );
  CHECK_THAT(  -25e-3, WithinRel( chunk.correlationMatrix().correlations()[4] ) );
  CHECK_THAT(  -25e-3, WithinRel( chunk.correlationMatrix().correlations()[5] ) );
  CHECK_THAT(  -15e-3, WithinRel( chunk.correlationMatrix().correlations()[6] ) );
  CHECK_THAT(   25e-3, WithinRel( chunk.correlationMatrix().correlations()[7] ) );
  CHECK_THAT( -595e-3, WithinRel( chunk.correlationMatrix().correlations()[8] ) );
  CHECK_THAT(  -15e-3, WithinRel( chunk.correlationMatrix().correlations()[9] ) );
  CHECK_THAT(   25e-3, WithinRel( chunk.correlationMatrix().correlations()[10] ) );
  CHECK_THAT(   15e-3, WithinRel( chunk.correlationMatrix().correlations()[11] ) );
  CHECK_THAT(  -55e-3, WithinRel( chunk.correlationMatrix().correlations()[12] ) );
  CHECK_THAT(  -15e-3, WithinRel( chunk.correlationMatrix().correlations()[13] ) );
  CHECK_THAT(   15e-3, WithinRel( chunk.correlationMatrix().correlations()[14] ) );
  CHECK_THAT(  -65e-3, WithinRel( chunk.correlationMatrix().correlations()[15] ) );
  CHECK_THAT(  165e-3, WithinRel( chunk.correlationMatrix().correlations()[16] ) );

  CHECK( 25 == chunk.NC() );
}
