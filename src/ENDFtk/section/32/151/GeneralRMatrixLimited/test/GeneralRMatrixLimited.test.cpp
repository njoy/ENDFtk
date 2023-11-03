#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ShortRangeRMatrixLimitedBlock = section::Type< 32, 151 >::ShortRangeRMatrixLimitedBlock;
using ResonanceParameters = ShortRangeRMatrixLimitedBlock::ResonanceParameters;
using CovarianceMatrix = ShortRangeRMatrixLimitedBlock::CovarianceMatrix;
using GeneralRMatrixLimited = section::Type< 32, 151 >::GeneralRMatrixLimited;

std::string chunk();
void verifyChunk( const GeneralRMatrixLimited& );

SCENARIO( "GeneralRMatrixLimited" ) {

  GIVEN( "valid data for a GeneralRMatrixLimited" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;

      std::vector< ShortRangeRMatrixLimitedBlock > cshort = {

        ShortRangeRMatrixLimitedBlock(
          { ResonanceParameters( { -4.586687e+5, 1.913996e+6 },
                                 { { 1.000091, 9.809761e+2 },
                                   { 1., 1.878975e+5 } } ),
            ResonanceParameters( { 2.880782e+3, 6.957171e+3, 1.003819e+5 },
                                 { { 3.499989e-1 }, { 3.500785e-1 }, { 1.382810e+0 } } ) },

          CovarianceMatrix(
            {  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                   13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23.,
                        24., 25., 26., 27., 28., 29., 30., 31., 32., 33.,
                             34., 35., 36., 37., 38., 39., 40., 41., 42.,
                                  43., 44., 45., 46., 47., 48., 49., 50.,
                                       51., 52., 53., 54., 55., 56., 57.,
                                            58., 59., 60., 61., 62., 63.,
                                                 64., 65., 66., 67., 68.,
                                                      69., 70., 71., 72.,
                                                           73., 74., 75.,
                                                                76., 77.,
                                                                     78. } ) ) };

      GeneralRMatrixLimited chunk( awri, std::move( cshort ) );

      THEN( "a GeneralRMatrixLimited can be constructed and members can be "
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

      GeneralRMatrixLimited chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a GeneralRMatrixLimited can be constructed and members can be "
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
    " 0.000000+0 0.000000+0          0          1          0          0102532151     \n"
    " 1.982069+1 0.000000+0          0          0          1          0102532151     \n"
    " 0.000000+0 0.000000+0          2          0          0          0102532151     \n"
    " 0.000000+0 0.000000+0          2          2         12          2102532151     \n"
    "-4.586687+5 1.000091+0 9.809761+2 0.000000+0 0.000000+0 0.000000+0102532151     \n"
    " 1.913996+6 1.000000+0 1.878975+5 0.000000+0 0.000000+0 0.000000+0102532151     \n"
    " 0.000000+0 0.000000+0          1          3         18          3102532151     \n"
    " 2.880782+3 3.499989-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n"
    " 6.957171+3 3.500785-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n"
    " 1.003819+5 1.382810+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102532151     \n"
    " 0.000000+0 0.000000+0          0          0         78         12102532151     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0102532151     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1102532151     \n"
    " 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1 1.800000+1102532151     \n"
    " 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1 2.400000+1102532151     \n"
    " 2.500000+1 2.600000+1 2.700000+1 2.800000+1 2.900000+1 3.000000+1102532151     \n"
    " 3.100000+1 3.200000+1 3.300000+1 3.400000+1 3.500000+1 3.600000+1102532151     \n"
    " 3.700000+1 3.800000+1 3.900000+1 4.000000+1 4.100000+1 4.200000+1102532151     \n"
    " 4.300000+1 4.400000+1 4.500000+1 4.600000+1 4.700000+1 4.800000+1102532151     \n"
    " 4.900000+1 5.000000+1 5.100000+1 5.200000+1 5.300000+1 5.400000+1102532151     \n"
    " 5.500000+1 5.600000+1 5.700000+1 5.800000+1 5.900000+1 6.000000+1102532151     \n"
    " 6.100000+1 6.200000+1 6.300000+1 6.400000+1 6.500000+1 6.600000+1102532151     \n"
    " 6.700000+1 6.800000+1 6.900000+1 7.000000+1 7.100000+1 7.200000+1102532151     \n"
    " 7.300000+1 7.400000+1 7.500000+1 7.600000+1 7.700000+1 7.800000+1102532151     \n";
}

void verifyChunk( const GeneralRMatrixLimited& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 7 == chunk.LRF() );
  CHECK( 7 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );
  CHECK( 1 == chunk.LCOMP() );
  CHECK( 1 == chunk.covarianceRepresentation() );

  CHECK( 19.82069 == Approx( chunk.AWRI() ) );
  CHECK( 19.82069 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( std::nullopt == chunk.DAP() );
  CHECK( std::nullopt == chunk.scatteringRadiusUncertainty() );
  CHECK( false == chunk.ISR() );
  CHECK( false == chunk.scatteringRadiusUncertaintyFlag() );

  CHECK( 1 == chunk.NSRS() );
  CHECK( 1 == chunk.numberShortRangeBlocks() );
  CHECK( 1 == chunk.shortRangeBlocks().size() );

  auto block = chunk.shortRangeBlocks()[0];
  CHECK( 2 == block.NJSX() );
  CHECK( 2 == block.numberSpinGroups() );

  CHECK( 2 == block.resonanceParameters().size() );

  auto parameters1 = block.resonanceParameters()[0];
  CHECK( 2 == parameters1.NCH() );
  CHECK( 2 == parameters1.numberChannels() );
  CHECK( 2 == parameters1.NRB() );
  CHECK( 2 == parameters1.numberResonances() );
  CHECK( 2 == parameters1.NX() );
  CHECK( 2 == parameters1.numberLines() );

  CHECK( 2 == parameters1.ER().size() );
  CHECK( 2 == parameters1.resonanceEnergies().size() );
  CHECK( 2 == parameters1.GAM().size() );
  CHECK( 2 == parameters1.resonanceParameters().size() );

  CHECK( -4.586687e+5 == Approx( parameters1.ER()[0] ) );
  CHECK(  1.913996e+6 == Approx( parameters1.ER()[1] ) );
  CHECK( -4.586687e+5 == Approx( parameters1.resonanceEnergies()[0] ) );
  CHECK(  1.913996e+6 == Approx( parameters1.resonanceEnergies()[1] ) );
  CHECK( 2 == parameters1.GAM()[0].size() );
  CHECK( 2 == parameters1.GAM()[1].size() );
  CHECK( 1.000091 == Approx( parameters1.GAM()[0][0] ) );
  CHECK( 9.809761e+2 == Approx( parameters1.GAM()[0][1] ) );
  CHECK( 1. == Approx( parameters1.GAM()[1][0] ) );
  CHECK( 1.878975e+5 == Approx( parameters1.GAM()[1][1] ) );
  CHECK( 2 == parameters1.resonanceParameters()[0].size() );
  CHECK( 2 == parameters1.resonanceParameters()[1].size() );
  CHECK( 1.000091 == Approx( parameters1.resonanceParameters()[0][0] ) );
  CHECK( 9.809761e+2 == Approx( parameters1.resonanceParameters()[0][1] ) );
  CHECK( 1. == Approx( parameters1.resonanceParameters()[1][0] ) );
  CHECK( 1.878975e+5 == Approx( parameters1.resonanceParameters()[1][1] ) );

  auto parameters2 = block.resonanceParameters()[1];
  CHECK( 1 == parameters2.NCH() );
  CHECK( 1 == parameters2.numberChannels() );
  CHECK( 3 == parameters2.NRB() );
  CHECK( 3 == parameters2.numberResonances() );
  CHECK( 3 == parameters2.NX() );
  CHECK( 3 == parameters2.numberLines() );

  CHECK( 3 == parameters2.ER().size() );
  CHECK( 3 == parameters2.resonanceEnergies().size() );
  CHECK( 3 == parameters2.GAM().size() );
  CHECK( 3 == parameters2.resonanceParameters().size() );

  CHECK( 2.880782e+3 == Approx( parameters2.ER()[0] ) );
  CHECK( 6.957171e+3 == Approx( parameters2.ER()[1] ) );
  CHECK( 1.003819e+5 == Approx( parameters2.ER()[2] ) );
  CHECK( 2.880782e+3 == Approx( parameters2.resonanceEnergies()[0] ) );
  CHECK( 6.957171e+3 == Approx( parameters2.resonanceEnergies()[1] ) );
  CHECK( 1.003819e+5 == Approx( parameters2.resonanceEnergies()[2] ) );
  CHECK( 1 == parameters2.GAM()[0].size() );
  CHECK( 1 == parameters2.GAM()[1].size() );
  CHECK( 1 == parameters2.GAM()[2].size() );
  CHECK( .3499989 == Approx( parameters2.GAM()[0][0] ) );
  CHECK( .3500785 == Approx( parameters2.GAM()[1][0] ) );
  CHECK( 1.382810 == Approx( parameters2.GAM()[2][0] ) );
  CHECK( 1 == parameters2.resonanceParameters()[0].size() );
  CHECK( 1 == parameters2.resonanceParameters()[1].size() );
  CHECK( 1 == parameters2.resonanceParameters()[2].size() );
  CHECK( .3499989 == Approx( parameters2.resonanceParameters()[0][0] ) );
  CHECK( .3500785 == Approx( parameters2.resonanceParameters()[1][0] ) );
  CHECK( 1.382810 == Approx( parameters2.resonanceParameters()[2][0] ) );

  auto matrix = block.covarianceMatrix();
  CHECK( 12 == matrix.NPARB() );
  CHECK( 12 == matrix.covarianceMatrixOrder() );

  CHECK( 78 == matrix.covarianceMatrix().size() );
  CHECK( 78 == matrix.NVS() );
  CHECK( 78 == matrix.numberValues() );

  CHECK(  1. == Approx( matrix.covarianceMatrix()[ 0] ) );
  CHECK(  2. == Approx( matrix.covarianceMatrix()[ 1] ) );
  CHECK(  3. == Approx( matrix.covarianceMatrix()[ 2] ) );
  CHECK(  4. == Approx( matrix.covarianceMatrix()[ 3] ) );
  CHECK(  5. == Approx( matrix.covarianceMatrix()[ 4] ) );
  CHECK(  6. == Approx( matrix.covarianceMatrix()[ 5] ) );
  CHECK(  7. == Approx( matrix.covarianceMatrix()[ 6] ) );
  CHECK(  8. == Approx( matrix.covarianceMatrix()[ 7] ) );
  CHECK(  9. == Approx( matrix.covarianceMatrix()[ 8] ) );
  CHECK( 10. == Approx( matrix.covarianceMatrix()[ 9] ) );
  CHECK( 11. == Approx( matrix.covarianceMatrix()[10] ) );
  CHECK( 12. == Approx( matrix.covarianceMatrix()[11] ) );
  CHECK( 13. == Approx( matrix.covarianceMatrix()[12] ) );
  CHECK( 14. == Approx( matrix.covarianceMatrix()[13] ) );
  CHECK( 15. == Approx( matrix.covarianceMatrix()[14] ) );
  CHECK( 16. == Approx( matrix.covarianceMatrix()[15] ) );
  CHECK( 17. == Approx( matrix.covarianceMatrix()[16] ) );
  CHECK( 18. == Approx( matrix.covarianceMatrix()[17] ) );
  CHECK( 19. == Approx( matrix.covarianceMatrix()[18] ) );
  CHECK( 20. == Approx( matrix.covarianceMatrix()[19] ) );
  CHECK( 21. == Approx( matrix.covarianceMatrix()[20] ) );
  CHECK( 22. == Approx( matrix.covarianceMatrix()[21] ) );
  CHECK( 23. == Approx( matrix.covarianceMatrix()[22] ) );
  CHECK( 24. == Approx( matrix.covarianceMatrix()[23] ) );
  CHECK( 25. == Approx( matrix.covarianceMatrix()[24] ) );
  CHECK( 26. == Approx( matrix.covarianceMatrix()[25] ) );
  CHECK( 27. == Approx( matrix.covarianceMatrix()[26] ) );
  CHECK( 28. == Approx( matrix.covarianceMatrix()[27] ) );
  CHECK( 29. == Approx( matrix.covarianceMatrix()[28] ) );
  CHECK( 30. == Approx( matrix.covarianceMatrix()[29] ) );
  CHECK( 31. == Approx( matrix.covarianceMatrix()[30] ) );
  CHECK( 32. == Approx( matrix.covarianceMatrix()[31] ) );
  CHECK( 33. == Approx( matrix.covarianceMatrix()[32] ) );
  CHECK( 34. == Approx( matrix.covarianceMatrix()[33] ) );
  CHECK( 35. == Approx( matrix.covarianceMatrix()[34] ) );
  CHECK( 36. == Approx( matrix.covarianceMatrix()[35] ) );
  CHECK( 37. == Approx( matrix.covarianceMatrix()[36] ) );
  CHECK( 38. == Approx( matrix.covarianceMatrix()[37] ) );
  CHECK( 39. == Approx( matrix.covarianceMatrix()[38] ) );
  CHECK( 40. == Approx( matrix.covarianceMatrix()[39] ) );
  CHECK( 41. == Approx( matrix.covarianceMatrix()[40] ) );
  CHECK( 42. == Approx( matrix.covarianceMatrix()[41] ) );
  CHECK( 43. == Approx( matrix.covarianceMatrix()[42] ) );
  CHECK( 44. == Approx( matrix.covarianceMatrix()[43] ) );
  CHECK( 45. == Approx( matrix.covarianceMatrix()[44] ) );
  CHECK( 46. == Approx( matrix.covarianceMatrix()[45] ) );
  CHECK( 47. == Approx( matrix.covarianceMatrix()[46] ) );
  CHECK( 48. == Approx( matrix.covarianceMatrix()[47] ) );
  CHECK( 49. == Approx( matrix.covarianceMatrix()[48] ) );
  CHECK( 50. == Approx( matrix.covarianceMatrix()[49] ) );
  CHECK( 51. == Approx( matrix.covarianceMatrix()[50] ) );
  CHECK( 52. == Approx( matrix.covarianceMatrix()[51] ) );
  CHECK( 53. == Approx( matrix.covarianceMatrix()[52] ) );
  CHECK( 54. == Approx( matrix.covarianceMatrix()[53] ) );
  CHECK( 55. == Approx( matrix.covarianceMatrix()[54] ) );
  CHECK( 56. == Approx( matrix.covarianceMatrix()[55] ) );
  CHECK( 57. == Approx( matrix.covarianceMatrix()[56] ) );
  CHECK( 58. == Approx( matrix.covarianceMatrix()[57] ) );
  CHECK( 59. == Approx( matrix.covarianceMatrix()[58] ) );
  CHECK( 60. == Approx( matrix.covarianceMatrix()[59] ) );
  CHECK( 61. == Approx( matrix.covarianceMatrix()[60] ) );
  CHECK( 62. == Approx( matrix.covarianceMatrix()[61] ) );
  CHECK( 63. == Approx( matrix.covarianceMatrix()[62] ) );
  CHECK( 64. == Approx( matrix.covarianceMatrix()[63] ) );
  CHECK( 65. == Approx( matrix.covarianceMatrix()[64] ) );
  CHECK( 66. == Approx( matrix.covarianceMatrix()[65] ) );
  CHECK( 67. == Approx( matrix.covarianceMatrix()[66] ) );
  CHECK( 68. == Approx( matrix.covarianceMatrix()[67] ) );
  CHECK( 69. == Approx( matrix.covarianceMatrix()[68] ) );
  CHECK( 70. == Approx( matrix.covarianceMatrix()[69] ) );
  CHECK( 71. == Approx( matrix.covarianceMatrix()[70] ) );
  CHECK( 72. == Approx( matrix.covarianceMatrix()[71] ) );
  CHECK( 73. == Approx( matrix.covarianceMatrix()[72] ) );
  CHECK( 74. == Approx( matrix.covarianceMatrix()[73] ) );
  CHECK( 75. == Approx( matrix.covarianceMatrix()[74] ) );
  CHECK( 76. == Approx( matrix.covarianceMatrix()[75] ) );
  CHECK( 77. == Approx( matrix.covarianceMatrix()[76] ) );
  CHECK( 78. == Approx( matrix.covarianceMatrix()[77] ) );

  CHECK( 24 == chunk.NC() );
}
