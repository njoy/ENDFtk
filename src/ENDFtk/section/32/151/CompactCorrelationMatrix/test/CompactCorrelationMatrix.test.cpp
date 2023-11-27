// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactCorrelationMatrix =
section::Type< 32, 151 >::CompactCorrelationMatrix;

std::string chunk();
void verifyChunk( const CompactCorrelationMatrix& );
std::string invalidDigits();

SCENARIO( "CompactCorrelationMatrix" ) {

  GIVEN( "valid data for a CompactCorrelationMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > i = {  2,  3,  3,  7,  7,  7,  7,  7,  7,
                                         7,  7,  7,  7,  7,  7,  7,  7,  7,
                                         7, 10, 10, 10 };
      std::vector< unsigned int > j = {  1,  1,  2,  5,  6,  9, 10, 11, 12,
                                        13, 14, 15, 16, 17, 18, 19, 20, 21,
                                        23, 4,  6,  8 };
      std::vector< double > correlations = { 0.025, 0.035, 0.085, 0.085, 0.055,
                                             0.015, 0.015, 0.015, 0.015, 0.015,
                                             0.015, 0.015, 0.015, 0.015, 0.015,
                                             0.015, 0.015, 0.015, 0.025, 0.015,
                                             0.015, 0.015 };
      unsigned int ndigit = 2;
      unsigned int order = 25;

      CompactCorrelationMatrix chunk( order,
                                      std::move( i ), std::move( j ),
                                      std::move( correlations ), ndigit );

      THEN( "a CompactCorrelationMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1725, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CompactCorrelationMatrix chunk( begin, end, lineNumber, 1725, 32, 151 );

      THEN( "a CompactCorrelationMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1725, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      unsigned int order = 12;
      std::vector< unsigned int > i = { 3, 4 };
      std::vector< unsigned int > j = { 1, 2 };
      std::vector< double > correlations = { 0.015 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactCorrelationMatrix( order,
                                                std::move( i ), std::move( j ),
                                                std::move( correlations ) ) );
      } // THEN
    } // WHEN

    WHEN( "an invalid NDIGIT is used" ) {

      unsigned int order = 12;
      std::vector< unsigned int > i = { 3, 4 };
      std::vector< unsigned int > j = { 1, 2 };
      std::vector< double > correlations = { 0.015, 0.025 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactCorrelationMatrix( order,
                                                std::move( i ), std::move( j ),
                                                std::move( correlations ),
                                                7 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with an invalid NDIGIT is used" ) {

      std::string string = invalidDigits();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactCorrelationMatrix( begin, end, lineNumber, 1725, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2         25          5          0172532151     \n"
    "    2    1   2                                                    172532151     \n"
    "    3    1   3  8                                                 172532151     \n"
    "    7    5   8  5  0  0  1  1  1  1  1  1  1  1  1  1  1  1  1    172532151     \n"
    "    7   23   2                                                    172532151     \n"
    "   10    4   1  0  1  0  1                                        172532151     \n";
}

void verifyChunk( const CompactCorrelationMatrix& chunk ) {

  CHECK( 2 == chunk.NDIGIT() );
  CHECK( 2 == chunk.numberDigits() );
  CHECK( 25 == chunk.NNN() );
  CHECK( 25 == chunk.order() );
  CHECK( 22 == chunk.I().size() );
  CHECK( 22 == chunk.J().size() );
  CHECK( 22 == chunk.correlations().size() );

  CHECK(  2 == chunk.I()[0] );
  CHECK(  3 == chunk.I()[1] );
  CHECK(  3 == chunk.I()[2] );
  CHECK(  7 == chunk.I()[3] );
  CHECK(  7 == chunk.I()[4] );
  CHECK(  7 == chunk.I()[5] );
  CHECK(  7 == chunk.I()[6] );
  CHECK(  7 == chunk.I()[7] );
  CHECK(  7 == chunk.I()[8] );
  CHECK(  7 == chunk.I()[9] );
  CHECK(  7 == chunk.I()[10] );
  CHECK(  7 == chunk.I()[11] );
  CHECK(  7 == chunk.I()[12] );
  CHECK(  7 == chunk.I()[13] );
  CHECK(  7 == chunk.I()[14] );
  CHECK(  7 == chunk.I()[15] );
  CHECK(  7 == chunk.I()[16] );
  CHECK(  7 == chunk.I()[17] );
  CHECK(  7 == chunk.I()[18] );
  CHECK( 10 == chunk.I()[19] );
  CHECK( 10 == chunk.I()[20] );
  CHECK( 10 == chunk.I()[21] );
  CHECK(  1 == chunk.J()[0] );
  CHECK(  1 == chunk.J()[1] );
  CHECK(  2 == chunk.J()[2] );
  CHECK(  5 == chunk.J()[3] );
  CHECK(  6 == chunk.J()[4] );
  CHECK(  9 == chunk.J()[5] );
  CHECK( 10 == chunk.J()[6] );
  CHECK( 11 == chunk.J()[7] );
  CHECK( 12 == chunk.J()[8] );
  CHECK( 13 == chunk.J()[9] );
  CHECK( 14 == chunk.J()[10] );
  CHECK( 15 == chunk.J()[11] );
  CHECK( 16 == chunk.J()[12] );
  CHECK( 17 == chunk.J()[13] );
  CHECK( 18 == chunk.J()[14] );
  CHECK( 19 == chunk.J()[15] );
  CHECK( 20 == chunk.J()[16] );
  CHECK( 21 == chunk.J()[17] );
  CHECK( 23 == chunk.J()[18] );
  CHECK(  4 == chunk.J()[19] );
  CHECK(  6 == chunk.J()[20] );
  CHECK(  8 == chunk.J()[21] );
  CHECK_THAT( 0.025, WithinRel( chunk.correlations()[0] ) );
  CHECK_THAT( 0.035, WithinRel( chunk.correlations()[1] ) );
  CHECK_THAT( 0.085, WithinRel( chunk.correlations()[2] ) );
  CHECK_THAT( 0.085, WithinRel( chunk.correlations()[3] ) );
  CHECK_THAT( 0.055, WithinRel( chunk.correlations()[4] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[5] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[6] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[7] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[8] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[9] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[10] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[11] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[12] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[13] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[14] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[15] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[16] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[17] ) );
  CHECK_THAT( 0.025, WithinRel( chunk.correlations()[18] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[19] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[20] ) );
  CHECK_THAT( 0.015, WithinRel( chunk.correlations()[21] ) );

  CHECK( 6 == chunk.NC() );
}

std::string invalidDigits() {
  return
    " 0.000000+0 0.000000+0          7         25          4          0172532151     \n"
    "    2    1   2                                                    172532151     \n"
    "    3    1   3  8                                                 172532151     \n"
    "    7    5   8  5                                                 172532151     \n"
    "   10    4   1  0  1  0  1                                        172532151     \n";
}
