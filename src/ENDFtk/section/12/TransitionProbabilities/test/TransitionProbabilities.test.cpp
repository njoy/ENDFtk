// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/12.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TransitionProbabilities = section::Type< 12 >::TransitionProbabilities;

std::string chunkWithLG1();
void verifyChunkWithLG1( const TransitionProbabilities& );
std::string chunkWithLG2();
void verifyChunkWithLG2( const TransitionProbabilities& );
std::string chunkWithInvalidLG();
std::string chunkWithBadNPL();

SCENARIO( "TransitionProbabilities" ) {

  GIVEN( "valid data for a TransitionProbabilities with LG = 1" ) {

    std::string string = chunkWithLG1();

    WHEN( "the data is given explicitly" ) {

      double energy = 5.170900e+4;
      std::vector< double > energies = { 1.304000e+4, 7.700000e+1 };
      std::vector< double > probabilities = { 2.709000e-1, 7.291000e-1 };

      TransitionProbabilities chunk( energy,
                                     std::move( energies ),
                                     std::move( probabilities ) );

      THEN( "a TransitionProbabilities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 51 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TransitionProbabilities chunk( begin, end, lineNumber, 9228, 12, 51 );

      THEN( "a TransitionProbabilities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 51 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a TransitionProbabilities with LG = 2" ) {

    std::string string = chunkWithLG2();

    WHEN( "the data is given explicitly" ) {

      double energy = 5.170900e+4;
      std::vector< double > energies = { 1.304000e+4, 7.700000e+1 };
      std::vector< double > probabilities = { 2.709000e-1, 7.291000e-1 };
      std::vector< double > conditionals = { 3.215434e-3, 3.144654e-3 };

      TransitionProbabilities chunk( energy,
                                     std::move( energies ),
                                     std::move( probabilities ),
                                     std::move( conditionals ) );

      THEN( "a TransitionProbabilities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 51 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TransitionProbabilities chunk( begin, end, lineNumber, 9228, 12, 51 );

      THEN( "a TransitionProbabilities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 51 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TransitionProbabilities" ) {

    WHEN( "inconsistent data is used for LG = 1" ) {

      double energy = 5.170900e+4;
      std::vector< double > energies = { 1.304000e+4, 7.700000e+1 };
      // wrong size for probabilities
      std::vector< double > probabilities = { 2.709000e-1, 7.291000e-1, 1.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TransitionProbabilities( energy,
                                               std::move( energies ),
                                               std::move( probabilities ) ) );
      } // THEN
    } // WHEN

    WHEN( "inconsistent data is used for LG = 2" ) {

      double energy = 5.170900e+4;
      std::vector< double > energies = { 1.304000e+4, 7.700000e+1 };
      std::vector< double > probabilities = { 2.709000e-1, 7.291000e-1 };
      // wrong size for conditional probabilities
      std::vector< double > conditionals = { 2.709000e-1, 7.291000e-1, 1.0 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TransitionProbabilities( energy,
                                               std::move( energies ),
                                               std::move( probabilities ),
                                               std::move( conditionals ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LG is given" ) {

      std::string string = chunkWithInvalidLG(); // LG = 6, which is invalid
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TransitionProbabilities( begin, end, lineNumber,
                                               9228, 12, 51 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an bad NPL is used" ) {

      std::string string = chunkWithBadNPL(); // NPL = 4, while list size is 6
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TransitionProbabilities( begin, end, lineNumber,
                                               9228, 12, 51 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLG1() {
  return
  " 5.170900+4 0.000000+0          0          0          4          2922812 51     \n"
  " 1.304000+4 2.709000-1 7.700000+1 7.291000-1                      922812 51     \n";
}

void verifyChunkWithLG1( const TransitionProbabilities& chunk ) {

  CHECK( 2 == chunk.LO() );
  CHECK( 2 == chunk.representation() );

  CHECK_THAT( 5.170900e+4, WithinRel( chunk.ES() ) );
  CHECK_THAT( 5.170900e+4, WithinRel( chunk.highestEnergyLevel() ) );
  CHECK( 1 == chunk.LG() );
  CHECK( 1 == chunk.transitionType() );
  CHECK( 2 == chunk.NT() );
  CHECK( 2 == chunk.numberTransitions() );

  CHECK( 2 == chunk.transitions().size() );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.transitions()[0].E() ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.transitions()[1].E() ) );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.transitions()[0].energy() ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.transitions()[1].energy() ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitions()[0].TP() ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitions()[1].TP() ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitions()[0].transitionProbability() ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitions()[1].transitionProbability() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.transitions()[0].GP() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.transitions()[1].GP() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.transitions()[0].conditionalProbability() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.transitions()[1].conditionalProbability() ) );

  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.TP().size() );
  CHECK( 2 == chunk.transitionProbabilities().size() );
  CHECK( 2 == chunk.GP().size() );
  CHECK( 2 == chunk.conditionalProbabilities().size() );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.TP()[0] ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.TP()[1] ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitionProbabilities()[0] ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitionProbabilities()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.GP()[0] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.GP()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.conditionalProbabilities()[0] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.conditionalProbabilities()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkWithLG2() {
  return
  " 5.170900+4 0.000000+0          0          0          6          2922812 51     \n"
  " 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n";
}

void verifyChunkWithLG2( const TransitionProbabilities& chunk ) {

  CHECK( 2 == chunk.LO() );
  CHECK( 2 == chunk.representation() );

  CHECK_THAT( 5.170900e+4, WithinRel( chunk.ES() ) );
  CHECK_THAT( 5.170900e+4, WithinRel( chunk.highestEnergyLevel() ) );
  CHECK( 2 == chunk.LG() );
  CHECK( 2 == chunk.transitionType() );
  CHECK( 2 == chunk.NT() );
  CHECK( 2 == chunk.numberTransitions() );

  CHECK( 2 == chunk.transitions().size() );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.transitions()[0].E() ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.transitions()[1].E() ) );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.transitions()[0].energy() ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.transitions()[1].energy() ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitions()[0].TP() ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitions()[1].TP() ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitions()[0].transitionProbability() ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitions()[1].transitionProbability() ) );
  CHECK_THAT( 3.215434e-3, WithinRel( chunk.transitions()[0].GP() ) );
  CHECK_THAT( 3.144654e-3, WithinRel( chunk.transitions()[1].GP() ) );
  CHECK_THAT( 3.215434e-3, WithinRel( chunk.transitions()[0].conditionalProbability() ) );
  CHECK_THAT( 3.144654e-3, WithinRel( chunk.transitions()[1].conditionalProbability() ) );

  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.TP().size() );
  CHECK( 2 == chunk.transitionProbabilities().size() );
  CHECK( 2 == chunk.GP().size() );
  CHECK( 2 == chunk.conditionalProbabilities().size() );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1.304000e+4, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 7.700000e+1, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.TP()[0] ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.TP()[1] ) );
  CHECK_THAT( 2.709000e-1, WithinRel( chunk.transitionProbabilities()[0] ) );
  CHECK_THAT( 7.291000e-1, WithinRel( chunk.transitionProbabilities()[1] ) );
  CHECK_THAT( 3.215434e-3, WithinRel( chunk.GP()[0] ) );
  CHECK_THAT( 3.144654e-3, WithinRel( chunk.GP()[1] ) );
  CHECK_THAT( 3.215434e-3, WithinRel( chunk.conditionalProbabilities()[0] ) );
  CHECK_THAT( 3.144654e-3, WithinRel( chunk.conditionalProbabilities()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkWithInvalidLG() {
  return
  " 5.170900+4 0.000000+0          0          0          6          1922812 51     \n"
  " 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n";
}

std::string chunkWithBadNPL() {
  return
  " 5.170900+4 0.000000+0          0          0          4          2922812 51     \n"
  " 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n";
}
