#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using MadlandNixSpectrum = 
section::Type< 5 >::MadlandNixSpectrum;

std::string chunk();
void verifyChunk( const MadlandNixSpectrum& );
std::string invalidChunk();

SCENARIO( "MadlandNixSpectrum" ) {

  GIVEN( "valid data for a MadlandNixSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double efl = 1.029979e+6;
      double efh = 5.467297e+5;
      std::vector< long > boundaries = { 4 };
      std::vector< long > interpolants = { 5 };
      std::vector< double > energies = { 1e-5, 5.000001e+5, 1.4e+7, 3e+7 };
      std::vector< double > temperatures = { 1.092064e+6, 1.101483e+6,
                                             1.129269e+6, 1.182884e+6 };

      MadlandNixSpectrum chunk( efl, efh,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( temperatures ) );

      THEN( "an MadlandNixSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      MadlandNixSpectrum chunk( begin, end, lineNumber, 9543, 5, 18 );

      THEN( "a MadlandNixSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a MadlandNixSpectrum" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double efl = 1.029979e+6;
      double efh = 5.467297e+5;
      std::vector< long > boundaries = { 4 };
      std::vector< long > wrongInterpolants = { 5, 2 };
      std::vector< double > energies = { 1e-5, 5.000001e+5, 1.4e+7, 3e+7 };
      std::vector< double > temperatures = { 1.092064e+6, 1.101483e+6,
                                             1.129269e+6, 1.182884e+6 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( MadlandNixSpectrum( 
                                efl, efh,
                                std::move( boundaries ),
                                std::move( wrongInterpolants ),
                                std::move( energies ),
                                std::move( temperatures ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( MadlandNixSpectrum( begin, end, lineNumber,
                                            9543, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.029979+6 5.467297+5          0          0          1          49543 5 18     \n"
    "          4          5                                            9543 5 18     \n"
    " 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n"
    " 3.000000+7 1.182884+6                                            9543 5 18     \n";
}

void verifyChunk( const MadlandNixSpectrum& chunk ) {

  REQUIRE( 12 == chunk.LF() );
  REQUIRE( 12 == chunk.LAW() );

  REQUIRE( 1.029979e+6 == Approx( chunk.EFL() ) );
  REQUIRE( 1.029979e+6 == Approx( chunk.lightFragmentEnergy() ) );
  REQUIRE( 5.467297e+5 == Approx( chunk.EFH() ) );
  REQUIRE( 5.467297e+5 == Approx( chunk.heavyFragmentEnergy() ) );

  REQUIRE( 4 == chunk.NE() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 5 == chunk.interpolants()[0] );
  REQUIRE( 4 == chunk.boundaries()[0] );
  REQUIRE( 4 == chunk.E().size() );
  REQUIRE( 4 == chunk.energies().size() );
  REQUIRE( 4 == chunk.TM().size() );
  REQUIRE( 4 == chunk.maximumTemperatureValues().size() );
  REQUIRE( 1e-5 == Approx( chunk.E()[0] ) );
  REQUIRE( 5.000001e+5 == Approx( chunk.E()[1] ) );
  REQUIRE( 1.4e+7 == Approx( chunk.E()[2] ) );
  REQUIRE( 3.0e+7 == Approx( chunk.E()[3] ) );
  REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
  REQUIRE( 5.000001e+5 == Approx( chunk.energies()[1] ) );
  REQUIRE( 1.4e+7 == Approx( chunk.energies()[2] ) );
  REQUIRE( 3.0e+7 == Approx( chunk.energies()[3] ) );
  REQUIRE( 1.092064e+6 == Approx( chunk.TM()[0] ) );
  REQUIRE( 1.101483e+6 == Approx( chunk.TM()[1] ) );
  REQUIRE( 1.129269e+6 == Approx( chunk.TM()[2] ) );
  REQUIRE( 1.182884e+6 == Approx( chunk.TM()[3] ) );
  REQUIRE( 1.092064e+6 == Approx( chunk.maximumTemperatureValues()[0] ) );
  REQUIRE( 1.101483e+6 == Approx( chunk.maximumTemperatureValues()[1] ) );
  REQUIRE( 1.129269e+6 == Approx( chunk.maximumTemperatureValues()[2] ) );
  REQUIRE( 1.182884e+6 == Approx( chunk.maximumTemperatureValues()[3] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 1.029979+6 5.467297+5          0          0          2          49543 5 18     \n"
    "          4          5                                            9543 5 18     \n"
    " 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n"
    " 3.000000+7 1.182884+6                                            9543 5 18     \n";
}
