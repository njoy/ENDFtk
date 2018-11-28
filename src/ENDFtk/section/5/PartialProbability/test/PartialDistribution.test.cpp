#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using PartialProbability = 
section::Type< 5 >::PartialProbability;

std::string chunk();

SCENARIO( "PartialProbability" ) {

  GIVEN( "valid data for a PartialProbability" ) {

    double u = 1.0;
    long lf = 1;
    std::vector< long > boundaries = { 2 };
    std::vector< long > interpolants = { 2 };
    std::vector< double > energies = { 1e-5, 3e+7 };
    std::vector< double > probabilities = { 1., 1. };
    std::vector< long > boundaries2 = { 2 };
    std::vector< long > interpolants2 = { 2 };
    std::vector< double > energies2 = { 1e-5, 3e+7 };
    std::vector< double > probabilities2 = { 1., 1. };

    THEN( "a PartialProbability can be constructed and members can be tested "
          "when not specifying the value of U (default 0.0)" ) {
      PartialProbability chunk( lf,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( probabilities ) );

      REQUIRE( 0.0 == Approx ( chunk.U() ) );
      REQUIRE( 0.0 == Approx ( chunk.energyLimitConstant() ) );
      REQUIRE( 1 == chunk.LF() );
      REQUIRE( 1 == chunk.distributionType() );

      REQUIRE( 2 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 3e+7 == Approx( chunk.energies()[1] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }

    THEN( "a PartialProbability can be constructed and members can be tested "
          "when specifying the value of U" ) {
      PartialProbability chunk( lf,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( probabilities ),
                                u );

      REQUIRE( 1.0 == Approx ( chunk.U() ) );
      REQUIRE( 1.0 == Approx ( chunk.energyLimitConstant() ) );
      REQUIRE( 1 == chunk.LF() );
      REQUIRE( 1 == chunk.distributionType() );

      REQUIRE( 2 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 3e+7 == Approx( chunk.energies()[1] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid PartialProbability" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a PartialProbability can be constructed and members can be tested" ) {
      PartialProbability chunk( begin, end, lineNumber, 9437, 5, 18 );

      REQUIRE( 1.0 == Approx ( chunk.U() ) );
      REQUIRE( 1.0 == Approx ( chunk.energyLimitConstant() ) );
      REQUIRE( 1 == chunk.LF() );
      REQUIRE( 1 == chunk.distributionType() );

      REQUIRE( 2 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 3e+7 == Approx( chunk.energies()[1] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 1. == Approx( chunk.probabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of PartialProbability" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    PartialProbability chunk(begin, end, lineNumber, 9437, 5, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9437, 5, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 0.000000+0          0          1          1          29437 5 18     \n"
    "          2          2                                            9437 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n";
}
