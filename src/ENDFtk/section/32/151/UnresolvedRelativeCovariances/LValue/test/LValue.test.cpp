#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

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
        chunk.print( output, 5655, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LValue chunk( begin, end, lineNumber, 5655, 2, 151 );

      THEN( "a LValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 5655, 2, 151 );

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

        CHECK_THROWS( LValue( begin, end, lineNumber, 5655, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.387090+2 0.000000+0          1          0         12          25655 2151     \n"
    " 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+05655 2151     \n";
}

void verifyChunk( const LValue& chunk ) {

  CHECK( 138.709 == Approx( chunk.AWRI() ) );
  CHECK( 138.709 == Approx( chunk.atomicWeightRatio() ) );
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

  CHECK( 0.5 == Approx( chunk.AJ()[0] ) );
  CHECK( 1.5 == Approx( chunk.AJ()[1] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[0] ) );
  CHECK( 1.5 == Approx( chunk.spinValues()[1] ) );
  CHECK( 0.528 == Approx( chunk.GNO()[0] ) );
  CHECK( 0.264 == Approx( chunk.GNO()[1] ) );
  CHECK( 0.528 == Approx( chunk.averageNeutronWidths()[0] ) );
  CHECK( 0.264 == Approx( chunk.averageNeutronWidths()[1] ) );
  CHECK( 0.090 == Approx( chunk.GG()[0] ) );
  CHECK( 0.091 == Approx( chunk.GG()[1] ) );
  CHECK( 0.090 == Approx( chunk.averageGammaWidths()[0] ) );
  CHECK( 0.091 == Approx( chunk.averageGammaWidths()[1] ) );
  CHECK( 1. == Approx( chunk.GF()[0] ) );
  CHECK( 2. == Approx( chunk.GF()[1] ) );
  CHECK( 1. == Approx( chunk.averageFissionWidths()[0] ) );
  CHECK( 2. == Approx( chunk.averageFissionWidths()[1] ) );
  CHECK( 3. == Approx( chunk.GX()[0] ) );
  CHECK( 4. == Approx( chunk.GX()[1] ) );
  CHECK( 3. == Approx( chunk.averageCompetitiveWidths()[0] ) );
  CHECK( 4. == Approx( chunk.averageCompetitiveWidths()[1] ) );

  CHECK( 0.5 == Approx( chunk.jValues()[0].AJ() ) );
  CHECK( 1.5 == Approx( chunk.jValues()[1].AJ() ) );
  CHECK( 0.5 == Approx( chunk.jValues()[0].spin() ) );
  CHECK( 1.5 == Approx( chunk.jValues()[1].spin() ) );
  CHECK( 0.528 == Approx( chunk.jValues()[0].GNO() ) );
  CHECK( 0.264 == Approx( chunk.jValues()[1].GNO() ) );
  CHECK( 0.528 == Approx( chunk.jValues()[0].averageNeutronWidth() ) );
  CHECK( 0.264 == Approx( chunk.jValues()[1].averageNeutronWidth() ) );
  CHECK( 0.090 == Approx( chunk.jValues()[0].GG() ) );
  CHECK( 0.091 == Approx( chunk.jValues()[1].GG() ) );
  CHECK( 0.090 == Approx( chunk.jValues()[0].averageGammaWidth() ) );
  CHECK( 0.091 == Approx( chunk.jValues()[1].averageGammaWidth() ) );
  CHECK( 1. == Approx( chunk.jValues()[0].GF() ) );
  CHECK( 2. == Approx( chunk.jValues()[1].GF() ) );
  CHECK( 1. == Approx( chunk.jValues()[0].averageFissionWidth() ) );
  CHECK( 2. == Approx( chunk.jValues()[1].averageFissionWidth() ) );
  CHECK( 3. == Approx( chunk.jValues()[0].GX() ) );
  CHECK( 4. == Approx( chunk.jValues()[1].GX() ) );
  CHECK( 3. == Approx( chunk.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 4. == Approx( chunk.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.387090+2 0.000000+0          1          0         12          15655 2151     \n"
    " 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+05655 2151     \n";
}
