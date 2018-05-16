#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 2 == chunk.NMU() );
      REQUIRE( 1 == chunk.NRM() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 4 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto cosines = chunk.cosines();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( 1. == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energies().size() );
      REQUIRE( 4 == cosines[0].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energies()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energies()[3] ) );
      REQUIRE( 0. == Approx( cosines[0].probabilities()[0] ) );
      REQUIRE( 2. == Approx( cosines[0].probabilities()[1] ) );
      REQUIRE( 4. == Approx( cosines[0].probabilities()[2] ) );
      REQUIRE( 6. == Approx( cosines[0].probabilities()[3] ) );

      REQUIRE( -1. == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 5 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energies().size() );
      REQUIRE( 3 == cosines[1].probabilities().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energies()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energies()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energies()[2] ) );
      REQUIRE( 6. == Approx( cosines[1].probabilities()[0] ) );
      REQUIRE( 4. == Approx( cosines[1].probabilities()[1] ) );
      REQUIRE( 2. == Approx( cosines[1].probabilities()[2] ) );

      REQUIRE( 9 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution
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
    " 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n"
    " 3.000000+7 6.000000+0                                            9228 6  5     \n"
    " 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n"
    "          3          5                                            9228 6  5     \n"
    " 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n";
}
