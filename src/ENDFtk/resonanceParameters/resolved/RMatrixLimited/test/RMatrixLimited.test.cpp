#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ParticlePairs =
resonanceParameters::resolved::RMatrixLimited::ParticlePairs;
using SpinGroup =
resonanceParameters::resolved::RMatrixLimited::SpinGroup;
using RMatrixLimited =
resonanceParameters::resolved::RMatrixLimited;

std::string chunk();
void verifyChunk( const RMatrixLimited& );
std::string invalidSize();

SCENARIO( "RMatrixLimited" ) {

  GIVEN( "valid data for an RMatrixLimited" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      bool ifg =  false;
      bool krl = false;
      int krm = 3;
      ParticlePairs pairs = { { 0., 1. }, { 5.446635e+1, 5.347624e+1 },
                              { 0., 0. }, { 26., 26. },
                              { 1., 0.5 }, { 0., 0. },
                              { 0., 0. }, { 0., 1. },
                              { 0., 0. }, { 0, 1 },
                              { 0, 0 }, { 102, 2 } };
      std::vector< SpinGroup > groups =
        { { { 0.5, 0., { 0., 0. }, { 0., 0.5 }, { 0., 0. },
              { 0., 0.54373 }, { 0., 0.54373 } },
            { { -1.223300e+6, 7.788000e+3 },
              { { 1., 9.611086e+5 }, { 1.455, 1.187354e+3 } } } },
          { { -0.5, 0., { 0., 1. }, { 0., 0.5 }, { 0., 0. },
              { 0., 0.54373 }, { 0., 0.54373 } },
            { { 5.152000e+4, 5.359000e+4 },
              { { .36, 16.002 }, { 1.5, 17. } } } } };

      RMatrixLimited chunk( ifg, krl, krm,
                            std::move( pairs ), std::move( groups ) );

      THEN( "an RMatrixLimited can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      RMatrixLimited chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "an RMatrixLimited can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          3          2          02625 2151     \n"
    " 0.000000+0 0.000000+0          2          0         24          42625 2151     \n"
    " 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+02625 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+02625 2151     \n"
    " 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+02625 2151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+02625 2151     \n"
    " 5.000000-1 0.000000+0          0          0         12          22625 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-12625 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22625 2151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    "-5.000000-1 0.000000+0          0          0         12          22625 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-12625 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22625 2151     \n"
    " 5.152000+4 3.600000-1 1.600200+1 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 5.359000+4 1.500000+0 1.700000+1 0.000000+0 0.000000+0 0.000000+02625 2151     \n";
}

void verifyChunk( const RMatrixLimited& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 7 == chunk.LRF() );
  CHECK( 7 == chunk.representation() );

  CHECK( false == chunk.IFG() );
  CHECK( false == chunk.reducedWidths() );
  CHECK( false == chunk.KRL() );
  CHECK( false == chunk.nonRelativisticKinematics() );
  CHECK( 3 == chunk.KRM() );
  CHECK( 3 == chunk.formalism() );

  auto pairs = chunk.particlePairs();
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

  CHECK( 0. == Approx( pairs.MA()[0] ) );
  CHECK( 1. == Approx( pairs.MA()[1] ) );
  CHECK( 0 == Approx( pairs.massParticleA()[0] ) );
  CHECK( 1 == Approx( pairs.massParticleA()[1] ) );
  CHECK( 5.446635e+1 == Approx( pairs.MB()[0] ) );
  CHECK( 5.347624e+1 == Approx( pairs.MB()[1] ) );
  CHECK( 5.446635e+1 == Approx( pairs.massParticleB()[0] ) );
  CHECK( 5.347624e+1 == Approx( pairs.massParticleB()[1] ) );
  CHECK( 0. == Approx( pairs.ZA()[0] ) );
  CHECK( 0. == Approx( pairs.ZA()[1] ) );
  CHECK( 0. == Approx( pairs.chargeParticleA()[0] ) );
  CHECK( 0. == Approx( pairs.chargeParticleA()[1] ) );
  CHECK( 26. == Approx( pairs.ZB()[0] ) );
  CHECK( 26. == Approx( pairs.ZB()[1] ) );
  CHECK( 26. == Approx( pairs.chargeParticleB()[0] ) );
  CHECK( 26. == Approx( pairs.chargeParticleB()[1] ) );
  CHECK( 1. == Approx( pairs.IA()[0] ) );
  CHECK( 0.5 == Approx( pairs.IA()[1] ) );
  CHECK( 1. == Approx( pairs.spinParticleA()[0] ) );
  CHECK( 0.5 == Approx( pairs.spinParticleA()[1] ) );
  CHECK( 0. == Approx( pairs.IB()[0] ) );
  CHECK( 0. == Approx( pairs.IB()[1] ) );
  CHECK( 0. == Approx( pairs.spinParticleB()[0] ) );
  CHECK( 0. == Approx( pairs.spinParticleB()[1] ) );
  CHECK( 0. == Approx( pairs.PA()[0] ) );
  CHECK( 0. == Approx( pairs.PA()[1] ) );
  CHECK( 0. == Approx( pairs.parityParticleA()[0] ) );
  CHECK( 0. == Approx( pairs.parityParticleA()[1] ) );
  CHECK( 0. == Approx( pairs.PB()[0] ) );
  CHECK( 1. == Approx( pairs.PB()[1] ) );
  CHECK( 0. == Approx( pairs.parityParticleB()[0] ) );
  CHECK( 1. == Approx( pairs.parityParticleB()[1] ) );
  CHECK( 0. == Approx( pairs.Q()[0] ) );
  CHECK( 0. == Approx( pairs.Q()[1] ) );
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

  CHECK( 2 == chunk.NJS() );
  CHECK( 2 == chunk.numberSpinGroups() );
  CHECK( 2 == chunk.spinGroups().size() );

  auto group1 = chunk.spinGroups()[0];
  CHECK( 0.5 == Approx( group1.AJ() ) );
  CHECK( 0.5 == Approx( group1.spin() ) );
  CHECK( 0. == Approx( group1.PJ() ) );
  CHECK( 0. == Approx( group1.parity() ) );
  CHECK( 2 == group1.NCH() );
  CHECK( 2 == group1.numberChannels() );
  CHECK( 2 == group1.NRS() );
  CHECK( 2 == group1.numberResonances() );

  auto channels1 = group1.channels();
  CHECK( 0.5 == Approx( channels1.AJ() ) );
  CHECK( 0.5 == Approx( channels1.spin() ) );
  CHECK( 0. == Approx( channels1.PJ() ) );
  CHECK( 0. == Approx( channels1.parity() ) );
  CHECK( 0 == channels1.KBK() );
  CHECK( 0 == channels1.backgroundRMatrixOption() );
  CHECK( 0 == channels1.KPS() );
  CHECK( 0 == channels1.phaseShiftOption() );
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
  CHECK( 0. == Approx( channels1.L()[0] ) );
  CHECK( 0. == Approx( channels1.L()[1] ) );
  CHECK( 0. == Approx( channels1.orbitalMomentumValues()[0] ) );
  CHECK( 0. == Approx( channels1.orbitalMomentumValues()[1] ) );
  CHECK( 0. == Approx( channels1.SCH()[0] ) );
  CHECK( .5 == Approx( channels1.SCH()[1] ) );
  CHECK( 0. == Approx( channels1.channelSpinValues()[0] ) );
  CHECK( .5 == Approx( channels1.channelSpinValues()[1] ) );
  CHECK( 0. == Approx( channels1.BND()[0] ) );
  CHECK( 0. == Approx( channels1.BND()[1] ) );
  CHECK( 0. == Approx( channels1.boundaryConditionValues()[0] ) );
  CHECK( 0. == Approx( channels1.boundaryConditionValues()[1] ) );
  CHECK( 0. == Approx( channels1.APT()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels1.APT()[1] ) );
  CHECK( 0. == Approx( channels1.trueChannelRadii()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels1.trueChannelRadii()[1] ) );
  CHECK( 0. == Approx( channels1.APE()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels1.APE()[1] ) );
  CHECK( 0. == Approx( channels1.effectiveChannelRadii()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels1.effectiveChannelRadii()[1] ) );

  auto parameters1 = group1.parameters();
  CHECK( 2 == parameters1.NRS() );
  CHECK( 2 == parameters1.numberResonances() );
  CHECK( 2 == parameters1.NX() );
  CHECK( 2 == parameters1.numberLines() );

  CHECK( 2 == parameters1.ER().size() );
  CHECK( 2 == parameters1.resonanceEnergies().size() );
  CHECK( 2 == parameters1.GAM().size() );
  CHECK( 2 == parameters1.resonanceParameters().size() );

  CHECK( -1.223300e+6 == Approx( parameters1.ER()[0] ) );
  CHECK(  7.788000e+3 == Approx( parameters1.ER()[1] ) );
  CHECK( -1.223300e+6 == Approx( parameters1.resonanceEnergies()[0] ) );
  CHECK(  7.788000e+3 == Approx( parameters1.resonanceEnergies()[1] ) );
  CHECK( 5 == parameters1.GAM()[0].size() );
  CHECK( 5 == parameters1.GAM()[1].size() );
  CHECK( 1. == Approx( parameters1.GAM()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( parameters1.GAM()[0][1] ) );
  CHECK( 0. == Approx( parameters1.GAM()[0][2] ) );
  CHECK( 0. == Approx( parameters1.GAM()[0][3] ) );
  CHECK( 0. == Approx( parameters1.GAM()[0][4] ) );
  CHECK( 1.455 == Approx( parameters1.GAM()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( parameters1.GAM()[1][1] ) );
  CHECK( 0. == Approx( parameters1.GAM()[1][2] ) );
  CHECK( 0. == Approx( parameters1.GAM()[1][3] ) );
  CHECK( 0. == Approx( parameters1.GAM()[1][4] ) );
  CHECK( 5 == parameters1.resonanceParameters()[0].size() );
  CHECK( 5 == parameters1.resonanceParameters()[1].size() );
  CHECK( 1. == Approx( parameters1.resonanceParameters()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( parameters1.resonanceParameters()[0][1] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[0][2] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[0][3] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[0][4] ) );
  CHECK( 1.455 == Approx( parameters1.resonanceParameters()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( parameters1.resonanceParameters()[1][1] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[1][2] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[1][3] ) );
  CHECK( 0. == Approx( parameters1.resonanceParameters()[1][4] ) );

  auto group2 = chunk.spinGroups()[1];
  CHECK( -0.5 == Approx( group2.AJ() ) );
  CHECK( -0.5 == Approx( group2.spin() ) );
  CHECK( 0. == Approx( group2.PJ() ) );
  CHECK( 0. == Approx( group2.parity() ) );
  CHECK( 2 == group2.NCH() );
  CHECK( 2 == group2.numberChannels() );
  CHECK( 2 == group2.NRS() );
  CHECK( 2 == group2.numberResonances() );

  auto channels2 = group2.channels();
  CHECK( -0.5 == Approx( channels2.AJ() ) );
  CHECK( -0.5 == Approx( channels2.spin() ) );
  CHECK( 0. == Approx( channels2.PJ() ) );
  CHECK( 0. == Approx( channels2.parity() ) );
  CHECK( 0 == channels2.KBK() );
  CHECK( 0 == channels2.backgroundRMatrixOption() );
  CHECK( 0 == channels2.KPS() );
  CHECK( 0 == channels2.phaseShiftOption() );
  CHECK( 2 == channels2.NCH() );
  CHECK( 2 == channels2.numberChannels() );

  CHECK( 2 == channels2.PPI().size() );
  CHECK( 2 == channels2.particlePairNumbers().size() );
  CHECK( 2 == channels2.L().size() );
  CHECK( 2 == channels2.orbitalMomentumValues().size() );
  CHECK( 2 == channels2.SCH().size() );
  CHECK( 2 == channels2.channelSpinValues().size() );
  CHECK( 2 == channels2.BND().size() );
  CHECK( 2 == channels2.boundaryConditionValues().size() );
  CHECK( 2 == channels2.APT().size() );
  CHECK( 2 == channels2.trueChannelRadii().size() );
  CHECK( 2 == channels2.APE().size() );
  CHECK( 2 == channels2.effectiveChannelRadii().size() );

  CHECK( 1 == channels2.PPI()[0] );
  CHECK( 2 == channels2.PPI()[1] );
  CHECK( 1 == channels2.particlePairNumbers()[0] );
  CHECK( 2 == channels2.particlePairNumbers()[1] );
  CHECK( 0. == Approx( channels2.L()[0] ) );
  CHECK( 1. == Approx( channels2.L()[1] ) );
  CHECK( 0. == Approx( channels2.orbitalMomentumValues()[0] ) );
  CHECK( 1. == Approx( channels2.orbitalMomentumValues()[1] ) );
  CHECK( 0. == Approx( channels2.SCH()[0] ) );
  CHECK( .5 == Approx( channels2.SCH()[1] ) );
  CHECK( 0. == Approx( channels2.channelSpinValues()[0] ) );
  CHECK( .5 == Approx( channels2.channelSpinValues()[1] ) );
  CHECK( 0. == Approx( channels2.BND()[0] ) );
  CHECK( 0. == Approx( channels2.BND()[1] ) );
  CHECK( 0. == Approx( channels2.boundaryConditionValues()[0] ) );
  CHECK( 0. == Approx( channels2.boundaryConditionValues()[1] ) );
  CHECK( 0. == Approx( channels2.APT()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels2.APT()[1] ) );
  CHECK( 0. == Approx( channels2.trueChannelRadii()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels2.trueChannelRadii()[1] ) );
  CHECK( 0. == Approx( channels2.APE()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels2.APE()[1] ) );
  CHECK( 0. == Approx( channels2.effectiveChannelRadii()[0] ) );
  CHECK( 5.437300e-1 == Approx( channels2.effectiveChannelRadii()[1] ) );

  auto parameters2 = group2.parameters();
  CHECK( 2 == parameters2.NRS() );
  CHECK( 2 == parameters2.numberResonances() );
  CHECK( 2 == parameters2.NX() );
  CHECK( 2 == parameters2.numberLines() );

  CHECK( 2 == parameters2.ER().size() );
  CHECK( 2 == parameters2.resonanceEnergies().size() );
  CHECK( 2 == parameters2.GAM().size() );
  CHECK( 2 == parameters2.resonanceParameters().size() );

  CHECK( 5.152000e+4 == Approx( parameters2.ER()[0] ) );
  CHECK( 5.359000e+4 == Approx( parameters2.ER()[1] ) );
  CHECK( 5.152000e+4 == Approx( parameters2.resonanceEnergies()[0] ) );
  CHECK( 5.359000e+4 == Approx( parameters2.resonanceEnergies()[1] ) );
  CHECK( 5 == parameters2.GAM()[0].size() );
  CHECK( 5 == parameters2.GAM()[1].size() );
  CHECK( .36 == Approx( parameters2.GAM()[0][0] ) );
  CHECK( 16.002 == Approx( parameters2.GAM()[0][1] ) );
  CHECK( 0. == Approx( parameters2.GAM()[0][2] ) );
  CHECK( 0. == Approx( parameters2.GAM()[0][3] ) );
  CHECK( 0. == Approx( parameters2.GAM()[0][4] ) );
  CHECK( 1.5 == Approx( parameters2.GAM()[1][0] ) );
  CHECK( 17. == Approx( parameters2.GAM()[1][1] ) );
  CHECK( 0. == Approx( parameters2.GAM()[1][2] ) );
  CHECK( 0. == Approx( parameters2.GAM()[1][3] ) );
  CHECK( 0. == Approx( parameters2.GAM()[1][4] ) );
  CHECK( 5 == parameters2.resonanceParameters()[0].size() );
  CHECK( 5 == parameters2.resonanceParameters()[1].size() );
  CHECK( .36 == Approx( parameters2.resonanceParameters()[0][0] ) );
  CHECK( 16.002 == Approx( parameters2.resonanceParameters()[0][1] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[0][2] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[0][3] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[0][4] ) );
  CHECK( 1.5 == Approx( parameters2.resonanceParameters()[1][0] ) );
  CHECK( 17. == Approx( parameters2.resonanceParameters()[1][1] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[1][2] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[1][3] ) );
  CHECK( 0. == Approx( parameters2.resonanceParameters()[1][4] ) );

  CHECK( 18 == chunk.NC() );
}
