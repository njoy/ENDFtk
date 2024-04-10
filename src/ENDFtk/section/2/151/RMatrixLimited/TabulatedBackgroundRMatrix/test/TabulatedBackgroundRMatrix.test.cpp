// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedBackgroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::TabulatedBackgroundRMatrix;

std::string chunk();
void verifyChunk( const TabulatedBackgroundRMatrix& );
std::string invalidLBK();

SCENARIO( "TabulatedBackgroundRMatrix" ) {

  GIVEN( "valid data for a TabulatedBackgroundRMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int index = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 2e+7 };
      std::vector< std::complex< double > > rmatrix = { { 1., 2. }, { 2., 1. } };

      TabulatedBackgroundRMatrix chunk( index,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( energies ),
                                        std::move( rmatrix ) );

      THEN( "a TabulatedBackgroundRMatrix can be constructed and members can be "
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

      TabulatedBackgroundRMatrix chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a TabulatedBackgroundRMatrix can be constructed and members can be "
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

        CHECK_THROWS( TabulatedBackgroundRMatrix( begin, end, lineNumber,
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

void verifyChunk( const TabulatedBackgroundRMatrix& chunk ) {

  CHECK( 1 == chunk.LBK() );
  CHECK( 1 == chunk.representation() );
  CHECK( 1 == chunk.LCH() );
  CHECK( 1 == chunk.channelIndex() );

  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 2 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.RB().size() );
  CHECK( 2 == chunk.rmatrix().size() );
  CHECK( 2 == chunk.RBR().size() );
  CHECK( 2 == chunk.real().size() );
  CHECK( 2 == chunk.RBI().size() );
  CHECK( 2 == chunk.imaginary().size() );

  CHECK_THAT( 1e-5, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.RBR()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.RBR()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.real()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.real()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.RBI()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.RBI()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.imaginary()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.imaginary()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.RB()[0].real() ) );
  CHECK_THAT( 2., WithinRel( chunk.RB()[1].real() ) );
  CHECK_THAT( 2., WithinRel( chunk.RB()[0].imag() ) );
  CHECK_THAT( 1., WithinRel( chunk.RB()[1].imag() ) );
  CHECK_THAT( 1., WithinRel( chunk.rmatrix()[0].real() ) );
  CHECK_THAT( 2., WithinRel( chunk.rmatrix()[1].real() ) );
  CHECK_THAT( 2., WithinRel( chunk.rmatrix()[0].imag() ) );
  CHECK_THAT( 1., WithinRel( chunk.rmatrix()[1].imag() ) );

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
