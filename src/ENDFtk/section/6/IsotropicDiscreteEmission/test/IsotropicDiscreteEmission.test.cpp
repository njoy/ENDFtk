// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using IsotropicDiscreteEmission =
section::Type< 6 >::IsotropicDiscreteEmission;

SCENARIO( "IsotropicDiscreteEmission" ) {

  GIVEN( "a string representation of a valid IsotropicDiscreteEmission" ) {

    THEN( "a IsotropicDiscreteEmission can be constructed and "
          "members can be tested" ) {
      IsotropicDiscreteEmission chunk;

      CHECK( 3 == chunk.LAW() );

      CHECK( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of IsotropicDiscreteEmission" ) {

    IsotropicDiscreteEmission chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO
