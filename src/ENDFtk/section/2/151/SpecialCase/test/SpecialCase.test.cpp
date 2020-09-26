#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SpecialCase =
section::Type< 2, 151 >::SpecialCase;

std::string chunk();
void verifyChunk( const SpecialCase& );

SCENARIO( "SpecialCase" ) {

  GIVEN( "valid data for an SpecialCase" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi =  0.5;
      double ap = 1.276553;

      SpecialCase chunk( spi, ap );

      THEN( "a SpecialCase can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      SpecialCase chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a SpecialCase can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000-1 1.276553+0          0          0          0          02625 2151     \n";
}

void verifyChunk( const SpecialCase& chunk ) {

  CHECK( 0 == chunk.LRU() );
  CHECK( 0 == chunk.type() );
  CHECK( 0 == chunk.LRF() );
  CHECK( 0 == chunk.representation() );

  CHECK( 0.5 == Approx( chunk.SPI() ) );
  CHECK( 0.5 == Approx( chunk.spin() ) );
  CHECK( 1.276553 == Approx( chunk.AP() ) );
  CHECK( 1.276553 == Approx( chunk.scatteringRadius() ) );

  CHECK( 1 == chunk.NC() );
}
