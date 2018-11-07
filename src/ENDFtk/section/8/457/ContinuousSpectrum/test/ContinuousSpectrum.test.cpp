#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ContinuousSpectrum = section::Type< 8, 457 >::ContinuousSpectrum;

std::string chunk();

SCENARIO( "ContinuousSpectrum" ) {

  GIVEN( "valid data for a ContinuousSpectrum" ) {

    double decayChain = 4.;
    std::vector< long > boundaries = { 3 };
    std::vector< long > interpolants = { 1 };
    std::vector< double > energies = { 0.0, 5e+5, 7.3e+6 };
    std::vector< double > spectralValues = { 6.133200e-7, 6.133300e-7,
                                             6.02040e-17 };

    THEN( "a ContinuousSpectrum can be constructed and members can be "
          "tested" ) {
      ContinuousSpectrum chunk( decayChain,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( spectralValues ) );

      REQUIRE( 4. == chunk.decayChain() );
      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.spectralValues().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( chunk.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( chunk.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( chunk.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( chunk.spectralValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid ContinuousSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a ContinuousSpectrum can be constructed and members can be tested" ) {
      ContinuousSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 4. == chunk.decayChain() );
      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.spectralValues().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( chunk.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( chunk.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( chunk.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( chunk.spectralValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of ContinuousSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    ContinuousSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}
