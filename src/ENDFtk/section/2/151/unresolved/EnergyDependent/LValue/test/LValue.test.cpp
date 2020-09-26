#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using JValue = resonanceParameters::unresolved::EnergyDependent::JValue;
using LValue = resonanceParameters::unresolved::EnergyDependent::LValue;

std::string chunk();
void verifyChunk( const LValue& );
std::string chunkWithNoJValues();

SCENARIO( "LValue" ) {

  GIVEN( "valid data for an LValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 89.13540;
      unsigned int l = 1;

      std::vector< JValue > jvalues =
        { { 0.5, 3, 2, 1, 4, 5,
            { 6000., 7000., 8000. }, { 12406., 12406., 12406. },
            { 6.7238, 6.7238, 6.7238 }, { 0.205, 0.205, 0.205 },
            { 0., 0., 0. }, { 0., 0., 0. } },
          { 1.5, 1, 4, 2, 0, 5,
            { 6000., 8000. }, { 6202.8, 6202.8 },
            { 3.3619, 3.3619 }, { 0.205, 0.205 },
            { 0., 0. }, { 0., 0. } } };

      LValue chunk( awri, l, std::move( jvalues ) );

      THEN( "a LValue can be constructed and members can be "
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

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LValue chunk( begin, end, lineNumber, 3843, 2, 151 );

      THEN( "a LValue can be constructed and members can be tested" ) {

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

  GIVEN( "invalid data" ) {

    WHEN( "no j values are given" ) {

      double awri = 237.992;
      int l = 1;
      std::vector< JValue > jvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( awri, l, std::move( jvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no j values is used" ) {

      std::string string = chunkWithNoJValues();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( begin, end, lineNumber, 9440, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 8.913540+1 0.000000+0          1          0          2          03843 2151     \n"
    " 5.000000-1 0.000000+0          5          0         24          33843 2151     \n"
    " 0.000000+0 0.000000+0 4.000000+0 3.000000+0 2.000000+0 1.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 1.500000+0 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 4.000000+0 2.000000+03843 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n";
}

void verifyChunk( const LValue& chunk ) {

  CHECK( 89.1354 == Approx( chunk.AWRI() ) );
  CHECK( 89.1354 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );
  CHECK( 2 == chunk.NJS() );
  CHECK( 2 == chunk.numberSpinValues() );

  auto jvalue10 = chunk.jValues()[0];
  CHECK( 0.5 == Approx( jvalue10.AJ() ) );
  CHECK( 0.5 == Approx( jvalue10.spin() ) );

  CHECK( 3 == jvalue10.AMUN() );
  CHECK( 3 == jvalue10.neutronWidthDegreesFreedom() );
  CHECK( 2 == jvalue10.AMUG() );
  CHECK( 2 == jvalue10.gammaWidthDegreesFreedom() );
  CHECK( 1 == jvalue10.AMUF() );
  CHECK( 1 == jvalue10.fissionWidthDegreesFreedom() );
  CHECK( 4 == jvalue10.AMUX() );
  CHECK( 4 == jvalue10.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue10.INT() );

  CHECK( 1 == jvalue10.NR() );
  CHECK( 1 == jvalue10.interpolants().size() );
  CHECK( 1 == jvalue10.boundaries().size() );
  CHECK( 5 == jvalue10.interpolants()[0] );
  CHECK( 3 == jvalue10.boundaries()[0] );

  CHECK( 3 == jvalue10.NE() );
  CHECK( 3 == jvalue10.ES().size() );
  CHECK( 3 == jvalue10.energies().size() );
  CHECK( 3 == jvalue10.D().size() );
  CHECK( 3 == jvalue10.averageLevelSpacings().size() );
  CHECK( 3 == jvalue10.GN().size() );
  CHECK( 3 == jvalue10.averageNeutronWidths().size() );
  CHECK( 3 == jvalue10.GG().size() );
  CHECK( 3 == jvalue10.averageGammaWidths().size() );
  CHECK( 3 == jvalue10.GF().size() );
  CHECK( 3 == jvalue10.averageFissionWidths().size() );
  CHECK( 3 == jvalue10.GX().size() );
  CHECK( 3 == jvalue10.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue10.ES()[0] ) );
  CHECK( 7000. == Approx( jvalue10.ES()[1] ) );
  CHECK( 8000. == Approx( jvalue10.ES()[2] ) );
  CHECK( 6000. == Approx( jvalue10.energies()[0] ) );
  CHECK( 7000. == Approx( jvalue10.energies()[1] ) );
  CHECK( 8000. == Approx( jvalue10.energies()[2] ) );
  CHECK( 12406. == Approx( jvalue10.D()[0] ) );
  CHECK( 12406. == Approx( jvalue10.D()[1] ) );
  CHECK( 12406. == Approx( jvalue10.D()[2] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[0] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[1] ) );
  CHECK( 12406. == Approx( jvalue10.averageLevelSpacings()[2] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[0] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[1] ) );
  CHECK( 6.7238 == Approx( jvalue10.GN()[2] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[0] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[1] ) );
  CHECK( 6.7238 == Approx( jvalue10.averageNeutronWidths()[2] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[0] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[1] ) );
  CHECK( 0.205 == Approx( jvalue10.GG()[2] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[0] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[1] ) );
  CHECK( 0.205 == Approx( jvalue10.averageGammaWidths()[2] ) );
  CHECK( 0. == Approx( jvalue10.GF()[0] ) );
  CHECK( 0. == Approx( jvalue10.GF()[1] ) );
  CHECK( 0. == Approx( jvalue10.GF()[2] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue10.averageFissionWidths()[2] ) );
  CHECK( 0. == Approx( jvalue10.GX()[0] ) );
  CHECK( 0. == Approx( jvalue10.GX()[1] ) );
  CHECK( 0. == Approx( jvalue10.GX()[2] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[1] ) );
  CHECK( 0. == Approx( jvalue10.averageCompetitiveWidths()[2] ) );

  auto jvalue11 = chunk.jValues()[1];
  CHECK( 1.5 == Approx( jvalue11.AJ() ) );
  CHECK( 1.5 == Approx( jvalue11.spin() ) );

  CHECK( 1 == jvalue11.AMUN() );
  CHECK( 1 == jvalue11.neutronWidthDegreesFreedom() );
  CHECK( 4 == jvalue11.AMUG() );
  CHECK( 4 == jvalue11.gammaWidthDegreesFreedom() );
  CHECK( 2 == jvalue11.AMUF() );
  CHECK( 2 == jvalue11.fissionWidthDegreesFreedom() );
  CHECK( 0 == jvalue11.AMUX() );
  CHECK( 0 == jvalue11.competitiveWidthDegreesFreedom() );

  CHECK( 5 == jvalue11.INT() );

  CHECK( 1 == jvalue11.NR() );
  CHECK( 1 == jvalue11.interpolants().size() );
  CHECK( 1 == jvalue11.boundaries().size() );
  CHECK( 5 == jvalue11.interpolants()[0] );
  CHECK( 2 == jvalue11.boundaries()[0] );

  CHECK( 2 == jvalue11.NE() );
  CHECK( 2 == jvalue11.ES().size() );
  CHECK( 2 == jvalue11.energies().size() );
  CHECK( 2 == jvalue11.D().size() );
  CHECK( 2 == jvalue11.averageLevelSpacings().size() );
  CHECK( 2 == jvalue11.GN().size() );
  CHECK( 2 == jvalue11.averageNeutronWidths().size() );
  CHECK( 2 == jvalue11.GG().size() );
  CHECK( 2 == jvalue11.averageGammaWidths().size() );
  CHECK( 2 == jvalue11.GF().size() );
  CHECK( 2 == jvalue11.averageFissionWidths().size() );
  CHECK( 2 == jvalue11.GX().size() );
  CHECK( 2 == jvalue11.averageCompetitiveWidths().size() );

  CHECK( 6000. == Approx( jvalue11.ES()[0] ) );
  CHECK( 8000. == Approx( jvalue11.ES()[1] ) );
  CHECK( 6000. == Approx( jvalue11.energies()[0] ) );
  CHECK( 8000. == Approx( jvalue11.energies()[1] ) );
  CHECK( 6202.8 == Approx( jvalue11.D()[0] ) );
  CHECK( 6202.8 == Approx( jvalue11.D()[1] ) );
  CHECK( 6202.8 == Approx( jvalue11.averageLevelSpacings()[0] ) );
  CHECK( 6202.8 == Approx( jvalue11.averageLevelSpacings()[1] ) );
  CHECK( 3.3619 == Approx( jvalue11.GN()[0] ) );
  CHECK( 3.3619 == Approx( jvalue11.GN()[1] ) );
  CHECK( 3.3619 == Approx( jvalue11.averageNeutronWidths()[0] ) );
  CHECK( 3.3619 == Approx( jvalue11.averageNeutronWidths()[1] ) );
  CHECK( 0.205 == Approx( jvalue11.GG()[0] ) );
  CHECK( 0.205 == Approx( jvalue11.GG()[1] ) );
  CHECK( 0.205 == Approx( jvalue11.averageGammaWidths()[0] ) );
  CHECK( 0.205 == Approx( jvalue11.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( jvalue11.GF()[0] ) );
  CHECK( 0. == Approx( jvalue11.GF()[1] ) );
  CHECK( 0. == Approx( jvalue11.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( jvalue11.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( jvalue11.GX()[0] ) );
  CHECK( 0. == Approx( jvalue11.GX()[1] ) );
  CHECK( 0. == Approx( jvalue11.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( jvalue11.averageCompetitiveWidths()[1] ) );

  CHECK( 10 == chunk.NC() );
}

std::string chunkWithNoJValues() {
  return
    " 2.379920+2 0.000000+0          1          0          0          09440 2151     \n";
}
