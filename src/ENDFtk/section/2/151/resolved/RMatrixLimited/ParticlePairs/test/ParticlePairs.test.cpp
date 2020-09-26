#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ParticlePairs =
resonanceParameters::resolved::RMatrixLimited::ParticlePairs;

std::string chunk();
void verifyChunk( const ParticlePairs& );
std::string invalidSize();
std::string zeroSize();
std::string zeroNumberParticlePair();

SCENARIO( "ParticlePairs" ) {

  GIVEN( "valid data for a ParticlePairs" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > ma = { 0., 1. };
      std::vector< double > mb = { 5.446635e+1, 5.347624e+1 };
      std::vector< double > za = { 2., 3. };
      std::vector< double > zb = { 26., 27. };
      std::vector< double > ia = { 1., 0.5 };
      std::vector< double > ib = { 4., 5. };
      std::vector< double > q = { 6., 7. };
      std::vector< int > pnt = { 8, 9 };
      std::vector< int > shf = { 10, 11 };
      std::vector< int > mt = { 102, 2 };
      std::vector< double > pa = { 12., 13. };
      std::vector< double > pb = { 14., 15. };

      ParticlePairs chunk( std::move( ma ), std::move( mb ),
                           std::move( za ), std::move( zb ),
                           std::move( ia ), std::move( ib ),
                           std::move( pa ), std::move( pb ),
                           std::move( q ), std::move( pnt ),
                           std::move( shf ), std::move( mt ) );

      THEN( "a ParticlePairs can be constructed and members can be "
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

      ParticlePairs chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a ParticlePairs can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      std::vector< double > wrong = { 0. };
      std::vector< double > mb = { 5.446635e+1, 5.347624e+1 };
      std::vector< double > za = { 2., 3. };
      std::vector< double > zb = { 26., 27. };
      std::vector< double > ia = { 1., 0.5 };
      std::vector< double > ib = { 4., 5. };
      std::vector< double > q = { 6., 7. };
      std::vector< int > pnt = { 8, 9 };
      std::vector< int > shf = { 10, 11 };
      std::vector< int > mt = { 102, 2 };
      std::vector< double > pa = { 12., 13. };
      std::vector< double > pb = { 14., 15. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( std::move( wrong ), std::move( mb ),
                                     std::move( za ), std::move( zb ),
                                     std::move( ia ), std::move( ib ),
                                     std::move( pa ), std::move( pb ),
                                     std::move( q ), std::move( pnt ),
                                     std::move( shf ), std::move( mt ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is empty" ) {

      std::vector< double > ma = {};
      std::vector< double > mb = {};
      std::vector< double > za = {};
      std::vector< double > zb = {};
      std::vector< double > ia = {};
      std::vector< double > ib = {};
      std::vector< double > q = {};
      std::vector< int > pnt = {};
      std::vector< int > shf = {};
      std::vector< int > mt = {};
      std::vector< double > pa = {};
      std::vector< double > pb = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( std::move( ma ), std::move( mb ),
                                     std::move( za ), std::move( zb ),
                                     std::move( ia ), std::move( ib ),
                                     std::move( pa ), std::move( pb ),
                                     std::move( q ), std::move( pnt ),
                                     std::move( shf ), std::move( mt ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NPP is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL is used" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPP is used" ) {

      std::string string = zeroNumberParticlePair();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          0         24          42625 2151     \n"
    " 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+02625 2151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+12625 2151     \n"
    " 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+02625 2151     \n"
    " 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+12625 2151     \n";
}

void verifyChunk( const ParticlePairs& chunk ) {

  CHECK( 2 == chunk.NPP() );
  CHECK( 2 == chunk.numberParticlePairs() );
  CHECK( 2 == chunk.MA().size() );
  CHECK( 2 == chunk.massParticleA().size() );
  CHECK( 2 == chunk.MB().size() );
  CHECK( 2 == chunk.massParticleB().size() );
  CHECK( 2 == chunk.ZA().size() );
  CHECK( 2 == chunk.chargeParticleA().size() );
  CHECK( 2 == chunk.ZB().size() );
  CHECK( 2 == chunk.chargeParticleB().size() );
  CHECK( 2 == chunk.IA().size() );
  CHECK( 2 == chunk.spinParticleA().size() );
  CHECK( 2 == chunk.IB().size() );
  CHECK( 2 == chunk.spinParticleB().size() );
  CHECK( 2 == chunk.PA().size() );
  CHECK( 2 == chunk.parityParticleA().size() );
  CHECK( 2 == chunk.PB().size() );
  CHECK( 2 == chunk.parityParticleB().size() );
  CHECK( 2 == chunk.Q().size() );
  CHECK( 2 == chunk.PNT().size() );
  CHECK( 2 == chunk.penetrabilityFlag().size() );
  CHECK( 2 == chunk.SHF().size() );
  CHECK( 2 == chunk.shiftFactorFlag().size() );
  CHECK( 2 == chunk.MT().size() );

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
  " 0.000000+0 0.000000+0          2          0         23          42625 2151     \n"
  " 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+02625 2151     \n"
  " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+02625 2151     \n"
  " 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+02625 2151     \n"
  " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0           2625 2151     \n";
}

std::string zeroSize() {
  return
  " 0.000000+0 0.000000+0          2          0          0          42625 2151     \n";
}

std::string zeroNumberParticlePair() {
  return
    " 0.000000+0 0.000000+0          0          0         24          02625 2151     \n"
    " 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+02625 2151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+12625 2151     \n"
    " 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+02625 2151     \n"
    " 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+12625 2151     \n";
}
