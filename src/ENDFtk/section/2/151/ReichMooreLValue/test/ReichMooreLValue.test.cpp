// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReichMooreLValue =
section::Type< 2, 151 >::ReichMooreLValue;

std::string chunk();
void verifyChunk( const ReichMooreLValue& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "ReichMooreLValue" ) {

  GIVEN( "valid data for a ReichMooreLValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double apl = 0.0;
      double l = 1.;
      std::vector< double > er = { -1.470000e+5, 4.730000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 5.430695e+2, 1.072906e+5 };
      std::vector< double > gg = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gfa = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gfb = { 3., 4. };

      ReichMooreLValue chunk( awri, apl, l,
                              std::move( er ), std::move( aj ),
                              std::move( gn ), std::move( gg ),
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

    WHEN( "the data is empty" ) {

      double awri = 1.982069e+1;
      double qx = 1.0;
      double l = 1.;
      std::vector< double > er = {};
      std::vector< double > aj = {};
      std::vector< double > gt = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gf = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMooreLValue( awri, qx, l,
                                        std::move( er ), std::move( aj ),
                                        std::move( gt ), std::move( gn ),
                                        std::move( gg ), std::move( gf ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different sizes" ) {

      double awri = 1.982069e+1;
      double qx = 1.0;
      double l = 1.;
      std::vector< double > wrong = { -1.470000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gt = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gf = { 3., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMooreLValue( awri, qx, l,
                                        std::move( wrong ), std::move( aj ),
                                        std::move( gt ), std::move( gn ),
                                        std::move( gg ), std::move( gf ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMooreLValue( begin, end, lineNumber, 1025, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReichMooreLValue( begin, end, lineNumber, 1025, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = noNumberResonances();
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

  CHECK_THAT( 1.982069e+1, WithinRel( chunk.AWRI() ) );
  CHECK_THAT( 1.982069e+1, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 0., WithinRel( chunk.APL() ) );
  CHECK_THAT( 0., WithinRel( chunk.lDependentScatteringRadius() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );

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

  CHECK_THAT( -1.470000e+5, WithinRel( chunk.ER()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.ER()[1] ) );
  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonanceEnergies()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonanceEnergies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinValues()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinValues()[1] ) );
  CHECK_THAT( 5.430695e+2, WithinRel( chunk.GN()[0] ) );
  CHECK_THAT( 1.072906e+5, WithinRel( chunk.GN()[1] ) );
  CHECK_THAT( 5.430695e+2, WithinRel( chunk.neutronWidths()[0] ) );
  CHECK_THAT( 1.072906e+5, WithinRel( chunk.neutronWidths()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.GG()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.GG()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.gammaWidths()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.gammaWidths()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.GFA()[0] ) );
  CHECK_THAT( 0.56, WithinRel( chunk.GFA()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.firstFissionWidths()[0] ) );
  CHECK_THAT( 0.56, WithinRel( chunk.firstFissionWidths()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.GFB()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.GFB()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.secondFissionWidths()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.secondFissionWidths()[1] ) );

  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonances()[0].ER() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonances()[1].ER() ) );
  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonances()[0].resonanceEnergy() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonances()[1].resonanceEnergy() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[0].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[0].spin() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[1].spin() ) );
  CHECK_THAT( 5.430695e+2, WithinRel( chunk.resonances()[0].GN() ) );
  CHECK_THAT( 1.072906e+5, WithinRel( chunk.resonances()[1].GN() ) );
  CHECK_THAT( 5.430695e+2, WithinRel( chunk.resonances()[0].neutronWidth() ) );
  CHECK_THAT( 1.072906e+5, WithinRel( chunk.resonances()[1].neutronWidth() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.resonances()[0].GG() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.resonances()[1].GG() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.resonances()[0].gammaWidth() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.resonances()[1].gammaWidth() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.resonances()[0].GFA() ) );
  CHECK_THAT( 0.56, WithinRel( chunk.resonances()[1].GFA() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.resonances()[0].firstFissionWidth() ) );
  CHECK_THAT( 0.56, WithinRel( chunk.resonances()[1].firstFissionWidth() ) );
  CHECK_THAT( 3., WithinRel( chunk.resonances()[0].GFB() ) );
  CHECK_THAT( 4., WithinRel( chunk.resonances()[1].GFB() ) );
  CHECK_THAT( 3., WithinRel( chunk.resonances()[0].secondFissionWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.resonances()[1].secondFissionWidth() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 0.000000+0          0          0         11          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1           1025 2151     \n";
}

std::string zeroSize() {
  return
    " 1.982069+1 0.000000+0          0          0          0          21025 2151     \n";
}

std::string noNumberResonances() {
  return
    " 1.982069+1 1.000000+0          1          1         12          01025 2151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n";
}
