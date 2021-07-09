#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Multiplicity =
section::Type< 6 >::Multiplicity;

std::string chunk();
void verifyChunk( const Multiplicity& );
std::string invalidChunk();

SCENARIO( "Multiplicity" ) {

  GIVEN( "valid data for a Multiplicity" ) {

    std::string string = chunk();

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

      Multiplicity chunk( zap, awp, lip, law,
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
        chunk.print( output, 9228, 6, 5 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Multiplicity chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a Multiplicity can be constructed and members can be tested" ) {

        verifyChunk( chunk );
     } // THEN

     THEN( "it can be printed" ) {

       std::string buffer;
       auto output = std::back_inserter( buffer );
       chunk.print( output, 9228, 6, 5 );

       CHECK( buffer == string );
     } // THEN
    } // WHEN
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

        CHECK_THROWS( Multiplicity( zap, awp, lip, law,
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

        CHECK_THROWS( Multiplicity( begin, end, lineNumber, 9228, 6, 5 ) );
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

  CHECK( 1001. == Approx( chunk.ZAP() ) );
  CHECK( 1001. == Approx( chunk.productIdentifier() ) );
  CHECK( 0.9986234 == Approx( chunk.AWP() ) );
  CHECK( 0.9986234 == Approx( chunk.productWeightRatio() ) );
  CHECK( 0 == chunk.LIP() );
  CHECK( 0 == chunk.productModifierFlag() );
  CHECK( 1 == chunk.LAW() );

  CHECK( 4 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 4 == chunk.boundaries()[0] );
  CHECK( 4 == chunk.E().size() );
  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.Y().size() );
  CHECK( 4 == chunk.multiplicities().size() );
  CHECK( 1e-5 == Approx( chunk.E()[0] ) );
  CHECK( 1.1e+7 == Approx( chunk.E()[1] ) );
  CHECK( 1.147e+7 == Approx( chunk.E()[2] ) );
  CHECK( 3e+7 == Approx( chunk.E()[3] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 1.1e+7 == Approx( chunk.energies()[1] ) );
  CHECK( 1.147e+7 == Approx( chunk.energies()[2] ) );
  CHECK( 3e+7 == Approx( chunk.energies()[3] ) );
  CHECK( 0. == Approx( chunk.Y()[0] ) );
  CHECK( 8.45368e-11 == Approx( chunk.Y()[1] ) );
  CHECK( 6.622950e-8 == Approx( chunk.Y()[2] ) );
  CHECK( 2.149790e-1 == Approx( chunk.Y()[3] ) );
  CHECK( 0. == Approx( chunk.multiplicities()[0] ) );
  CHECK( 8.45368e-11 == Approx( chunk.multiplicities()[1] ) );
  CHECK( 6.622950e-8 == Approx( chunk.multiplicities()[2] ) );
  CHECK( 2.149790e-1 == Approx( chunk.multiplicities()[3] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {

  return
    " 1.001000+3 9.986234-1          0          1          1          59228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 3.000000+7 2.149790-1                                            9228 6  5     \n";
}
