// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LValue = section::Type< 32, 151 >::UnresolvedRelativeCovariances::LValue;

std::string chunk();
void verifyChunk( const LValue& );
std::string invalidSize();

SCENARIO( "LValue" ) {

  GIVEN( "valid data for a LValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.387090e+2;
      double l = 1.;
      std::vector< double > d = { 4400., 2200. };
      std::vector< double > aj = { 0.5, 1.5 };
      std::vector< double > gno = { 0.528, 0.264 };
      std::vector< double > gg = { 0.09, 0.091 };
      std::vector< double > gf = { 1., 2. };
      std::vector< double > gx = { 3., 4. };

      LValue chunk( awri, l,
                    std::move( aj ), std::move( d ),
                    std::move( gno ), std::move( gg ),
                    std::move( gf ), std::move( gx ) );

      THEN( "a LValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 5655, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LValue chunk( begin, end, lineNumber, 5655, 32, 151 );

      THEN( "a LValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 5655, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      double awri = 1.387090e+2;
      double l = 1.;
      std::vector< double > d = { 4400., 2200. };
      std::vector< double > aj = { 0.5, 1.5 };
      std::vector< int > amun = { 1, 2 };
      std::vector< double > gno = { 0.528, 0.264 };
      std::vector< double > wrong = { 0.09 };
      std::vector< double > gf = { 1., 2. };
      std::vector< double > gx = { 3., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( awri, l,
                              std::move( aj ), std::move( d ),
                              std::move( gno ), std::move( wrong ),
                              std::move( gf ), std::move( gx ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NJS is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( begin, end, lineNumber, 5655, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.387090+2 0.000000+0          1          0         12          2565532151     \n"
    " 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+0565532151     \n"
    " 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+0565532151     \n";
}

void verifyChunk( const LValue& chunk ) {

  CHECK_THAT( 138.709, WithinRel( chunk.AWRI() ) );
  CHECK_THAT( 138.709, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );

  CHECK( 2 == chunk.NJS() );
  CHECK( 2 == chunk.numberSpinValues() );
  CHECK( 2 == chunk.AJ().size() );
  CHECK( 2 == chunk.spinValues().size() );
  CHECK( 2 == chunk.D().size() );
  CHECK( 2 == chunk.averageLevelSpacings().size() );
  CHECK( 2 == chunk.GNO().size() );
  CHECK( 2 == chunk.averageNeutronWidths().size() );
  CHECK( 2 == chunk.GG().size() );
  CHECK( 2 == chunk.averageGammaWidths().size() );
  CHECK( 2 == chunk.GF().size() );
  CHECK( 2 == chunk.averageFissionWidths().size() );
  CHECK( 2 == chunk.GX().size() );
  CHECK( 2 == chunk.averageCompetitiveWidths().size() );
  CHECK( 2 == chunk.jValues().size() );

  CHECK_THAT( 0.5, WithinRel( chunk.AJ()[0] ) );
  CHECK_THAT( 1.5, WithinRel( chunk.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinValues()[0] ) );
  CHECK_THAT( 1.5, WithinRel( chunk.spinValues()[1] ) );
  CHECK_THAT( 0.528, WithinRel( chunk.GNO()[0] ) );
  CHECK_THAT( 0.264, WithinRel( chunk.GNO()[1] ) );
  CHECK_THAT( 0.528, WithinRel( chunk.averageNeutronWidths()[0] ) );
  CHECK_THAT( 0.264, WithinRel( chunk.averageNeutronWidths()[1] ) );
  CHECK_THAT( 0.090, WithinRel( chunk.GG()[0] ) );
  CHECK_THAT( 0.091, WithinRel( chunk.GG()[1] ) );
  CHECK_THAT( 0.090, WithinRel( chunk.averageGammaWidths()[0] ) );
  CHECK_THAT( 0.091, WithinRel( chunk.averageGammaWidths()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.GF()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.GF()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.averageFissionWidths()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.averageFissionWidths()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.GX()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.GX()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.averageCompetitiveWidths()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.averageCompetitiveWidths()[1] ) );

  CHECK_THAT( 0.5, WithinRel( chunk.jValues()[0].AJ() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.jValues()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.jValues()[0].spin() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.jValues()[1].spin() ) );
  CHECK_THAT( 0.528, WithinRel( chunk.jValues()[0].GNO() ) );
  CHECK_THAT( 0.264, WithinRel( chunk.jValues()[1].GNO() ) );
  CHECK_THAT( 0.528, WithinRel( chunk.jValues()[0].averageNeutronWidth() ) );
  CHECK_THAT( 0.264, WithinRel( chunk.jValues()[1].averageNeutronWidth() ) );
  CHECK_THAT( 0.090, WithinRel( chunk.jValues()[0].GG() ) );
  CHECK_THAT( 0.091, WithinRel( chunk.jValues()[1].GG() ) );
  CHECK_THAT( 0.090, WithinRel( chunk.jValues()[0].averageGammaWidth() ) );
  CHECK_THAT( 0.091, WithinRel( chunk.jValues()[1].averageGammaWidth() ) );
  CHECK_THAT( 1., WithinRel( chunk.jValues()[0].GF() ) );
  CHECK_THAT( 2., WithinRel( chunk.jValues()[1].GF() ) );
  CHECK_THAT( 1., WithinRel( chunk.jValues()[0].averageFissionWidth() ) );
  CHECK_THAT( 2., WithinRel( chunk.jValues()[1].averageFissionWidth() ) );
  CHECK_THAT( 3., WithinRel( chunk.jValues()[0].GX() ) );
  CHECK_THAT( 4., WithinRel( chunk.jValues()[1].GX() ) );
  CHECK_THAT( 3., WithinRel( chunk.jValues()[0].averageCompetitiveWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.387090+2 0.000000+0          1          0         12          1565532151     \n"
    " 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+0565532151     \n"
    " 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+0565532151     \n";
}
