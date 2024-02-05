// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using JValue = section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths::JValue;

std::string chunk();
void verifyChunk( const JValue& );
std::string chunkWithInvalidSize();
std::string chunkWithNoFissionWidths();

SCENARIO( "JValue" ) {

  GIVEN( "valid data for a JValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int l = 1;
      double d = 13.1;
      double spin = 0.5;
      int amun = 1;
      int amuf = 1;
      double gn = 3.013000e-3;
      double gg = 3.100000e-2;
      std::vector< double > gf = { 4.314000e-3, 4.572000e-3, 4.740000e-3,
                                   5.000000e-3, 5.520000e-3, 7.057000e-3,
                                   8.251000e-3, 9.276000e-3, 9.930000e-3,
                                   1.035000e-2, 1.210000e-2, 1.341000e-2,
                                   1.456000e-2, 1.542000e-2 };

      JValue chunk( l, spin, d, amun, amuf, gn, gg, std::move( gf ) );

      THEN( "a JValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9440, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      JValue chunk( begin, end, lineNumber, 9440, 2, 151 );

      THEN( "a JValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9440, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "no fission width values are given" ) {

      int l = 1;
      double d = 13.1;
      double spin = 0.5;
      int amun = 1;
      int amuf = 1;
      double gn = 3.013000e-3;
      double gg = 3.100000e-2;
      std::vector< double > gf = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( l, spin, d, amun, amuf,
                              gn, gg, std::move( gf ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string without fission width values" ) {

      std::string string = chunkWithNoFissionWidths();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( begin, end, lineNumber, 9440, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with wrong NPL is used" ) {

      // this is a list error, not every list error is tested

      std::string string = chunkWithInvalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( begin, end, lineNumber, 9440, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n";
}

void verifyChunk( const JValue& chunk ) {

  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );

  CHECK( 14 == chunk.NE() );
  CHECK( 14 == chunk.GF().size() );
  CHECK( 14 == chunk.averageFissionWidths().size() );

  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 14 == chunk.boundaries()[0] );

  CHECK_THAT( 0.5, WithinRel( chunk.AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spin() ) );
  CHECK_THAT( 13.1, WithinRel( chunk.D() ) );
  CHECK_THAT( 13.1, WithinRel( chunk.averageLevelSpacing() ) );
  CHECK( 1 == chunk.AMUN() );
  CHECK( 1 == chunk.neutronWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUG() );
  CHECK( 0 == chunk.gammaWidthDegreesFreedom() );
  CHECK( 1 == chunk.AMUF() );
  CHECK( 1 == chunk.fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUX() );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom() );
  CHECK_THAT( 3.013000e-3, WithinRel( chunk.GN() ) );
  CHECK_THAT( 3.013000e-3, WithinRel( chunk.averageNeutronWidth() ) );
  CHECK_THAT( 3.100000e-2, WithinRel( chunk.GG() ) );
  CHECK_THAT( 3.100000e-2, WithinRel( chunk.averageGammaWidth() ) );

  CHECK_THAT( 4.314000e-3, WithinRel( chunk.GF()[0] ) );
  CHECK_THAT( 4.572000e-3, WithinRel( chunk.GF()[1] ) );
  CHECK_THAT( 4.740000e-3, WithinRel( chunk.GF()[2] ) );
  CHECK_THAT( 5.000000e-3, WithinRel( chunk.GF()[3] ) );
  CHECK_THAT( 5.520000e-3, WithinRel( chunk.GF()[4] ) );
  CHECK_THAT( 7.057000e-3, WithinRel( chunk.GF()[5] ) );
  CHECK_THAT( 8.251000e-3, WithinRel( chunk.GF()[6] ) );
  CHECK_THAT( 9.276000e-3, WithinRel( chunk.GF()[7] ) );
  CHECK_THAT( 9.930000e-3, WithinRel( chunk.GF()[8] ) );
  CHECK_THAT( 1.035000e-2, WithinRel( chunk.GF()[9] ) );
  CHECK_THAT( 1.210000e-2, WithinRel( chunk.GF()[10] ) );
  CHECK_THAT( 1.341000e-2, WithinRel( chunk.GF()[11] ) );
  CHECK_THAT( 1.456000e-2, WithinRel( chunk.GF()[12] ) );
  CHECK_THAT( 1.542000e-2, WithinRel( chunk.GF()[13] ) );
  CHECK_THAT( 4.314000e-3, WithinRel( chunk.averageFissionWidths()[0] ) );
  CHECK_THAT( 4.572000e-3, WithinRel( chunk.averageFissionWidths()[1] ) );
  CHECK_THAT( 4.740000e-3, WithinRel( chunk.averageFissionWidths()[2] ) );
  CHECK_THAT( 5.000000e-3, WithinRel( chunk.averageFissionWidths()[3] ) );
  CHECK_THAT( 5.520000e-3, WithinRel( chunk.averageFissionWidths()[4] ) );
  CHECK_THAT( 7.057000e-3, WithinRel( chunk.averageFissionWidths()[5] ) );
  CHECK_THAT( 8.251000e-3, WithinRel( chunk.averageFissionWidths()[6] ) );
  CHECK_THAT( 9.276000e-3, WithinRel( chunk.averageFissionWidths()[7] ) );
  CHECK_THAT( 9.930000e-3, WithinRel( chunk.averageFissionWidths()[8] ) );
  CHECK_THAT( 1.035000e-2, WithinRel( chunk.averageFissionWidths()[9] ) );
  CHECK_THAT( 1.210000e-2, WithinRel( chunk.averageFissionWidths()[10] ) );
  CHECK_THAT( 1.341000e-2, WithinRel( chunk.averageFissionWidths()[11] ) );
  CHECK_THAT( 1.456000e-2, WithinRel( chunk.averageFissionWidths()[12] ) );
  CHECK_THAT( 1.542000e-2, WithinRel( chunk.averageFissionWidths()[13] ) );
  CHECK_THAT( 0., WithinRel( chunk.GX() ) );
  CHECK_THAT( 0., WithinRel( chunk.averageCompetitiveWidth() ) );

  CHECK( 5 == chunk.NC() );
}

std::string chunkWithInvalidSize() {
  return
    " 0.000000+0 0.000000+0          1          1         19          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n";
}

std::string chunkWithNoFissionWidths() {
  return
    " 0.000000+0 0.000000+0          1          1          6          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n";
}
