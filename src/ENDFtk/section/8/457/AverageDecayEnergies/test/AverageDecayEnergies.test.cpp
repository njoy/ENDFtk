#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using AverageDecayEnergies = section::Type< 8, 457 >::AverageDecayEnergies;

std::string chunk();
void verifyChunk( const AverageDecayEnergies& );
std::string chunkForStableNuclide();
void verifyChunkForStableNuclide( const AverageDecayEnergies& );
std::string wrongNC();

SCENARIO( "AverageDecayEnergies" ) {

  GIVEN( "valid data for an AverageDecayEnergies for an unstable nuclide" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > halfLife = {{ 4.449622e+9, 6.311520e+7 }};
      std::vector< std::array< double, 2 > > decayEnergies =
      { {{ 4.008322e+4, 4.128931e+3 }},
        {{ 5.373671e+3, 3.660206e+2 }},
        {{ 2.441003e+4, 6.191754e+2 }} };

      AverageDecayEnergies chunk( halfLife, std::move( decayEnergies ) );

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      AverageDecayEnergies chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an AverageDecayEnergies for a stable nuclide" ) {

    std::string string = chunkForStableNuclide();

    WHEN( "the data is given explicitly" ) {

      AverageDecayEnergies chunk;

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested for a stable nuclide" ) {

        verifyChunkForStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      AverageDecayEnergies chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "an AverageDecayEnergies can be constructed and members can be "
            "tested" ) {

        verifyChunkForStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an AverageDecayEnergies" ) {

    WHEN( "data with a wrong number of decay energies is used" ) {

      std::array< double, 2 > halfLife = {{ 4.449622e+9, 6.311520e+7 }};
      std::vector< std::array< double, 2 > > decayEnergies =
          { {{ 4.008322e+4, 4.128931e+3 }},
            {{ 5.373671e+3, 3.660206e+2 }},
            {{ 2.441003e+4, 6.191754e+2 }},
            {{ 1., 20. }} };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( AverageDecayEnergies( halfLife,
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

        CHECK_THROWS( AverageDecayEnergies( begin, end, lineNumber,
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

  CHECK( 4.449622e+9 == Approx( chunk.T()[0] ) );
  CHECK( 6.311520e+7 == Approx( chunk.T()[1] ) );
  CHECK( 4.449622e+9 == Approx( chunk.halfLife()[0] ) );
  CHECK( 6.311520e+7 == Approx( chunk.halfLife()[1] ) );

  CHECK( 3 == chunk.NCE() );
  CHECK( 3 == chunk.numberDecayEnergies() );
  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.decayEnergies().size() );
  CHECK( 4.008322e+4 == Approx( chunk.E()[0][0] ) );
  CHECK( 4.128931e+3 == Approx( chunk.E()[0][1] ) );
  CHECK( 5.373671e+3 == Approx( chunk.E()[1][0] ) );
  CHECK( 3.660206e+2 == Approx( chunk.E()[1][1] ) );
  CHECK( 2.441003e+4 == Approx( chunk.E()[2][0] ) );
  CHECK( 6.191754e+2 == Approx( chunk.E()[2][1] ) );
  CHECK( 4.008322e+4 == Approx( chunk.decayEnergies()[0][0] ) );
  CHECK( 4.128931e+3 == Approx( chunk.decayEnergies()[0][1] ) );
  CHECK( 5.373671e+3 == Approx( chunk.decayEnergies()[1][0] ) );
  CHECK( 3.660206e+2 == Approx( chunk.decayEnergies()[1][1] ) );
  CHECK( 2.441003e+4 == Approx( chunk.decayEnergies()[2][0] ) );
  CHECK( 6.191754e+2 == Approx( chunk.decayEnergies()[2][1] ) );

  CHECK( 4.008322e+4 == Approx( chunk.ELP()[0] ) );
  CHECK( 4.128931e+3 == Approx( chunk.ELP()[1] ) );
  CHECK( 4.008322e+4 == Approx( chunk.lightParticleDecayEnergy()[0] ) );
  CHECK( 4.128931e+3 == Approx( chunk.lightParticleDecayEnergy()[1] ) );
  CHECK( 5.373671e+3 == Approx( chunk.EEM()[0] ) );
  CHECK( 3.660206e+2 == Approx( chunk.EEM()[1] ) );
  CHECK( 5.373671e+3 == Approx( chunk.electromagneticDecayEnergy()[0] ) );
  CHECK( 3.660206e+2 == Approx( chunk.electromagneticDecayEnergy()[1] ) );
  CHECK( 2.441003e+4 == Approx( chunk.EHP()[0] ) );
  CHECK( 6.191754e+2 == Approx( chunk.EHP()[1] ) );
  CHECK( 2.441003e+4 == Approx( chunk.heavyParticleDecayEnergy()[0] ) );
  CHECK( 6.191754e+2 == Approx( chunk.heavyParticleDecayEnergy()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkForStableNuclide() {
  return
    " 0.000000+0 0.000000+0          0          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n";
}

void verifyChunkForStableNuclide( const AverageDecayEnergies& chunk ) {

  CHECK( 0.0 == Approx( chunk.T()[0] ) );
  CHECK( 0.0 == Approx( chunk.T()[1] ) );
  CHECK( 0.0 == Approx( chunk.halfLife()[0] ) );
  CHECK( 0.0 == Approx( chunk.halfLife()[1] ) );

  CHECK( 3 == chunk.NCE() );
  CHECK( 3 == chunk.numberDecayEnergies() );
  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.decayEnergies().size() );

  CHECK( 0.0 == Approx( chunk.E()[0][0] ) );
  CHECK( 0.0 == Approx( chunk.E()[0][1] ) );
  CHECK( 0.0 == Approx( chunk.E()[1][0] ) );
  CHECK( 0.0 == Approx( chunk.E()[1][1] ) );
  CHECK( 0.0 == Approx( chunk.E()[2][0] ) );
  CHECK( 0.0 == Approx( chunk.E()[2][1] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[0][0] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[0][1] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[1][0] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[1][1] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[2][0] ) );
  CHECK( 0.0 == Approx( chunk.decayEnergies()[2][1] ) );

  CHECK( 0.0 == Approx( chunk.ELP()[0] ) );
  CHECK( 0.0 == Approx( chunk.ELP()[1] ) );
  CHECK( 0.0 == Approx( chunk.lightParticleDecayEnergy()[0] ) );
  CHECK( 0.0 == Approx( chunk.lightParticleDecayEnergy()[1] ) );
  CHECK( 0.0 == Approx( chunk.EEM()[0] ) );
  CHECK( 0.0 == Approx( chunk.EEM()[1] ) );
  CHECK( 0.0 == Approx( chunk.electromagneticDecayEnergy()[0] ) );
  CHECK( 0.0 == Approx( chunk.electromagneticDecayEnergy()[1] ) );
  CHECK( 0.0 == Approx( chunk.EHP()[0] ) );
  CHECK( 0.0 == Approx( chunk.EHP()[1] ) );
  CHECK( 0.0 == Approx( chunk.heavyParticleDecayEnergy()[0] ) );
  CHECK( 0.0 == Approx( chunk.heavyParticleDecayEnergy()[1] ) );

  CHECK( 2 == chunk.NC() );
}
std::string wrongNC() {
  return
    " 4.449622+9 6.311520+7          0          0          8          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n"
    " 1.000000+0 2.000000+1                                            3580 8457     \n";
}
