// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Parameter =
section::Type< 5 >::Parameter;

std::string chunk();
void verifyChunk( const Parameter& );
std::string invalidChunk();

SCENARIO( "Parameter" ) {

  GIVEN( "valid data for a Parameter" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      Parameter chunk( std::move( boundaries ),
                       std::move( interpolants ),
                       std::move( x ),
                       std::move( y ) );

      THEN( "a Parameter can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Parameter chunk( begin, end, lineNumber, 9437, 5, 455 );

      THEN( "a Parameter can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Parameter" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 5 };
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Parameter( std::move( boundaries ),
                                   std::move( wrongInterpolants ),
                                   std::move( x ),
                                   std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Parameter( begin, end, lineNumber, 9437, 5, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}

void verifyChunk( const Parameter& chunk ) {

  CHECK( 5 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 5 == chunk.boundaries()[0] );
  CHECK( 5 == chunk.E().size() );
  CHECK( 5 == chunk.energies().size() );
  CHECK( 5 == chunk.values().size() );
  CHECK_THAT( 1.0, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.E()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.E()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.E()[4] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 6.0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 7.0, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 8.0, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 9.0, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 10.0, WithinRel( chunk.values()[4] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}
