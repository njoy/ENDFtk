// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/CovariancePairs.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CovariancePairs = section::CovariancePairs;

std::string chunkLB1();
std::string chunkLB3();
std::string invalidLB();
std::string inconsistentNT();
void verifyChunkLB1( const CovariancePairs& );
void verifyChunkLB3( const CovariancePairs& );


SCENARIO( "CovariancePairs" ) {

  GIVEN( "valid data for a CovariancePairs" ) {

    std::string string = chunkLB1();

    WHEN( "the data is given explicitly for LB=1" ) {

      std::vector< double > energies = { 1, 3 };
      std::vector< double > fvalues = { 2, 4 };

      CovariancePairs chunk( 1, std::move(energies), std::move(fvalues) );

      THEN( "a CovariancePairs can be constructed "
            "and members can be tested" ) {

        verifyChunkLB1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CovariancePairs chunk( begin, end, lineNumber, 9228, 33, 5 );

      THEN( "a CovariancePairs object can be constructed "
            "and members can be tested" ) {

        verifyChunkLB1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "valid data for a LB=3 CovariancePairs") {

    std::string string = chunkLB3();

    WHEN( "the data is given explicitly for LB=3" ) {

      std::vector< double > ek = { 1, 3, 5 };
      std::vector< double > fk = { 2, 4, 6 };
      std::vector< double > el = { 7, 9 };
      std::vector< double > fl = { 8, 10 };

      CovariancePairs chunk( 3,
            std::move(ek), std::move(fk),
            std::move(el), std::move(fl) );

      THEN( "a CovariancePairs object can be constructed "
            "and members can be tested" ) {

        verifyChunkLB3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CovariancePairs chunk( begin, end, lineNumber, 9228, 33, 5 );

      THEN( "a CovariancePairs object can be constructed "
            "and members can be tested" ) {

        verifyChunkLB3( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a CovariancePairs" ) {

    WHEN( "a string representation is used with an invalid LB" ) {

      std::string string = invalidLB();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          CovariancePairs( begin, end, lineNumber, 9228, 33, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent LB and NT" ) {

      std::string string = inconsistentNT();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          CovariancePairs( begin, end, lineNumber, 9228, 33, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunkLB1() {
  return
    " 0.000000+0 0.000000+0          0          1          4          2922833  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922833  5     \n";
}

std::string chunkLB3() {
  return
    " 0.000000+0 0.000000+0          2          3         10          5922833  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922833  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                      922833  5     \n";
}

void verifyChunkLB1( const CovariancePairs& chunk ) {

  // metadata
  CHECK( 0 == chunk.LT() );
  CHECK( 0 == chunk.numberSecondPairs() );
  CHECK( 1 == chunk.LB() );
  CHECK( 1 == chunk.procedure() );
  CHECK( 4 == chunk.NT() );
  CHECK( 4 == chunk.numberValues() );
  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberPairs() );

  // values
  CHECK_THAT( 1., WithinRel( chunk.EK()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.FK()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.EK()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.FK()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.firstArrayEnergies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.firstArrayFValues()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.firstArrayEnergies()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.firstArrayFValues()[1] ) );

  CHECK( 2 == chunk.NC() );

}

void verifyChunkLB3( const CovariancePairs& chunk ) {

  // metadata
  CHECK( 2 == chunk.LT() );
  CHECK( 2 == chunk.numberSecondPairs() );
  CHECK( 3 == chunk.LB() );
  CHECK( 3 == chunk.procedure() );
  CHECK( 10 == chunk.NT() );
  CHECK( 10 == chunk.numberValues() );
  CHECK( 5 == chunk.NP() );
  CHECK( 5 == chunk.numberPairs() );

  // values
  CHECK_THAT( 1., WithinRel( chunk.EK()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.FK()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.EK()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.FK()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.EL()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.FL()[0] ) );
  CHECK_THAT( 9., WithinRel( chunk.EL()[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.FL()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.firstArrayEnergies()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.firstArrayFValues()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.firstArrayEnergies()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.firstArrayFValues()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.secondArrayEnergies()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.secondArrayFValues()[0] ) );
  CHECK_THAT( 9., WithinRel( chunk.secondArrayEnergies()[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.secondArrayFValues()[1] ) );

  CHECK( 3 == chunk.NC() );

}

std::string invalidLB() {
  return
    " 0.000000+0 0.000000+0          0          5          4          2922833  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922833  5     \n";
}

std::string inconsistentNT() {
  return
    " 0.000000+0 0.000000+0          0          3          4          2922833  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922833  5     \n";
}
