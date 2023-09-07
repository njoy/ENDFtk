#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Multiplicity =
section::Type< 26 >::Multiplicity;

std::string chunk();
void verifyChunk( const Multiplicity& );
std::string invalidChunk();

SCENARIO( "Multiplicity" ) {

  GIVEN( "valid data for a Multiplicity" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double zap = 11.;
      double awi = 5.438673E-4;
      long law = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 10., 1.e+11 };
      std::vector< double > multiplicities = { 1., 1. };

      Multiplicity chunk( zap, awi, law,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( multiplicities ) );

      THEN( "a Multiplicity can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Multiplicity chunk( begin, end, lineNumber, 100, 26, 525 );

      THEN( "a Multiplicity can be constructed and members can be tested" ) {

        verifyChunk( chunk );
     } // THEN

     THEN( "it can be printed" ) {

       std::string buffer;
       auto output = std::back_inserter( buffer );
       chunk.print( output, 100, 26, 525 );

       CHECK( buffer == string );
     } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Multiplicity" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double zap = 11.;
      double awi = 5.438673E-4;
      long law = 2;
      std::vector< long > wrongBoundaries = { 4, 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 10., 1.e+11 };
      std::vector< double > multiplicities = { 1., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Multiplicity( zap, awi, law,
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

        CHECK_THROWS( Multiplicity( begin, end, lineNumber, 100, 26, 525 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 1.100000+1 5.438673-4          0          2          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n";
}

void verifyChunk( const Multiplicity& chunk ) {

  CHECK( 11. == Approx( chunk.ZAP() ) );
  CHECK( 11. == Approx( chunk.productIdentifier() ) );
  CHECK( 5.438673e-4 == Approx( chunk.AWI() ) );
  CHECK( 5.438673e-4 == Approx( chunk.projectileWeightRatio() ) );
  CHECK( 2 == chunk.LAW() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.Y().size() );
  CHECK( 2 == chunk.multiplicities().size() );
  CHECK( 10. == Approx( chunk.E()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.E()[1] ) );
  CHECK( 10. == Approx( chunk.energies()[0] ) );
  CHECK( 1.e+11 == Approx( chunk.energies()[1] ) );
  CHECK( 1. == Approx( chunk.Y()[0] ) );
  CHECK( 1. == Approx( chunk.Y()[1] ) );
  CHECK( 1. == Approx( chunk.multiplicities()[0] ) );
  CHECK( 1. == Approx( chunk.multiplicities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {

  return
  " 1.100000+1 5.438673-4          0          2          2          2 10026525     \n"
  "          2          2                                             10026525     \n"
  " 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n";
}
