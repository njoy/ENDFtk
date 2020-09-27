#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using EffectiveTemperature =
section::Type< 7, 4 >::EffectiveTemperature;

std::string chunk();
void verifyChunk( const EffectiveTemperature& );
std::string invalidChunk();

SCENARIO( "EffectiveTemperature" ) {

  GIVEN( "valid data for a EffectiveTemperature" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > moderatorTemperatures = { 293.6, 600., 1200. };
      std::vector< double > effectiveTemperatures = { 5.332083e+2, 7.354726e+2,
                                                      1.270678e+3 };

      EffectiveTemperature chunk( std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( moderatorTemperatures ),
                                  std::move( effectiveTemperatures ) );

      THEN( "an EffectiveTemperature can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EffectiveTemperature chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a EffectiveTemperature can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a EffectiveTemperature" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > wrongBoundaries = { 3, 4 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > moderatorTemperatures = { 293.6, 600., 1200. };
      std::vector< double > effectiveTemperatures = { 5.332083e+2, 7.354726e+2,
                                                      1.270678e+3 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( EffectiveTemperature(
                              std::move( wrongBoundaries ),
                              std::move( interpolants ),
                              std::move( moderatorTemperatures ),
                              std::move( effectiveTemperatures ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS(
            EffectiveTemperature( begin, end, lineNumber, 27, 7, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}

void verifyChunk( const EffectiveTemperature& chunk ) {

  REQUIRE( 3 == chunk.NT() );
  REQUIRE( 3 == chunk.numberTemperatures() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 2 == chunk.interpolants()[0] );
  REQUIRE( 3 == chunk.boundaries()[0] );
  REQUIRE( 3 == chunk.moderatorTemperatures().size() );
  REQUIRE( 3 == chunk.effectiveTemperatures().size() );
  REQUIRE( 293.6 == Approx( chunk.moderatorTemperatures()[0] ) );
  REQUIRE( 600. == Approx( chunk.moderatorTemperatures()[1] ) );
  REQUIRE( 1200. == Approx( chunk.moderatorTemperatures()[2] ) );
  REQUIRE( 5.332083e+2 == Approx( chunk.effectiveTemperatures()[0] ) );
  REQUIRE( 7.354726e+2 == Approx( chunk.effectiveTemperatures()[1] ) );
  REQUIRE( 1.270678e+3 == Approx( chunk.effectiveTemperatures()[2] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          4  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}
