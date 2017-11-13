#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 1 == chunk.LTP() );
      REQUIRE( 15 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 7 == chunk.b().size() );
      REQUIRE( 1. == Approx( chunk.b()[0] ) );
      REQUIRE( 2. == Approx( chunk.b()[1] ) );
      REQUIRE( 3. == Approx( chunk.b()[2] ) );
      REQUIRE( 4. == Approx( chunk.b()[3] ) );
      REQUIRE( 5. == Approx( chunk.b()[4] ) );
      REQUIRE( 6. == Approx( chunk.b()[5] ) );
      REQUIRE( 7. == Approx( chunk.b()[6] ) );
      REQUIRE( 4 == chunk.real_a().size() );
      REQUIRE( 8. == Approx( chunk.real_a()[0] ) );
      REQUIRE( 10. == Approx( chunk.real_a()[1] ) );
      REQUIRE( 12. == Approx( chunk.real_a()[2] ) );
      REQUIRE( 14. == Approx( chunk.real_a()[3] ) );
      REQUIRE( 4 == chunk.imaginary_a().size() );
      REQUIRE( 9. == Approx( chunk.imaginary_a()[0] ) );
      REQUIRE( 11. == Approx( chunk.imaginary_a()[1] ) );
      REQUIRE( 13. == Approx( chunk.imaginary_a()[2] ) );
      REQUIRE( 15. == Approx( chunk.imaginary_a()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::CosineOutgoingEnergyDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          1          0         15          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}