// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK_THROWS( EffectiveTemperature(
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

        CHECK_THROWS(
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

  CHECK( 3 == chunk.NP() );
  CHECK( 3 == chunk.NT() );
  CHECK( 3 == chunk.numberTemperatures() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 3 == chunk.TMOD().size() );
  CHECK( 3 == chunk.moderatorTemperatures().size() );
  CHECK( 3 == chunk.TEFF().size() );
  CHECK( 3 == chunk.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( chunk.TMOD()[0] ) );
  CHECK_THAT( 600., WithinRel( chunk.TMOD()[1] ) );
  CHECK_THAT( 1200., WithinRel( chunk.TMOD()[2] ) );
  CHECK_THAT( 293.6, WithinRel( chunk.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( chunk.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( chunk.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( chunk.TEFF()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( chunk.TEFF()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( chunk.TEFF()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( chunk.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( chunk.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( chunk.effectiveTemperatures()[2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          4  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}
