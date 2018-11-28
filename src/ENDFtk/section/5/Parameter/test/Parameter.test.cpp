#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Parameter = 
section::Type< 5 >::Parameter;

std::string chunk();

SCENARIO( "Parameter" ) {

  GIVEN( "valid data for a Parameter" ) {

    std::vector< long > boundaries = { 5 };
    std::vector< long > interpolants = { 1 };
    std::vector< double > x = { 1., 2., 3., 4., 5. };
    std::vector< double > y = { 6., 7., 8., 9., 10. };

    THEN( "a Parameter can be constructed and members can be tested" ) {
      Parameter chunk( std::move( boundaries ),
                       std::move( interpolants ),
                       std::move( x ),
                       std::move( y ) );

      REQUIRE( 5 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 5 == chunk.boundaries()[0] );
      REQUIRE( 5 == chunk.x().size() );
      REQUIRE( 5 == chunk.y().size() );
      REQUIRE( 1.0 == Approx( chunk.x()[0] ) );
      REQUIRE( 2.0 == Approx( chunk.x()[1] ) );
      REQUIRE( 3.0 == Approx( chunk.x()[2] ) );
      REQUIRE( 4.0 == Approx( chunk.x()[3] ) );
      REQUIRE( 5.0 == Approx( chunk.x()[4] ) );
      REQUIRE( 6.0 == Approx( chunk.y()[0] ) );
      REQUIRE( 7.0 == Approx( chunk.y()[1] ) );
      REQUIRE( 8.0 == Approx( chunk.y()[2] ) );
      REQUIRE( 9.0 == Approx( chunk.y()[3] ) );
      REQUIRE( 10.0 == Approx( chunk.y()[4] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid Parameter" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a Parameter can be constructed and members can be tested" ) {
      Parameter chunk( begin, end, lineNumber, 9437, 5, 455 );

      REQUIRE( 5 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 5 == chunk.boundaries()[0] );
      REQUIRE( 5 == chunk.x().size() );
      REQUIRE( 5 == chunk.y().size() );
      REQUIRE( 1.0 == Approx( chunk.x()[0] ) );
      REQUIRE( 2.0 == Approx( chunk.x()[1] ) );
      REQUIRE( 3.0 == Approx( chunk.x()[2] ) );
      REQUIRE( 4.0 == Approx( chunk.x()[3] ) );
      REQUIRE( 5.0 == Approx( chunk.x()[4] ) );
      REQUIRE( 6.0 == Approx( chunk.y()[0] ) );
      REQUIRE( 7.0 == Approx( chunk.y()[1] ) );
      REQUIRE( 8.0 == Approx( chunk.y()[2] ) );
      REQUIRE( 9.0 == Approx( chunk.y()[3] ) );
      REQUIRE( 10.0 == Approx( chunk.y()[4] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of Parameter" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    Parameter chunk(begin, end, lineNumber, 9437, 5, 455 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9437, 5, 455 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          59437 5455     \n"
    "          5          1                                            9437 5455     \n"
    " 1.000000+0 6.000000+0 2.000000+0 7.000000+0 3.000000+0 8.000000+09437 5455     \n"
    " 4.000000+0 9.000000+0 5.000000+0 1.000000+1                      9437 5455     \n";
}
