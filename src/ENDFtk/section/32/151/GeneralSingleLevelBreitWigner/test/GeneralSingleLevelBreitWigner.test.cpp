// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ShortRangeBreitWignerBlock = section::Type< 32, 151 >::ShortRangeBreitWignerBlock;
using LongRangeCovarianceBlock = section::Type< 32, 151 >::LongRangeCovarianceBlock;
using GeneralSingleLevelBreitWigner = section::Type< 32, 151 >::GeneralSingleLevelBreitWigner;

std::string chunk();
void verifyChunk( const GeneralSingleLevelBreitWigner& );

SCENARIO( "GeneralSingleLevelBreitWigner" ) {

  GIVEN( "valid data for a GeneralSingleLevelBreitWigner" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double spi = 1.5;
      double ap = .33651;
      double dap = .0033651;
      unsigned int nls = 1;

      std::vector< ShortRangeBreitWignerBlock > cshort = {

        { 4,
          { -1.470000e+5, 4.730000e+5 }, { 0.5, 0.5 },
          { 5.470695e+2, 1.072946e+5 }, { 3.680695e+2, 1.072900e+5 },
          { 1.750000e+2, 5.600000e-1 }, { 3., 4. },
          {  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                 13., 14., 15., 16., 17., 18., 19.,
                      20., 21., 22., 23., 24., 25.,
                           26., 27., 28., 29., 30.,
                                31., 32., 33., 34.,
                                     35., 36., 37.,
                                          38., 39.,
                                               40. } } };

      std::vector< LongRangeCovarianceBlock > clong = {};

      GeneralSingleLevelBreitWigner chunk( awri, spi, ap, dap, nls,
                                           std::move( cshort ),
                                           std::move( clong ) );

      THEN( "a GeneralSingleLevelBreitWigner can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      GeneralSingleLevelBreitWigner chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a GeneralSingleLevelBreitWigner can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.500000+0 3.365100-1          0          1          1          1102532151     \n"
    " 0.000000+0 3.365100-3          0          0          0          0102532151     \n"
    " 1.982069+1 0.000000+0          0          0          1          0102532151     \n"
    " 0.000000+0 0.000000+0          4          0         48          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}

void verifyChunk( const GeneralSingleLevelBreitWigner& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 1 == chunk.LCOMP() );
  CHECK( 1 == chunk.covarianceRepresentation() );

  CHECK_THAT( 19.82069, WithinRel( chunk.AWRI() ) );
  CHECK_THAT( 19.82069, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK_THAT( 1.5, WithinRel( chunk.SPI() ) );
  CHECK_THAT( 1.5, WithinRel( chunk.spin() ) );
  CHECK_THAT( .33651, WithinRel( chunk.AP() ) );
  CHECK_THAT( .33651, WithinRel( chunk.scatteringRadius() ) );

  CHECK( .0033651 == chunk.DAP() );
  CHECK( .0033651 == chunk.scatteringRadiusUncertainty() );
  CHECK( true == chunk.ISR() );
  CHECK( true == chunk.scatteringRadiusUncertaintyFlag() );

  CHECK( 1 == chunk.NLS() );
  CHECK( 1 == chunk.numberLValues() );

  CHECK( 1 == chunk.NSRS() );
  CHECK( 1 == chunk.numberShortRangeBlocks() );
  CHECK( 0 == chunk.NLRS() );
  CHECK( 0 == chunk.numberLongRangeBlocks() );
  CHECK( 1 == chunk.shortRangeBlocks().size() );
  CHECK( 0 == chunk.longRangeBlocks().size() );

  auto block = chunk.shortRangeBlocks()[0];
  CHECK( 4 == block.MPAR() );
  CHECK( 4 == block.numberParametersWithCovariances() );

  CHECK( 2 == block.NRB() );
  CHECK( 2 == block.numberResonances() );
  CHECK( 2 == block.ER().size() );
  CHECK( 2 == block.resonanceEnergies().size() );
  CHECK( 2 == block.AJ().size() );
  CHECK( 2 == block.spinValues().size() );
  CHECK( 2 == block.GT().size() );
  CHECK( 2 == block.totalWidths().size() );
  CHECK( 2 == block.GN().size() );
  CHECK( 2 == block.neutronWidths().size() );
  CHECK( 2 == block.GG().size() );
  CHECK( 2 == block.gammaWidths().size() );
  CHECK( 2 == block.GF().size() );
  CHECK( 2 == block.fissionWidths().size() );

  CHECK_THAT( -1.470000e+5, WithinRel( block.ER()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( block.ER()[1] ) );
  CHECK_THAT( -1.470000e+5, WithinRel( block.resonanceEnergies()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( block.resonanceEnergies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( block.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( block.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( block.spinValues()[0] ) );
  CHECK_THAT( 0.5, WithinRel( block.spinValues()[1] ) );
  CHECK_THAT( 5.470695e+2, WithinRel( block.GT()[0] ) );
  CHECK_THAT( 1.072946e+5, WithinRel( block.GT()[1] ) );
  CHECK_THAT( 5.470695e+2, WithinRel( block.totalWidths()[0] ) );
  CHECK_THAT( 1.072946e+5, WithinRel( block.totalWidths()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( block.GN()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( block.GN()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( block.neutronWidths()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( block.neutronWidths()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( block.GG()[0] ) );
  CHECK_THAT( 0.56, WithinRel( block.GG()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( block.gammaWidths()[0] ) );
  CHECK_THAT( 0.56, WithinRel( block.gammaWidths()[1] ) );
  CHECK_THAT( 3., WithinRel( block.GF()[0] ) );
  CHECK_THAT( 4., WithinRel( block.GF()[1] ) );
  CHECK_THAT( 3., WithinRel( block.fissionWidths()[0] ) );
  CHECK_THAT( 4., WithinRel( block.fissionWidths()[1] ) );

  CHECK_THAT( -1.470000e+5, WithinRel( block.resonances()[0].ER() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( block.resonances()[1].ER() ) );
  CHECK_THAT( -1.470000e+5, WithinRel( block.resonances()[0].resonanceEnergy() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( block.resonances()[1].resonanceEnergy() ) );
  CHECK_THAT( 0.5, WithinRel( block.resonances()[0].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( block.resonances()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( block.resonances()[0].spin() ) );
  CHECK_THAT( 0.5, WithinRel( block.resonances()[1].spin() ) );
  CHECK_THAT( 5.470695e+2, WithinRel( block.resonances()[0].GT() ) );
  CHECK_THAT( 1.072946e+5, WithinRel( block.resonances()[1].GT() ) );
  CHECK_THAT( 5.470695e+2, WithinRel( block.resonances()[0].totalWidth() ) );
  CHECK_THAT( 1.072946e+5, WithinRel( block.resonances()[1].totalWidth() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( block.resonances()[0].GN() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( block.resonances()[1].GN() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( block.resonances()[0].neutronWidth() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( block.resonances()[1].neutronWidth() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( block.resonances()[0].GG() ) );
  CHECK_THAT( 0.56, WithinRel( block.resonances()[1].GG() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( block.resonances()[0].gammaWidth() ) );
  CHECK_THAT( 0.56, WithinRel( block.resonances()[1].gammaWidth() ) );
  CHECK_THAT( 3., WithinRel( block.resonances()[0].GF() ) );
  CHECK_THAT( 4., WithinRel( block.resonances()[1].GF() ) );
  CHECK_THAT( 3., WithinRel( block.resonances()[0].fissionWidth() ) );
  CHECK_THAT( 4., WithinRel( block.resonances()[1].fissionWidth() ) );

  CHECK( 8 == block.NPARB() );
  CHECK( 8 == block.covarianceMatrixOrder() );
  CHECK( 36 == block.covarianceMatrix().size() );
  CHECK( 36 == block.NVS() );
  CHECK( 36 == block.numberValues() );

  CHECK_THAT(  5., WithinRel( block.covarianceMatrix()[ 0] ) );
  CHECK_THAT(  6., WithinRel( block.covarianceMatrix()[ 1] ) );
  CHECK_THAT(  7., WithinRel( block.covarianceMatrix()[ 2] ) );
  CHECK_THAT(  8., WithinRel( block.covarianceMatrix()[ 3] ) );
  CHECK_THAT(  9., WithinRel( block.covarianceMatrix()[ 4] ) );
  CHECK_THAT( 10., WithinRel( block.covarianceMatrix()[ 5] ) );
  CHECK_THAT( 11., WithinRel( block.covarianceMatrix()[ 6] ) );
  CHECK_THAT( 12., WithinRel( block.covarianceMatrix()[ 7] ) );
  CHECK_THAT( 13., WithinRel( block.covarianceMatrix()[ 8] ) );
  CHECK_THAT( 14., WithinRel( block.covarianceMatrix()[ 9] ) );
  CHECK_THAT( 15., WithinRel( block.covarianceMatrix()[10] ) );
  CHECK_THAT( 16., WithinRel( block.covarianceMatrix()[11] ) );
  CHECK_THAT( 17., WithinRel( block.covarianceMatrix()[12] ) );
  CHECK_THAT( 18., WithinRel( block.covarianceMatrix()[13] ) );
  CHECK_THAT( 19., WithinRel( block.covarianceMatrix()[14] ) );
  CHECK_THAT( 20., WithinRel( block.covarianceMatrix()[15] ) );
  CHECK_THAT( 21., WithinRel( block.covarianceMatrix()[16] ) );
  CHECK_THAT( 22., WithinRel( block.covarianceMatrix()[17] ) );
  CHECK_THAT( 23., WithinRel( block.covarianceMatrix()[18] ) );
  CHECK_THAT( 24., WithinRel( block.covarianceMatrix()[19] ) );
  CHECK_THAT( 25., WithinRel( block.covarianceMatrix()[20] ) );
  CHECK_THAT( 26., WithinRel( block.covarianceMatrix()[21] ) );
  CHECK_THAT( 27., WithinRel( block.covarianceMatrix()[22] ) );
  CHECK_THAT( 28., WithinRel( block.covarianceMatrix()[23] ) );
  CHECK_THAT( 29., WithinRel( block.covarianceMatrix()[24] ) );
  CHECK_THAT( 30., WithinRel( block.covarianceMatrix()[25] ) );
  CHECK_THAT( 31., WithinRel( block.covarianceMatrix()[26] ) );
  CHECK_THAT( 32., WithinRel( block.covarianceMatrix()[27] ) );
  CHECK_THAT( 33., WithinRel( block.covarianceMatrix()[28] ) );
  CHECK_THAT( 34., WithinRel( block.covarianceMatrix()[29] ) );
  CHECK_THAT( 35., WithinRel( block.covarianceMatrix()[30] ) );
  CHECK_THAT( 36., WithinRel( block.covarianceMatrix()[31] ) );
  CHECK_THAT( 37., WithinRel( block.covarianceMatrix()[32] ) );
  CHECK_THAT( 38., WithinRel( block.covarianceMatrix()[33] ) );
  CHECK_THAT( 39., WithinRel( block.covarianceMatrix()[34] ) );
  CHECK_THAT( 40., WithinRel( block.covarianceMatrix()[35] ) );

  CHECK( 12 == chunk.NC() );
}
