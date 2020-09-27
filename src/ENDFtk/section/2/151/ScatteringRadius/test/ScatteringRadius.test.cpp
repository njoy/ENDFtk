#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ScatteringRadius =
section::Type< 2, 151 >::ScatteringRadius;

std::string chunk();
void verifyChunk( const ScatteringRadius& );
std::string invalidChunk();

SCENARIO( "ScatteringRadius" ) {

  GIVEN( "valid data for a ScatteringRadius" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 1 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      ScatteringRadius chunk( std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( x ),
                              std::move( y ) );

      THEN( "a ScatteringRadius can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 2, 151 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ScatteringRadius chunk( begin, end, lineNumber, 9228, 2, 151 );

      THEN( "a ScatteringRadius can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 2, 151 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ScatteringRadius" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 5 };
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< double > x = { 1., 2., 3., 4., 5. };
      std::vector< double > y = { 6., 7., 8., 9., 10. };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( ScatteringRadius( std::move( boundaries ),
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

        REQUIRE_THROWS( ScatteringRadius( begin, end, lineNumber,
                                          9228, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          59228 2151     \n"
    "          5          1                                            9228 2151     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09228 2151     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9228 2151     \n";
}

void verifyChunk( const ScatteringRadius& chunk ) {

  REQUIRE( 5 == chunk.NP() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );
  REQUIRE( 5 == chunk.boundaries()[0] );
  REQUIRE( 5 == chunk.E().size() );
  REQUIRE( 5 == chunk.energies().size() );
  REQUIRE( 5 == chunk.AP().size() );
  REQUIRE( 5 == chunk.radii().size() );
  REQUIRE( 1.0 == Approx( chunk.E()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.E()[1] ) );
  REQUIRE( 3.0 == Approx( chunk.E()[2] ) );
  REQUIRE( 4.0 == Approx( chunk.E()[3] ) );
  REQUIRE( 5.0 == Approx( chunk.E()[4] ) );
  REQUIRE( 1.0 == Approx( chunk.energies()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.energies()[1] ) );
  REQUIRE( 3.0 == Approx( chunk.energies()[2] ) );
  REQUIRE( 4.0 == Approx( chunk.energies()[3] ) );
  REQUIRE( 5.0 == Approx( chunk.energies()[4] ) );
  REQUIRE( 6.0 == Approx( chunk.AP()[0] ) );
  REQUIRE( 7.0 == Approx( chunk.AP()[1] ) );
  REQUIRE( 8.0 == Approx( chunk.AP()[2] ) );
  REQUIRE( 9.0 == Approx( chunk.AP()[3] ) );
  REQUIRE( 10.0 == Approx( chunk.AP()[4] ) );
  REQUIRE( 6.0 == Approx( chunk.radii()[0] ) );
  REQUIRE( 7.0 == Approx( chunk.radii()[1] ) );
  REQUIRE( 8.0 == Approx( chunk.radii()[2] ) );
  REQUIRE( 9.0 == Approx( chunk.radii()[3] ) );
  REQUIRE( 10.0 == Approx( chunk.radii()[4] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          59228 2151     \n"
    "          5          1                                            9228 2151     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09228 2151     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9228 2151     \n";
}
