// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CovarianceMatrix =
section::Type< 32, 151 >::UnresolvedRelativeCovariances::CovarianceMatrix;

std::string chunk();
void verifyChunk( const CovarianceMatrix& );
std::string invalidSize();
std::string zeroSize();
std::string wrongNPAR();

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid data for a CovarianceMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int mpar = 4;
      std::vector< double > values = {  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                            13., 14., 15., 16., 17., 18., 19.,
                                                 20., 21., 22., 23., 24., 25.,
                                                      26., 27., 28., 29., 30.,
                                                           31., 32., 33., 34.,
                                                                35., 36., 37.,
                                                                     38., 39.,
                                                                          40. };

      CovarianceMatrix chunk( mpar, std::move( values ) );

      THEN( "a CovarianceMatrix can be constructed and members can be "
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

      CovarianceMatrix chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a CovarianceMatrix can be constructed and members can be "
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

  GIVEN( "invalid data" ) {

    WHEN( "the data is empty" ) {

      unsigned int mpar = 4;
      std::vector< double > values = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( mpar, std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NPAR is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NPAR is used" ) {

      std::string string = wrongNPAR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          4          0         36          8102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}

void verifyChunk( const CovarianceMatrix& chunk ) {

  CHECK( 4 == chunk.MPAR() );
  CHECK( 4 == chunk.numberAverageParameters() );

  CHECK( 8 == chunk.NPAR() );
  CHECK( 8 == chunk.covarianceMatrixOrder() );

  CHECK( 36 == chunk.covarianceMatrix().size() );
  CHECK( 36 == chunk.NVS() );
  CHECK( 36 == chunk.numberValues() );

  CHECK_THAT(  5., WithinRel( chunk.covarianceMatrix()[ 0] ) );
  CHECK_THAT(  6., WithinRel( chunk.covarianceMatrix()[ 1] ) );
  CHECK_THAT(  7., WithinRel( chunk.covarianceMatrix()[ 2] ) );
  CHECK_THAT(  8., WithinRel( chunk.covarianceMatrix()[ 3] ) );
  CHECK_THAT(  9., WithinRel( chunk.covarianceMatrix()[ 4] ) );
  CHECK_THAT( 10., WithinRel( chunk.covarianceMatrix()[ 5] ) );
  CHECK_THAT( 11., WithinRel( chunk.covarianceMatrix()[ 6] ) );
  CHECK_THAT( 12., WithinRel( chunk.covarianceMatrix()[ 7] ) );
  CHECK_THAT( 13., WithinRel( chunk.covarianceMatrix()[ 8] ) );
  CHECK_THAT( 14., WithinRel( chunk.covarianceMatrix()[ 9] ) );
  CHECK_THAT( 15., WithinRel( chunk.covarianceMatrix()[10] ) );
  CHECK_THAT( 16., WithinRel( chunk.covarianceMatrix()[11] ) );
  CHECK_THAT( 17., WithinRel( chunk.covarianceMatrix()[12] ) );
  CHECK_THAT( 18., WithinRel( chunk.covarianceMatrix()[13] ) );
  CHECK_THAT( 19., WithinRel( chunk.covarianceMatrix()[14] ) );
  CHECK_THAT( 20., WithinRel( chunk.covarianceMatrix()[15] ) );
  CHECK_THAT( 21., WithinRel( chunk.covarianceMatrix()[16] ) );
  CHECK_THAT( 22., WithinRel( chunk.covarianceMatrix()[17] ) );
  CHECK_THAT( 23., WithinRel( chunk.covarianceMatrix()[18] ) );
  CHECK_THAT( 24., WithinRel( chunk.covarianceMatrix()[19] ) );
  CHECK_THAT( 25., WithinRel( chunk.covarianceMatrix()[20] ) );
  CHECK_THAT( 26., WithinRel( chunk.covarianceMatrix()[21] ) );
  CHECK_THAT( 27., WithinRel( chunk.covarianceMatrix()[22] ) );
  CHECK_THAT( 28., WithinRel( chunk.covarianceMatrix()[23] ) );
  CHECK_THAT( 29., WithinRel( chunk.covarianceMatrix()[24] ) );
  CHECK_THAT( 30., WithinRel( chunk.covarianceMatrix()[25] ) );
  CHECK_THAT( 31., WithinRel( chunk.covarianceMatrix()[26] ) );
  CHECK_THAT( 32., WithinRel( chunk.covarianceMatrix()[27] ) );
  CHECK_THAT( 33., WithinRel( chunk.covarianceMatrix()[28] ) );
  CHECK_THAT( 34., WithinRel( chunk.covarianceMatrix()[29] ) );
  CHECK_THAT( 35., WithinRel( chunk.covarianceMatrix()[30] ) );
  CHECK_THAT( 36., WithinRel( chunk.covarianceMatrix()[31] ) );
  CHECK_THAT( 37., WithinRel( chunk.covarianceMatrix()[32] ) );
  CHECK_THAT( 38., WithinRel( chunk.covarianceMatrix()[33] ) );
  CHECK_THAT( 39., WithinRel( chunk.covarianceMatrix()[34] ) );
  CHECK_THAT( 40., WithinRel( chunk.covarianceMatrix()[35] ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 0.000000+0          4          0         35          8102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n";
}

std::string zeroSize() {
  return
    " 0.000000+0 0.000000+0          4          0          0          2102532151     \n";
}

std::string wrongNPAR() {
  return
    " 0.000000+0 0.000000+0          4          0         36          0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}
