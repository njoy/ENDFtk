#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using UnresolvedEnergyDependentFissionWidths = section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths;
using LValue = section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths::LValue;

std::string chunk();
void verifyChunk( const UnresolvedEnergyDependentFissionWidths& );
std::string chunkWithInconsistentSize();
std::string chunkWithNoLValues();

SCENARIO( "UnresolvedEnergyDependentFissionWidths" ) {

  GIVEN( "valid data for a UnresolvedEnergyDependentFissionWidths" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 0.0;
      double ap = 0.888;
      bool lssf = false;
      std::vector< double > energies =
        { 5.700000e+3, 7.000000e+3, 8.000000e+3, 9.000000e+3, 1.000000e+4,
          1.200000e+4, 1.400000e+4, 1.600000e+4, 1.800000e+4, 2.000000e+4,
          2.500000e+4, 3.000000e+4, 3.500000e+4, 4.000000e+4 };
      std::vector< LValue > lvalues =
        { { 237.992, 0, { { 0, 0.5, 13.1, 1, 1, 1.572e-3, 3.100000e-2,
                            { 1.256000e-3, 1.544000e-3, 1.825000e-3,
                              2.025000e-3, 2.119000e-3, 2.051000e-3,
                              1.992000e-3, 1.879000e-3, 1.860000e-3,
                              1.838000e-3, 1.694000e-3, 1.581000e-3,
                              1.481000e-3, 1.403000e-3 } } } },
          { 237.992, 1, { { 1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                            { 4.314000e-3, 4.572000e-3, 4.740000e-3,
                              5.000000e-3, 5.520000e-3, 7.057000e-3,
                              8.251000e-3, 9.276000e-3, 9.930000e-3,
                              1.035000e-2, 1.210000e-2, 1.341000e-2,
                              1.456000e-2, 1.542000e-2 } } } } };

      UnresolvedEnergyDependentFissionWidths chunk( spi, ap, lssf,
                                          std::move( energies ),
                                          std::move( lvalues ) );

      THEN( "a UnresolvedEnergyDependentFissionWidths can be constructed and members can "
            "be tested" ) {

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

      UnresolvedEnergyDependentFissionWidths chunk( begin, end, lineNumber,
                                          9440, 2, 151 );

      THEN( "a UnresolvedEnergyDependentFissionWidths can be constructed and members can "
            "be tested" ) {

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

    WHEN( "no l values are given" ) {

      double spi = 0.0;
      double ap = 0.888;
      bool lssf = false;
      std::vector< double > energies =
        { 5.700000e+3, 7.000000e+3, 8.000000e+3, 9.000000e+3, 1.000000e+4,
          1.200000e+4, 1.400000e+4, 1.600000e+4, 1.800000e+4, 2.000000e+4 };
      std::vector< LValue > lvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependentFissionWidths( spi, ap, lssf,
                                                    std::move( energies ),
                                                    std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "J value data with different numbers of fission widths are given" ) {

      double spi = 0.0;
      double ap = 0.888;
      bool lssf = false;
      std::vector< double > energies =
        { 5.700000e+3, 7.000000e+3, 8.000000e+3, 9.000000e+3, 1.000000e+4,
          1.200000e+4, 1.400000e+4, 1.600000e+4, 1.800000e+4, 2.000000e+4 };
      std::vector< LValue > lvalues =
        { { 237.992, 0, { { 0, 0.5, 13.1, 1, 1, 1.572e-3, 3.100000e-2,
                            { 1.256000e-3, 1.544000e-3, 1.825000e-3,
                              2.025000e-3, 2.119000e-3, 2.051000e-3,
                              1.992000e-3, 1.879000e-3, 1.860000e-3,
                              1.838000e-3, 1.694000e-3, 1.581000e-3,
                              1.481000e-3, 1.403000e-3 } } } },
          { 237.992, 1, { { 1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                            { 4.314000e-3, 4.572000e-3, 4.740000e-3,
                              5.000000e-3, 5.520000e-3, 7.057000e-3,
                              8.251000e-3, 9.276000e-3, 9.930000e-3,
                              1.035000e-2, 1.210000e-2, 1.341000e-2,
                              1.456000e-2, 1.542000e-2 } } } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependentFissionWidths( spi, ap, lssf,
                                                    std::move( energies ),
                                                    std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no l values is used" ) {

      std::string string = chunkWithNoLValues();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependentFissionWidths( begin, end, lineNumber,
                                                    9440, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent number of fission widths" ) {

      std::string string = chunkWithInconsistentSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedEnergyDependentFissionWidths( begin, end, lineNumber,
                                                    9440, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 8.880000-1          0          0         14          29440 2151     \n"
    " 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n"
    " 1.400000+4 1.600000+4 1.800000+4 2.000000+4 2.500000+4 3.000000+49440 2151     \n"
    " 3.500000+4 4.000000+4                                            9440 2151     \n"
    " 2.379920+2 0.000000+0          0          0          1          09440 2151     \n"
    " 0.000000+0 0.000000+0          0          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+09440 2151     \n"
    " 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-39440 2151     \n"
    " 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-39440 2151     \n"
    " 1.481000-3 1.403000-3                                            9440 2151     \n"
    " 2.379920+2 0.000000+0          1          0          1          09440 2151     \n"
    " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
    " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
    " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
    " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
    " 1.456000-2 1.542000-2                                            9440 2151     \n";
}

void verifyChunk( const UnresolvedEnergyDependentFissionWidths& chunk ) {

  CHECK( 2 == chunk.LRU() );
  CHECK( 2 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( true == chunk.LFW() );
  CHECK( true == chunk.averageFissionWidthFlag() );

  CHECK( 0.0 == Approx( chunk.SPI() ) );
  CHECK( 0.0 == Approx( chunk.spin() ) );
  CHECK( 0.888 == Approx( chunk.AP() ) );
  CHECK( 0.888 == Approx( chunk.scatteringRadius() ) );
  CHECK( false == Approx( chunk.LSSF() ) );
  CHECK( false == Approx( chunk.selfShieldingOnly() ) );

  CHECK( 2 == chunk.NLS() );

  CHECK( 14 == chunk.NE() );
  CHECK( 5.700000e+3 == Approx( chunk.ES()[0] ) );
  CHECK( 7.000000e+3 == Approx( chunk.ES()[1] ) );
  CHECK( 8.000000e+3 == Approx( chunk.ES()[2] ) );
  CHECK( 9.000000e+3 == Approx( chunk.ES()[3] ) );
  CHECK( 1.000000e+4 == Approx( chunk.ES()[4] ) );
  CHECK( 1.200000e+4 == Approx( chunk.ES()[5] ) );
  CHECK( 1.400000e+4 == Approx( chunk.ES()[6] ) );
  CHECK( 1.600000e+4 == Approx( chunk.ES()[7] ) );
  CHECK( 1.800000e+4 == Approx( chunk.ES()[8] ) );
  CHECK( 2.000000e+4 == Approx( chunk.ES()[9] ) );
  CHECK( 2.500000e+4 == Approx( chunk.ES()[10] ) );
  CHECK( 3.000000e+4 == Approx( chunk.ES()[11] ) );
  CHECK( 3.500000e+4 == Approx( chunk.ES()[12] ) );
  CHECK( 4.000000e+4 == Approx( chunk.ES()[13] ) );
  CHECK( 5.700000e+3 == Approx( chunk.energies()[0] ) );
  CHECK( 7.000000e+3 == Approx( chunk.energies()[1] ) );
  CHECK( 8.000000e+3 == Approx( chunk.energies()[2] ) );
  CHECK( 9.000000e+3 == Approx( chunk.energies()[3] ) );
  CHECK( 1.000000e+4 == Approx( chunk.energies()[4] ) );
  CHECK( 1.200000e+4 == Approx( chunk.energies()[5] ) );
  CHECK( 1.400000e+4 == Approx( chunk.energies()[6] ) );
  CHECK( 1.600000e+4 == Approx( chunk.energies()[7] ) );
  CHECK( 1.800000e+4 == Approx( chunk.energies()[8] ) );
  CHECK( 2.000000e+4 == Approx( chunk.energies()[9] ) );
  CHECK( 2.500000e+4 == Approx( chunk.energies()[10] ) );
  CHECK( 3.000000e+4 == Approx( chunk.energies()[11] ) );
  CHECK( 3.500000e+4 == Approx( chunk.energies()[12] ) );
  CHECK( 4.000000e+4 == Approx( chunk.energies()[13] ) );

  auto lvalue0 = chunk.lValues()[0];
  CHECK( 237.992 == Approx( lvalue0.AWRI() ) );
  CHECK( 237.992 == Approx( lvalue0.atomicWeightRatio() ) );
  CHECK( 0 == lvalue0.L() );
  CHECK( 0 == lvalue0.orbitalMomentum() );

  CHECK( 1 == lvalue0.NJS() );
  CHECK( 1 == lvalue0.numberSpinValues() );
  CHECK( 1 == lvalue0.jValues().size() );

  auto jvalue0 = lvalue0.jValues()[0];
  CHECK( 14 == jvalue0.NE() );
  CHECK( 14 == jvalue0.GF().size() );
  CHECK( 14 == jvalue0.averageFissionWidths().size() );

  CHECK( 1 == jvalue0.NR() );
  CHECK( 1 == jvalue0.interpolants().size() );
  CHECK( 1 == jvalue0.boundaries().size() );
  CHECK( 2 == jvalue0.interpolants()[0] );
  CHECK( 14 == jvalue0.boundaries()[0] );

  CHECK( 0.5 == Approx( jvalue0.AJ() ) );
  CHECK( 0.5 == Approx( jvalue0.spin() ) );
  CHECK( 13.1 == Approx( jvalue0.D() ) );
  CHECK( 13.1 == Approx( jvalue0.averageLevelSpacing() ) );
  CHECK( 1 == jvalue0.AMUN() );
  CHECK( 1 == jvalue0.neutronWidthDegreesFreedom() );
  CHECK( 0 == jvalue0.AMUG() );
  CHECK( 0 == jvalue0.gammaWidthDegreesFreedom() );
  CHECK( 1 == jvalue0.AMUF() );
  CHECK( 1 == jvalue0.fissionWidthDegreesFreedom() );
  CHECK( 0 == jvalue0.AMUX() );
  CHECK( 0 == jvalue0.competitiveWidthDegreesFreedom() );
  CHECK( 1.572e-3 == Approx( jvalue0.GN() ) );
  CHECK( 1.572e-3 == Approx( jvalue0.averageNeutronWidth() ) );
  CHECK( 3.100000e-2 == Approx( jvalue0.GG() ) );
  CHECK( 3.100000e-2 == Approx( jvalue0.averageGammaWidth() ) );

  CHECK( 1.256000e-3 == Approx( jvalue0.GF()[0] ) );
  CHECK( 1.544000e-3 == Approx( jvalue0.GF()[1] ) );
  CHECK( 1.825000e-3 == Approx( jvalue0.GF()[2] ) );
  CHECK( 2.025000e-3 == Approx( jvalue0.GF()[3] ) );
  CHECK( 2.119000e-3 == Approx( jvalue0.GF()[4] ) );
  CHECK( 2.051000e-3 == Approx( jvalue0.GF()[5] ) );
  CHECK( 1.992000e-3 == Approx( jvalue0.GF()[6] ) );
  CHECK( 1.879000e-3 == Approx( jvalue0.GF()[7] ) );
  CHECK( 1.860000e-3 == Approx( jvalue0.GF()[8] ) );
  CHECK( 1.838000e-3 == Approx( jvalue0.GF()[9] ) );
  CHECK( 1.694000e-3 == Approx( jvalue0.GF()[10] ) );
  CHECK( 1.581000e-3 == Approx( jvalue0.GF()[11] ) );
  CHECK( 1.481000e-3 == Approx( jvalue0.GF()[12] ) );
  CHECK( 1.403000e-3 == Approx( jvalue0.GF()[13] ) );
  CHECK( 1.256000e-3 == Approx( jvalue0.averageFissionWidths()[0] ) );
  CHECK( 1.544000e-3 == Approx( jvalue0.averageFissionWidths()[1] ) );
  CHECK( 1.825000e-3 == Approx( jvalue0.averageFissionWidths()[2] ) );
  CHECK( 2.025000e-3 == Approx( jvalue0.averageFissionWidths()[3] ) );
  CHECK( 2.119000e-3 == Approx( jvalue0.averageFissionWidths()[4] ) );
  CHECK( 2.051000e-3 == Approx( jvalue0.averageFissionWidths()[5] ) );
  CHECK( 1.992000e-3 == Approx( jvalue0.averageFissionWidths()[6] ) );
  CHECK( 1.879000e-3 == Approx( jvalue0.averageFissionWidths()[7] ) );
  CHECK( 1.860000e-3 == Approx( jvalue0.averageFissionWidths()[8] ) );
  CHECK( 1.838000e-3 == Approx( jvalue0.averageFissionWidths()[9] ) );
  CHECK( 1.694000e-3 == Approx( jvalue0.averageFissionWidths()[10] ) );
  CHECK( 1.581000e-3 == Approx( jvalue0.averageFissionWidths()[11] ) );
  CHECK( 1.481000e-3 == Approx( jvalue0.averageFissionWidths()[12] ) );
  CHECK( 1.403000e-3 == Approx( jvalue0.averageFissionWidths()[13] ) );
  CHECK( 0. == Approx( jvalue0.GX() ) );
  CHECK( 0. == Approx( jvalue0.averageCompetitiveWidth() ) );

  auto lvalue1 = chunk.lValues()[1];
  CHECK( 237.992 == Approx( lvalue1.AWRI() ) );
  CHECK( 237.992 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 1 == lvalue1.L() );
  CHECK( 1 == lvalue1.orbitalMomentum() );

  CHECK( 1 == lvalue1.NJS() );
  CHECK( 1 == lvalue1.numberSpinValues() );
  CHECK( 1 == lvalue1.jValues().size() );

  auto jvalue1 = lvalue1.jValues()[0];
  CHECK( 14 == jvalue1.NE() );
  CHECK( 14 == jvalue1.GF().size() );
  CHECK( 14 == jvalue1.averageFissionWidths().size() );

  CHECK( 1 == jvalue1.NR() );
  CHECK( 1 == jvalue1.interpolants().size() );
  CHECK( 1 == jvalue1.boundaries().size() );
  CHECK( 2 == jvalue1.interpolants()[0] );
  CHECK( 14 == jvalue1.boundaries()[0] );

  CHECK( 0.5 == Approx( jvalue1.AJ() ) );
  CHECK( 0.5 == Approx( jvalue1.spin() ) );
  CHECK( 13.1 == Approx( jvalue1.D() ) );
  CHECK( 13.1 == Approx( jvalue1.averageLevelSpacing() ) );
  CHECK( 1 == jvalue1.AMUN() );
  CHECK( 1 == jvalue1.neutronWidthDegreesFreedom() );
  CHECK( 0 == jvalue1.AMUG() );
  CHECK( 0 == jvalue1.gammaWidthDegreesFreedom() );
  CHECK( 1 == jvalue1.AMUF() );
  CHECK( 1 == jvalue1.fissionWidthDegreesFreedom() );
  CHECK( 0 == jvalue1.AMUX() );
  CHECK( 0 == jvalue1.competitiveWidthDegreesFreedom() );
  CHECK( 3.013000e-3 == Approx( jvalue1.GN() ) );
  CHECK( 3.013000e-3 == Approx( jvalue1.averageNeutronWidth() ) );
  CHECK( 3.100000e-2 == Approx( jvalue1.GG() ) );
  CHECK( 3.100000e-2 == Approx( jvalue1.averageGammaWidth() ) );

  CHECK( 4.314000e-3 == Approx( jvalue1.GF()[0] ) );
  CHECK( 4.572000e-3 == Approx( jvalue1.GF()[1] ) );
  CHECK( 4.740000e-3 == Approx( jvalue1.GF()[2] ) );
  CHECK( 5.000000e-3 == Approx( jvalue1.GF()[3] ) );
  CHECK( 5.520000e-3 == Approx( jvalue1.GF()[4] ) );
  CHECK( 7.057000e-3 == Approx( jvalue1.GF()[5] ) );
  CHECK( 8.251000e-3 == Approx( jvalue1.GF()[6] ) );
  CHECK( 9.276000e-3 == Approx( jvalue1.GF()[7] ) );
  CHECK( 9.930000e-3 == Approx( jvalue1.GF()[8] ) );
  CHECK( 1.035000e-2 == Approx( jvalue1.GF()[9] ) );
  CHECK( 1.210000e-2 == Approx( jvalue1.GF()[10] ) );
  CHECK( 1.341000e-2 == Approx( jvalue1.GF()[11] ) );
  CHECK( 1.456000e-2 == Approx( jvalue1.GF()[12] ) );
  CHECK( 1.542000e-2 == Approx( jvalue1.GF()[13] ) );
  CHECK( 4.314000e-3 == Approx( jvalue1.averageFissionWidths()[0] ) );
  CHECK( 4.572000e-3 == Approx( jvalue1.averageFissionWidths()[1] ) );
  CHECK( 4.740000e-3 == Approx( jvalue1.averageFissionWidths()[2] ) );
  CHECK( 5.000000e-3 == Approx( jvalue1.averageFissionWidths()[3] ) );
  CHECK( 5.520000e-3 == Approx( jvalue1.averageFissionWidths()[4] ) );
  CHECK( 7.057000e-3 == Approx( jvalue1.averageFissionWidths()[5] ) );
  CHECK( 8.251000e-3 == Approx( jvalue1.averageFissionWidths()[6] ) );
  CHECK( 9.276000e-3 == Approx( jvalue1.averageFissionWidths()[7] ) );
  CHECK( 9.930000e-3 == Approx( jvalue1.averageFissionWidths()[8] ) );
  CHECK( 1.035000e-2 == Approx( jvalue1.averageFissionWidths()[9] ) );
  CHECK( 1.210000e-2 == Approx( jvalue1.averageFissionWidths()[10] ) );
  CHECK( 1.341000e-2 == Approx( jvalue1.averageFissionWidths()[11] ) );
  CHECK( 1.456000e-2 == Approx( jvalue1.averageFissionWidths()[12] ) );
  CHECK( 1.542000e-2 == Approx( jvalue1.averageFissionWidths()[13] ) );
  CHECK( 0. == Approx( jvalue1.GX() ) );
  CHECK( 0. == Approx( jvalue1.averageCompetitiveWidth() ) );

  CHECK( 16 == chunk.NC() );
}

std::string chunkWithInconsistentSize() {
  return // 10 energy values, 14 widths for each l,J value
  " 0.000000+0 8.880000-1          0          0         10          29440 2151     \n"
  " 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n"
  " 1.400000+4 1.600000+4 1.800000+4 2.000000+4                      9440 2151     \n"
  " 2.379920+2 0.000000+0          0          0          1          09440 2151     \n"
  " 0.000000+0 0.000000+0          0          1         20          09440 2151     \n"
  " 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+09440 2151     \n"
  " 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-39440 2151     \n"
  " 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-39440 2151     \n"
  " 1.481000-3 1.403000-3                                            9440 2151     \n"
  " 2.379920+2 0.000000+0          1          0          1          09440 2151     \n"
  " 0.000000+0 0.000000+0          1          1         20          09440 2151     \n"
  " 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n"
  " 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n"
  " 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n"
  " 1.456000-2 1.542000-2                                            9440 2151     \n";
}

std::string chunkWithNoLValues() {
  return
  " 0.000000+0 8.880000-1          0          0         10          09440 2151     \n"
  " 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n"
  " 1.400000+4 1.600000+4 1.800000+4 2.000000+4                      9440 2151     \n";
}
