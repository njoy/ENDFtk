#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using WattSpectrum =
section::Type< 5 >::WattSpectrum;
using Parameter =
section::Type< 5 >::Parameter;

std::string chunk();
void verifyChunk( const WattSpectrum& );
std::string invalidChunk();

SCENARIO( "WattSpectrum" ) {

  GIVEN( "valid data for a WattSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      Parameter a{ {3}, {2},
                   { 1e-5, 1.5e+6, 3e+7 },
                   { 9.77e+5, 1e+6, 1.06e+6 } };
      Parameter b{ {5}, {2},
                   { 1e-5, 1.5e+6, 1e+7, 1.22e+7, 3e+7 },
                   { 2.546e-6, 2.546e-6, 2.474e-6, 2.612e-6, 2.62e-6 } };

      WattSpectrum chunk( std::move( a ), std::move( b ) );

      THEN( "a WattSpectrum can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      WattSpectrum chunk( begin, end, lineNumber, 9222, 5, 18 );

      THEN( "a WattSpectrum can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a WattSpectrum" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( WattSpectrum( begin, end, lineNumber, 9222, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n"
    "          3          2                                            9222 5 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n"
    "          5          2                                            9222 5 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n";
}

void verifyChunk( const WattSpectrum& chunk ) {

  REQUIRE( 11 == chunk.LF() );
  REQUIRE( 11 == chunk.LAW() );

  auto valueA = chunk.a();
  REQUIRE( 3 == valueA.NE() );
  REQUIRE( 1 == valueA.NR() );
  REQUIRE( 1 == valueA.interpolants().size() );
  REQUIRE( 1 == valueA.boundaries().size() );
  REQUIRE( 2 == valueA.interpolants()[0] );
  REQUIRE( 3 == valueA.boundaries()[0] );
  REQUIRE( 3 == valueA.energies().size() );
  REQUIRE( 3 == valueA.values().size() );
  REQUIRE( 1e-5 == Approx( valueA.energies()[0] ) );
  REQUIRE( 1.5e+6 == Approx( valueA.energies()[1] ) );
  REQUIRE( 3e+7 == Approx( valueA.energies()[2] ) );
  REQUIRE( 9.77e+5 == Approx( valueA.values()[0] ) );
  REQUIRE( 1e+6 == Approx( valueA.values()[1] ) );
  REQUIRE( 1.06e+6 == Approx( valueA.values()[2] ) );

  auto valueB = chunk.b();
  REQUIRE( 5 == valueB.NE() );
  REQUIRE( 1 == valueB.NR() );
  REQUIRE( 1 == valueB.interpolants().size() );
  REQUIRE( 1 == valueB.boundaries().size() );
  REQUIRE( 2 == valueB.interpolants()[0] );
  REQUIRE( 5 == valueB.boundaries()[0] );
  REQUIRE( 5 == valueB.energies().size() );
  REQUIRE( 5 == valueB.values().size() );
  REQUIRE( 1e-5 == Approx( valueB.energies()[0] ) );
  REQUIRE( 1.5e+6 == Approx( valueB.energies()[1] ) );
  REQUIRE( 1e+7 == Approx( valueB.energies()[2] ) );
  REQUIRE( 1.22e+7 == Approx( valueB.energies()[3] ) );
  REQUIRE( 3e+7 == Approx( valueB.energies()[4] ) );
  REQUIRE( 2.546e-6 == Approx( valueB.values()[0] ) );
  REQUIRE( 2.546e-6 == Approx( valueB.values()[1] ) );
  REQUIRE( 2.474e-6 == Approx( valueB.values()[2] ) );
  REQUIRE( 2.612e-6 == Approx( valueB.values()[3] ) );
  REQUIRE( 2.62e-6 == Approx( valueB.values()[4] ) );

  REQUIRE( 7 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          39222 5 18     \n"
    "          3          2                                            9222 5 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n"
    "          5          2                                            9222 5 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n";
}
