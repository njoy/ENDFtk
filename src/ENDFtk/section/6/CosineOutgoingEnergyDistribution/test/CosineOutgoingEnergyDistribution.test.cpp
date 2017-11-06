#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::CosineOutgoingEnergyDistribution" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::CosineOutgoingEnergyDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 6 >::CosineOutgoingEnergyDistribution can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::CosineOutgoingEnergyDistribution
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1. == Approx( chunk.cosine() ) );

      REQUIRE( 1 == chunk.NRP() );
      REQUIRE( 4 == chunk.NEP() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 4 == chunk.boundaries()[0] );
      REQUIRE( 4 == chunk.energy().size() );
      REQUIRE( 4 == chunk.distribution().size() );
      REQUIRE( 1e-5 == Approx( chunk.energy()[0] ) );
      REQUIRE( 1.1e+7 == Approx( chunk.energy()[1] ) );
      REQUIRE( 1.147e+7 == Approx( chunk.energy()[2] ) );
      REQUIRE( 3e+7 == Approx( chunk.energy()[3] ) );
      REQUIRE( 0. == Approx( chunk.distribution()[0] ) );
      REQUIRE( 8.45368e-11 == Approx( chunk.distribution()[1] ) );
      REQUIRE( 6.622950e-8 == Approx( chunk.distribution()[2] ) );
      REQUIRE( 2.149790e-1 == Approx( chunk.distribution()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::CosineOutgoingEnergyDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::CosineOutgoingEnergyDistribution
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
    " 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 3.000000+7 2.149790-1                                            9228 6  5     \n";
}
