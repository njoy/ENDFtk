#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DistributionFunction = 
section::Type< 5 >::DistributionFunction;

std::string chunk();
void verifyChunk( const DistributionFunction& );
std::string invalidChunk();

SCENARIO( "DistributionFunction" ) {

  GIVEN( "valid data for a DistributionFunction" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      DistributionFunction chunk( std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( x ),
                                  std::move( y ) );

      THEN( "a DistributionFunction can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DistributionFunction chunk( begin, end, lineNumber, 9437, 5, 455 );

      THEN( "a DistributionFunction can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DistributionFunction" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 5 };
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( DistributionFunction( std::move( boundaries ),
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

        REQUIRE_THROWS( DistributionFunction( begin, end, lineNumber, 9437, 5, 455 ) );
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

void verifyChunk( const DistributionFunction& chunk ) {

  REQUIRE( 5 == chunk.NF() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );
  REQUIRE( 5 == chunk.boundaries()[0] );
  REQUIRE( 5 == chunk.x().size() );
  REQUIRE( 5 == chunk.values().size() );
  REQUIRE( 1.0 == Approx( chunk.x()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.x()[1] ) );
  REQUIRE( 3.0 == Approx( chunk.x()[2] ) );
  REQUIRE( 4.0 == Approx( chunk.x()[3] ) );
  REQUIRE( 5.0 == Approx( chunk.x()[4] ) );
  REQUIRE( 6.0 == Approx( chunk.values()[0] ) );
  REQUIRE( 7.0 == Approx( chunk.values()[1] ) );
  REQUIRE( 8.0 == Approx( chunk.values()[2] ) );
  REQUIRE( 9.0 == Approx( chunk.values()[3] ) );
  REQUIRE( 10.0 == Approx( chunk.values()[4] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}
