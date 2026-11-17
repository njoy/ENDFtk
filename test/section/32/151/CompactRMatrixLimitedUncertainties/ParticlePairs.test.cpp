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

std::string chunk();
void verifyChunk( const ParticlePairs& );
std::string invalidSize();
std::string zeroSize();
std::string zeroNumberParticlePair();

SCENARIO( "ParticlePairs" ) {

  GIVEN( "valid data for a ParticlePairs" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int njsx = 1;
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

      ParticlePairs chunk( njsx,
                           std::move( ma ), std::move( mb ),
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
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ParticlePairs chunk( begin, end, lineNumber, 2625, 32, 151 );

      THEN( "a ParticlePairs can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      int njsx = 1;
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

        CHECK_THROWS( ParticlePairs( njsx,
                                     std::move( wrong ), std::move( mb ),
                                     std::move( za ), std::move( zb ),
                                     std::move( ia ), std::move( ib ),
                                     std::move( pa ), std::move( pb ),
                                     std::move( q ), std::move( pnt ),
                                     std::move( shf ), std::move( mt ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is empty" ) {

      int njsx = 1;
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

        CHECK_THROWS( ParticlePairs( njsx,
                                     std::move( ma ), std::move( mb ),
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

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL is used" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPP is used" ) {

      std::string string = zeroNumberParticlePair();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ParticlePairs( begin, end, lineNumber, 2625, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          1         24          4262532151     \n"
    " 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+0262532151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+1262532151     \n"
    " 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+0262532151     \n"
    " 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+1262532151     \n";
}

void verifyChunk( const ParticlePairs& chunk ) {

  CHECK( 1 == chunk.NJSX() );
  CHECK( 1 == chunk.numberSpinGroups() );

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

  CHECK_THAT( 0., WithinRel( chunk.MA()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.MA()[1] ) );
  CHECK_THAT( 0, WithinRel( chunk.massParticleA()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.massParticleA()[1] ) );
  CHECK_THAT( 5.446635e+1, WithinRel( chunk.MB()[0] ) );
  CHECK_THAT( 5.347624e+1, WithinRel( chunk.MB()[1] ) );
  CHECK_THAT( 5.446635e+1, WithinRel( chunk.massParticleB()[0] ) );
  CHECK_THAT( 5.347624e+1, WithinRel( chunk.massParticleB()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.ZA()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.ZA()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.chargeParticleA()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.chargeParticleA()[1] ) );
  CHECK_THAT( 26., WithinRel( chunk.ZB()[0] ) );
  CHECK_THAT( 27., WithinRel( chunk.ZB()[1] ) );
  CHECK_THAT( 26., WithinRel( chunk.chargeParticleB()[0] ) );
  CHECK_THAT( 27., WithinRel( chunk.chargeParticleB()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.IA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.IA()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.spinParticleA()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinParticleA()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.IB()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.IB()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.spinParticleB()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.spinParticleB()[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.PA()[0] ) );
  CHECK_THAT( 13., WithinRel( chunk.PA()[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.parityParticleA()[0] ) );
  CHECK_THAT( 13., WithinRel( chunk.parityParticleA()[1] ) );
  CHECK_THAT( 14., WithinRel( chunk.PB()[0] ) );
  CHECK_THAT( 15., WithinRel( chunk.PB()[1] ) );
  CHECK_THAT( 14., WithinRel( chunk.parityParticleB()[0] ) );
  CHECK_THAT( 15., WithinRel( chunk.parityParticleB()[1] ) );
  CHECK_THAT( 6., WithinRel( chunk.Q()[0] ) );
  CHECK_THAT( 7., WithinRel( chunk.Q()[1] ) );
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
  " 0.000000+0 0.000000+0          2          1         23          4262532151     \n"
  " 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+0262532151     \n"
  " 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0262532151     \n"
  " 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+0262532151     \n"
  " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0           262532151     \n";
}

std::string zeroSize() {
  return
  " 0.000000+0 0.000000+0          2          1          0          4262532151     \n";
}

std::string zeroNumberParticlePair() {
  return
    " 0.000000+0 0.000000+0          0          1         24          0262532151     \n"
    " 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+0262532151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+1262532151     \n"
    " 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+0262532151     \n"
    " 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+1262532151     \n";
}
