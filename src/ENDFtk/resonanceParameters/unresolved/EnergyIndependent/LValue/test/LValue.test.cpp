#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using LValue = resonanceParameters::unresolved::EnergyIndependent::LValue;

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

  CHECK( 0.5 == Approx( chunk.AJ()[0] ) );
  CHECK( 1.5 == Approx( chunk.AJ()[1] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[0] ) );
  CHECK( 1.5 == Approx( chunk.spinValues()[1] ) );
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
  CHECK( 0.528 == Approx( chunk.GN()[0] ) );
  CHECK( 0.264 == Approx( chunk.GN()[1] ) );
  CHECK( 0.528 == Approx( chunk.averageNeutronWidths()[0] ) );
  CHECK( 0.264 == Approx( chunk.averageNeutronWidths()[1] ) );
  CHECK( 0.090 == Approx( chunk.GG()[0] ) );
  CHECK( 0.091 == Approx( chunk.GG()[1] ) );
  CHECK( 0.090 == Approx( chunk.averageGammaWidths()[0] ) );
  CHECK( 0.091 == Approx( chunk.averageGammaWidths()[1] ) );
  CHECK( 0. == Approx( chunk.GF()[0] ) );
  CHECK( 0. == Approx( chunk.GF()[1] ) );
  CHECK( 0. == Approx( chunk.averageFissionWidths()[0] ) );
  CHECK( 0. == Approx( chunk.averageFissionWidths()[1] ) );
  CHECK( 0. == Approx( chunk.GX()[0] ) );
  CHECK( 0. == Approx( chunk.GX()[1] ) );
  CHECK( 0. == Approx( chunk.averageCompetitiveWidths()[0] ) );
  CHECK( 0. == Approx( chunk.averageCompetitiveWidths()[1] ) );

  CHECK( 0.5 == Approx( chunk.jValues()[0].AJ() ) );
  CHECK( 1.5 == Approx( chunk.jValues()[1].AJ() ) );
  CHECK( 0.5 == Approx( chunk.jValues()[0].spin() ) );
  CHECK( 1.5 == Approx( chunk.jValues()[1].spin() ) );
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
  CHECK( 0.528 == Approx( chunk.jValues()[0].GN() ) );
  CHECK( 0.264 == Approx( chunk.jValues()[1].GN() ) );
  CHECK( 0.528 == Approx( chunk.jValues()[0].averageNeutronWidth() ) );
  CHECK( 0.264 == Approx( chunk.jValues()[1].averageNeutronWidth() ) );
  CHECK( 0.090 == Approx( chunk.jValues()[0].GG() ) );
  CHECK( 0.091 == Approx( chunk.jValues()[1].GG() ) );
  CHECK( 0.090 == Approx( chunk.jValues()[0].averageGammaWidth() ) );
  CHECK( 0.091 == Approx( chunk.jValues()[1].averageGammaWidth() ) );
  CHECK( 0. == Approx( chunk.jValues()[0].GF() ) );
  CHECK( 0. == Approx( chunk.jValues()[1].GF() ) );
  CHECK( 0. == Approx( chunk.jValues()[0].averageFissionWidth() ) );
  CHECK( 0. == Approx( chunk.jValues()[1].averageFissionWidth() ) );
  CHECK( 0. == Approx( chunk.jValues()[0].GX() ) );
  CHECK( 0. == Approx( chunk.jValues()[1].GX() ) );
  CHECK( 0. == Approx( chunk.jValues()[0].averageCompetitiveWidth() ) );
  CHECK( 0. == Approx( chunk.jValues()[1].averageCompetitiveWidth() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.387090+2 0.000000+0          1          0         12          15655 2151     \n"
    " 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n"
    " 2.200000+3 1.500000+0 2.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n";
}
