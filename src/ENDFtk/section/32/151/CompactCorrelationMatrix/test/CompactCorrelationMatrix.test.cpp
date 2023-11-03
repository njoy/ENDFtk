#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

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

      std::vector< unsigned int > i = { 2, 3, 3, 7, 7, 10, 10, 10 };
      std::vector< unsigned int > j = { 1, 1, 2, 5, 6,  4,  6,  8 };
      std::vector< double > correlations = { 0.025, 0.035, 0.085, 0.085, 0.055,
                                             0.015, 0.015, 0.015 };
      unsigned int ndigit = 2;
      unsigned int order = 12;

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

    WHEN( "the data is empty" ) {

      unsigned int order = 12;
      std::vector< unsigned int > i = {};
      std::vector< unsigned int > j = {};
      std::vector< double > correlations = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactCorrelationMatrix( order,
                                                std::move( i ), std::move( j ),
                                                std::move( correlations ) ) );
      } // THEN
    } // WHEN

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
    " 0.000000+0 0.000000+0          2         12          4          0172532151     \n"
    "    2    1   2                                                    172532151     \n"
    "    3    1   3  8                                                 172532151     \n"
    "    7    5   8  5                                                 172532151     \n"
    "   10    4   1  0  1  0  1                                        172532151     \n";
}

void verifyChunk( const CompactCorrelationMatrix& chunk ) {

  CHECK( 2 == chunk.NDIGIT() );
  CHECK( 2 == chunk.numberDigits() );
  CHECK( 12 == chunk.NNN() );
  CHECK( 12 == chunk.order() );
  CHECK( 8 == chunk.I().size() );
  CHECK( 8 == chunk.J().size() );
  CHECK( 8 == chunk.correlations().size() );

  CHECK(  2 == chunk.I()[0] );
  CHECK(  3 == chunk.I()[1] );
  CHECK(  3 == chunk.I()[2] );
  CHECK(  7 == chunk.I()[3] );
  CHECK(  7 == chunk.I()[4] );
  CHECK( 10 == chunk.I()[5] );
  CHECK( 10 == chunk.I()[6] );
  CHECK( 10 == chunk.I()[7] );
  CHECK(  1 == chunk.J()[0] );
  CHECK(  1 == chunk.J()[1] );
  CHECK(  2 == chunk.J()[2] );
  CHECK(  5 == chunk.J()[3] );
  CHECK(  6 == chunk.J()[4] );
  CHECK(  4 == chunk.J()[5] );
  CHECK(  6 == chunk.J()[6] );
  CHECK(  8 == chunk.J()[7] );
  CHECK( 0.025 == Approx( chunk.correlations()[0] ) );
  CHECK( 0.035 == Approx( chunk.correlations()[1] ) );
  CHECK( 0.085 == Approx( chunk.correlations()[2] ) );
  CHECK( 0.085 == Approx( chunk.correlations()[3] ) );
  CHECK( 0.055 == Approx( chunk.correlations()[4] ) );
  CHECK( 0.015 == Approx( chunk.correlations()[5] ) );
  CHECK( 0.015 == Approx( chunk.correlations()[6] ) );
  CHECK( 0.015 == Approx( chunk.correlations()[7] ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidDigits() {
  return
    " 0.000000+0 0.000000+0          7         12          4          0172532151     \n"
    "    2    1   2                                                    172532151     \n"
    "    3    1   3  8                                                 172532151     \n"
    "    7    5   8  5                                                 172532151     \n"
    "   10    4   1  0  1  0  1                                        172532151     \n";
}
