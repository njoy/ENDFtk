// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using JValue = section::Type< 2, 151 >::UnresolvedEnergyDependent::JValue;

std::string chunk();
void verifyChunk( const JValue& );
std::string invalidSize();
std::string invalidNJS();

SCENARIO( "JValue" ) {

  GIVEN( "valid data for a JValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int interpolation = 2;
      double spin = 3.;
      int amux = 0;
      int amun = 1;
      int amug = 3;
      int amuf = 2;
      std::vector< double > energies = { 2.25e+3, 3.5e+3,  2.5e+4 };
      std::vector< double > d = { 1.05857, 1.055928, 1.011535 };
      std::vector< double > gx = { 1., 2., 3. };
      std::vector< double > gn = { 9.567005e-5, 9.510382e-5, 8.847673e-5 };
      std::vector< double > gg = { 3.882094e-2, 3.884319e-2, 3.922727e-2 };
      std::vector< double > gf = { 2.893370e-1, 2.893379e-1, 2.893518e-1 };

      JValue chunk( spin, amun, amug, amuf, amux, interpolation,
                    std::move( energies ), std::move( d ),
                    std::move( gn ), std::move( gg ),
                    std::move( gf ), std::move( gx ) );

      THEN( "a JValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      JValue chunk( begin, end, lineNumber, 9228, 2, 151 );

      THEN( "a JValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the energy dependent widths are of inconsistent sizes" ) {

      int interpolation = 1;
      double spin = 3.;
      int amux = 0;
      int amun = 1;
      int amug = 3;
      int amuf = 2;
      std::vector< double > wrongEnergies = { 2.25e+3, 3.5e+3 };
      std::vector< double > d = { 1.05857, 1.055928, 1.01135 };
      std::vector< double > gx = { 1., 2., 3. };
      std::vector< double > gn = { 9.567005e-5, 9.510382e-5, 8.847673e-5 };
      std::vector< double > gg = { 3.882094e-2, 3.884319e-2, 3.922727e-2 };
      std::vector< double > gf = { 2.893370e-1, 2.893379e-1, 2.893518e-1 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( spin, amun, amug, amuf, amux, interpolation,
                              std::move( wrongEnergies ), std::move( d ),
                              std::move( gn ), std::move( gg ),
                              std::move( gf ), std::move( gx ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with wrong NPL is used" ) {

      // this is a list error, not every list error is tested

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( begin, end, lineNumber, 9228, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "empty vectors are used" ) {

      int interpolation = 1;
      double spin = 3.;
      int amux = 0;
      int amun = 1;
      int amug = 3;
      int amuf = 2;
      std::vector< double > energies = {};
      std::vector< double > d = {};
      std::vector< double > gx = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gf = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( spin, amun, amug, amuf, amux, interpolation,
                              std::move( energies ), std::move( d ),
                              std::move( gn ), std::move( gg ),
                              std::move( gf ), std::move( gx ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with NJS = 0 is used" ) {

      // this is a list error, not every list error is tested

      std::string string = invalidNJS();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( JValue( begin, end, lineNumber, 9228, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 3.000000+0 0.000000+0          2          0         24          39228 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+09228 2151     \n"
    " 2.250000+3 1.058570+0 1.000000+0 9.567005-5 3.882094-2 2.893370-19228 2151     \n"
    " 3.500000+3 1.055928+0 2.000000+0 9.510382-5 3.884319-2 2.893379-19228 2151     \n"
    " 2.500000+4 1.011535+0 3.000000+0 8.847673-5 3.922727-2 2.893518-19228 2151     \n";
}

void verifyChunk( const JValue& chunk ) {

  CHECK_THAT( 3., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 3., WithinRel( chunk.spin() ) );

  CHECK( 1 == chunk.AMUN() );
  CHECK( 1 == chunk.neutronWidthDegreesFreedom() );
  CHECK( 3 == chunk.AMUG() );
  CHECK( 3 == chunk.gammaWidthDegreesFreedom() );
  CHECK( 2 == chunk.AMUF() );
  CHECK( 2 == chunk.fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUX() );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom() );

  CHECK( 2 == chunk.INT() );

  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.boundaries()[0] );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.ES().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.D().size() );
  CHECK( 3 == chunk.averageLevelSpacings().size() );
  CHECK( 3 == chunk.GN().size() );
  CHECK( 3 == chunk.averageNeutronWidths().size() );
  CHECK( 3 == chunk.GG().size() );
  CHECK( 3 == chunk.averageGammaWidths().size() );
  CHECK( 3 == chunk.GF().size() );
  CHECK( 3 == chunk.averageFissionWidths().size() );
  CHECK( 3 == chunk.GX().size() );
  CHECK( 3 == chunk.averageCompetitiveWidths().size() );

  CHECK_THAT( 2.25e+3, WithinRel( chunk.ES()[0] ) );
  CHECK_THAT( 3.5e+3, WithinRel( chunk.ES()[1] ) );
  CHECK_THAT( 2.5e+4, WithinRel( chunk.ES()[2] ) );
  CHECK_THAT( 2.25e+3, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 3.5e+3, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2.5e+4, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.05857, WithinRel( chunk.D()[0] ) );
  CHECK_THAT( 1.055928, WithinRel( chunk.D()[1] ) );
  CHECK_THAT( 1.011535, WithinRel( chunk.D()[2] ) );
  CHECK_THAT( 1.05857, WithinRel( chunk.averageLevelSpacings()[0] ) );
  CHECK_THAT( 1.055928, WithinRel( chunk.averageLevelSpacings()[1] ) );
  CHECK_THAT( 1.011535, WithinRel( chunk.averageLevelSpacings()[2] ) );
  CHECK_THAT( 9.567005e-5, WithinRel( chunk.GN()[0] ) );
  CHECK_THAT( 9.510382e-5, WithinRel( chunk.GN()[1] ) );
  CHECK_THAT( 8.847673e-5, WithinRel( chunk.GN()[2] ) );
  CHECK_THAT( 9.567005e-5, WithinRel( chunk.averageNeutronWidths()[0] ) );
  CHECK_THAT( 9.510382e-5, WithinRel( chunk.averageNeutronWidths()[1] ) );
  CHECK_THAT( 8.847673e-5, WithinRel( chunk.averageNeutronWidths()[2] ) );
  CHECK_THAT( 3.882094e-2, WithinRel( chunk.GG()[0] ) );
  CHECK_THAT( 3.884319e-2, WithinRel( chunk.GG()[1] ) );
  CHECK_THAT( 3.922727e-2, WithinRel( chunk.GG()[2] ) );
  CHECK_THAT( 3.882094e-2, WithinRel( chunk.averageGammaWidths()[0] ) );
  CHECK_THAT( 3.884319e-2, WithinRel( chunk.averageGammaWidths()[1] ) );
  CHECK_THAT( 3.922727e-2, WithinRel( chunk.averageGammaWidths()[2] ) );
  CHECK_THAT( 2.893370e-1, WithinRel( chunk.GF()[0] ) );
  CHECK_THAT( 2.893379e-1, WithinRel( chunk.GF()[1] ) );
  CHECK_THAT( 2.893518e-1, WithinRel( chunk.GF()[2] ) );
  CHECK_THAT( 2.893370e-1, WithinRel( chunk.averageFissionWidths()[0] ) );
  CHECK_THAT( 2.893379e-1, WithinRel( chunk.averageFissionWidths()[1] ) );
  CHECK_THAT( 2.893518e-1, WithinRel( chunk.averageFissionWidths()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.GX()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.GX()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.GX()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.averageCompetitiveWidths()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageCompetitiveWidths()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageCompetitiveWidths()[2] ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidSize() {
  return
  " 3.000000+0 0.000000+0          2          0         20          49228 2151     \n"
  " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+09228 2151     \n"
  " 2.250000+3 1.058570+0 1.000000+0 9.567005-5 3.882094-2 2.893370-19228 2151     \n"
  " 3.500000+3 1.055928+0 2.000000+0 9.510382-5 3.884319-2 2.893379-19228 2151     \n"
  " 2.500000+4 1.011535+0                                            9228 2151     \n";
}

std::string invalidNJS() {
  return
  " 3.000000+0 0.000000+0          2          0          6          09228 2151     \n";
}
