#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscreteTwoBodyScattering =
section::Type< 26 >::DiscreteTwoBodyScattering;
using TabulatedDistribution =
section::Type< 26 >::DiscreteTwoBodyScattering::TabulatedDistribution;

std::string chunk();
void verifyChunk( const DiscreteTwoBodyScattering& );
std::string invalidLANG();

SCENARIO( "DiscreteTwoBodyScattering" ) {

  GIVEN( "valid data for a DiscreteTwoBodyScattering" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< TabulatedDistribution > sequence = {
        TabulatedDistribution( 1e-5, 12, { 1., 3. }, { 2., 4. } ),
        TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

      DiscreteTwoBodyScattering
        chunk( std::move( boundaries ), std::move( interpolants ),
               std::move( sequence ) );

      THEN( "a DiscreteTwoBodyScattering can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 26, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DiscreteTwoBodyScattering chunk( begin, end, lineNumber, 9228, 26, 5 );

      THEN( "a DiscreteTwoBodyScattering can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 26, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DiscreteTwoBodyScattering" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< TabulatedDistribution > sequence = {
          TabulatedDistribution( 1e-5, 12, { 1., 3. }, { 2., 4. } ),
          TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

        CHECK_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongBoundaries ),
                                       std::move( interpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< TabulatedDistribution > sequence = {
          TabulatedDistribution( 1e-5, 12, { 1., 3. }, { 2., 4. } ),
          TabulatedDistribution( 2e+7, 12, { 1., 3., 5. }, { 2., 4., 6. } ) };

        CHECK_THROWS(
            DiscreteTwoBodyScattering( std::move( wrongInterpolants ),
                                       std::move( wrongInterpolants ),
                                       std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< TabulatedDistribution > wrongSequence = {
          TabulatedDistribution( 1e-5, 12, { 1., 3. }, { 2., 4. } ) };

        CHECK_THROWS(
            DiscreteTwoBodyScattering( std::move( boundaries ),
                                       std::move( interpolants ),
                                       std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LANG" ) {

      std::string string = invalidLANG();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( DiscreteTwoBodyScattering( begin, end, lineNumber,
                                                 9228, 26, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          2922826  5     \n"
    "          2          1                                            922826  5     \n"
    " 0.000000+0 1.000000-5         12          0          4          2922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922826  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          3922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n";
}

void verifyChunk( const DiscreteTwoBodyScattering& chunk ) {

      CHECK( 2 == chunk.LAW() );
      CHECK( 2 == chunk.NE() );
      CHECK( 1 == chunk.NR() );
      CHECK( 1 == chunk.interpolants().size() );
      CHECK( 1 == chunk.boundaries().size() );
      CHECK( 1 == chunk.interpolants()[0] );
      CHECK( 2 == chunk.boundaries()[0] );

      CHECK( 2 == chunk.E().size() );
      CHECK( 2 == chunk.incidentEnergies().size() );
      CHECK( 1e-5 == Approx( chunk.E()[0] ) );
      CHECK( 2e+7 == Approx( chunk.E()[1] ) );
      CHECK( 1e-5 == Approx( chunk.incidentEnergies()[0] ) );
      CHECK( 2e+7 == Approx( chunk.incidentEnergies()[1] ) );

      auto energies = chunk.distributions();

      CHECK( 1e-5 == Approx( energies[0].E() ) );
      CHECK( 1e-5 == Approx( energies[0].incidentEnergy() ) );
      CHECK( 12 == energies[0].LANG() );
      CHECK( 4 == energies[0].NW() );
      CHECK( 2 == energies[0].NL() );
      CHECK( 2 == energies[0].MU().size() );
      CHECK( 2 == energies[0].cosines().size() );
      CHECK( 1. == Approx( energies[0].MU()[0] ) );
      CHECK( 3. == Approx( energies[0].MU()[1] ) );
      CHECK( 1. == Approx( energies[0].cosines()[0] ) );
      CHECK( 3. == Approx( energies[0].cosines()[1] ) );
      CHECK( 2 == energies[0].F().size() );
      CHECK( 2 == energies[0].probabilities().size() );
      CHECK( 2. == Approx( energies[0].F()[0] ) );
      CHECK( 4. == Approx( energies[0].F()[1] ) );
      CHECK( 2. == Approx( energies[0].probabilities()[0] ) );
      CHECK( 4. == Approx( energies[0].probabilities()[1] ) );

      CHECK( 2e+7 == Approx( energies[1].E() ) );
      CHECK( 2e+7 == Approx( energies[1].incidentEnergy() ) );
      CHECK( 12 == energies[1].LANG() );
      CHECK( 6 == energies[1].NW() );
      CHECK( 3 == energies[1].NL() );
      CHECK( 3 == energies[1].MU().size() );
      CHECK( 3 == energies[1].cosines().size() );
      CHECK( 1. == Approx( energies[1].MU()[0] ) );
      CHECK( 3. == Approx( energies[1].MU()[1] ) );
      CHECK( 5. == Approx( energies[1].MU()[2] ) );
      CHECK( 1. == Approx( energies[1].cosines()[0] ) );
      CHECK( 3. == Approx( energies[1].cosines()[1] ) );
      CHECK( 5. == Approx( energies[1].cosines()[2] ) );
      CHECK( 3 == energies[1].F().size() );
      CHECK( 3 == energies[1].probabilities().size() );
      CHECK( 2. == Approx( energies[1].F()[0] ) );
      CHECK( 4. == Approx( energies[1].F()[1] ) );
      CHECK( 6. == Approx( energies[1].F()[2] ) );
      CHECK( 2. == Approx( energies[1].probabilities()[0] ) );
      CHECK( 4. == Approx( energies[1].probabilities()[1] ) );
      CHECK( 6. == Approx( energies[1].probabilities()[2] ) );

      CHECK( 6 == chunk.NC() );
}

std::string invalidLANG() {
  return
    " 0.000000+0 0.000000+0          0          0          1          2922826  5     \n"
    "          2          1                                            922826  5     \n"
    " 0.000000+0 1.000000-5          1          0          4          2922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922826  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          3922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n";
}
