#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using EffectiveTemperature = 
section::Type< 5 >::EffectiveTemperature;

std::string chunk();

SCENARIO( "EffectiveTemperature" ) {

  GIVEN( "valid data for a EffectiveTemperature" ) {

    std::vector< long > boundaries = { 5 };
    std::vector< long > interpolants = { 1 };
    std::vector< double > energies = { 0.0, 1e+4, 2e+4, 1.83e+6, 1.84e+6 };
    std::vector< double > thetas = { 2.265227e-7, 2.029471e-6, 2.272542e-6, 0.0, 0.0 };

    THEN( "an EffectiveTemperature can be constructed and members can be tested" ) {
      EffectiveTemperature chunk( std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( energies ),
                                  std::move( thetas ) );

      REQUIRE( 5 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 5 == chunk.boundaries()[0] );
      REQUIRE( 5 == chunk.energies().size() );
      REQUIRE( 5 == chunk.thetas().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+4 == Approx( chunk.energies()[1] ) );
      REQUIRE( 2e+4 == Approx( chunk.energies()[2] ) );
      REQUIRE( 1.83e+6 == Approx( chunk.energies()[3] ) );
      REQUIRE( 1.84e+6 == Approx( chunk.energies()[4] ) );
      REQUIRE( 2.265227e-7 == Approx( chunk.thetas()[0] ) );
      REQUIRE( 2.029471e-6 == Approx( chunk.thetas()[1] ) );
      REQUIRE( 2.272542e-6 == Approx( chunk.thetas()[2] ) );
      REQUIRE( 0. == Approx( chunk.thetas()[3] ) );
      REQUIRE( 0. == Approx( chunk.thetas()[4] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid EffectiveTemperature" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an EffectiveTemperature can be constructed and members can be tested" ) {
      EffectiveTemperature chunk( begin, end, lineNumber, 9437, 5, 455 );

      REQUIRE( 5 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 5 == chunk.boundaries()[0] );
      REQUIRE( 5 == chunk.energies().size() );
      REQUIRE( 5 == chunk.thetas().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+4 == Approx( chunk.energies()[1] ) );
      REQUIRE( 2e+4 == Approx( chunk.energies()[2] ) );
      REQUIRE( 1.83e+6 == Approx( chunk.energies()[3] ) );
      REQUIRE( 1.84e+6 == Approx( chunk.energies()[4] ) );
      REQUIRE( 2.265227e-7 == Approx( chunk.thetas()[0] ) );
      REQUIRE( 2.029471e-6 == Approx( chunk.thetas()[1] ) );
      REQUIRE( 2.272542e-6 == Approx( chunk.thetas()[2] ) );
      REQUIRE( 0. == Approx( chunk.thetas()[3] ) );
      REQUIRE( 0. == Approx( chunk.thetas()[4] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of EffectiveTemperature" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    EffectiveTemperature chunk(begin, end, lineNumber, 9437, 5, 455 );

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
    " 0.000000+0 2.265227-7 1.000000+4 2.029471-6 2.000000+4 2.272542-69437 5455     \n"
    " 1.830000+6 0.000000+0 1.840000+6 0.000000+0                      9437 5455     \n";
}
