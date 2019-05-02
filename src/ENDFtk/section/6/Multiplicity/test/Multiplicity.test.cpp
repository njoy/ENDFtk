#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Multiplicity = 
section::Type< 6 >::Multiplicity;

std::string chunk();
void verifyChunk( const Multiplicity& );
std::string invalidChunk();

SCENARIO( "Multiplicity" ) {

  GIVEN( "valid data for a Multiplicity" ) {

    WHEN( "the data is given explicitly" ) {

      double zap = 1001.;
      double awp = 0.9986234;
      long lip = 0;
      long law = 1;
      std::vector< long > boundaries = { 4 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 1.1e+7, 1.147e+7, 3e+7 };
      std::vector< double > multiplicities = { 0., 8.45368e-11,
                                               6.622950e-8, 2.149790e-1 };
      
      THEN( "a Multiplicity can be constructed and members can be tested" ) {

        Multiplicity chunk( zap, awp, lip, law,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( multiplicities ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a Multiplicity can be constructed and members can be tested" ) {

        Multiplicity chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
     } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of Multiplicity" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    Multiplicity chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a Multiplicity" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double zap = 1001.;
      double awp = 0.9986234;
      long lip = 0;
      long law = 1;
      std::vector< long > wrongBoundaries = { 4, 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 1.1e+7, 1.147e+7, 3e+7 };
      std::vector< double > multiplicities = { 0., 8.45368e-11,
                                               6.622950e-8, 2.149790e-1 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( Multiplicity( zap, awp, lip, law,
                                      std::move( wrongBoundaries ),
                                      std::move( interpolants ),
                                      std::move( energies ),
                                      std::move( multiplicities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( Multiplicity( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.001000+3 9.986234-1          0          1          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 3.000000+7 2.149790-1                                            9228 6  5     \n";
}

void verifyChunk( const Multiplicity& chunk ) {

  REQUIRE( 1001. == Approx( chunk.ZAP() ) );
  REQUIRE( 1001. == Approx( chunk.productIdentifier() ) );
  REQUIRE( 0.9986234 == Approx( chunk.AWP() ) );
  REQUIRE( 0.9986234 == Approx( chunk.productMassRatio() ) );
  REQUIRE( 0 == chunk.LIP() );
  REQUIRE( 0 == chunk.productModifierFlag() );
  REQUIRE( 1 == chunk.LAW() );

  REQUIRE( 4 == chunk.NP() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 2 == chunk.interpolants()[0] );
  REQUIRE( 4 == chunk.boundaries()[0] );
  REQUIRE( 4 == chunk.energies().size() );
  REQUIRE( 4 == chunk.multiplicities().size() );
  REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
  REQUIRE( 1.1e+7 == Approx( chunk.energies()[1] ) );
  REQUIRE( 1.147e+7 == Approx( chunk.energies()[2] ) );
  REQUIRE( 3e+7 == Approx( chunk.energies()[3] ) );
  REQUIRE( 0. == Approx( chunk.multiplicities()[0] ) );
  REQUIRE( 8.45368e-11 == Approx( chunk.multiplicities()[1] ) );
  REQUIRE( 6.622950e-8 == Approx( chunk.multiplicities()[2] ) );
  REQUIRE( 2.149790e-1 == Approx( chunk.multiplicities()[3] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 1.001000+3 9.986234-1          0          1          1          59228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 3.000000+7 2.149790-1                                            9228 6  5     \n";
}

