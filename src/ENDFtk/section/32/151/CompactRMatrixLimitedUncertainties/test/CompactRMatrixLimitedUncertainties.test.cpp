// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ParticlePairs =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ParticlePairs;
using SpinGroup =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::SpinGroup;
using CompactRMatrixLimitedUncertainties =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties;

std::string chunk();
void verifyChunk( const CompactRMatrixLimitedUncertainties& );
std::string chunkWithoutSpinGroups();

SCENARIO( "CompactRMatrixLimitedUncertainties" ) {

  GIVEN( "valid data for an CompactRMatrixLimitedUncertainties" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      ParticlePairs pairs = { 2,
                              { 0., 1. }, { 5.446635e+1, 5.347624e+1 },
                              { 0., 0. }, { 26., 26. },
                              { 1., 0.5 }, { 0., 0. },
                              { 0., 0. }, { 0., 1. },
                              { 0., 0. }, { 0, 1 },
                              { 0, 0 }, { 102, 2 } };
      std::vector< SpinGroup > groups =
        { { { 0.5, 0., { 1, 2 }, { 0, 0 }, { 0., 0.5 }, { 0., 0. },
              { 0., 0.54373 }, { 0., 0.54373 } },
            { { -1.223300e+6, 7.788000e+3 },
              { { 1., 9.611086e+5 }, { 1.455, 1.187354e+3 } },
              { 1., 2. },
              { { 3., 4. }, { 5., 6. } } } },
          { { -0.5, 0., { 1, 2 }, { 0, 1 }, { 0., 0.5 }, { 0., 0. },
              { 0., 0.54373 }, { 0., 0.54373 } },
            { { 5.152000e+4, 5.359000e+4 },
              { { .36, 16.002 }, { 1.5, 17. } },
              { 7., 8. },
              { { 9., 10. }, { 11., 12. } } } } };

      CompactRMatrixLimitedUncertainties chunk( std::move( pairs ),
                                                std::move( groups ) );

      THEN( "an CompactRMatrixLimitedUncertainties can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CompactRMatrixLimitedUncertainties chunk( begin, end, lineNumber,
                                                2625, 32, 151, 2 );

      THEN( "an CompactRMatrixLimitedUncertainties can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "no spin groups are given" ) {

      ParticlePairs pairs = { 0,
                              { 0., 1. }, { 5.446635e+1, 5.347624e+1 },
                              { 0., 0. }, { 26., 26. },
                              { 1., 0.5 }, { 0., 0. },
                              { 0., 0. }, { 0., 1. },
                              { 0., 0. }, { 0, 1 },
                              { 0, 0 }, { 102, 2 } };
      std::vector< SpinGroup > groups = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactRMatrixLimitedUncertainties( std::move( pairs ),
                                                          std::move( groups ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no spin groups is used" ) {

      std::string string = chunkWithoutSpinGroups();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactRMatrixLimitedUncertainties( begin, end, lineNumber,
                                                          2625, 2, 151, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          2         24          4262532151     \n"
    " 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+0262532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0262532151     \n"
    " 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+0262532151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+0262532151     \n"
    " 5.000000-1 0.000000+0          0          0         12          2262532151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n"
    " 0.000000+0 0.000000+0          0          2         24          2262532151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 1.000000+0 3.000000+0 4.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 5.000000+0 6.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    "-5.000000-1 0.000000+0          0          0         12          2262532151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n"
    " 0.000000+0 0.000000+0          0          2         24          2262532151     \n"
    " 5.152000+4 3.600000-1 1.600200+1 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 7.000000+0 9.000000+0 1.000000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 5.359000+4 1.500000+0 1.700000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 8.000000+0 1.100000+1 1.200000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n";
}

void verifyChunk( const CompactRMatrixLimitedUncertainties& chunk ) {

  auto pairs = chunk.particlePairs();
  CHECK( 2 == pairs.NJSX() );
  CHECK( 2 == pairs.numberSpinGroups() );
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
  CHECK_THAT( 5.446635e+1, WithinRel( pairs.MB()[0] ) );
  CHECK_THAT( 5.347624e+1, WithinRel( pairs.MB()[1] ) );
  CHECK_THAT( 5.446635e+1, WithinRel( pairs.massParticleB()[0] ) );
  CHECK_THAT( 5.347624e+1, WithinRel( pairs.massParticleB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.ZA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.chargeParticleA()[1] ) );
  CHECK_THAT( 26., WithinRel( pairs.ZB()[0] ) );
  CHECK_THAT( 26., WithinRel( pairs.ZB()[1] ) );
  CHECK_THAT( 26., WithinRel( pairs.chargeParticleB()[0] ) );
  CHECK_THAT( 26., WithinRel( pairs.chargeParticleB()[1] ) );
  CHECK_THAT( 1., WithinRel( pairs.IA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pairs.IA()[1] ) );
  CHECK_THAT( 1., WithinRel( pairs.spinParticleA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pairs.spinParticleA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.IB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.IB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.spinParticleB()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.spinParticleB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.PA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.PA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleA()[0] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleA()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.PB()[0] ) );
  CHECK_THAT( 1., WithinRel( pairs.PB()[1] ) );
  CHECK_THAT( 0., WithinRel( pairs.parityParticleB()[0] ) );
  CHECK_THAT( 1., WithinRel( pairs.parityParticleB()[1] ) );
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

  CHECK( 2 == chunk.NJSX() );
  CHECK( 2 == chunk.numberSpinGroups() );
  CHECK( 2 == chunk.spinGroups().size() );

  auto group1 = chunk.spinGroups()[0];
  CHECK_THAT( 0.5, WithinRel( group1.AJ() ) );
  CHECK_THAT( 0.5, WithinRel( group1.spin() ) );
  CHECK_THAT( 0., WithinRel( group1.PJ() ) );
  CHECK_THAT( 0., WithinRel( group1.parity() ) );
  CHECK( 2 == group1.NCH() );
  CHECK( 2 == group1.numberChannels() );
  CHECK( 2 == group1.NRSA() );
  CHECK( 2 == group1.numberResonances() );

  auto channels1 = group1.channels();
  CHECK_THAT( 0.5, WithinRel( channels1.AJ() ) );
  CHECK_THAT( 0.5, WithinRel( channels1.spin() ) );
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
  CHECK_THAT( .5, WithinRel( channels1.SCH()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.channelSpinValues()[0] ) );
  CHECK_THAT( .5, WithinRel( channels1.channelSpinValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.BND()[0] ) );
  CHECK_THAT( 0., WithinRel( channels1.BND()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.boundaryConditionValues()[0] ) );
  CHECK_THAT( 0., WithinRel( channels1.boundaryConditionValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.APT()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels1.APT()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.trueChannelRadii()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels1.trueChannelRadii()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.APE()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels1.APE()[1] ) );
  CHECK_THAT( 0., WithinRel( channels1.effectiveChannelRadii()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels1.effectiveChannelRadii()[1] ) );

  auto parameters1 = group1.parameters();
  CHECK( 2 == parameters1.NRSA() );
  CHECK( 2 == parameters1.numberResonances() );
  CHECK( 2 == parameters1.NX() );
  CHECK( 2 == parameters1.numberLines() );

  CHECK( 2 == parameters1.ER().size() );
  CHECK( 2 == parameters1.resonanceEnergies().size() );
  CHECK( 2 == parameters1.GAM().size() );
  CHECK( 2 == parameters1.resonanceParameters().size() );
  CHECK( 2 == parameters1.DER().size() );
  CHECK( 2 == parameters1.resonanceEnergyUncertainties().size() );
  CHECK( 2 == parameters1.DGAM().size() );
  CHECK( 2 == parameters1.resonanceParameterUncertainties().size() );

  CHECK_THAT( -1.223300e+6, WithinRel( parameters1.ER()[0] ) );
  CHECK_THAT(  7.788000e+3, WithinRel( parameters1.ER()[1] ) );
  CHECK_THAT( -1.223300e+6, WithinRel( parameters1.resonanceEnergies()[0] ) );
  CHECK_THAT(  7.788000e+3, WithinRel( parameters1.resonanceEnergies()[1] ) );
  CHECK( 5 == parameters1.GAM()[0].size() );
  CHECK( 5 == parameters1.GAM()[1].size() );
  CHECK_THAT( 1., WithinRel( parameters1.GAM()[0][0] ) );
  CHECK_THAT( 9.611086e+5, WithinRel( parameters1.GAM()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[0][4] ) );
  CHECK_THAT( 1.455, WithinRel( parameters1.GAM()[1][0] ) );
  CHECK_THAT( 1.187354e+3, WithinRel( parameters1.GAM()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.GAM()[1][4] ) );
  CHECK( 5 == parameters1.resonanceParameters()[0].size() );
  CHECK( 5 == parameters1.resonanceParameters()[1].size() );
  CHECK_THAT( 1., WithinRel( parameters1.resonanceParameters()[0][0] ) );
  CHECK_THAT( 9.611086e+5, WithinRel( parameters1.resonanceParameters()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[0][4] ) );
  CHECK_THAT( 1.455, WithinRel( parameters1.resonanceParameters()[1][0] ) );
  CHECK_THAT( 1.187354e+3, WithinRel( parameters1.resonanceParameters()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameters()[1][4] ) );

  CHECK_THAT( 1., WithinRel( parameters1.DER()[0] ) );
  CHECK_THAT( 2., WithinRel( parameters1.DER()[1] ) );
  CHECK_THAT( 1., WithinRel( parameters1.resonanceEnergyUncertainties()[0] ) );
  CHECK_THAT( 2., WithinRel( parameters1.resonanceEnergyUncertainties()[1] ) );
  CHECK( 5 == parameters1.DGAM()[0].size() );
  CHECK( 5 == parameters1.DGAM()[1].size() );
  CHECK_THAT( 3., WithinRel( parameters1.DGAM()[0][0] ) );
  CHECK_THAT( 4., WithinRel( parameters1.DGAM()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[0][4] ) );
  CHECK_THAT( 5., WithinRel( parameters1.DGAM()[1][0] ) );
  CHECK_THAT( 6., WithinRel( parameters1.DGAM()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.DGAM()[1][4] ) );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[0].size() );
  CHECK( 5 == parameters1.resonanceParameterUncertainties()[1].size() );
  CHECK_THAT( 3., WithinRel( parameters1.resonanceParameterUncertainties()[0][0] ) );
  CHECK_THAT( 4., WithinRel( parameters1.resonanceParameterUncertainties()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[0][4] ) );
  CHECK_THAT( 5., WithinRel( parameters1.resonanceParameterUncertainties()[1][0] ) );
  CHECK_THAT( 6., WithinRel( parameters1.resonanceParameterUncertainties()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters1.resonanceParameterUncertainties()[1][4] ) );

  auto group2 = chunk.spinGroups()[1];
  CHECK_THAT( -0.5, WithinRel( group2.AJ() ) );
  CHECK_THAT( -0.5, WithinRel( group2.spin() ) );
  CHECK_THAT( 0., WithinRel( group2.PJ() ) );
  CHECK_THAT( 0., WithinRel( group2.parity() ) );
  CHECK( 2 == group2.NCH() );
  CHECK( 2 == group2.numberChannels() );
  CHECK( 2 == group2.NRSA() );
  CHECK( 2 == group2.numberResonances() );

  auto channels2 = group2.channels();
  CHECK_THAT( -0.5, WithinRel( channels2.AJ() ) );
  CHECK_THAT( -0.5, WithinRel( channels2.spin() ) );
  CHECK_THAT( 0., WithinRel( channels2.PJ() ) );
  CHECK_THAT( 0., WithinRel( channels2.parity() ) );
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
  CHECK( 0 == channels2.L()[0] );
  CHECK( 1 == channels2.L()[1] );
  CHECK( 0 == channels2.orbitalMomentumValues()[0] );
  CHECK( 1 == channels2.orbitalMomentumValues()[1] );
  CHECK_THAT( 0., WithinRel( channels2.SCH()[0] ) );
  CHECK_THAT( .5, WithinRel( channels2.SCH()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.channelSpinValues()[0] ) );
  CHECK_THAT( .5, WithinRel( channels2.channelSpinValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.BND()[0] ) );
  CHECK_THAT( 0., WithinRel( channels2.BND()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.boundaryConditionValues()[0] ) );
  CHECK_THAT( 0., WithinRel( channels2.boundaryConditionValues()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.APT()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels2.APT()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.trueChannelRadii()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels2.trueChannelRadii()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.APE()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels2.APE()[1] ) );
  CHECK_THAT( 0., WithinRel( channels2.effectiveChannelRadii()[0] ) );
  CHECK_THAT( 5.437300e-1, WithinRel( channels2.effectiveChannelRadii()[1] ) );

  auto parameters2 = group2.parameters();
  CHECK( 2 == parameters2.NRSA() );
  CHECK( 2 == parameters2.numberResonances() );
  CHECK( 2 == parameters2.NX() );
  CHECK( 2 == parameters2.numberLines() );

  CHECK( 2 == parameters2.ER().size() );
  CHECK( 2 == parameters2.resonanceEnergies().size() );
  CHECK( 2 == parameters2.GAM().size() );
  CHECK( 2 == parameters2.resonanceParameters().size() );
  CHECK( 2 == parameters2.DER().size() );
  CHECK( 2 == parameters2.resonanceEnergyUncertainties().size() );
  CHECK( 2 == parameters2.DGAM().size() );
  CHECK( 2 == parameters2.resonanceParameterUncertainties().size() );

  CHECK_THAT( 5.152000e+4, WithinRel( parameters2.ER()[0] ) );
  CHECK_THAT( 5.359000e+4, WithinRel( parameters2.ER()[1] ) );
  CHECK_THAT( 5.152000e+4, WithinRel( parameters2.resonanceEnergies()[0] ) );
  CHECK_THAT( 5.359000e+4, WithinRel( parameters2.resonanceEnergies()[1] ) );
  CHECK( 5 == parameters2.GAM()[0].size() );
  CHECK( 5 == parameters2.GAM()[1].size() );
  CHECK_THAT( .36, WithinRel( parameters2.GAM()[0][0] ) );
  CHECK_THAT( 16.002, WithinRel( parameters2.GAM()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[0][4] ) );
  CHECK_THAT( 1.5, WithinRel( parameters2.GAM()[1][0] ) );
  CHECK_THAT( 17., WithinRel( parameters2.GAM()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters2.GAM()[1][4] ) );
  CHECK( 5 == parameters2.resonanceParameters()[0].size() );
  CHECK( 5 == parameters2.resonanceParameters()[1].size() );
  CHECK_THAT( .36, WithinRel( parameters2.resonanceParameters()[0][0] ) );
  CHECK_THAT( 16.002, WithinRel( parameters2.resonanceParameters()[0][1] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[0][2] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[0][3] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[0][4] ) );
  CHECK_THAT( 1.5, WithinRel( parameters2.resonanceParameters()[1][0] ) );
  CHECK_THAT( 17., WithinRel( parameters2.resonanceParameters()[1][1] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[1][2] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[1][3] ) );
  CHECK_THAT( 0., WithinRel( parameters2.resonanceParameters()[1][4] ) );

  CHECK_THAT(  7., WithinRel( parameters2.DER()[0] ) );
  CHECK_THAT(  8., WithinRel( parameters2.DER()[1] ) );
  CHECK_THAT(  7., WithinRel( parameters2.resonanceEnergyUncertainties()[0] ) );
  CHECK_THAT(  8., WithinRel( parameters2.resonanceEnergyUncertainties()[1] ) );
  CHECK(  5 == parameters2.DGAM()[0].size() );
  CHECK(  5 == parameters2.DGAM()[1].size() );
  CHECK_THAT(  9., WithinRel( parameters2.DGAM()[0][0] ) );
  CHECK_THAT( 10., WithinRel( parameters2.DGAM()[0][1] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[0][2] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[0][3] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[0][4] ) );
  CHECK_THAT( 11., WithinRel( parameters2.DGAM()[1][0] ) );
  CHECK_THAT( 12., WithinRel( parameters2.DGAM()[1][1] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[1][2] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[1][3] ) );
  CHECK_THAT(  0., WithinRel( parameters2.DGAM()[1][4] ) );
  CHECK(  5 == parameters2.resonanceParameterUncertainties()[0].size() );
  CHECK(  5 == parameters2.resonanceParameterUncertainties()[1].size() );
  CHECK_THAT(  9., WithinRel( parameters2.resonanceParameterUncertainties()[0][0] ) );
  CHECK_THAT( 10., WithinRel( parameters2.resonanceParameterUncertainties()[0][1] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[0][2] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[0][3] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[0][4] ) );
  CHECK_THAT( 11., WithinRel( parameters2.resonanceParameterUncertainties()[1][0] ) );
  CHECK_THAT( 12., WithinRel( parameters2.resonanceParameterUncertainties()[1][1] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[1][2] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[1][3] ) );
  CHECK_THAT(  0., WithinRel( parameters2.resonanceParameterUncertainties()[1][4] ) );

  CHECK( 21 == chunk.NC() );
}

std::string chunkWithoutSpinGroups() {
  return
    " 0.000000+0 0.000000+0          2          0         24          4262532151     \n"
    " 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+0262532151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0262532151     \n"
    " 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+0262532151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+0262532151     \n";
}
