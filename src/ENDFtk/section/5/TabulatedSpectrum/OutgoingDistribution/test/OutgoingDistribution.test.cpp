#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using OutgoingDistribution = 
section::Type< 5 >::TabulatedSpectrum::OutgoingDistribution;

std::string chunk();

SCENARIO( "OutgoingDistribution" ) {

  GIVEN( "valid data for an OutgoingDistribution" ) {

    double incident = 1e-5;
    std::vector< long > boundaries = { 3 };
    std::vector< long > interpolants = { 2 };
    std::vector< double > energies = { 0.0, 1e+5, 3e+7 };
    std::vector< double > values = { 0.0, 1.757570e-9, 1.843350e-9 };
      
    THEN( "an OutgoingDistribution can be constructed and members can be tested" ) {
      OutgoingDistribution chunk( incident,
                                  std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( energies ),
                                  std::move( values ) );

      REQUIRE( 1e-5 == Approx( chunk.incidentEnergy() ) );

      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.values().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 3e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 0. == Approx( chunk.values()[0] ) );
      REQUIRE( 1.757570e-9 == Approx( chunk.values()[1] ) );
      REQUIRE( 1.843350e-9 == Approx( chunk.values()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid OutgoingDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an OutgoingDistribution can be constructed and members can be tested" ) {
      OutgoingDistribution chunk( begin, end, lineNumber, 9437, 5, 18 );

      REQUIRE( 1e-5 == Approx( chunk.incidentEnergy() ) );

      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.energies().size() );
      REQUIRE( 3 == chunk.values().size() );
      REQUIRE( 0.0 == Approx( chunk.energies()[0] ) );
      REQUIRE( 1e+5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 3e+7 == Approx( chunk.energies()[2] ) );
      REQUIRE( 0. == Approx( chunk.values()[0] ) );
      REQUIRE( 1.757570e-9 == Approx( chunk.values()[1] ) );
      REQUIRE( 1.843350e-9 == Approx( chunk.values()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of OutgoingDistribution" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    OutgoingDistribution chunk(begin, end, lineNumber, 9437, 5, 18 );

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
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n";
}
