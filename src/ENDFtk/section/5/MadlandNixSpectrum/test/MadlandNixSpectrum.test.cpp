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

    double efl = 1.029979e+6;
    double efh = 5.467297e+5;
    std::vector< long > boundaries = { 4 };
    std::vector< long > interpolants = { 5 };
    std::vector< double > energies = { 1e-5, 5.000001e+5, 1.4e+7, 3e+7 };
    std::vector< double > temperatures = { 1.092064e+6, 1.101483e+6,
                                           1.129269e+6, 1.182884e+6 };

    THEN( "an MadlandNixSpectrum can be constructed and members can be tested" ) {
      MadlandNixSpectrum chunk( efl, efh,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( temperatures ) );

      REQUIRE( 1.029979e+6 == Approx( chunk.EFL() ) );
      REQUIRE( 1.029979e+6 == Approx( chunk.lightKineticEnergy() ) );
      REQUIRE( 5.467297e+5 == Approx( chunk.EFH() ) );
      REQUIRE( 5.467297e+5 == Approx( chunk.heavyKineticEnergy() ) );

      REQUIRE( 4 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 5 == chunk.interpolants()[0] );
      REQUIRE( 4 == chunk.boundaries()[0] );
      REQUIRE( 4 == chunk.energies().size() );
      REQUIRE( 4 == chunk.maximumTemperatureValues().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 5.000001e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 1.4e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 3.0e+7 == Approx( chunk.energies()[3] ) );
      REQUIRE( 1.092064e+6 == Approx( chunk.maximumTemperatureValues()[0] ) );
      REQUIRE( 1.101483e+6 == Approx( chunk.maximumTemperatureValues()[1] ) );
      REQUIRE( 1.129269e+6 == Approx( chunk.maximumTemperatureValues()[2] ) );
      REQUIRE( 1.182884e+6 == Approx( chunk.maximumTemperatureValues()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid MadlandNixSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an MadlandNixSpectrum can be constructed and members can be tested" ) {
      MadlandNixSpectrum chunk( begin, end, lineNumber, 9543, 5, 18 );

      REQUIRE( 1.029979e+6 == Approx( chunk.EFL() ) );
      REQUIRE( 1.029979e+6 == Approx( chunk.lightKineticEnergy() ) );
      REQUIRE( 5.467297e+5 == Approx( chunk.EFH() ) );
      REQUIRE( 5.467297e+5 == Approx( chunk.heavyKineticEnergy() ) );

      REQUIRE( 4 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 5 == chunk.interpolants()[0] );
      REQUIRE( 4 == chunk.boundaries()[0] );
      REQUIRE( 4 == chunk.energies().size() );
      REQUIRE( 4 == chunk.maximumTemperatureValues().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 5.000001e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 1.4e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 3.0e+7 == Approx( chunk.energies()[3] ) );
      REQUIRE( 1.092064e+6 == Approx( chunk.maximumTemperatureValues()[0] ) );
      REQUIRE( 1.101483e+6 == Approx( chunk.maximumTemperatureValues()[1] ) );
      REQUIRE( 1.129269e+6 == Approx( chunk.maximumTemperatureValues()[2] ) );
      REQUIRE( 1.182884e+6 == Approx( chunk.maximumTemperatureValues()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of MadlandNixSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    MadlandNixSpectrum chunk(begin, end, lineNumber, 9543, 5, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9543, 5, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.029979+6 5.467297+5          0          0          1          49543 5 18     \n"
    "          4          5                                            9543 5 18     \n"
    " 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n"
    " 3.000000+7 1.182884+6                                            9543 5 18     \n";
}
