// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/InterpolationRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const InterpolationRecord& );
std::string chunkWithInvalidNP();
std::string chunkWithInvalidNR();
std::string chunkWithNegativeNP();
std::string chunkWithNegativeNR();
std::string chunkWithZeroNP();
std::string chunkWithZeroNR();
std::string chunkWithOutOfOrderBoundaries();
std::string chunkWithInconsistentNP();

SCENARIO( "InterpolationRecord" ) {

  GIVEN( "valid data for an InterpolationRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6, 8 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };

      InterpolationRecord chunk( C1, C2, L1, L2,
                               std::move( boundaries ),
                               std::move( interpolants ) );

      THEN( "an InterpolationRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      InterpolationRecord chunk( begin, end, lineNumber, 125, 3, 102 );

      THEN( "an InterpolationRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "different InterpolationRecord" ) {

    GIVEN( "they can be compared" ) {

      InterpolationRecord chunk( 1., 2., 3, 4, { 2, 4 }, { 5, 2 } );
      InterpolationRecord equal( 1., 2., 3, 4, { 2, 4 }, { 5, 2 } );
      InterpolationRecord c1( 2., 2., 3, 4, { 2, 4 }, { 5, 2 } );
      InterpolationRecord c2( 1., 1., 3, 4, { 2, 4 }, { 5, 2 } );
      InterpolationRecord boundaries( 1., 2., 3, 4, { 3, 4 }, { 5, 2 } );
      InterpolationRecord interpolants( 1., 2., 3, 4, { 2, 4 }, { 2, 5 } );

      CHECK( chunk == equal );
      CHECK( chunk != c1 );
      CHECK( chunk != c2 );
      CHECK( chunk != boundaries );
      CHECK( chunk != interpolants );
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationRecord" ) {

    WHEN( "a string representation with an incorrect NP value is given" ) {

      std::string string = chunkWithInvalidNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an incorrect NR value is given" ) {

      std::string string = chunkWithInvalidNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a negative NP value is given" ) {

      std::string string = chunkWithNegativeNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a negative NR value is given" ) {

      std::string string = chunkWithNegativeNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a zero NP value is given" ) {

      std::string string = chunkWithZeroNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a zero NR value is given" ) {

      std::string string = chunkWithZeroNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has out of order boundaries" ) {

      std::string string = chunkWithOutOfOrderBoundaries();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has inconsistent NP values" ) {

      std::string string = chunkWithInconsistentNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has a mismatch in the tail values" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 5, 3, 102 ) ); // MAT
        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 1, 102 ) ); // MF
        CHECK_THROWS( InterpolationRecord( begin, end, lineNumber, 125, 3, 103 ) ); // MT
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants are of different lengths" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are out of order" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 6, 5, 8 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

void verifyChunk( const InterpolationRecord& chunk ) {

  CHECK_THAT( 1.0, WithinRel( chunk.C1() ) );
  CHECK_THAT( 2.0, WithinRel( chunk.C2() ) );
  CHECK( 3 == chunk.L1() );
  CHECK( 4 == chunk.L2() );

  CHECK( 8 == chunk.NZ() );
  CHECK( 4 == chunk.NR() );

  CHECK( 4 == chunk.boundaries().size() );
  CHECK( 4 == chunk.interpolants().size() );
  CHECK( 4 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.boundaries()[1] );
  CHECK( 6 == chunk.boundaries()[2] );
  CHECK( 8 == chunk.boundaries()[3] );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.interpolants()[1] );
  CHECK( 3 == chunk.interpolants()[2] );
  CHECK( 5 == chunk.interpolants()[3] );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithInvalidNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          6 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithInvalidNR() {

  return
    " 1.000000+0 2.000000+0          3          4          3          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithNegativeNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4         -1 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithNegativeNR() {

  return
    " 1.000000+0 2.000000+0          3          4         -1          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithZeroNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          0 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithZeroNR() {

  return
    " 1.000000+0 2.000000+0          3          4          0          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithOutOfOrderBoundaries() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          6          2          5          3 125 3102     \n"
    "          8          5                                             125 3102     \n";
}

std::string chunkWithInconsistentNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          6          2          5          3 125 3102     \n"
    "          7          5                                             125 3102     \n";
}
