#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/34.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SquareMatrix = section::Type< 34 >::SquareMatrix;

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
      std::vector< double > values = { 1, 2, 3, 4 };

      SquareMatrix chunk( 0, std::move(energies), std::move(values) );

      THEN( "a SquareMatrix can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 34, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      SquareMatrix chunk( begin, end, lineNumber, 9228, 34, 5 );

      THEN( "a SquareMatrix object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 34, 5 );
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
          SquareMatrix( begin, end, lineNumber, 9228, 34, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent LS and NT" ) {

      std::string string = inconsistentSymmetric();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          SquareMatrix( begin, end, lineNumber, 9228, 34, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent LS and NT" ) {

      std::string string = inconsistentAsymmetric();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          SquareMatrix( begin, end, lineNumber, 9228, 34, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          5          7          3922834  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922834  5     \n"
    " 4.000000+0                                                       922834  5     \n";
}

void verifyChunk( const SquareMatrix& chunk ) {

  // metadata
  CHECK( 0 == chunk.LS() );
  CHECK( 0 == chunk.symmetryFlag() );
  CHECK( !chunk.isSymmetric() );
  CHECK( 5 == chunk.LB() );
  CHECK( 5 == chunk.procedure() );
  CHECK( 7 == chunk.NT() );
  CHECK( 7 == chunk.numberValues() );
  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergies() );

  // values
  CHECK( 0. == Approx( chunk.energies()[0] ) );
  CHECK( 100. == Approx( chunk.energies()[1] ) );
  CHECK( 200. == Approx( chunk.energies()[2] ) );
  CHECK( 1. == Approx( chunk.values()[0] ) );
  CHECK( 2. == Approx( chunk.values()[1] ) );
  CHECK( 3. == Approx( chunk.values()[2] ) );
  CHECK( 4. == Approx( chunk.values()[3] ) );

  CHECK( 3 == chunk.NC() );

}


std::string invalidLB() {
  return
    " 0.000000+0 0.000000+0          0          1          7          3922834  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922834  5     \n"
    " 4.000000+0                                                       922834  5     \n";
}

std::string inconsistentSymmetric() {
  return
    " 0.000000+0 0.000000+0          1          5          7          3922834  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922834  5     \n"
    " 4.000000+0                                                       922834  5     \n";
}

std::string inconsistentAsymmetric() {
  return
    " 0.000000+0 0.000000+0          0          5          6          3922834  5     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922834  5     \n";
}
