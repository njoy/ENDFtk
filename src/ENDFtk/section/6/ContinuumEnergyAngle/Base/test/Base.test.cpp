#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Base = 
section::Type< 6 >::ContinuumEnergyAngle::Base;

std::string chunk();
std::string invalidSize();

SCENARIO( "Base" ) {

  GIVEN( "valid data for a Base" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
    std::vector< std::pair< double, std::vector< double > > > data = { 
      std::make_pair< double, std::vector< double > >( 1., { 2., 3. } ),
      std::make_pair< double, std::vector< double > >( 4., { 5., 6. } ) };

    THEN( "a Base can "
          "be constructed using a list and members can be tested" ) {
      Base chunk( energy, nd, na, nep, std::move( list ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 0 == chunk.numberDiscreteEnergies() );
      REQUIRE( 1 == chunk.NA() );
      REQUIRE( 1 == chunk.numberAngularParameters() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.numberSecondaryEnergies() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 4. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.data().size() );
      REQUIRE( 2. == Approx( chunk.data()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.data()[0][1] ) );
      REQUIRE( 5. == Approx( chunk.data()[1][0] ) );
      REQUIRE( 6. == Approx( chunk.data()[1][1] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid Base" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a Base can "
          "be constructed and members can be tested" ) {
      Base chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 0 == chunk.numberDiscreteEnergies() );
      REQUIRE( 1 == chunk.NA() );
      REQUIRE( 1 == chunk.numberAngularParameters() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.numberSecondaryEnergies() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 4. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.data().size() );
      REQUIRE( 2. == Approx( chunk.data()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.data()[0][1] ) );
      REQUIRE( 5. == Approx( chunk.data()[1][0] ) );
      REQUIRE( 6. == Approx( chunk.data()[1][1] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "data with inconsistent sizes" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > wronglist = { 1., 2., 3., 4., 5. };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Base( energy, nd, na, nep, std::move( wronglist ) ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW, NA, NEP" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Base( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of Base" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    Base
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
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          1          5          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           9228 6  5     \n";
}
