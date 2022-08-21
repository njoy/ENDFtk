#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/35.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SquareMatrix = section::Type< 35 >::SquareMatrix;

std::string chunk();
std::string invalidLB();
std::string inconsistentSymmetric();
std::string inconsistentAsymmetric();
void verifyChunk( const SquareMatrix& );


SCENARIO( "SquareMatrix" ) {

  GIVEN( "valid data for a SquareMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 0, 100, 200 };
      std::vector< double > values = { 1, 2, 3 };

      SquareMatrix chunk( 1.0e6, 1.0e7,
                          std::move(energies), std::move(values) );

      THEN( "a SquareMatrix can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 35, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      SquareMatrix chunk( begin, end, lineNumber, 9228, 35, 5 );

      THEN( "a SquareMatrix object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 35, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "invalid data for a SquareMatrix" ) {

    WHEN( "a string representation is used with an invalid LB" ) {

      std::string string = invalidLB();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          SquareMatrix( begin, end, lineNumber, 9228, 35, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 1.000000+6 1.000000+7          1          7          6          3922835  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922835  5     \n";
}

void verifyChunk( const SquareMatrix& chunk ) {

  // metadata
  CHECK( 1 == chunk.LS() );
  CHECK( 1 == chunk.symmetryFlag() );
  CHECK( chunk.isSymmetric() );
  CHECK( 7 == chunk.LB() );
  CHECK( 7 == chunk.procedure() );
  CHECK( 6 == chunk.NT() );
  CHECK( 6 == chunk.numberValues() );
  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergies() );

  // values
  CHECK( 0. == Approx( chunk.energies()[0] ) );
  CHECK( 100. == Approx( chunk.energies()[1] ) );
  CHECK( 200. == Approx( chunk.energies()[2] ) );
  CHECK( 1. == Approx( chunk.values()[0] ) );
  CHECK( 2. == Approx( chunk.values()[1] ) );
  CHECK( 3. == Approx( chunk.values()[2] ) );

  CHECK( 2 == chunk.NC() );

}


std::string invalidLB() {
  return
    " 0.000000+0 0.000000+0          0          5          7          3922835  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922835  5     \n";
}
