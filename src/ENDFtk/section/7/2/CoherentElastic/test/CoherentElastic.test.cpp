#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;

std::string chunkWithOneTemperature();
void verifyOneTemperature( const CoherentElastic& );
std::string chunkWithTwoTemperatures();
void verifyTwoTemperatures( const CoherentElastic& );
std::string invalidChunk();
std::string chunkWithInvalidNP();

SCENARIO( "CoherentElastic" ) {

  GIVEN( "valid data for a CoherentElastic with only one temperature" ) {

    std::string string = chunkWithOneTemperature();

    WHEN( "the data is given explicitly" ) {

      // single temperature constructor
      double temperature = 293.6;
      std::vector< long > interpolants = { 1 };
      std::vector< long > boundaries = { 3 };
      std::vector< double > energies = { 1.059427e-3, 3.718355e-3,  4.237708e-3 };
      std::vector< double > s = { 0.0, 9.364524e-3, 1.548925e-2 };

      // multiple temperature constructor with data for only one
      std::vector< long > Interpolants = { 1 };
      std::vector< long > Boundaries = { 3 };
      std::vector< double > Energies = { 1.059427e-3, 3.718355e-3,
                                         4.237708e-3 };
      std::vector< long > Li = {};
      std::vector< double > Temperatures = { 293.6 };
      std::vector< std::vector< double > > S =
                                     { { 0.0, 9.364524e-3, 1.548925e-2 } };

      CoherentElastic chunk( temperature,
                             std::move( boundaries ),
                             std::move( interpolants ),
                             std::move( energies ),
                             std::move( s ) );

      CoherentElastic chunk2( std::move( Boundaries ),
                              std::move( Interpolants ),
                              std::move( Temperatures ),
                              std::move( Li ),
                              std::move( Energies ),
                              std::move( S ) );

      THEN( "a CoherentElastic can be constructed using separate arrays and "
            "members can be tested" ) {

        verifyOneTemperature( chunk );
      } // THEN

      THEN( "a CoherentElastic can be constructed with the multiple "
            "temperature constructor using separate arrays and members can be "
            "tested" ) {

        verifyOneTemperature( chunk2 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );

        std::string buffer2;
        output = std::back_inserter( buffer2 );
        chunk2.print( output, 27, 7, 2 );

        CHECK( buffer2 == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );

      THEN( "a CoherentElastic can "
            "be constructed and members can be tested" ) {

        verifyOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a CoherentElastic with two temperatures" ) {

    std::string string = chunkWithTwoTemperatures();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 1 };
      std::vector< long > li = { 2 };
      std::vector< double > temperatures = { 293.6, 400.0 };
      std::vector< double > energies = { 1.059427e-3, 3.718355e-3,
                                         4.237708e-3 };
      std::vector< std::vector< double > > s = { { 0.0, 9.364524e-3,
                                                   1.548925e-2 },
                                                 { 0.5, 8.318414e-3,
                                                   1.640584e-2 } };

      CoherentElastic chunk( std::move( boundaries ),
                             std::move( interpolants ),
                             std::move( temperatures ),
                             std::move( li ),
                             std::move( energies ),
                             std::move( s ) );

      THEN( "a CoherentElastic can be constructed using separate arrays and "
            "members can be tested" ) {

        verifyTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      CoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );

      THEN( "a CoherentElastic can "
            "be constructed and members can be tested" ) {

        verifyTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a CoherentElastic" ) {

    WHEN( "data with an inconsistent number of T and S(E,T) functions" ) {

      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 1 };
      std::vector< long > li = { 2 };
      std::vector< double > temperatures = { 293.6 }; // should be two to pass
      std::vector< double > energies = { 1.059427e-3, 3.718355e-3,  4.237708e-3 };
      std::vector< std::vector< double > > s = { { 0.0, 9.364524e-3,
                                                   1.548925e-2 },
                                                 { 0.5, 8.318414e-3,
                                                   1.640584e-2 } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoherentElastic( std::move( boundaries ),
                                         std::move( interpolants ),
                                         std::move( temperatures ),
                                         std::move( li ),
                                         std::move( energies ),
                                         std::move( s ) ) );
      } // THEN
    } // WHEN

    WHEN( "data with an inconsistent number of points NP is given" ) {

      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 1 };
      std::vector< long > li = { 2 };
      std::vector< double > temperatures = { 293.6, 400.0 };
      std::vector< double > energies = { 1.059427e-3, 3.718355e-3,
                                         4.237708e-3 };
      std::vector< std::vector< double > > s = { { 0.0, 9.364524e-3,
                                                   1.548925e-2 },
                                                 { 0.5, 8.318414e-3 } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoherentElastic( std::move( boundaries ),
                                         std::move( interpolants ),
                                         std::move( temperatures ),
                                         std::move( li ),
                                         std::move( energies ),
                                         std::move( s ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with inconsistent NP is given" ) {

      std::string string = chunkWithInvalidNP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoherentElastic( begin, end, lineNumber, 27, 7, 2 ) );
      } // THEN
    } // WHEN

    WHEN( "inconsistent data for the single temperature constructor is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double temperature = 293.6;
      std::vector< long > wrongInterpolants = { 1, 2 };
      std::vector< long > boundaries = { 3 };
      std::vector< double > energies = { 1.059427e-3, 3.718355e-3,  4.237708e-3 };
      std::vector< double > s = { 0.0, 9.364524e-3, 1.548925e-2 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoherentElastic( temperature,
                                         std::move( boundaries ),
                                         std::move( wrongInterpolants ),
                                         std::move( energies ),
                                         std::move( s )  ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoherentElastic( begin, end, lineNumber, 27, 7, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOneTemperature() {
  return
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n";
}

void verifyOneTemperature( const CoherentElastic& chunk ) {

  CHECK( 1 == chunk.LTHR() );
  CHECK( 1 == chunk.elasticScatteringType() );
  CHECK( 0 == chunk.LT() );
  CHECK( 0 == chunk.temperatureDependenceFlag() );
  CHECK( 1 == chunk.NT() );
  CHECK( 1 == chunk.numberTemperatures() );
  CHECK( 3 == chunk.NP() );
  CHECK( 3 == chunk.numberBraggEdges() );

  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.interpolants()[0] );

  CHECK( 1 == chunk.T().size() );
  CHECK( 1 == chunk.temperatures().size() );
  CHECK( 293.6 == Approx( chunk.T()[0] ) );
  CHECK( 293.6 == Approx( chunk.temperatures()[0] ) );

  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 1.059427e-3 == Approx( chunk.E()[0] ) );
  CHECK( 3.718355e-3 == Approx( chunk.E()[1] ) );
  CHECK( 4.237708e-3 == Approx( chunk.E()[2] ) );
  CHECK( 1.059427e-3 == Approx( chunk.energies()[0] ) );
  CHECK( 3.718355e-3 == Approx( chunk.energies()[1] ) );
  CHECK( 4.237708e-3 == Approx( chunk.energies()[2] ) );

  CHECK( 0 == chunk.LI().size() );
  CHECK( 0 == chunk.temperatureInterpolants().size() );

  CHECK( 1 == chunk.thermalScatteringValues().size() );
  CHECK( 3 == chunk.thermalScatteringValues()[0].size() );
  CHECK( 0.0 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( chunk.thermalScatteringValues()[0][2] ) );

  CHECK( 1 == chunk.S().size() );
  CHECK( 3 == chunk.S()[0].size() );
  CHECK( 0.0 == Approx( chunk.S()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( chunk.S()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( chunk.S()[0][2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithTwoTemperatures() {
  return
    " 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          3          0  27 7  2     \n"
    " 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n";
}

void verifyTwoTemperatures( const CoherentElastic& chunk ) {

  CHECK( 1 == chunk.LTHR() );
  CHECK( 1 == chunk.elasticScatteringType() );
  CHECK( 1 == chunk.LT() );
  CHECK( 1 == chunk.temperatureDependenceFlag() );
  CHECK( 2 == chunk.NT() );
  CHECK( 2 == chunk.numberTemperatures() );
  CHECK( 3 == chunk.NP() );
  CHECK( 3 == chunk.numberBraggEdges() );

  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.interpolants()[0] );

  CHECK( 2 == chunk.T().size() );
  CHECK( 2 == chunk.temperatures().size() );
  CHECK( 293.6 == Approx( chunk.T()[0] ) );
  CHECK( 400. == Approx( chunk.T()[1] ) );
  CHECK( 293.6 == Approx( chunk.temperatures()[0] ) );
  CHECK( 400. == Approx( chunk.temperatures()[1] ) );

  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 1.059427e-3 == Approx( chunk.E()[0] ) );
  CHECK( 3.718355e-3 == Approx( chunk.E()[1] ) );
  CHECK( 4.237708e-3 == Approx( chunk.E()[2] ) );
  CHECK( 1.059427e-3 == Approx( chunk.energies()[0] ) );
  CHECK( 3.718355e-3 == Approx( chunk.energies()[1] ) );
  CHECK( 4.237708e-3 == Approx( chunk.energies()[2] ) );

  CHECK( 1 == chunk.LI().size() );
  CHECK( 2 == chunk.LI()[0] );
  CHECK( 1 == chunk.temperatureInterpolants().size() );
  CHECK( 2 == chunk.temperatureInterpolants()[0] );

  CHECK( 2 == chunk.S().size() );
  CHECK( 3 == chunk.S()[0].size() );
  CHECK( 0.0 == Approx( chunk.S()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( chunk.S()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( chunk.S()[0][2] ) );
  CHECK( 3 == chunk.S()[1].size() );
  CHECK( 0.5 == Approx( chunk.S()[1][0] ) );
  CHECK( 8.318414e-3 == Approx( chunk.S()[1][1] ) );
  CHECK( 1.640584e-2 == Approx( chunk.S()[1][2] ) );

  CHECK( 2 == chunk.thermalScatteringValues().size() );
  CHECK( 3 == chunk.thermalScatteringValues()[0].size() );
  CHECK( 0.0 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  CHECK( 3 == chunk.thermalScatteringValues()[1].size() );
  CHECK( 0.5 == Approx( chunk.thermalScatteringValues()[1][0] ) );
  CHECK( 8.318414e-3 == Approx( chunk.thermalScatteringValues()[1][1] ) );
  CHECK( 1.640584e-2 == Approx( chunk.thermalScatteringValues()[1][2] ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 2.936000+2 0.000000+0          0          0          1          4  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n";
}

std::string chunkWithInvalidNP() {
  return
    " 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          2          0  27 7  2     \n"
    " 5.000000-1 8.318414-3                                              27 7  2     \n";
}
