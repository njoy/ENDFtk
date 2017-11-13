#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::LaboratoryAngleEnergy" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::LaboratoryAngleEnergy" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 6 >::LaboratoryAngleEnergy can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::LaboratoryAngleEnergy
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.energies();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );

      REQUIRE( 2 == energies[0].NMU() );
      REQUIRE( 1 == energies[0].NRM() );
      REQUIRE( 1 == energies[0].interpolants().size() );
      REQUIRE( 1 == energies[0].boundaries().size() );
      REQUIRE( 4 == energies[0].interpolants()[0] );
      REQUIRE( 2 == energies[0].boundaries()[0] );

      auto cosines = energies[0].cosines();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( 1. == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energy().size() );
      REQUIRE( 4 == cosines[0].distribution().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energy()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energy()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energy()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energy()[3] ) );
      REQUIRE( 0. == Approx( cosines[0].distribution()[0] ) );
      REQUIRE( 2. == Approx( cosines[0].distribution()[1] ) );
      REQUIRE( 4. == Approx( cosines[0].distribution()[2] ) );
      REQUIRE( 6. == Approx( cosines[0].distribution()[3] ) );

      REQUIRE( -1. == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energy().size() );
      REQUIRE( 3 == cosines[1].distribution().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energy()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energy()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energy()[2] ) );
      REQUIRE( 6. == Approx( cosines[1].distribution()[0] ) );
      REQUIRE( 4. == Approx( cosines[1].distribution()[1] ) );
      REQUIRE( 2. == Approx( cosines[1].distribution()[2] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );

      REQUIRE( 2 == energies[1].NMU() );
      REQUIRE( 1 == energies[1].NRM() );
      REQUIRE( 1 == energies[1].interpolants().size() );
      REQUIRE( 1 == energies[1].boundaries().size() );
      REQUIRE( 4 == energies[1].interpolants()[0] );
      REQUIRE( 2 == energies[1].boundaries()[0] );

      cosines = energies[1].cosines();
      REQUIRE( 2 == cosines.size() );

      REQUIRE( .9 == Approx( cosines[0].cosine() ) );
      REQUIRE( 1 == cosines[0].NRP() );
      REQUIRE( 4 == cosines[0].NEP() );
      REQUIRE( 1 == cosines[0].interpolants().size() );
      REQUIRE( 1 == cosines[0].boundaries().size() );
      REQUIRE( 2 == cosines[0].interpolants()[0] );
      REQUIRE( 4 == cosines[0].boundaries()[0] );
      REQUIRE( 4 == cosines[0].energy().size() );
      REQUIRE( 4 == cosines[0].distribution().size() );
      REQUIRE( 1e-5 == Approx( cosines[0].energy()[0] ) );
      REQUIRE( 1.1e+7 == Approx( cosines[0].energy()[1] ) );
      REQUIRE( 1.147e+7 == Approx( cosines[0].energy()[2] ) );
      REQUIRE( 3e+7 == Approx( cosines[0].energy()[3] ) );
      REQUIRE( 1. == Approx( cosines[0].distribution()[0] ) );
      REQUIRE( 3. == Approx( cosines[0].distribution()[1] ) );
      REQUIRE( 5. == Approx( cosines[0].distribution()[2] ) );
      REQUIRE( 7. == Approx( cosines[0].distribution()[3] ) );

      REQUIRE( -.9 == Approx( cosines[1].cosine() ) );
      REQUIRE( 1 == cosines[1].NRP() );
      REQUIRE( 3 == cosines[1].NEP() );
      REQUIRE( 1 == cosines[1].interpolants().size() );
      REQUIRE( 1 == cosines[1].boundaries().size() );
      REQUIRE( 2 == cosines[1].interpolants()[0] );
      REQUIRE( 3 == cosines[1].boundaries()[0] );
      REQUIRE( 3 == cosines[1].energy().size() );
      REQUIRE( 3 == cosines[1].distribution().size() );
      REQUIRE( 1e-5 == Approx( cosines[1].energy()[0] ) );
      REQUIRE( 1e+6 == Approx( cosines[1].energy()[1] ) );
      REQUIRE( 3e+7 == Approx( cosines[1].energy()[2] ) );
      REQUIRE( 5. == Approx( cosines[1].distribution()[0] ) );
      REQUIRE( 3. == Approx( cosines[1].distribution()[1] ) );
      REQUIRE( 1. == Approx( cosines[1].distribution()[2] ) );

      REQUIRE( 20 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::LaboratoryAngleEnergy" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::LaboratoryAngleEnergy
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
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n"
    " 3.000000+7 6.000000+0                                            9228 6  5     \n"
    " 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          1          29228 6  5     \n"
    "          2          4                                            9228 6  5     \n"
    " 0.000000+0 9.000000-1          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 1.000000+0 1.100000+7 3.000000+0 1.147000+7 5.000000+09228 6  5     \n"
    " 3.000000+7 7.000000+0                                            9228 6  5     \n"
    " 0.000000+0-9.000000-1          0          0          1          39228 6  5     \n"
    "          3          2                                            9228 6  5     \n"
    " 1.000000-5 5.000000+0 1.000000+6 3.000000+0 3.000000+7 1.000000+09228 6  5     \n";
}