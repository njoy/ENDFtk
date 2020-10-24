#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/nubar.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string oddNPL();
std::string inconsistentNPL();

SCENARIO( "nubar::EnergyDependent" ) {

  GIVEN( "a string representation of a valid nubar::EnergyDependent" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a nubar::EnergyDependent can be constructed and members can be tested" ) {
      nubar::EnergyDependent chunk( begin, end, lineNumber, 9228, 1, 455 );

      auto interpolants = chunk.interpolants();
      auto boundaries = chunk.boundaries();
      auto constants = chunk.constants();

      REQUIRE( 8 == chunk.NC() );
      REQUIRE( 1 == chunk.LDG() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 6 == chunk.NNF() );
      REQUIRE( 1 == interpolants.size() );
      REQUIRE( 1 == boundaries.size() );
      REQUIRE( 4 == interpolants[0] );
      REQUIRE( 2 == boundaries[0] );
      REQUIRE( 2 == constants.size() );
      REQUIRE( 1e-5 == Approx( constants[0].energy() ) );
      REQUIRE( 2e+7 == Approx( constants[1].energy() ) );
      auto lambdas = constants[0].lambdas();
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 1. == Approx( lambdas[0] ) );
      REQUIRE( 2. == Approx( lambdas[1] ) );
      REQUIRE( 3. == Approx( lambdas[2] ) );
      REQUIRE( 4. == Approx( lambdas[3] ) );
      REQUIRE( 5. == Approx( lambdas[4] ) );
      REQUIRE( 6. == Approx( lambdas[5] ) );
      lambdas = constants[1].lambdas();
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 6. == Approx( lambdas[0] ) );
      REQUIRE( 5. == Approx( lambdas[1] ) );
      REQUIRE( 4. == Approx( lambdas[2] ) );
      REQUIRE( 3. == Approx( lambdas[3] ) );
      REQUIRE( 2. == Approx( lambdas[4] ) );
      REQUIRE( 1. == Approx( lambdas[5] ) );
      auto alphas = constants[0].alphas();
      REQUIRE( 6 == alphas.size() );
      REQUIRE( 1.1 == Approx( alphas[0] ) );
      REQUIRE( 2.1 == Approx( alphas[1] ) );
      REQUIRE( 3.1 == Approx( alphas[2] ) );
      REQUIRE( 4.1 == Approx( alphas[3] ) );
      REQUIRE( 5.1 == Approx( alphas[4] ) );
      REQUIRE( 6.1 == Approx( alphas[5] ) );
      alphas = constants[1].alphas();
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 6.1 == Approx( alphas[0] ) );
      REQUIRE( 5.1 == Approx( alphas[1] ) );
      REQUIRE( 4.1 == Approx( alphas[2] ) );
      REQUIRE( 3.1 == Approx( alphas[3] ) );
      REQUIRE( 2.1 == Approx( alphas[4] ) );
      REQUIRE( 1.1 == Approx( alphas[5] ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of nubar::EnergyDependent" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    nubar::EnergyDependent chunk( begin, end, lineNumber, 9228, 1, 455 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 455 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a nubar::EnergyDependent"
         " with an inconsistent NPL" ){
    std::string string = inconsistentNPL();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( nubar::EnergyDependent( begin, end, lineNumber, 9228, 1, 455 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a nubar::EnergyDependent"
         " with an odd NPL" ){
    std::string string = oddNPL();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( nubar::EnergyDependent( begin, end, lineNumber, 9228, 1, 455 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         12          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n";
}

std::string oddNPL() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         11          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0           9228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         11          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0           9228 1455     \n";
}

std::string inconsistentNPL() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         10          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0                      9228 1455     \n";
}