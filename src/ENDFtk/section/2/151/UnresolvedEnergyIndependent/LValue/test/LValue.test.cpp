// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LValue = section::Type< 2, 151 >::UnresolvedEnergyIndependent::LValue;

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
      std::vector< int > amun = { 1, 2 };
      std::vector< double > gn = { 0.528, 0.264 };
      std::vector< double > gg = { 0.09, 0.091 };

      LValue chunk( awri, l,
                    std::move( aj ), std::move( d ), std::move( amun ),
                    std::move( gn ), std::move( gg ) );

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
      std::vector< double > gn = { 0.528, 0.264 };
      std::vector< double > wrong = { 0.09 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LValue( awri, l, std::move( aj ), std::move( d ),
                              std::move( amun ), std::move( gn ),
                              std::move( wrong ) ) );
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
    " 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 2.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n";
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
  CHECK( 2 == chunk.AMUN().size() );
  CHECK( 2 == chunk.neutronWidthDegreesFreedom().size() );
  CHECK( 2 == chunk.AMUG().size() );
  CHECK( 2 == chunk.gammaWidthDegreesFreedom().size() );
  CHECK( 2 == chunk.AMUF().size() );
  CHECK( 2 == chunk.fissionWidthDegreesFreedom().size() );
  CHECK( 2 == chunk.AMUX().size() );
  CHECK( 2 == chunk.competitiveWidthDegreesFreedom().size() );
  CHECK( 2 == chunk.GN().size() );
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
  CHECK( 1 == chunk.AMUN()[0] );
  CHECK( 2 == chunk.AMUN()[1] );
  CHECK( 1 == chunk.neutronWidthDegreesFreedom()[0] );
  CHECK( 2 == chunk.neutronWidthDegreesFreedom()[1] );
  CHECK( 0 == chunk.AMUG()[0] );
  CHECK( 0 == chunk.AMUG()[1] );
  CHECK( 0 == chunk.gammaWidthDegreesFreedom()[0] );
  CHECK( 0 == chunk.gammaWidthDegreesFreedom()[1] );
  CHECK( 0 == chunk.AMUF()[0] );
  CHECK( 0 == chunk.AMUF()[1] );
  CHECK( 0 == chunk.fissionWidthDegreesFreedom()[0] );
  CHECK( 0 == chunk.fissionWidthDegreesFreedom()[1] );
  CHECK( 0 == chunk.AMUX()[0] );
  CHECK( 0 == chunk.AMUX()[1] );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom()[0] );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom()[1] );
  CHECK_THAT( 0.528, WithinRel( chunk.GN()[0] ) );
  CHECK_THAT( 0.264, WithinRel( chunk.GN()[1] ) );
  CHECK_THAT( 0.528, WithinRel( chunk.averageNeutronWidths()[0] ) );
  CHECK_THAT( 0.264, WithinRel( chunk.averageNeutronWidths()[1] ) );
  CHECK_THAT( 0.090, WithinRel( chunk.GG()[0] ) );
  CHECK_THAT( 0.091, WithinRel( chunk.GG()[1] ) );
  CHECK_THAT( 0.090, WithinRel( chunk.averageGammaWidths()[0] ) );
  CHECK_THAT( 0.091, WithinRel( chunk.averageGammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.GF()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.averageFissionWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.averageFissionWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.GX()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.GX()[1] ) );
  CHECK_THAT( 0., WithinRel( chunk.averageCompetitiveWidths()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.averageCompetitiveWidths()[1] ) );

  CHECK_THAT( 0.5, WithinRel( chunk.jValues()[0].AJ() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.jValues()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.jValues()[0].spin() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.jValues()[1].spin() ) );
  CHECK( 1 == chunk.jValues()[0].AMUN() );
  CHECK( 2 == chunk.jValues()[1].AMUN() );
  CHECK( 1 == chunk.jValues()[0].neutronWidthDegreesFreedom() );
  CHECK( 2 == chunk.jValues()[1].neutronWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[0].AMUG() );
  CHECK( 0 == chunk.jValues()[1].AMUG() );
  CHECK( 0 == chunk.jValues()[0].gammaWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[1].gammaWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[0].AMUF() );
  CHECK( 0 == chunk.jValues()[1].AMUF() );
  CHECK( 0 == chunk.jValues()[0].fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[1].fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[0].AMUX() );
  CHECK( 0 == chunk.jValues()[1].AMUX() );
  CHECK( 0 == chunk.jValues()[0].competitiveWidthDegreesFreedom() );
  CHECK( 0 == chunk.jValues()[1].competitiveWidthDegreesFreedom() );
  CHECK_THAT( 0.528, WithinRel( chunk.jValues()[0].GN() ) );
  CHECK_THAT( 0.264, WithinRel( chunk.jValues()[1].GN() ) );
  CHECK_THAT( 0.528, WithinRel( chunk.jValues()[0].averageNeutronWidth() ) );
  CHECK_THAT( 0.264, WithinRel( chunk.jValues()[1].averageNeutronWidth() ) );
  CHECK_THAT( 0.090, WithinRel( chunk.jValues()[0].GG() ) );
  CHECK_THAT( 0.091, WithinRel( chunk.jValues()[1].GG() ) );
  CHECK_THAT( 0.090, WithinRel( chunk.jValues()[0].averageGammaWidth() ) );
  CHECK_THAT( 0.091, WithinRel( chunk.jValues()[1].averageGammaWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[0].GF() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[1].GF() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[0].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[1].averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[0].GX() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[1].GX() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[0].averageCompetitiveWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.387090+2 0.000000+0          1          0         12          15655 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 2.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n";
}
