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
using LValue = section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths::LValue;

std::string chunk();
void verifyChunk( const LValue& );
std::string chunkWithInconsistentSize();
std::string chunkWithNoJValues();

SCENARIO( "LValue" ) {

  GIVEN( "valid data for a LValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 237.992;
      int l = 1;
      std::vector< JValue > jvalues =
        { { 1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
            { 4.314000e-3, 4.572000e-3, 4.740000e-3,
              5.000000e-3, 5.520000e-3, 7.057000e-3,
              8.251000e-3, 9.276000e-3, 9.930000e-3,
              1.035000e-2, 1.210000e-2, 1.341000e-2,
              1.456000e-2, 1.542000e-2 } } };

      LValue chunk( awri, l, std::move( jvalues ) );

      THEN( "a LValue can be constructed and members can be tested" ) {

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

      LValue chunk( begin, end, lineNumber, 9440, 2, 151 );

      THEN( "a LValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9440, 2, 151 );

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

    WHEN( "J value data with different numbers of fission widths are given" ) {

      double awri = 237.992;
      int l = 1;
      std::vector< JValue > jvalues =
        { { 0, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
            { 4.314000e-3, 4.572000e-3, 4.740000e-3,
              5.000000e-3, 5.520000e-3, 7.057000e-3,
              8.251000e-3, 9.276000e-3, 9.930000e-3,
              1.035000e-2, 1.210000e-2, 1.341000e-2,
              1.456000e-2, 1.542000e-2 } },
          { 1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
              { 4.314000e-3, 4.572000e-3, 4.740000e-3,
                5.000000e-3, 5.520000e-3, 7.057000e-3 } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( awri, l, std::move( jvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent number of fission widths" ) {

      std::string string = chunkWithInconsistentSize();
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
    " 2.379920+2 0.000000+0          1          0          1          09440 2151     \n"
    " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n";
}

void verifyChunk( const LValue& chunk ) {

  CHECK_THAT( 237.992, WithinRel( chunk.AWRI() ) );
  CHECK_THAT( 237.992, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );

  CHECK( 1 == chunk.NJS() );
  CHECK( 1 == chunk.numberSpinValues() );
  CHECK( 1 == chunk.jValues().size() );

  auto jvalue = chunk.jValues()[0];
  CHECK( 14 == jvalue.NE() );
  CHECK( 14 == jvalue.GF().size() );
  CHECK( 14 == jvalue.averageFissionWidths().size() );

  CHECK( 1 == jvalue.NR() );
  CHECK( 1 == jvalue.interpolants().size() );
  CHECK( 1 == jvalue.boundaries().size() );
  CHECK( 2 == jvalue.interpolants()[0] );
  CHECK( 14 == jvalue.boundaries()[0] );

  CHECK_THAT( 0.5, WithinRel( jvalue.AJ() ) );
  CHECK_THAT( 0.5, WithinRel( jvalue.spin() ) );
  CHECK_THAT( 13.1, WithinRel( jvalue.D() ) );
  CHECK_THAT( 13.1, WithinRel( jvalue.averageLevelSpacing() ) );
  CHECK( 1 == jvalue.AMUN() );
  CHECK( 1 == jvalue.neutronWidthDegreesFreedom() );
  CHECK( 0 == jvalue.AMUG() );
  CHECK( 0 == jvalue.gammaWidthDegreesFreedom() );
  CHECK( 1 == jvalue.AMUF() );
  CHECK( 1 == jvalue.fissionWidthDegreesFreedom() );
  CHECK( 0 == jvalue.AMUX() );
  CHECK( 0 == jvalue.competitiveWidthDegreesFreedom() );
  CHECK_THAT( 3.013000e-3, WithinRel( jvalue.GN() ) );
  CHECK_THAT( 3.013000e-3, WithinRel( jvalue.averageNeutronWidth() ) );
  CHECK_THAT( 3.100000e-2, WithinRel( jvalue.GG() ) );
  CHECK_THAT( 3.100000e-2, WithinRel( jvalue.averageGammaWidth() ) );

  CHECK_THAT( 4.314000e-3, WithinRel( jvalue.GF()[0] ) );
  CHECK_THAT( 4.572000e-3, WithinRel( jvalue.GF()[1] ) );
  CHECK_THAT( 4.740000e-3, WithinRel( jvalue.GF()[2] ) );
  CHECK_THAT( 5.000000e-3, WithinRel( jvalue.GF()[3] ) );
  CHECK_THAT( 5.520000e-3, WithinRel( jvalue.GF()[4] ) );
  CHECK_THAT( 7.057000e-3, WithinRel( jvalue.GF()[5] ) );
  CHECK_THAT( 8.251000e-3, WithinRel( jvalue.GF()[6] ) );
  CHECK_THAT( 9.276000e-3, WithinRel( jvalue.GF()[7] ) );
  CHECK_THAT( 9.930000e-3, WithinRel( jvalue.GF()[8] ) );
  CHECK_THAT( 1.035000e-2, WithinRel( jvalue.GF()[9] ) );
  CHECK_THAT( 1.210000e-2, WithinRel( jvalue.GF()[10] ) );
  CHECK_THAT( 1.341000e-2, WithinRel( jvalue.GF()[11] ) );
  CHECK_THAT( 1.456000e-2, WithinRel( jvalue.GF()[12] ) );
  CHECK_THAT( 1.542000e-2, WithinRel( jvalue.GF()[13] ) );
  CHECK_THAT( 4.314000e-3, WithinRel( jvalue.averageFissionWidths()[0] ) );
  CHECK_THAT( 4.572000e-3, WithinRel( jvalue.averageFissionWidths()[1] ) );
  CHECK_THAT( 4.740000e-3, WithinRel( jvalue.averageFissionWidths()[2] ) );
  CHECK_THAT( 5.000000e-3, WithinRel( jvalue.averageFissionWidths()[3] ) );
  CHECK_THAT( 5.520000e-3, WithinRel( jvalue.averageFissionWidths()[4] ) );
  CHECK_THAT( 7.057000e-3, WithinRel( jvalue.averageFissionWidths()[5] ) );
  CHECK_THAT( 8.251000e-3, WithinRel( jvalue.averageFissionWidths()[6] ) );
  CHECK_THAT( 9.276000e-3, WithinRel( jvalue.averageFissionWidths()[7] ) );
  CHECK_THAT( 9.930000e-3, WithinRel( jvalue.averageFissionWidths()[8] ) );
  CHECK_THAT( 1.035000e-2, WithinRel( jvalue.averageFissionWidths()[9] ) );
  CHECK_THAT( 1.210000e-2, WithinRel( jvalue.averageFissionWidths()[10] ) );
  CHECK_THAT( 1.341000e-2, WithinRel( jvalue.averageFissionWidths()[11] ) );
  CHECK_THAT( 1.456000e-2, WithinRel( jvalue.averageFissionWidths()[12] ) );
  CHECK_THAT( 1.542000e-2, WithinRel( jvalue.averageFissionWidths()[13] ) );
  CHECK_THAT( 0., WithinRel( jvalue.GX() ) );
  CHECK_THAT( 0., WithinRel( jvalue.averageCompetitiveWidth() ) );

  CHECK( 6 == chunk.NC() );
}

std::string chunkWithInconsistentSize() {
  return
    " 2.379920+2 0.000000+0          1          0          2          09440 2151     \n"
    " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n"
    " 0.000000+0 0.000000+0          1          1         12          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n";
}

std::string chunkWithNoJValues() {
  return
    " 2.379920+2 0.000000+0          1          0          0          09440 2151     \n";
}
