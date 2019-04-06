#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using AverageDecayEnergies = section::Type< 8, 457 >::AverageDecayEnergies;

std::string chunk();
void verifyChunk( const AverageDecayEnergies& );
std::string chunkForStableNuclide();
void verifyChunkForStableNuclide( const AverageDecayEnergies& );
std::string wrongNC();

SCENARIO( "AverageDecayEnergies" ) {

  GIVEN( "valid data for an AverageDecayEnergies for an unstable nuclide" ) {

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > halfLife = {{ 4.449622e+9, 6.311520e+7 }};
      std::vector< std::array< double, 2 > > decayEnergies =
      { {{ 4.008322e+4, 4.128931e+3 }},
        {{ 5.373671e+3, 3.660206e+2 }},
        {{ 2.441003e+4, 6.191754e+2 }} };

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        AverageDecayEnergies chunk( halfLife, std::move( decayEnergies ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        AverageDecayEnergies chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an AverageDecayEnergies for a stable nuclide" ) {

    WHEN( "the data is given explicitly" ) {

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested for a stable nuclide" ) {

        AverageDecayEnergies chunk;
        verifyChunkForStableNuclide( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkForStableNuclide();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        AverageDecayEnergies chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkForStableNuclide( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of AverageDecayEnergies" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    AverageDecayEnergies chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of AverageDecayEnergies for a stable nuclide" ) {

    std::string string = chunkForStableNuclide();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    AverageDecayEnergies chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for an AverageDecayEnergies" ) {

    WHEN( "data with a wrong number of decay energies is used" ) {

      std::array< double, 2 > halfLife = { 4.449622e+9, 6.311520e+7 };
      std::vector< std::array< double, 2 > > decayEnergies =
      { {{ 4.008322e+4, 4.128931e+3 }},
        {{ 5.373671e+3, 3.660206e+2 }},
        {{ 2.441003e+4, 6.191754e+2 }},
        {{ 1., 20. }} };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( AverageDecayEnergies( halfLife,
                                              std::move( decayEnergies ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with a wrong number of decay energies "
          "is used" ) {

      std::string string = wrongNC();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( AverageDecayEnergies( begin, end, lineNumber,
                                              3580, 8, 457 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 4.449622+9 6.311520+7          0          0          6          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n";
}

void verifyChunk( const AverageDecayEnergies& chunk ) {

  auto halfLife = chunk.halfLife();
  REQUIRE( 4.449622e+9 == Approx( halfLife[0] ) );
  REQUIRE( 6.311520e+7 == Approx( halfLife[1] ) );

  REQUIRE( 3 == chunk.numberDecayEnergies() );
  REQUIRE( 3 == chunk.decayEnergies().size() );
  auto lightParticle = chunk.decayEnergies()[0];
  REQUIRE( 4.008322e+4 == Approx( lightParticle[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle[1] ) );
  auto electroMagnetic = chunk.decayEnergies()[1];
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic[1] ) );
  auto heavyParticle = chunk.decayEnergies()[2];
  REQUIRE( 2.441003e+4 == Approx( heavyParticle[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle[1] ) );

  auto lightParticle2 = chunk.lightParticleDecayEnergy();
  REQUIRE( 4.008322e+4 == Approx( lightParticle2[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle2[1] ) );
  auto electroMagnetic2 = chunk.electromagneticDecayEnergy();
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic2[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic2[1] ) );
  auto heavyParticle2 = chunk.heavyParticleDecayEnergy();
  REQUIRE( 2.441003e+4 == Approx( heavyParticle2[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle2[1] ) );

  REQUIRE( 2 == chunk.NC() );
}

std::string chunkForStableNuclide() {
  return
    " 0.000000+0 0.000000+0          0          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n";
}

void verifyChunkForStableNuclide( const AverageDecayEnergies& chunk ) {

  auto halfLife = chunk.halfLife();
  REQUIRE( 0.0 == Approx( halfLife[0] ) );
  REQUIRE( 0.0 == Approx( halfLife[1] ) );

  REQUIRE( 3 == chunk.numberDecayEnergies() );
  REQUIRE( 3 == chunk.decayEnergies().size() );
  auto lightParticle = chunk.decayEnergies()[0];
  REQUIRE( 0.0 == Approx( lightParticle[0] ) );
  REQUIRE( 0.0 == Approx( lightParticle[1] ) );
  auto electroMagnetic = chunk.decayEnergies()[1];
  REQUIRE( 0.0 == Approx( electroMagnetic[0] ) );
  REQUIRE( 0.0 == Approx( electroMagnetic[1] ) );
  auto heavyParticle = chunk.decayEnergies()[2];
  REQUIRE( 0.0 == Approx( heavyParticle[0] ) );
  REQUIRE( 0.0 == Approx( heavyParticle[1] ) );

  auto lightParticle2 = chunk.lightParticleDecayEnergy();
  REQUIRE( 0.0 == Approx( lightParticle2[0] ) );
  REQUIRE( 0.0 == Approx( lightParticle2[1] ) );
  auto electroMagnetic2 = chunk.electromagneticDecayEnergy();
  REQUIRE( 0.0 == Approx( electroMagnetic2[0] ) );
  REQUIRE( 0.0 == Approx( electroMagnetic2[1] ) );
  auto heavyParticle2 = chunk.heavyParticleDecayEnergy();
  REQUIRE( 0.0 == Approx( heavyParticle2[0] ) );
  REQUIRE( 0.0 == Approx( heavyParticle2[1] ) );

  REQUIRE( 2 == chunk.NC() );
}
std::string wrongNC() {
  return
    " 4.449622+9 6.311520+7          0          0          8          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n"
    " 1.000000+0 2.000000+1                                            3580 8457     \n";
}
