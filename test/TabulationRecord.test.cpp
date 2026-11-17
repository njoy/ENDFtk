// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/TabulationRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const TabulationRecord& );
std::string chunkWithInvalidNP();
std::string chunkWithInvalidNR();
std::string chunkWithNegativeNP();
std::string chunkWithNegativeNR();
std::string chunkWithZeroNP();
std::string chunkWithZeroNR();
std::string chunkWithOutOfOrderXValues();
std::string chunkWithOutOfOrderBoundaries();
std::string chunkWithInconsistentNP();

SCENARIO( "TabulationRecord" ) {

  GIVEN( "valid data for a TabulationRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6, 8 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };
      std::vector< double > x = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
      std::vector< double > y = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

      TabulationRecord chunk( C1, C2, L1, L2,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( x ),
                              std::move( y ) );

      THEN( "a TabulationRecord can be constructed and members can be tested" ) {

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

      TabulationRecord chunk( begin, end, lineNumber, 125, 3, 102 );

      THEN( "a TabulationRecord can be constructed and members can be tested" ) {

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

  GIVEN( "different TabulationRecord" ) {

    GIVEN( "they can be compared" ) {

      TabulationRecord chunk( 1., 2., 3, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord equal( 1., 2., 3, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord c1( 2., 2., 3, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord c2( 1., 1., 3, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord l1( 1., 2., 4, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord l2( 1., 2., 3, 5, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord boundaries( 1., 2., 3, 4, { 3, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord interpolants( 1., 2., 3, 4, { 2, 4 }, { 2, 5 }, { 1., 2., 3., 4. }, { 4., 3., 2., 1. } );
      TabulationRecord x( 1., 2., 3, 4, { 2, 4 }, { 5, 2 }, { 2., 3., 4., 5. }, { 4., 3., 2., 1. } );
      TabulationRecord y( 1., 2., 3, 4, { 2, 4 }, { 5, 2 }, { 1., 2., 3., 4. }, { 6., 7., 8., 9. } );

      CHECK( chunk == equal );
      CHECK( chunk != c1 );
      CHECK( chunk != c2 );
      CHECK( chunk != boundaries );
      CHECK( chunk != interpolants );
      CHECK( chunk != x );
      CHECK( chunk != y );
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data for a TabulationRecord" ) {

    WHEN( "a string representation with an incorrect NP value is given" ) {

      std::string string = chunkWithInvalidNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an incorrect NR value is given" ) {

      std::string string = chunkWithInvalidNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a negative NP value is given" ) {

      std::string string = chunkWithNegativeNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a negative NR value is given" ) {

      std::string string = chunkWithNegativeNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a zero NP value is given" ) {

      std::string string = chunkWithZeroNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a zero NR value is given" ) {

      std::string string = chunkWithZeroNR();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has out of order boundaries" ) {

      std::string string = chunkWithOutOfOrderBoundaries();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has out of order x values" ) {

      std::string string = chunkWithOutOfOrderXValues();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has inconsistent NP values" ) {

      std::string string = chunkWithInconsistentNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 102 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has a mismatch in the tail values" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 5, 3, 102 ) ); // MAT
        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 1, 102 ) ); // MF
        CHECK_THROWS( TabulationRecord( begin, end, lineNumber, 125, 3, 103 ) ); // MT
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants are of different lengths" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };
      std::vector< double > x = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
      std::vector< double > y = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y values are of different lengths" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6, 8 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };
      std::vector< double > x = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
      std::vector< double > y = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are out of order" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 6, 5, 8 };
      std::vector< long > interpolants = { 1, 2, 3, 5 };
      std::vector< double > x = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
      std::vector< double > y = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "there is a mismatch between the interpolation data and the x and y values" ) {

      double C1 = 1.;
      double C2 = 2.;
      int L1 = 3;
      int L2 = 4;
      std::vector< long > boundaries = { 4, 5, 6 };
      std::vector< long > interpolants = { 1, 2, 3 };
      std::vector< double > x = { 2.0, 1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
      std::vector< double > y = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulationRecord( C1, C2, L1, L2,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

void verifyChunk( const TabulationRecord& chunk ) {

  CHECK_THAT( 1.0, WithinRel( chunk.C1() ) );
  CHECK_THAT( 2.0, WithinRel( chunk.C2() ) );
  CHECK( 3 == chunk.L1() );
  CHECK( 4 == chunk.L2() );

  CHECK( 8 == chunk.NP() );
  CHECK( 4 == chunk.NR() );
  CHECK( 8 == chunk.numberPoints() );
  CHECK( 4 == chunk.numberInterpolationRegions() );

  CHECK( 4 == chunk.NBT().size() );
  CHECK( 4 == chunk.INT().size() );
  CHECK( 4 == chunk.NBT()[0] );
  CHECK( 5 == chunk.NBT()[1] );
  CHECK( 6 == chunk.NBT()[2] );
  CHECK( 8 == chunk.NBT()[3] );
  CHECK( 1 == chunk.INT()[0] );
  CHECK( 2 == chunk.INT()[1] );
  CHECK( 3 == chunk.INT()[2] );
  CHECK( 5 == chunk.INT()[3] );

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

  CHECK( 8 == chunk.x().size() );
  CHECK( 8 == chunk.y().size() );
  CHECK_THAT(  1., WithinRel( chunk.x()[0] ) );
  CHECK_THAT(  2., WithinRel( chunk.x()[1] ) );
  CHECK_THAT(  3., WithinRel( chunk.x()[2] ) );
  CHECK_THAT(  4., WithinRel( chunk.x()[3] ) );
  CHECK_THAT(  5., WithinRel( chunk.x()[4] ) );
  CHECK_THAT(  6., WithinRel( chunk.x()[5] ) );
  CHECK_THAT(  7., WithinRel( chunk.x()[6] ) );
  CHECK_THAT(  8., WithinRel( chunk.x()[7] ) );
  CHECK_THAT(  3., WithinRel( chunk.y()[0] ) );
  CHECK_THAT(  4., WithinRel( chunk.y()[1] ) );
  CHECK_THAT(  5., WithinRel( chunk.y()[2] ) );
  CHECK_THAT(  6., WithinRel( chunk.y()[3] ) );
  CHECK_THAT(  7., WithinRel( chunk.y()[4] ) );
  CHECK_THAT(  8., WithinRel( chunk.y()[5] ) );
  CHECK_THAT(  9., WithinRel( chunk.y()[6] ) );
  CHECK_THAT( 10., WithinRel( chunk.y()[7] ) );

  CHECK( 6 == chunk.NC() );
}

std::string chunkWithInvalidNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          6 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithInvalidNR() {

  return
    " 1.000000+0 2.000000+0          3          4          3          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithNegativeNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4         -1 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithNegativeNR() {

  return
    " 1.000000+0 2.000000+0          3          4         -1          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithZeroNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          0 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithZeroNR() {

  return
    " 1.000000+0 2.000000+0          3          4          0          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithOutOfOrderXValues() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          5          2          6          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 2.000000+0 3.000000+0 1.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithOutOfOrderBoundaries() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          6          2          5          3 125 3102     \n"
    "          8          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}

std::string chunkWithInconsistentNP() {

  return
    " 1.000000+0 2.000000+0          3          4          4          8 125 3102     \n"
    "          4          1          6          2          5          3 125 3102     \n"
    "          7          5                                             125 3102     \n"
    " 1.000000+0 3.000000+0 2.000000+0 4.000000+0 3.000000+0 5.000000+0 125 3102     \n"
    " 4.000000+0 6.000000+0 5.000000+0 7.000000+0 6.000000+0 8.000000+0 125 3102     \n"
    " 7.000000+0 9.000000+0 8.000000+0 1.000000+1                       125 3102     \n";
}
