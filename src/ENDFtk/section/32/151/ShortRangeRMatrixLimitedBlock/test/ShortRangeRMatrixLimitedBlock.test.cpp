// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ShortRangeRMatrixLimitedBlock = section::Type< 32, 151 >::ShortRangeRMatrixLimitedBlock;
using ResonanceParameters = ShortRangeRMatrixLimitedBlock::ResonanceParameters;
using CovarianceMatrix = ShortRangeRMatrixLimitedBlock::CovarianceMatrix;

std::string chunk();
void verifyChunk( const ShortRangeRMatrixLimitedBlock& );

SCENARIO( "ShortRangeRMatrixLimitedBlock" ) {

  GIVEN( "valid data for a ShortRangeRMatrixLimitedBlock" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< ResonanceParameters > parameters = {

        ResonanceParameters( { -4.586687e+5, 1.913996e+6 },
                             { { 1.000091, 9.809761e+2 },
                               { 1., 1.878975e+5 } } ),
        ResonanceParameters( { 2.880782e+3, 6.957171e+3, 1.003819e+5 },
                             { { 3.499989e-1 }, { 3.500785e-1 }, { 1.382810e+0 } } )
      };

      CovarianceMatrix covariances(
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
                                                                 78. } );

      ShortRangeRMatrixLimitedBlock chunk( std::move( parameters ),
                                           std::move( covariances ) );

      THEN( "a ShortRangeRMatrixLimitedBlock can be constructed and members can be "
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

      ShortRangeRMatrixLimitedBlock chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a ShortRangeRMatrixLimitedBlock can be constructed and members can be "
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

void verifyChunk( const ShortRangeRMatrixLimitedBlock& chunk ) {

  CHECK( 2 == chunk.NJSX() );
  CHECK( 2 == chunk.numberSpinGroups() );

  CHECK( 2 == chunk.resonanceParameters().size() );

  auto parameters1 = chunk.resonanceParameters()[0];
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

  CHECK_THAT( -4.586687e+5, WithinRel( parameters1.ER()[0] ) );
  CHECK_THAT(  1.913996e+6, WithinRel( parameters1.ER()[1] ) );
  CHECK_THAT( -4.586687e+5, WithinRel( parameters1.resonanceEnergies()[0] ) );
  CHECK_THAT(  1.913996e+6, WithinRel( parameters1.resonanceEnergies()[1] ) );
  CHECK( 5 == parameters1.GAM()[0].size() );
  CHECK( 5 == parameters1.GAM()[1].size() );
  CHECK_THAT( 1.000091, WithinRel( parameters1.GAM()[0][0] ) );
  CHECK_THAT( 9.809761e+2, WithinRel( parameters1.GAM()[0][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[0][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[0][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[0][4] ) );
  CHECK_THAT( 1., WithinRel( parameters1.GAM()[1][0] ) );
  CHECK_THAT( 1.878975e+5, WithinRel( parameters1.GAM()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[1][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[1][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.GAM()[1][4] ) );
  CHECK( 5 == parameters1.resonanceParameters()[0].size() );
  CHECK( 5 == parameters1.resonanceParameters()[1].size() );
  CHECK_THAT( 1.000091, WithinRel( parameters1.resonanceParameters()[0][0] ) );
  CHECK_THAT( 9.809761e+2, WithinRel( parameters1.resonanceParameters()[0][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[0][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[0][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[0][4] ) );
  CHECK_THAT( 1., WithinRel( parameters1.resonanceParameters()[1][0] ) );
  CHECK_THAT( 1.878975e+5, WithinRel( parameters1.resonanceParameters()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[1][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[1][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters1.resonanceParameters()[1][4] ) );

  auto parameters2 = chunk.resonanceParameters()[1];
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

  CHECK_THAT( 2.880782e+3, WithinRel( parameters2.ER()[0] ) );
  CHECK_THAT( 6.957171e+3, WithinRel( parameters2.ER()[1] ) );
  CHECK_THAT( 1.003819e+5, WithinRel( parameters2.ER()[2] ) );
  CHECK_THAT( 2.880782e+3, WithinRel( parameters2.resonanceEnergies()[0] ) );
  CHECK_THAT( 6.957171e+3, WithinRel( parameters2.resonanceEnergies()[1] ) );
  CHECK_THAT( 1.003819e+5, WithinRel( parameters2.resonanceEnergies()[2] ) );
  CHECK( 5 == parameters2.GAM()[0].size() );
  CHECK( 5 == parameters2.GAM()[1].size() );
  CHECK( 5 == parameters2.GAM()[2].size() );
  CHECK_THAT( .3499989, WithinRel( parameters2.GAM()[0][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][4] ) );
  CHECK_THAT( .3500785, WithinRel( parameters2.GAM()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[1][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[1][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[1][4] ) );
  CHECK_THAT( 1.382810, WithinRel( parameters2.GAM()[2][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.GAM()[0][4] ) );
  CHECK( 5 == parameters2.resonanceParameters()[0].size() );
  CHECK( 5 == parameters2.resonanceParameters()[1].size() );
  CHECK( 5 == parameters2.resonanceParameters()[2].size() );
  CHECK_THAT( .3499989, WithinRel( parameters2.resonanceParameters()[0][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[0][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[0][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[0][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[0][4] ) );
  CHECK_THAT( .3500785, WithinRel( parameters2.resonanceParameters()[1][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[1][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[1][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[1][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[1][4] ) );
  CHECK_THAT( 1.382810, WithinRel( parameters2.resonanceParameters()[2][0] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[2][1] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[2][2] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[2][3] ) );
  CHECK_THAT( 0.0, WithinRel( parameters2.resonanceParameters()[2][4] ) );

  auto matrix = chunk.covarianceMatrix();
  CHECK( 12 == matrix.NPARB() );
  CHECK( 12 == matrix.covarianceMatrixOrder() );

  CHECK( 78 == matrix.covarianceMatrix().size() );
  CHECK( 78 == matrix.NVS() );
  CHECK( 78 == matrix.numberValues() );

  CHECK_THAT(  1., WithinRel( matrix.covarianceMatrix()[ 0] ) );
  CHECK_THAT(  2., WithinRel( matrix.covarianceMatrix()[ 1] ) );
  CHECK_THAT(  3., WithinRel( matrix.covarianceMatrix()[ 2] ) );
  CHECK_THAT(  4., WithinRel( matrix.covarianceMatrix()[ 3] ) );
  CHECK_THAT(  5., WithinRel( matrix.covarianceMatrix()[ 4] ) );
  CHECK_THAT(  6., WithinRel( matrix.covarianceMatrix()[ 5] ) );
  CHECK_THAT(  7., WithinRel( matrix.covarianceMatrix()[ 6] ) );
  CHECK_THAT(  8., WithinRel( matrix.covarianceMatrix()[ 7] ) );
  CHECK_THAT(  9., WithinRel( matrix.covarianceMatrix()[ 8] ) );
  CHECK_THAT( 10., WithinRel( matrix.covarianceMatrix()[ 9] ) );
  CHECK_THAT( 11., WithinRel( matrix.covarianceMatrix()[10] ) );
  CHECK_THAT( 12., WithinRel( matrix.covarianceMatrix()[11] ) );
  CHECK_THAT( 13., WithinRel( matrix.covarianceMatrix()[12] ) );
  CHECK_THAT( 14., WithinRel( matrix.covarianceMatrix()[13] ) );
  CHECK_THAT( 15., WithinRel( matrix.covarianceMatrix()[14] ) );
  CHECK_THAT( 16., WithinRel( matrix.covarianceMatrix()[15] ) );
  CHECK_THAT( 17., WithinRel( matrix.covarianceMatrix()[16] ) );
  CHECK_THAT( 18., WithinRel( matrix.covarianceMatrix()[17] ) );
  CHECK_THAT( 19., WithinRel( matrix.covarianceMatrix()[18] ) );
  CHECK_THAT( 20., WithinRel( matrix.covarianceMatrix()[19] ) );
  CHECK_THAT( 21., WithinRel( matrix.covarianceMatrix()[20] ) );
  CHECK_THAT( 22., WithinRel( matrix.covarianceMatrix()[21] ) );
  CHECK_THAT( 23., WithinRel( matrix.covarianceMatrix()[22] ) );
  CHECK_THAT( 24., WithinRel( matrix.covarianceMatrix()[23] ) );
  CHECK_THAT( 25., WithinRel( matrix.covarianceMatrix()[24] ) );
  CHECK_THAT( 26., WithinRel( matrix.covarianceMatrix()[25] ) );
  CHECK_THAT( 27., WithinRel( matrix.covarianceMatrix()[26] ) );
  CHECK_THAT( 28., WithinRel( matrix.covarianceMatrix()[27] ) );
  CHECK_THAT( 29., WithinRel( matrix.covarianceMatrix()[28] ) );
  CHECK_THAT( 30., WithinRel( matrix.covarianceMatrix()[29] ) );
  CHECK_THAT( 31., WithinRel( matrix.covarianceMatrix()[30] ) );
  CHECK_THAT( 32., WithinRel( matrix.covarianceMatrix()[31] ) );
  CHECK_THAT( 33., WithinRel( matrix.covarianceMatrix()[32] ) );
  CHECK_THAT( 34., WithinRel( matrix.covarianceMatrix()[33] ) );
  CHECK_THAT( 35., WithinRel( matrix.covarianceMatrix()[34] ) );
  CHECK_THAT( 36., WithinRel( matrix.covarianceMatrix()[35] ) );
  CHECK_THAT( 37., WithinRel( matrix.covarianceMatrix()[36] ) );
  CHECK_THAT( 38., WithinRel( matrix.covarianceMatrix()[37] ) );
  CHECK_THAT( 39., WithinRel( matrix.covarianceMatrix()[38] ) );
  CHECK_THAT( 40., WithinRel( matrix.covarianceMatrix()[39] ) );
  CHECK_THAT( 41., WithinRel( matrix.covarianceMatrix()[40] ) );
  CHECK_THAT( 42., WithinRel( matrix.covarianceMatrix()[41] ) );
  CHECK_THAT( 43., WithinRel( matrix.covarianceMatrix()[42] ) );
  CHECK_THAT( 44., WithinRel( matrix.covarianceMatrix()[43] ) );
  CHECK_THAT( 45., WithinRel( matrix.covarianceMatrix()[44] ) );
  CHECK_THAT( 46., WithinRel( matrix.covarianceMatrix()[45] ) );
  CHECK_THAT( 47., WithinRel( matrix.covarianceMatrix()[46] ) );
  CHECK_THAT( 48., WithinRel( matrix.covarianceMatrix()[47] ) );
  CHECK_THAT( 49., WithinRel( matrix.covarianceMatrix()[48] ) );
  CHECK_THAT( 50., WithinRel( matrix.covarianceMatrix()[49] ) );
  CHECK_THAT( 51., WithinRel( matrix.covarianceMatrix()[50] ) );
  CHECK_THAT( 52., WithinRel( matrix.covarianceMatrix()[51] ) );
  CHECK_THAT( 53., WithinRel( matrix.covarianceMatrix()[52] ) );
  CHECK_THAT( 54., WithinRel( matrix.covarianceMatrix()[53] ) );
  CHECK_THAT( 55., WithinRel( matrix.covarianceMatrix()[54] ) );
  CHECK_THAT( 56., WithinRel( matrix.covarianceMatrix()[55] ) );
  CHECK_THAT( 57., WithinRel( matrix.covarianceMatrix()[56] ) );
  CHECK_THAT( 58., WithinRel( matrix.covarianceMatrix()[57] ) );
  CHECK_THAT( 59., WithinRel( matrix.covarianceMatrix()[58] ) );
  CHECK_THAT( 60., WithinRel( matrix.covarianceMatrix()[59] ) );
  CHECK_THAT( 61., WithinRel( matrix.covarianceMatrix()[60] ) );
  CHECK_THAT( 62., WithinRel( matrix.covarianceMatrix()[61] ) );
  CHECK_THAT( 63., WithinRel( matrix.covarianceMatrix()[62] ) );
  CHECK_THAT( 64., WithinRel( matrix.covarianceMatrix()[63] ) );
  CHECK_THAT( 65., WithinRel( matrix.covarianceMatrix()[64] ) );
  CHECK_THAT( 66., WithinRel( matrix.covarianceMatrix()[65] ) );
  CHECK_THAT( 67., WithinRel( matrix.covarianceMatrix()[66] ) );
  CHECK_THAT( 68., WithinRel( matrix.covarianceMatrix()[67] ) );
  CHECK_THAT( 69., WithinRel( matrix.covarianceMatrix()[68] ) );
  CHECK_THAT( 70., WithinRel( matrix.covarianceMatrix()[69] ) );
  CHECK_THAT( 71., WithinRel( matrix.covarianceMatrix()[70] ) );
  CHECK_THAT( 72., WithinRel( matrix.covarianceMatrix()[71] ) );
  CHECK_THAT( 73., WithinRel( matrix.covarianceMatrix()[72] ) );
  CHECK_THAT( 74., WithinRel( matrix.covarianceMatrix()[73] ) );
  CHECK_THAT( 75., WithinRel( matrix.covarianceMatrix()[74] ) );
  CHECK_THAT( 76., WithinRel( matrix.covarianceMatrix()[75] ) );
  CHECK_THAT( 77., WithinRel( matrix.covarianceMatrix()[76] ) );
  CHECK_THAT( 78., WithinRel( matrix.covarianceMatrix()[77] ) );

  CHECK( 22 == chunk.NC() );
}

// std::string invalidSize() {
//   return
//     " 1.982069+1 0.000000+0          4          0         47          2102532151     \n"
//     "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
//     " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
//     " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
//     " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
//     " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
//     " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
//     " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
//     " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n";
// }
//
// std::string zeroSize() {
//   return
//     " 1.982069+1 0.000000+0          0          0          0          2102532151     \n";
// }
//
// std::string noNumberResonances() {
//   return
//     " 1.982069+1 0.000000+0          4          0         48          0102532151     \n"
//     "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
//     " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
//     " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
//     " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
//     " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
//     " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
//     " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
//     " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
// }
//
