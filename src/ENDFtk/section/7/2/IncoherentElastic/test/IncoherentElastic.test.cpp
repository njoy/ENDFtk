#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;

std::string chunk();

SCENARIO( "IncoherentElastic" ) {

  GIVEN( "valid data for a IncoherentElastic" ) {

    double sb = 8.198006e+1;
    std::vector< long > boundaries = { 3 };
    std::vector< long > interpolants = { 2 };
    std::vector< double > temperatures = { 296., 400., 500. };
    std::vector< double > debyeWallerValues = { 8.486993e+0, 9.093191e+0,
                                                9.828159e+0 };

    THEN( "an IncoherentElastic can be constructed and members can be "
          "tested" ) {
      IncoherentElastic chunk( sb,
                               std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( temperatures ),
                               std::move( debyeWallerValues ) );

      REQUIRE( 2 == chunk.LTHR() );
      REQUIRE( 8.198006e+1 == Approx( chunk.SB() ) );
      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.temperatures().size() );
      REQUIRE( 3 == chunk.debyeWallerValues().size() );
      REQUIRE( 296. == Approx( chunk.temperatures()[0] ) );
      REQUIRE( 400. == Approx( chunk.temperatures()[1] ) );
      REQUIRE( 500. == Approx( chunk.temperatures()[2] ) );
      REQUIRE( 8.486993e+0 == Approx( chunk.debyeWallerValues()[0] ) );
      REQUIRE( 9.093191e+0 == Approx( chunk.debyeWallerValues()[1] ) );
      REQUIRE( 9.828159e+0 == Approx( chunk.debyeWallerValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid IncoherentElastic" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a IncoherentElastic can be constructed and members can be tested" ) {
      IncoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );

      REQUIRE( 2 == chunk.LTHR() );
      REQUIRE( 8.198006e+1 == Approx( chunk.SB() ) );
      REQUIRE( 3 == chunk.NP() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.interpolants()[0] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 3 == chunk.temperatures().size() );
      REQUIRE( 3 == chunk.debyeWallerValues().size() );
      REQUIRE( 296. == Approx( chunk.temperatures()[0] ) );
      REQUIRE( 400. == Approx( chunk.temperatures()[1] ) );
      REQUIRE( 500. == Approx( chunk.temperatures()[2] ) );
      REQUIRE( 8.486993e+0 == Approx( chunk.debyeWallerValues()[0] ) );
      REQUIRE( 9.093191e+0 == Approx( chunk.debyeWallerValues()[1] ) );
      REQUIRE( 9.828159e+0 == Approx( chunk.debyeWallerValues()[2] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of IncoherentElastic" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    IncoherentElastic chunk(begin, end, lineNumber, 27, 7, 2 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 2 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
}

