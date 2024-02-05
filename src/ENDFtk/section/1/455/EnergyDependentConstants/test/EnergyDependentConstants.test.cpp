// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/455.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DecayConstants = section::Type< 1, 455 >::DecayConstants;
using EnergyDependentConstants = section::Type< 1, 455 >::EnergyDependentConstants;

std::string chunk();
void verifyChunk( const EnergyDependentConstants& );
std::string oddNPL();
std::string inconsistentNNF();

SCENARIO( "EnergyDependentConstants" ) {

  GIVEN( "valid data for a EnergyDependentConstants" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 4 };
      std::vector< DecayConstants > constants = {

        DecayConstants( 1e-5, { 1., 2., 3., 4., 5., 6. },
                        { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 } ),
        DecayConstants( 2e+7, { 6., 5., 4., 3., 2., 1. },
                        { 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 } )
      };

      EnergyDependentConstants chunk( std::move( boundaries ),
                                      std::move( interpolants ),
                                      std::move( constants ) );

      THEN( "an EnergyDependentConstants can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyDependentConstants chunk( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "a EnergyDependentConstants can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a EnergyDependentConstants" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 1 };
      std::vector< long > interpolants = { 4 };
      std::vector< DecayConstants > constants = {

        DecayConstants( 1e-5, { 1., 2., 3., 4., 5., 6. },
                        { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 } ),
        DecayConstants( 1e-5, { 6., 5., 4., 3., 2., 1. },
                        { 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 } )
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyDependentConstants( std::move( boundaries ),
                                                std::move( interpolants ),
                                                std::move( constants ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an odd NPL is given" ) {

      std::string string = oddNPL();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyDependentConstants( begin, end, lineNumber,
                                                9228, 1, 455 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with inconsistent NNF values is given" ) {

      std::string string = inconsistentNNF();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyDependentConstants( begin, end, lineNumber,
                                                9228, 1, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         12          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n";
}

void verifyChunk( const EnergyDependentConstants& chunk ) {

  CHECK( 1 == chunk.LDG() );
  CHECK( 1 == chunk.type() );
  CHECK( 6 == chunk.NNF() );
  CHECK( 6 == chunk.numberPrecursors() );

  CHECK( 1 == chunk.NR() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 4 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  CHECK( 2 == chunk.constants().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.constants()[0].E() ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.constants()[1].E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.constants()[0].incidentEnergy() ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.constants()[1].incidentEnergy() ) );

  CHECK( 6 == chunk.constants()[0].lambdas().size() );
  CHECK( 6 == chunk.constants()[0].decayConstants().size() );
  CHECK_THAT( 1., WithinRel( chunk.constants()[0].lambdas()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.constants()[0].lambdas()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.constants()[0].lambdas()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.constants()[0].lambdas()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.constants()[0].lambdas()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.constants()[0].lambdas()[5] ) );
  CHECK_THAT( 1., WithinRel( chunk.constants()[0].decayConstants()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.constants()[0].decayConstants()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.constants()[0].decayConstants()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.constants()[0].decayConstants()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.constants()[0].decayConstants()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.constants()[0].decayConstants()[5] ) );

  CHECK( 6 == chunk.constants()[1].lambdas().size() );
  CHECK( 6 == chunk.constants()[1].decayConstants().size() );
  CHECK_THAT( 6., WithinRel( chunk.constants()[1].lambdas()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.constants()[1].lambdas()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.constants()[1].lambdas()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.constants()[1].lambdas()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.constants()[1].lambdas()[4] ) );
  CHECK_THAT( 1., WithinRel( chunk.constants()[1].lambdas()[5] ) );
  CHECK_THAT( 6., WithinRel( chunk.constants()[1].decayConstants()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.constants()[1].decayConstants()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.constants()[1].decayConstants()[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.constants()[1].decayConstants()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.constants()[1].decayConstants()[4] ) );
  CHECK_THAT( 1., WithinRel( chunk.constants()[1].decayConstants()[5] ) );

  CHECK( 6 == chunk.constants()[0].alphas().size() );
  CHECK( 6 == chunk.constants()[0].abundances().size() );
  CHECK_THAT( 1.1, WithinRel( chunk.constants()[0].alphas()[0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.constants()[0].alphas()[1] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.constants()[0].alphas()[2] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.constants()[0].alphas()[3] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.constants()[0].alphas()[4] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.constants()[0].alphas()[5] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.constants()[0].abundances()[0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.constants()[0].abundances()[1] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.constants()[0].abundances()[2] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.constants()[0].abundances()[3] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.constants()[0].abundances()[4] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.constants()[0].abundances()[5] ) );

  CHECK( 6 == chunk.constants()[1].alphas().size() );
  CHECK( 6 == chunk.constants()[1].abundances().size() );
  CHECK_THAT( 6.1, WithinRel( chunk.constants()[1].alphas()[0] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.constants()[1].alphas()[1] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.constants()[1].alphas()[2] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.constants()[1].alphas()[3] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.constants()[1].alphas()[4] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.constants()[1].alphas()[5] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.constants()[1].abundances()[0] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.constants()[1].abundances()[1] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.constants()[1].abundances()[2] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.constants()[1].abundances()[3] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.constants()[1].abundances()[4] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.constants()[1].abundances()[5] ) );

  CHECK( 8 == chunk.NC() );
}

std::string oddNPL() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         11          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0           9228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         11          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0           9228 1455     \n";
}

std::string inconsistentNNF() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         10          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0                      9228 1455     \n";
}
