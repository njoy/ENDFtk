#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ShortRangeReichMooreBlock = section::Type< 32, 151 >::ShortRangeReichMooreBlock;
using LongRangeCovarianceBlock = section::Type< 32, 151 >::LongRangeCovarianceBlock;
using GeneralReichMoore = section::Type< 32, 151 >::GeneralReichMoore;

std::string chunk();
void verifyChunk( const GeneralReichMoore& );

SCENARIO( "GeneralReichMoore" ) {

  GIVEN( "valid data for a GeneralReichMoore" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double spi = 1.5;
      double ap = .33651;
      unsigned int nls = 1;

      std::vector< ShortRangeReichMooreBlock > cshort = {

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

      GeneralReichMoore chunk( awri, spi, ap, nls, std::move( cshort ),
                               std::move( clong ) );

      THEN( "a GeneralReichMoore can be constructed and members can be "
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

      GeneralReichMoore chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a GeneralReichMoore can be constructed and members can be "
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
    " 1.500000+0 3.365100-1          0          1          1          0102532151     \n"
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

void verifyChunk( const GeneralReichMoore& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 3 == chunk.LRF() );
  CHECK( 3 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 1 == chunk.LCOMP() );
  CHECK( 1 == chunk.covarianceRepresentation() );

  CHECK( 19.82069 == Approx( chunk.AWRI() ) );
  CHECK( 19.82069 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( 1.5 == Approx( chunk.SPI() ) );
  CHECK( 1.5 == Approx( chunk.spin() ) );
  CHECK( .33651 == Approx( chunk.AP() ) );
  CHECK( .33651 == Approx( chunk.scatteringRadius() ) );

  CHECK( std::nullopt == chunk.DAP() );
  CHECK( std::nullopt == chunk.scatteringRadiusUncertainty() );
  CHECK( false == chunk.ISR() );
  CHECK( false == chunk.scatteringRadiusUncertaintyFlag() );

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
  CHECK( 2 == block.GN().size() );
  CHECK( 2 == block.gammaWidths().size() );
  CHECK( 2 == block.GG().size() );
  CHECK( 2 == block.firstFissionWidths().size() );
  CHECK( 2 == block.GFA().size() );
  CHECK( 2 == block.firstFissionWidths().size() );
  CHECK( 2 == block.GFB().size() );
  CHECK( 2 == block.secondFissionWidths().size() );

  CHECK( -1.470000e+5 == Approx( block.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( block.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( block.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( block.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( block.AJ()[0] ) );
  CHECK( 0.5 == Approx( block.AJ()[1] ) );
  CHECK( 0.5 == Approx( block.spinValues()[0] ) );
  CHECK( 0.5 == Approx( block.spinValues()[1] ) );
  CHECK( 5.470695e+2 == Approx( block.GN()[0] ) );
  CHECK( 1.072946e+5 == Approx( block.GN()[1] ) );
  CHECK( 5.470695e+2 == Approx( block.neutronWidths()[0] ) );
  CHECK( 1.072946e+5 == Approx( block.neutronWidths()[1] ) );
  CHECK( 3.680695e+2 == Approx( block.GG()[0] ) );
  CHECK( 1.072900e+5 == Approx( block.GG()[1] ) );
  CHECK( 3.680695e+2 == Approx( block.gammaWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( block.gammaWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( block.GFA()[0] ) );
  CHECK( 0.56 == Approx( block.GFA()[1] ) );
  CHECK( 1.750000e+2 == Approx( block.firstFissionWidths()[0] ) );
  CHECK( 0.56 == Approx( block.firstFissionWidths()[1] ) );
  CHECK( 3. == Approx( block.GFB()[0] ) );
  CHECK( 4. == Approx( block.GFB()[1] ) );
  CHECK( 3. == Approx( block.secondFissionWidths()[0] ) );
  CHECK( 4. == Approx( block.secondFissionWidths()[1] ) );

  CHECK( -1.470000e+5 == Approx( block.resonances()[0].ER() ) );
  CHECK(  4.730000e+5 == Approx( block.resonances()[1].ER() ) );
  CHECK( -1.470000e+5 == Approx( block.resonances()[0].resonanceEnergy() ) );
  CHECK(  4.730000e+5 == Approx( block.resonances()[1].resonanceEnergy() ) );
  CHECK( 0.5 == Approx( block.resonances()[0].AJ() ) );
  CHECK( 0.5 == Approx( block.resonances()[1].AJ() ) );
  CHECK( 0.5 == Approx( block.resonances()[0].spin() ) );
  CHECK( 0.5 == Approx( block.resonances()[1].spin() ) );
  CHECK( 5.470695e+2 == Approx( block.resonances()[0].GN() ) );
  CHECK( 1.072946e+5 == Approx( block.resonances()[1].GN() ) );
  CHECK( 5.470695e+2 == Approx( block.resonances()[0].neutronWidth() ) );
  CHECK( 1.072946e+5 == Approx( block.resonances()[1].neutronWidth() ) );
  CHECK( 3.680695e+2 == Approx( block.resonances()[0].GG() ) );
  CHECK( 1.072900e+5 == Approx( block.resonances()[1].GG() ) );
  CHECK( 3.680695e+2 == Approx( block.resonances()[0].gammaWidth() ) );
  CHECK( 1.072900e+5 == Approx( block.resonances()[1].gammaWidth() ) );
  CHECK( 1.750000e+2 == Approx( block.resonances()[0].GFA() ) );
  CHECK( 0.56 == Approx( block.resonances()[1].GFA() ) );
  CHECK( 1.750000e+2 == Approx( block.resonances()[0].firstFissionWidth() ) );
  CHECK( 0.56 == Approx( block.resonances()[1].firstFissionWidth() ) );
  CHECK( 3. == Approx( block.resonances()[0].GFB() ) );
  CHECK( 4. == Approx( block.resonances()[1].GFB() ) );
  CHECK( 3. == Approx( block.resonances()[0].secondFissionWidth() ) );
  CHECK( 4. == Approx( block.resonances()[1].secondFissionWidth() ) );

  CHECK( 8 == block.NPARB() );
  CHECK( 8 == block.covarianceMatrixOrder() );
  CHECK( 36 == block.covarianceMatrix().size() );
  CHECK( 36 == block.NVS() );
  CHECK( 36 == block.numberValues() );

  CHECK(  5. == Approx( block.covarianceMatrix()[ 0] ) );
  CHECK(  6. == Approx( block.covarianceMatrix()[ 1] ) );
  CHECK(  7. == Approx( block.covarianceMatrix()[ 2] ) );
  CHECK(  8. == Approx( block.covarianceMatrix()[ 3] ) );
  CHECK(  9. == Approx( block.covarianceMatrix()[ 4] ) );
  CHECK( 10. == Approx( block.covarianceMatrix()[ 5] ) );
  CHECK( 11. == Approx( block.covarianceMatrix()[ 6] ) );
  CHECK( 12. == Approx( block.covarianceMatrix()[ 7] ) );
  CHECK( 13. == Approx( block.covarianceMatrix()[ 8] ) );
  CHECK( 14. == Approx( block.covarianceMatrix()[ 9] ) );
  CHECK( 15. == Approx( block.covarianceMatrix()[10] ) );
  CHECK( 16. == Approx( block.covarianceMatrix()[11] ) );
  CHECK( 17. == Approx( block.covarianceMatrix()[12] ) );
  CHECK( 18. == Approx( block.covarianceMatrix()[13] ) );
  CHECK( 19. == Approx( block.covarianceMatrix()[14] ) );
  CHECK( 20. == Approx( block.covarianceMatrix()[15] ) );
  CHECK( 21. == Approx( block.covarianceMatrix()[16] ) );
  CHECK( 22. == Approx( block.covarianceMatrix()[17] ) );
  CHECK( 23. == Approx( block.covarianceMatrix()[18] ) );
  CHECK( 24. == Approx( block.covarianceMatrix()[19] ) );
  CHECK( 25. == Approx( block.covarianceMatrix()[20] ) );
  CHECK( 26. == Approx( block.covarianceMatrix()[21] ) );
  CHECK( 27. == Approx( block.covarianceMatrix()[22] ) );
  CHECK( 28. == Approx( block.covarianceMatrix()[23] ) );
  CHECK( 29. == Approx( block.covarianceMatrix()[24] ) );
  CHECK( 30. == Approx( block.covarianceMatrix()[25] ) );
  CHECK( 31. == Approx( block.covarianceMatrix()[26] ) );
  CHECK( 32. == Approx( block.covarianceMatrix()[27] ) );
  CHECK( 33. == Approx( block.covarianceMatrix()[28] ) );
  CHECK( 34. == Approx( block.covarianceMatrix()[29] ) );
  CHECK( 35. == Approx( block.covarianceMatrix()[30] ) );
  CHECK( 36. == Approx( block.covarianceMatrix()[31] ) );
  CHECK( 37. == Approx( block.covarianceMatrix()[32] ) );
  CHECK( 38. == Approx( block.covarianceMatrix()[33] ) );
  CHECK( 39. == Approx( block.covarianceMatrix()[34] ) );
  CHECK( 40. == Approx( block.covarianceMatrix()[35] ) );

  CHECK( 11 == chunk.NC() );
}
