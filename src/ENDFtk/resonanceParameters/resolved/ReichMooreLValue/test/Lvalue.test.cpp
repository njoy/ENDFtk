#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ReichMooreLValue =
resonanceParameters::resolved::ReichMooreLValue;

SCENARIO( "ReichMooreLValue" ) {

  GIVEN( "valid data for a ReichMooreLValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double apl = 0.0;
      double l = 1.;
      std::vector< double > er = { -1.470000+5, 4.730000+ };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 5.430695+2, 1.072906+5 };
      std::vector< double > gn = { 3.680695+2, 1.072900+5 };
      std::vector< double > gfa = { 1.750000+2, 5.600000-1 };
      std::vector< double > gfb = { 3., 4. };

      ReichMooreLValue chunk( awri, apl, l,
                              std::move( er ), std::move( aj ),
                              std::move( gn ), std::move( gn ),
                              std::move( gfa ), std::move( gfb ) );

      THEN( "a ReichMooreLValue can be constructed and members can be "
            "tested" ) {

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

      ReichMooreLValue chunk( begin, end, lineNumber, 1025, 2, 151 );

      THEN( "a ReichMooreLValue can be constructed and members can be "
            "tested" ) {

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

    WHEN( "a string with inconsistent NPL and NPP is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMooreLValue( begin, end, lineNumber, 1025, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.982069+1 0.000000+0          1          0         12          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n";
}

void verifyChunk( const ReichMooreLValue& chunk ) {

  CHECK( 0. == Approx( chunk.AWRI() ) );
  CHECK( 1. == Approx( chunk.atomicWeightRatio() ) );

  CHECK( 2 == chunk.NRS() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.AJ().size() );
  CHECK( 2 == chunk.spinValues().size() );
  CHECK( 2 == chunk.GN().size() );
  CHECK( 2 == chunk.neutronWidths().size() );
  CHECK( 2 == chunk.GG().size() );
  CHECK( 2 == chunk.gammaWidths().size() );
  CHECK( 2 == chunk.GFA().size() );
  CHECK( 2 == chunk.firstFissionWidths().size() );
  CHECK( 2 == chunk.GFB().size() );
  CHECK( 2 == chunk.secondFissionWidths().size() );
  CHECK( 2 == chunk.resonances().size() );

  CHECK( 0. == Approx( chunk.MA()[0] ) );
  CHECK( 1. == Approx( chunk.MA()[1] ) );
  CHECK( 0 == Approx( chunk.massParticleA()[0] ) );
  CHECK( 1 == Approx( chunk.massParticleA()[1] ) );
  CHECK( 5.446635e+1 == Approx( chunk.MB()[0] ) );
  CHECK( 5.347624e+1 == Approx( chunk.MB()[1] ) );
  CHECK( 5.446635e+1 == Approx( chunk.massParticleB()[0] ) );
  CHECK( 5.347624e+1 == Approx( chunk.massParticleB()[1] ) );
  CHECK( 2. == Approx( chunk.ZA()[0] ) );
  CHECK( 3. == Approx( chunk.ZA()[1] ) );
  CHECK( 2. == Approx( chunk.chargeParticleA()[0] ) );
  CHECK( 3. == Approx( chunk.chargeParticleA()[1] ) );
  CHECK( 26. == Approx( chunk.ZB()[0] ) );
  CHECK( 27. == Approx( chunk.ZB()[1] ) );
  CHECK( 26. == Approx( chunk.chargeParticleB()[0] ) );
  CHECK( 27. == Approx( chunk.chargeParticleB()[1] ) );
  CHECK( 1. == Approx( chunk.IA()[0] ) );
  CHECK( 0.5 == Approx( chunk.IA()[1] ) );
  CHECK( 1. == Approx( chunk.spinParticleA()[0] ) );
  CHECK( 0.5 == Approx( chunk.spinParticleA()[1] ) );
  CHECK( 4. == Approx( chunk.IB()[0] ) );
  CHECK( 5. == Approx( chunk.IB()[1] ) );
  CHECK( 4. == Approx( chunk.spinParticleB()[0] ) );
  CHECK( 5. == Approx( chunk.spinParticleB()[1] ) );
  CHECK( 12. == Approx( chunk.PA()[0] ) );
  CHECK( 13. == Approx( chunk.PA()[1] ) );
  CHECK( 12. == Approx( chunk.parityParticleA()[0] ) );
  CHECK( 13. == Approx( chunk.parityParticleA()[1] ) );
  CHECK( 14. == Approx( chunk.PB()[0] ) );
  CHECK( 15. == Approx( chunk.PB()[1] ) );
  CHECK( 14. == Approx( chunk.parityParticleB()[0] ) );
  CHECK( 15. == Approx( chunk.parityParticleB()[1] ) );
  CHECK( 6. == Approx( chunk.Q()[0] ) );
  CHECK( 7. == Approx( chunk.Q()[1] ) );
  CHECK( 8 == chunk.PNT()[0] );
  CHECK( 9 == chunk.PNT()[1] );
  CHECK( 8 == chunk.penetrabilityFlag()[0] );
  CHECK( 9 == chunk.penetrabilityFlag()[1] );
  CHECK( 10 == chunk.SHF()[0] );
  CHECK( 11 == chunk.SHF()[1] );
  CHECK( 10 == chunk.shiftFactorFlag()[0] );
  CHECK( 11 == chunk.shiftFactorFlag()[1] );
  CHECK( 102 == chunk.MT()[0] );
  CHECK( 2 == chunk.MT()[1] );

  CHECK( 5 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 0.000000+0          0          0         11          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1           1025 2151     \n";
}

