#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CovarianceMatrix =
section::Type< 32, 151 >::ShortRangeRMatrixLimitedBlock::CovarianceMatrix;

std::string chunk();
void verifyChunk( const CovarianceMatrix& );
std::string invalidSize();
std::string zeroSize();
std::string wrongNPARB();

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid data for a CovarianceMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = {  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                            13., 14., 15., 16., 17., 18., 19.,
                                                 20., 21., 22., 23., 24., 25.,
                                                      26., 27., 28., 29., 30.,
                                                           31., 32., 33., 34.,
                                                                35., 36., 37.,
                                                                     38., 39.,
                                                                          40. };

      CovarianceMatrix chunk( std::move( values ) );

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

      std::vector< double > values = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CovarianceMatrix( std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NPARB is used" ) {

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

    WHEN( "a string with inconsistent NPL and NPARB is used" ) {

      std::string string = wrongNPARB();
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
    " 0.000000+0 0.000000+0          0          0         36          8102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}

void verifyChunk( const CovarianceMatrix& chunk ) {

  CHECK( 8 == chunk.NPARB() );
  CHECK( 8 == chunk.covarianceMatrixOrder() );

  CHECK( 36 == chunk.covarianceMatrix().size() );
  CHECK( 36 == chunk.NVS() );
  CHECK( 36 == chunk.numberValues() );

  CHECK(  5. == Approx( chunk.covarianceMatrix()[ 0] ) );
  CHECK(  6. == Approx( chunk.covarianceMatrix()[ 1] ) );
  CHECK(  7. == Approx( chunk.covarianceMatrix()[ 2] ) );
  CHECK(  8. == Approx( chunk.covarianceMatrix()[ 3] ) );
  CHECK(  9. == Approx( chunk.covarianceMatrix()[ 4] ) );
  CHECK( 10. == Approx( chunk.covarianceMatrix()[ 5] ) );
  CHECK( 11. == Approx( chunk.covarianceMatrix()[ 6] ) );
  CHECK( 12. == Approx( chunk.covarianceMatrix()[ 7] ) );
  CHECK( 13. == Approx( chunk.covarianceMatrix()[ 8] ) );
  CHECK( 14. == Approx( chunk.covarianceMatrix()[ 9] ) );
  CHECK( 15. == Approx( chunk.covarianceMatrix()[10] ) );
  CHECK( 16. == Approx( chunk.covarianceMatrix()[11] ) );
  CHECK( 17. == Approx( chunk.covarianceMatrix()[12] ) );
  CHECK( 18. == Approx( chunk.covarianceMatrix()[13] ) );
  CHECK( 19. == Approx( chunk.covarianceMatrix()[14] ) );
  CHECK( 20. == Approx( chunk.covarianceMatrix()[15] ) );
  CHECK( 21. == Approx( chunk.covarianceMatrix()[16] ) );
  CHECK( 22. == Approx( chunk.covarianceMatrix()[17] ) );
  CHECK( 23. == Approx( chunk.covarianceMatrix()[18] ) );
  CHECK( 24. == Approx( chunk.covarianceMatrix()[19] ) );
  CHECK( 25. == Approx( chunk.covarianceMatrix()[20] ) );
  CHECK( 26. == Approx( chunk.covarianceMatrix()[21] ) );
  CHECK( 27. == Approx( chunk.covarianceMatrix()[22] ) );
  CHECK( 28. == Approx( chunk.covarianceMatrix()[23] ) );
  CHECK( 29. == Approx( chunk.covarianceMatrix()[24] ) );
  CHECK( 30. == Approx( chunk.covarianceMatrix()[25] ) );
  CHECK( 31. == Approx( chunk.covarianceMatrix()[26] ) );
  CHECK( 32. == Approx( chunk.covarianceMatrix()[27] ) );
  CHECK( 33. == Approx( chunk.covarianceMatrix()[28] ) );
  CHECK( 34. == Approx( chunk.covarianceMatrix()[29] ) );
  CHECK( 35. == Approx( chunk.covarianceMatrix()[30] ) );
  CHECK( 36. == Approx( chunk.covarianceMatrix()[31] ) );
  CHECK( 37. == Approx( chunk.covarianceMatrix()[32] ) );
  CHECK( 38. == Approx( chunk.covarianceMatrix()[33] ) );
  CHECK( 39. == Approx( chunk.covarianceMatrix()[34] ) );
  CHECK( 40. == Approx( chunk.covarianceMatrix()[35] ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 0.000000+0          0          0         35          8102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n";
}

std::string zeroSize() {
  return
    " 0.000000+0 0.000000+0          0          0          0          2102532151     \n";
}

std::string wrongNPARB() {
  return
    " 0.000000+0 0.000000+0          0          0         36          0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}
