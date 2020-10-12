#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Probability =
section::Type< 5 >::Probability;

std::string chunkWithUZero();
void verifyChunkWithUZero( const Probability& );
std::string chunkWithUOne();
void verifyChunkWithUOne( const Probability& );
std::string invalidChunk();

SCENARIO( "Probability" ) {

  GIVEN( "valid data for a Probability with U = 0" ) {

    std::string string = chunkWithUZero();

    WHEN( "the data is given explicitly" ) {

      long lf = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 3e+7 };
      std::vector< double > probabilities = { 1., 1. };

      Probability chunk( lf,
                         std::move( boundaries ),
                         std::move( interpolants ),
                         std::move( energies ),
                         std::move( probabilities ) );

      THEN( "a Probability can be constructed and members can be "
            "tested" ) {

        verifyChunkWithUZero( chunk );
      } //THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Probability chunk( begin, end, lineNumber, 9437, 5, 18 );

      THEN( "a Probability can be constructed and members can be "
            "tested" ) {

        verifyChunkWithUZero( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a Probability with U = 1" ) {

    std::string string = chunkWithUOne();

    WHEN( "the data is given explicitly" ) {

      double u = 1.0;
      long lf = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 3e+7 };
      std::vector< double > probabilities = { 1., 1. };

      Probability chunk( lf,
                         std::move( boundaries ),
                         std::move( interpolants ),
                         std::move( energies ),
                         std::move( probabilities ),
                         u );

      THEN( "a Probability can be constructed and members can be "
            "tested" ) {

        verifyChunkWithUOne( chunk );
      } //THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        CHECK( buffer == string );
      }
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Probability chunk( begin, end, lineNumber, 9437, 5, 18 );

      THEN( "a Probability can be constructed and members can be "
            "tested" ) {

        verifyChunkWithUOne( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Probability" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      long lf = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 2, 4 };
      std::vector< double > energies = { 1e-5, 3e+7 };
      std::vector< double > probabilities = { 1., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Probability( lf,
                                     std::move( boundaries ),
                                     std::move( wrongInterpolants ),
                                     std::move( energies ),
                                     std::move( probabilities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Probability( begin, end, lineNumber, 9437, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithUZero() {
  return
    " 0.000000+0 0.000000+0          0          1          1          29437 5 18     \n"
    "          2          2                                            9437 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n";
}

void verifyChunkWithUZero( const Probability& chunk ) {

  CHECK( 1 == chunk.LF() );
  CHECK( 1 == chunk.LAW() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.P().size() );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK( 1e-5 == Approx( chunk.E()[0] ) );
  CHECK( 3e+7 == Approx( chunk.E()[1] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 3e+7 == Approx( chunk.energies()[1] ) );
  CHECK( 1. == Approx( chunk.P()[0] ) );
  CHECK( 1. == Approx( chunk.P()[1] ) );
  CHECK( 1. == Approx( chunk.probabilities()[0] ) );
  CHECK( 1. == Approx( chunk.probabilities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithUOne() {
  return
    " 1.000000+0 0.000000+0          0          1          1          29437 5 18     \n"
    "          2          2                                            9437 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n";
}

void verifyChunkWithUOne( const Probability& chunk ) {

  CHECK( 1 == chunk.LF() );
  CHECK( 1 == chunk.LAW() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.P().size() );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK( 1e-5 == Approx( chunk.E()[0] ) );
  CHECK( 3e+7 == Approx( chunk.E()[1] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 3e+7 == Approx( chunk.energies()[1] ) );
  CHECK( 1. == Approx( chunk.P()[0] ) );
  CHECK( 1. == Approx( chunk.P()[1] ) );
  CHECK( 1. == Approx( chunk.probabilities()[0] ) );
  CHECK( 1. == Approx( chunk.probabilities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          1          2          29437 5 18     \n"
    "          2          2                                            9437 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n";
}
