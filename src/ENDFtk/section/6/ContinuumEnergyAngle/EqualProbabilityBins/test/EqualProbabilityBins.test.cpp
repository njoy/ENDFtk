#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using EqualProbabilityBins =
section::Type< 6 >::ContinuumEnergyAngle::EqualProbabilityBins;

std::string chunk();
void verifyChunk( const EqualProbabilityBins& );

SCENARIO( "EqualProbabilityBins" ) {

  GIVEN( "valid data for a EqualProbabilityBins" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int n2 = 6;
      std::vector< double > data = { 0., 0., 0., 0., 0., 0.,
                                     9.999999e-6, 9.477167e+1, -5.379121e-1,
                                     0.21062848, 0.70490082, 9.552579e-1,
                                     1.265100e-1, 0., 0., 0., 0., 0. };

      EqualProbabilityBins chunk( energy, n2, std::move( data ) );

      THEN( "a EqualProbabilityBins can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EqualProbabilityBins chunk( begin, end, lineNumber, 1301, 6, 222 );

      THEN( "a EqualProbabilityBins can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1301, 6, 222 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0         18          61301 6222     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n"
    " 9.999999-6 9.477167+1-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n"
    " 1.265100-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n";
}

void verifyChunk( const EqualProbabilityBins& chunk ) {

  REQUIRE( 3 == chunk.LANG() );
  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  auto data = chunk.data();
  REQUIRE( 18 == data.size() );
  REQUIRE( 0. == Approx( data[0] ) );
  REQUIRE( 0. == Approx( data[1] ) );
  REQUIRE( 0. == Approx( data[2] ) );
  REQUIRE( 0. == Approx( data[3] ) );
  REQUIRE( 0. == Approx( data[4] ) );
  REQUIRE( 0. == Approx( data[5] ) );
  REQUIRE( 9.999999e-6 == Approx( data[6] ) );
  REQUIRE( 9.477167e+1 == Approx( data[7] ) );
  REQUIRE( -5.379121e-1 == Approx( data[8] ) );
  REQUIRE( 0.21062848 == Approx( data[9] ) );
  REQUIRE( 0.70490082 == Approx( data[10] ) );
  REQUIRE( 9.552579e-1 == Approx( data[11] ) );
  REQUIRE( 1.265100e-1 == Approx( data[12] ) );
  REQUIRE( 0. == Approx( data[13] ) );
  REQUIRE( 0. == Approx( data[14] ) );
  REQUIRE( 0. == Approx( data[15] ) );
  REQUIRE( 0. == Approx( data[16] ) );
  REQUIRE( 0. == Approx( data[17] ) );

  REQUIRE( 4 == chunk.NC() );
}
