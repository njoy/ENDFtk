#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using EnergyDependent = resonanceParameters::unresolved::EnergyDependent;
using JValue = resonanceParameters::unresolved::EnergyDependent::JValue;
using LValue = resonanceParameters::unresolved::EnergyDependent::LValue;

std::string chunk();
void verifyChunk( const EnergyDependent& );

SCENARIO( "EnergyDependent" ) {

  GIVEN( "valid data for an EnergyDependent" ) {

    std::string string = chunk();

    /*WHEN( "the data is given explicitly" ) {

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

      EnergyDependent chunk( spin, ap, lssf, std::move( lvalues ) );

      THEN( "a EnergyDependent can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
*/
    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyDependent chunk( begin, end, lineNumber, 3843, 2, 151 );

      THEN( "a EnergyDependent can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 6.795900-1          0          0          2          03843 2151     \n"
  // L=0 CONT
    " 8.913540+1 0.000000+0          0          0          1          03843 2151     \n"
  // L=0 LIST
    " 5.000000-1 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 4.590100-1 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 1.000000-1 4.590100-1 2.051000-1 1.000000+03843 2151     \n"
    // L=1 CONT
    " 8.913540+1 0.000000+0          1          0          2          03843 2151     \n"
    // L=1,J=0 LIST
    " 5.000000-1 0.000000+0          5          0         24          33843 2151     \n"
    " 0.000000+0 0.000000+0 4.000000+0 3.000000+0 2.000000+0 1.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    // L=1,J=1 LIST
    " 1.500000+0 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 4.000000+0 2.000000+03843 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n";
}

void verifyChunk( const EnergyDependent& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 2 == chunk.LRF() );
  CHECK( 2 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK( 0.0 == Approx( chunk.SPI() ) );
  CHECK( 0.0 == Approx( chunk.spin() ) );
  CHECK( 0.67959 == Approx( chunk.AP() ) );
  CHECK( 0.67959 == Approx( chunk.scatteringRadius() ) );
  CHECK( false == Approx( chunk.LSSF() ) );
  CHECK( false == Approx( chunk.selfShieldingOnly() ) );

  CHECK( 2 == chunk.NLS() );

  auto lvalue0 = chunk.lValues()[0];
  CHECK( 89.1354 == Approx( lvalue0.AWRI() ) );
  CHECK( 89.1354 == Approx( lvalue0.atomicWeightRatio() ) );
  CHECK( 0 == lvalue0.L() );
  CHECK( 0 == lvalue0.orbitalMomentum() );
  CHECK( 1 == lvalue0.NJS() );
  CHECK( 1 == lvalue0.numberSpinValues() );

  auto jvalue00 = lvalue0.jValues()[0];
  CHECK( 0.5 == Approx( jvalue00.AJ() ) );
  CHECK( 0.5 == Approx( jvalue00.spin() ) );

  CHECK( 1 == jvalue00.AMUN() );
  CHECK( 1 == jvalue00.neutronWidthDegreesFreedom() );
  CHECK( 3 == jvalue00.AMUG() );
  CHECK( 3 == jvalue00.gammaWidthDegreesFreedom() );
  CHECK( 4 == jvalue00.AMUF() );
  CHECK( 4 == jvalue00.fissionWidthDegreesFreedom() );
  CHECK( 2 == jvalue00.AMUX() );
  CHECK( 2 == jvalue00.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue00.INT() );

  CHECK( 1 == jvalue00.NR() );
  CHECK( 1 == jvalue00.interpolants().size() );
  CHECK( 1 == jvalue00.boundaries().size() );
  CHECK( 5 == jvalue00.interpolants()[0] );
  CHECK( 2 == jvalue00.boundaries()[0] );

  CHECK( 2 == jvalue00.NE() );
  CHECK( 2 == jvalue00.ES().size() );
  CHECK( 2 == jvalue00.energies().size() );
  CHECK( 2 == jvalue00.D().size() );
  CHECK( 2 == jvalue00.averageLevelSpacings().size() );
  CHECK( 2 == jvalue00.GN().size() );
  CHECK( 2 == jvalue00.averageNeutronWidths().size() );
  CHECK( 2 == jvalue00.GG().size() );
  CHECK( 2 == jvalue00.averageGammaWidths().size() );
  CHECK( 2 == jvalue00.GF().size() );
  CHECK( 2 == jvalue00.averageFissionWidths().size() );
  CHECK( 2 == jvalue00.GX().size() );
  CHECK( 2 == jvalue00.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue00.ES()[0] ) );
  CHECK( 8000. == Approx( jvalue00.ES()[1] ) );
  CHECK( 6000. == Approx( jvalue00.energies()[0] ) );
  CHECK( 8000. == Approx( jvalue00.energies()[1] ) );
  CHECK( 6202.8 == Approx( jvalue00.D()[0] ) );
  CHECK( 6202.8 == Approx( jvalue00.D()[1] ) );
  CHECK( 6202.8 == Approx( jvalue00.averageLevelSpacings()[0] ) );
  CHECK( 6202.8 == Approx( jvalue00.averageLevelSpacings()[1] ) );
  CHECK( 0.45901 == Approx( jvalue00.GN()[0] ) );
  CHECK( 0.45901 == Approx( jvalue00.GN()[1] ) );
  CHECK( 0.45901 == Approx( jvalue00.averageNeutronWidths()[0] ) );
  CHECK( 0.45901 == Approx( jvalue00.averageNeutronWidths()[1] ) );
  CHECK( 0.2050 == Approx( jvalue00.GG()[0] ) );
  CHECK( 0.2051 == Approx( jvalue00.GG()[1] ) );
  CHECK( 0.2050 == Approx( jvalue00.averageGammaWidths()[0] ) );
  CHECK( 0.2051 == Approx( jvalue00.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( jvalue00.GF()[0] ) );
  CHECK( 0. == Approx( jvalue00.GF()[1] ) );
  CHECK( 0. == Approx( jvalue00.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue00.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue00.GX()[0] ) );
  CHECK( .1 == Approx( jvalue00.GX()[1] ) );
  CHECK( 0. == Approx( jvalue00.averageCompetitiveWidths()[0] ) );
  CHECK( .1 == Approx( jvalue00.averageCompetitiveWidths()[1] ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK( 89.1354 == Approx( lvalue1.AWRI() ) );
  CHECK( 89.1354 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 1 == lvalue1.L() );
  CHECK( 1 == lvalue1.orbitalMomentum() );
  CHECK( 2 == lvalue0.NJS() );
  CHECK( 2 == lvalue0.numberSpinValues() );

  auto jvalue10 = lvalue1.jValues()[0];

  auto jvalue11 = lvalue1.jValues()[1];

  CHECK( 16 == chunk.NC() );
}
