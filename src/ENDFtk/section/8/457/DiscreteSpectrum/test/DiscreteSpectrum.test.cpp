#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DiscreteSpectrum = section::Type< 8, 457 >::DiscreteSpectrum;

std::string chunk1();
std::string chunk2();
std::string chunk3();

SCENARIO( "DiscreteSpectrum" ) {

  GIVEN( "valid data for a DiscreteSpectrum" ) {

    std::tuple< double, double > discreteEnergy = { 4.863000e+4, 5.000000e+1 };
    double decayChain = 3.;
    double type = 0.;
    std::tuple< double, double > relativeIntensity = { 1.420112e-6, 2.85306e-10 };
    std::tuple< double, double > ris = { 1.0, 2.0 };
    std::tuple< double, double > ricc = { 7.010000e+5, 1.106180e-2 };
    std::tuple< double, double > rick = { 1.378999e-1, 2.000000e-3 };
    std::tuple< double, double > ricl = { 3.315735e+5, 5.608008e+3 };

    THEN( "a DiscreteSpectrum can be constructed and members can be "
          "tested for STYP not equal to 0 or 2" ) {
      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type );

      REQUIRE( 3. == chunk.decayChain() );
      REQUIRE( 4 == chunk.NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 0. == chunk.type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICL() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICL() ) ) );

      REQUIRE( 2 == chunk.NC() );
    }

    THEN( "a DiscreteSpectrum can be constructed and members can be "
          "tested for STYP equal to 2" ) {
      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type, ris );

      REQUIRE( 3. == chunk.decayChain() );
      REQUIRE( 6 == chunk.NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 0. == chunk.type() );
      REQUIRE( 1.0 == Approx( std::get< 0 >( chunk.RIS() ) ) );
      REQUIRE( 2.0 == Approx( std::get< 1 >( chunk.RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICL() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICL() ) ) );

      REQUIRE( 2 == chunk.NC() );
    }

    THEN( "a DiscreteSpectrum can be constructed and members can be "
          "tested for STYP equal to 0" ) {
      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type, ris, ricc, rick, ricl );

      REQUIRE( 3. == chunk.decayChain() );
      REQUIRE( 12 == chunk.NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 0. == chunk.type() );
      REQUIRE( 1.0 == Approx( std::get< 0 >( chunk.RIS() ) ) );
      REQUIRE( 2.0 == Approx( std::get< 1 >( chunk.RIS() ) ) );
      REQUIRE( 7.010000e+5 == Approx( std::get< 0 >( chunk.RICC() ) ) );
      REQUIRE( 1.106180e-2 == Approx( std::get< 1 >( chunk.RICC() ) ) );
      REQUIRE( 1.378999e-1 == Approx( std::get< 0 >( chunk.RICK() ) ) );
      REQUIRE( 2.000000e-3 == Approx( std::get< 1 >( chunk.RICK() ) ) );
      REQUIRE( 3.315735e+5 == Approx( std::get< 0 >( chunk.RICL() ) ) );
      REQUIRE( 5.608008e+3 == Approx( std::get< 1 >( chunk.RICL() ) ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid DiscreteSpectrum" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {
      DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 3. == chunk.decayChain() );
      REQUIRE( 4 == chunk.NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( chunk.discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( chunk.relativeIntensity() ) ) );
      REQUIRE( 0. == chunk.type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( chunk.RICL() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( chunk.RICL() ) ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP not equal to 0 or 2" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP equal to 2" ) {

    std::string string = chunk2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP equal to 0" ) {

    std::string string = chunk3();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk1() {
  return
    " 4.863000+4 5.000000+1          0          0          4          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10                      3580 8457     \n";
}

std::string chunk2() {
  return
    " 4.863000+4 5.000000+1          0          0          6          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n";
}

std::string chunk3() {
  return
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 1.378999-1 2.000000-3 3.315735+5 5.608008+33580 8457     \n";
}
