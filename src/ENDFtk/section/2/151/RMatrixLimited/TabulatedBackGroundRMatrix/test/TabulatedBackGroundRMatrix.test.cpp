#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedBackGroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::TabulatedBackGroundRMatrix;

std::string chunk();
void verifyChunk( const TabulatedBackGroundRMatrix& );
std::string invalidLBK();

SCENARIO( "TabulatedBackGroundRMatrix" ) {

  GIVEN( "valid data for a TabulatedBackGroundRMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int index = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 2e+7 };
      std::vector< std::complex< double > > rmatrix = { { 1., 2. }, { 2., 1. } };

      TabulatedBackGroundRMatrix chunk( index,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( energies ),
                                        std::move( rmatrix ) );

      THEN( "a TabulatedBackGroundRMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TabulatedBackGroundRMatrix chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a TabulatedBackGroundRMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "a string with the wrong LBK is used" ) {

      std::string string = invalidLBK();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedBackGroundRMatrix( begin, end, lineNumber,
                                                  2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          1          0          02625 2151     \n"
    " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
    "          2          2                                            2625 2151     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                      2625 2151     \n"
    " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
    "          2          2                                            2625 2151     \n"
    " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                      2625 2151     \n";
}

void verifyChunk( const TabulatedBackGroundRMatrix& chunk ) {

  CHECK( 1 == chunk.LBK() );
  CHECK( 1 == chunk.representation() );
  CHECK( 1 == chunk.LCH() );
  CHECK( 1 == chunk.channelIndex() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.rmatrix().size() );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 2e+7 == Approx( chunk.energies()[1] ) );
  CHECK( 1. == Approx( chunk.rmatrix()[0].real() ) );
  CHECK( 2. == Approx( chunk.rmatrix()[1].real() ) );
  CHECK( 2. == Approx( chunk.rmatrix()[0].imag() ) );
  CHECK( 1. == Approx( chunk.rmatrix()[1].imag() ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidLBK() {
  return
  " 0.000000+0 0.000000+0          1          5          0          02625 2151     \n"
  " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
  "          2          2                                            2625 2151     \n"
  " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                      2625 2151     \n"
  " 0.000000+0 0.000000+0          0          0          1          22625 2151     \n"
  "          2          2                                            2625 2151     \n"
  " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                      2625 2151     \n";

}
