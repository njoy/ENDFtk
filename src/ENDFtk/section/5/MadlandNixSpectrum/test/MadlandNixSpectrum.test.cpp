#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using MadlandNixSpectrum = 
section::Type< 5 >::MadlandNixSpectrum;

std::string chunk();

SCENARIO( "MadlandNixSpectrum" ) {

  GIVEN( "valid data for a MadlandNixSpectrum" ) {

    double efl = 1.;
    double efh = 2.;
    std::vector< long > boundaries = { 3 };
    std::vector< long > interpolants = { 1 };
    std::vector< double > energies = { 0.0, 1e+4, 2e+7 };
    std::vector< double > temperatures = { 4., 5., 6. };

    THEN( "an MadlandNixSpectrum can be constructed and members can be tested" ) {
      MadlandNixSpectrum chunk( efl, efh,
                                  std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( energies ),
                                  std::move( temperatures ) );

      REQUIRE( 1.0 == Approx( chunk.EFL() ) );
      REQUIRE( 1.0 == Approx( chunk.lightKineticEnergy() ) );
      REQUIRE( 2.0 == Approx( chunk.EFH() ) );
      REQUIRE( 2.0 == Approx( chunk.heavyKineticEnergy() ) );

      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.maximumTemperatureValues().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+4 == Approx( chunk.energies()[1] ) );
      REQUIRE( 2e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 4. == Approx( chunk.maximumTemperatureValues()[0] ) );
      REQUIRE( 5. == Approx( chunk.maximumTemperatureValues()[1] ) );
      REQUIRE( 6. == Approx( chunk.maximumTemperatureValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid MadlandNixSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an MadlandNixSpectrum can be constructed and members can be tested" ) {
      MadlandNixSpectrum chunk( begin, end, lineNumber, 9437, 5, 455 );

      REQUIRE( 1.0 == Approx( chunk.EFL() ) );
      REQUIRE( 1.0 == Approx( chunk.lightKineticEnergy() ) );
      REQUIRE( 2.0 == Approx( chunk.EFH() ) );
      REQUIRE( 2.0 == Approx( chunk.heavyKineticEnergy() ) );

      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.maximumTemperatureValues().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+4 == Approx( chunk.energies()[1] ) );
      REQUIRE( 2e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 4. == Approx( chunk.maximumTemperatureValues()[0] ) );
      REQUIRE( 5. == Approx( chunk.maximumTemperatureValues()[1] ) );
      REQUIRE( 6. == Approx( chunk.maximumTemperatureValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of MadlandNixSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    MadlandNixSpectrum chunk(begin, end, lineNumber, 9437, 5, 455 );

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
    " 1.000000+0 2.000000+0          0          0          1          39437 5455     \n"
    "          3          1                                            9437 5455     \n"
    " 0.000000+0 4.000000+0 1.000000+4 5.000000+0 2.000000+7 6.000000+09437 5455     \n";
}
