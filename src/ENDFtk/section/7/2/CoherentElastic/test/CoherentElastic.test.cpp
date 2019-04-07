#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;

std::string chunkWithOneTemperature();
void verifyOneTemperature( const CoherentElastic& );
std::string chunkWithTwoTemperatures();
void verifyTwoTemperatures( const CoherentElastic& );

SCENARIO( "CoherentElastic" ) {

  GIVEN( "valid data for a CoherentElastic with only one temperature" ) {

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

      THEN( "a CoherentElastic can be constructed using separate arrays and "
            "members can be tested" ) {
          
        CoherentElastic chunk( temperature,
                               std::move( boundaries ),
                               std::move( interpolants ), 
                               std::move( energies ),
                               std::move( s ) );

        verifyOneTemperature( chunk );
      } // THEN

      THEN( "a CoherentElastic can be constructed with the multiple "
            "temperature constructor using separate arrays and members can be "
            "tested" ) {
          
        CoherentElastic chunk( std::move( Boundaries ),
                               std::move( Interpolants ), 
                               std::move( Temperatures ),
                               std::move( Li ),
                               std::move( Energies ),
                               std::move( S ) );
        verifyOneTemperature( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      std::string string = chunkWithOneTemperature();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a CoherentElastic can "
            "be constructed and members can be tested" ) {

        CoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );
        verifyOneTemperature( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a CoherentElastic with two temperatures" ) {

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

      THEN( "a CoherentElastic can be constructed using separate arrays and "
            "members can be tested" ) {

        CoherentElastic chunk( std::move( boundaries ),
                               std::move( interpolants ), 
                               std::move( temperatures ),
                               std::move( li ),
                               std::move( energies ),
                               std::move( s ) );

        verifyTwoTemperatures( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      std::string string = chunkWithTwoTemperatures();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a CoherentElastic can "
            "be constructed and members can be tested" ) {

        CoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );
        verifyTwoTemperatures( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of a valid CoherentElastic with "
         "two temperatures" ) {

    std::string string = chunkWithTwoTemperatures();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a CoherentElastic can "
          "be constructed and members can be tested" ) {

      CoherentElastic chunk( begin, end, lineNumber, 27, 7, 2 );
      verifyTwoTemperatures( chunk );
    }
  } // GIVEN

  GIVEN( "a valid instance of CoherentElastic with only one temperature" ) {

    std::string string = chunkWithOneTemperature();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    CoherentElastic chunk(begin, end, lineNumber, 27, 7, 2 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 2 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of CoherentElastic with two temperatures" ) {

    std::string string = chunkWithTwoTemperatures();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    CoherentElastic chunk(begin, end, lineNumber, 27, 7, 2 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 2 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a CoherentElastic" ) {

    WHEN( "a string representation is used with an inconsistent number of T "
          "and S(E,T) functions" ) {

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

        REQUIRE_THROWS( CoherentElastic( std::move( boundaries ),
                                         std::move( interpolants ), 
                                         std::move( temperatures ),
                                         std::move( li ),
                                         std::move( energies ),
                                         std::move( s ) ) );
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

  REQUIRE( 1 == chunk.LTHR() );
  REQUIRE( 1 == chunk.elasticScatteringType() );
  REQUIRE( 0 == chunk.LT() );
  REQUIRE( 0 == chunk.temperatureDependenceFlag() );
  REQUIRE( 1 == chunk.NT() );
  REQUIRE( 1 == chunk.numberTemperatures() );

  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 3 == chunk.NP() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 3 == chunk.boundaries()[0] );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );

  REQUIRE( 1 == chunk.temperatures().size() );
  REQUIRE( 293.6 == Approx( chunk.temperatures()[0] ) );

  REQUIRE( 3 == chunk.energies().size() );
  REQUIRE( 1.059427e-3 == Approx( chunk.energies()[0] ) );
  REQUIRE( 3.718355e-3 == Approx( chunk.energies()[1] ) );
  REQUIRE( 4.237708e-3 == Approx( chunk.energies()[2] ) );

  REQUIRE( 0 == chunk.LI().size() );
  REQUIRE( 0 == chunk.temperatureInterpolants().size() );

  REQUIRE( 1 == chunk.thermalScatteringValues().size() );
  REQUIRE( 3 == chunk.thermalScatteringValues()[0].size() );
  REQUIRE( 0.0 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  REQUIRE( 9.364524e-3 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  REQUIRE( 1.548925e-2 == Approx( chunk.thermalScatteringValues()[0][2] ) );

  REQUIRE( 3 == chunk.NC() );
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

  REQUIRE( 1 == chunk.LTHR() );
  REQUIRE( 1 == chunk.elasticScatteringType() );
  REQUIRE( 1 == chunk.LT() );
  REQUIRE( 1 == chunk.temperatureDependenceFlag() );
  REQUIRE( 2 == chunk.NT() );
  REQUIRE( 2 == chunk.numberTemperatures() );

  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 3 == chunk.NP() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 3 == chunk.boundaries()[0] );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );

  REQUIRE( 2 == chunk.temperatures().size() );
  REQUIRE( 293.6 == Approx( chunk.temperatures()[0] ) );
  REQUIRE( 400. == Approx( chunk.temperatures()[1] ) );

  REQUIRE( 3 == chunk.energies().size() );
  REQUIRE( 1.059427e-3 == Approx( chunk.energies()[0] ) );
  REQUIRE( 3.718355e-3 == Approx( chunk.energies()[1] ) );
  REQUIRE( 4.237708e-3 == Approx( chunk.energies()[2] ) );

  REQUIRE( 1 == chunk.LI().size() );
  REQUIRE( 2 == chunk.LI()[0] );
  REQUIRE( 1 == chunk.temperatureInterpolants().size() );
  REQUIRE( 2 == chunk.temperatureInterpolants()[0] );

  REQUIRE( 2 == chunk.thermalScatteringValues().size() );
  REQUIRE( 3 == chunk.thermalScatteringValues()[0].size() );
  REQUIRE( 0.0 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  REQUIRE( 9.364524e-3 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  REQUIRE( 1.548925e-2 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  REQUIRE( 3 == chunk.thermalScatteringValues()[1].size() );
  REQUIRE( 0.5 == Approx( chunk.thermalScatteringValues()[1][0] ) );
  REQUIRE( 8.318414e-3 == Approx( chunk.thermalScatteringValues()[1][1] ) );
  REQUIRE( 1.640584e-2 == Approx( chunk.thermalScatteringValues()[1][2] ) );

  REQUIRE( 5 == chunk.NC() );
}
