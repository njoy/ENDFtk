#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/2.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ScatteringLaw = section::Type< 7, 2 >::ScatteringLaw;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;
using MixedElastic = section::Type< 7, 2 >::MixedElastic;

// macros don't like multiple template arguments
using section72 = section::Type< 7, 2 >;

std::string chunkWithCoherentElasticAndOneTemperature();
void verifyCoherentElasticWithOneTemperature( const section::Type< 7, 2 >& );
std::string chunkWithCoherentElasticAndTwoTemperatures();
void verifyCoherentElasticWithTwoTemperatures( const section::Type< 7, 2 >& );
std::string chunkWithIncoherentElastic();
void verifyIncoherentElastic( const section::Type< 7, 2 >& );
std::string chunkWithMixedElastic();
void verifyMixedElastic( const section::Type< 7, 2 >& );
std::string chunkWithInvalidLTHR();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 7, 2 >" ) {

  GIVEN( "valid data for a section::Type< 7, 2 > with coherent elastic "
         "scattering and one temperature" ) {

    std::string sectionString = chunkWithCoherentElasticAndOneTemperature() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      double za = 107.;
      double awr = 1.;
      ScatteringLaw law(
          CoherentElastic( 293.6, { 3 }, { 1 },
                           { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                           { 0.0, 9.364524e-3, 1.548925e-2 } ) );

      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyCoherentElasticWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyCoherentElasticWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 2, std::string( sectionString ) );

      section::Type< 7, 2 > chunk = section.parse< 7, 2 >();

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyCoherentElasticWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 2 > with coherent elastic "
         "scattering and two temperatures" ) {

    std::string sectionString = chunkWithCoherentElasticAndTwoTemperatures() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      double za = 107.;
      double awr = 1.;
      ScatteringLaw law(
          CoherentElastic( { 3 }, { 1 },
                           { 293.6, 400. },
                           { 2 },
                           { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                           { { 0.0, 9.364524e-3, 1.548925e-2 },
                             { 0.5, 8.318414e-3, 1.640584e-2 } } ) );

      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyCoherentElasticWithTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyCoherentElasticWithTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 2, std::string( sectionString ) );

      section::Type< 7, 2 > chunk = section.parse< 7, 2 >();

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ){

        verifyCoherentElasticWithTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 2 > with incoherent elastic "
         "scattering" ) {

    std::string sectionString = chunkWithIncoherentElastic() + validSEND();

    WHEN( "the data is given explicitly" ) {

      double za = 107.;
      double awr = 1.;
      ScatteringLaw law(
          IncoherentElastic( 8.198006e+1, { 3 }, { 2 },
                             { 296., 400., 500. },
                             { 8.486993e+0, 9.093191e+0, 9.828159e+0 } ) );

      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyIncoherentElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {

        verifyIncoherentElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 2, std::string( sectionString ) );

      section::Type< 7, 2 > chunk = section.parse< 7, 2 >();

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyIncoherentElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 2 > with mixed elastic "
         "scattering" ) {

    std::string sectionString = chunkWithMixedElastic() + validSEND();

    WHEN( "the data is given explicitly" ) {

      double za = 107.;
      double awr = 1.;
      ScatteringLaw law(
          MixedElastic( CoherentElastic(
                            { 3 }, { 1 }, { 293.6, 800.0 }, { 2 },
                            { 1.059427e-3, 3.718355e-3, 4.237708e-3 },
                            { { 0.0, 9.364524e-3, 1.548925e-2 },
                              { 0.5, 8.318414e-3, 1.640584e-2 } } ),
                        IncoherentElastic( 2.054202, { 2 }, { 2 },
                                           { 293.6, 800. },
                                           { 8.937898, 17.65328 } ) ) );

      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyMixedElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {

        verifyMixedElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 2, std::string( sectionString ) );

      section::Type< 7, 2 > chunk = section.parse< 7, 2 >();

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {

        verifyMixedElastic( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 7, 2 >" ) {

    WHEN( "a string representation of a section::Type< 7, 2 > with coherent "
          "elastic scattering and one temperature with an invalid SEND" ) {

      std::string sectionString = chunkWithCoherentElasticAndOneTemperature() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a section::Type< 7, 2 > with coherent "
          "elastic scattering and two temperatures with an invalid SEND" ) {

      std::string sectionString = chunkWithCoherentElasticAndTwoTemperatures() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a section::Type< 7, 2 > with incoherent "
          "elastic scattering with an invalid SEND" ) {

      std::string sectionString = chunkWithIncoherentElastic() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a section::Type< 7, 2 > with an "
          "illegal LTHR is used" ) {

      std::string sectionString = chunkWithInvalidLTHR() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithCoherentElasticAndOneTemperature() {
  return
    " 1.070000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n";
}

void verifyCoherentElasticWithOneTemperature(
       const section::Type< 7, 2 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 107. == Approx( chunk.ZA() ) );
  CHECK( 1. == Approx( chunk.AWR() ) );
  CHECK( 1. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.LTHR() );
  CHECK( 1 == chunk.elasticScatteringType() );

  auto law =
      std::get< CoherentElastic >( chunk.scatteringLaw() );
  CHECK( 1 == law.LTHR() );
  CHECK( 1 == law.elasticScatteringType() );
  CHECK( 0 == law.LT() );
  CHECK( 0 == law.temperatureDependenceFlag() );
  CHECK( 1 == law.NT() );
  CHECK( 1 == law.numberTemperatures() );
  CHECK( 3 == law.NP() );
  CHECK( 3 == law.numberBraggEdges() );

  CHECK( 1 == law.NR() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 3 == law.boundaries()[0] );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.interpolants()[0] );

  CHECK( 1 == law.temperatures().size() );
  CHECK( 293.6 == Approx( law.temperatures()[0] ) );

  CHECK( 3 == law.energies().size() );
  CHECK( 1.059427e-3 == Approx( law.energies()[0] ) );
  CHECK( 3.718355e-3 == Approx( law.energies()[1] ) );
  CHECK( 4.237708e-3 == Approx( law.energies()[2] ) );

  CHECK( 0 == law.LI().size() );
  CHECK( 0 == law.temperatureInterpolants().size() );

  CHECK( 1 == law.thermalScatteringValues().size() );
  CHECK( 3 == law.thermalScatteringValues()[0].size() );
  CHECK( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithCoherentElasticAndTwoTemperatures() {
  return
    " 1.070000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          3          0  27 7  2     \n"
    " 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n";
}

void verifyCoherentElasticWithTwoTemperatures(
       const section::Type< 7, 2 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 107. == Approx( chunk.ZA() ) );
  CHECK( 1. == Approx( chunk.AWR() ) );
  CHECK( 1. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.LTHR() );
  CHECK( 1 == chunk.elasticScatteringType() );

  auto law =
       std::get< CoherentElastic >( chunk.scatteringLaw() );
  CHECK( 1 == law.LTHR() );
  CHECK( 1 == law.elasticScatteringType() );
  CHECK( 1 == law.LT() );
  CHECK( 1 == law.temperatureDependenceFlag() );
  CHECK( 2 == law.NT() );
  CHECK( 2 == law.numberTemperatures() );
  CHECK( 3 == law.NP() );
  CHECK( 3 == law.numberBraggEdges() );

  CHECK( 1 == law.NR() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 3 == law.boundaries()[0] );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.interpolants()[0] );

  CHECK( 2 == law.temperatures().size() );
  CHECK( 293.6 == Approx( law.temperatures()[0] ) );
  CHECK( 400. == Approx( law.temperatures()[1] ) );

  CHECK( 3 == law.energies().size() );
  CHECK( 1.059427e-3 == Approx( law.energies()[0] ) );
  CHECK( 3.718355e-3 == Approx( law.energies()[1] ) );
  CHECK( 4.237708e-3 == Approx( law.energies()[2] ) );

  CHECK( 1 == law.LI().size() );
  CHECK( 2 == law.LI()[0] );
  CHECK( 1 == law.temperatureInterpolants().size() );
  CHECK( 2 == law.temperatureInterpolants()[0] );

  CHECK( 2 == law.thermalScatteringValues().size() );
  CHECK( 3 == law.thermalScatteringValues()[0].size() );
  CHECK( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );
  CHECK( 3 == law.thermalScatteringValues()[1].size() );
  CHECK( 0.5 == Approx( law.thermalScatteringValues()[1][0] ) );
  CHECK( 8.318414e-3 == Approx( law.thermalScatteringValues()[1][1] ) );
  CHECK( 1.640584e-2 == Approx( law.thermalScatteringValues()[1][2] ) );

  CHECK( 6 == chunk.NC() );
}

std::string chunkWithIncoherentElastic() {
  return
    " 1.070000+2 1.000000+0          2          0          0          0  27 7  2     \n"
    " 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
}

void verifyIncoherentElastic( const section::Type< 7, 2 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 107. == Approx( chunk.ZA() ) );
  CHECK( 1. == Approx( chunk.AWR() ) );
  CHECK( 1. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 2 == chunk.LTHR() );
  CHECK( 2 == chunk.elasticScatteringType() );

  auto law =
       std::get< IncoherentElastic >( chunk.scatteringLaw() );
  CHECK( 2 == law.LTHR() );
  CHECK( 2 == law.elasticScatteringType() );
  CHECK( 8.198006e+1 == Approx( law.SB() ) );
  CHECK( 8.198006e+1 == Approx( law.boundCrossSection() ) );
  CHECK( 3 == law.NP() );
  CHECK( 3 == law.numberTemperatures() );
  CHECK( 1 == law.NR() );
  CHECK( 1 == law.interpolants().size() );
  CHECK( 1 == law.boundaries().size() );
  CHECK( 2 == law.interpolants()[0] );
  CHECK( 3 == law.boundaries()[0] );
  CHECK( 3 == law.temperatures().size() );
  CHECK( 3 == law.debyeWallerValues().size() );
  CHECK( 296. == Approx( law.temperatures()[0] ) );
  CHECK( 400. == Approx( law.temperatures()[1] ) );
  CHECK( 500. == Approx( law.temperatures()[2] ) );
  CHECK( 8.486993e+0 == Approx( law.debyeWallerValues()[0] ) );
  CHECK( 9.093191e+0 == Approx( law.debyeWallerValues()[1] ) );
  CHECK( 9.828159e+0 == Approx( law.debyeWallerValues()[2] ) );

  CHECK( 4 == chunk.NC() );
}

std::string chunkWithMixedElastic() {
  return
    " 1.070000+2 1.000000+0          3          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    " 8.000000+2 0.000000+0          2          0          3          0  27 7  2     \n"
    " 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n"
    " 2.054202+0 0.000000+0          0          0          1          2  27 7  2     \n"
    "          2          2                                              27 7  2     \n"
    " 2.936000+2 8.937898+0 8.000000+2 1.765328+1                        27 7  2     \n";
}

void verifyMixedElastic( const section::Type< 7, 2 >& chunk ) {

  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  CHECK( 107. == Approx( chunk.ZA() ) );
  CHECK( 1. == Approx( chunk.AWR() ) );
  CHECK( 1. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 3 == chunk.LTHR() );
  CHECK( 3 == chunk.elasticScatteringType() );

  auto law = std::get< MixedElastic >( chunk.scatteringLaw() );

  CHECK( 3 == law.LTHR() );
  CHECK( 3 == law.elasticScatteringType() );

  decltype(auto) coherent = law.coherent();

  CHECK( 1 == coherent.LTHR() );
  CHECK( 1 == coherent.elasticScatteringType() );
  CHECK( 1 == coherent.LT() );
  CHECK( 1 == coherent.temperatureDependenceFlag() );
  CHECK( 2 == coherent.NT() );
  CHECK( 2 == coherent.numberTemperatures() );
  CHECK( 3 == coherent.NP() );
  CHECK( 3 == coherent.numberBraggEdges() );

  CHECK( 1 == coherent.NR() );
  CHECK( 1 == coherent.boundaries().size() );
  CHECK( 3 == coherent.boundaries()[0] );
  CHECK( 1 == coherent.interpolants().size() );
  CHECK( 1 == coherent.interpolants()[0] );

  CHECK( 2 == coherent.T().size() );
  CHECK( 2 == coherent.temperatures().size() );
  CHECK( 293.6 == Approx( coherent.T()[0] ) );
  CHECK( 800. == Approx( coherent.T()[1] ) );
  CHECK( 293.6 == Approx( coherent.temperatures()[0] ) );
  CHECK( 800. == Approx( coherent.temperatures()[1] ) );

  CHECK( 3 == coherent.E().size() );
  CHECK( 3 == coherent.energies().size() );
  CHECK( 1.059427e-3 == Approx( coherent.E()[0] ) );
  CHECK( 3.718355e-3 == Approx( coherent.E()[1] ) );
  CHECK( 4.237708e-3 == Approx( coherent.E()[2] ) );
  CHECK( 1.059427e-3 == Approx( coherent.energies()[0] ) );
  CHECK( 3.718355e-3 == Approx( coherent.energies()[1] ) );
  CHECK( 4.237708e-3 == Approx( coherent.energies()[2] ) );

  CHECK( 1 == coherent.LI().size() );
  CHECK( 2 == coherent.LI()[0] );
  CHECK( 1 == coherent.temperatureInterpolants().size() );
  CHECK( 2 == coherent.temperatureInterpolants()[0] );

  CHECK( 2 == coherent.S().size() );
  CHECK( 3 == coherent.S()[0].size() );
  CHECK( 0.0 == Approx( coherent.S()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( coherent.S()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( coherent.S()[0][2] ) );
  CHECK( 3 == coherent.S()[1].size() );
  CHECK( 0.5 == Approx( coherent.S()[1][0] ) );
  CHECK( 8.318414e-3 == Approx( coherent.S()[1][1] ) );
  CHECK( 1.640584e-2 == Approx( coherent.S()[1][2] ) );

  CHECK( 2 == coherent.thermalScatteringValues().size() );
  CHECK( 3 == coherent.thermalScatteringValues()[0].size() );
  CHECK( 0.0 == Approx( coherent.thermalScatteringValues()[0][0] ) );
  CHECK( 9.364524e-3 == Approx( coherent.thermalScatteringValues()[0][1] ) );
  CHECK( 1.548925e-2 == Approx( coherent.thermalScatteringValues()[0][2] ) );
  CHECK( 3 == coherent.thermalScatteringValues()[1].size() );
  CHECK( 0.5 == Approx( coherent.thermalScatteringValues()[1][0] ) );
  CHECK( 8.318414e-3 == Approx( coherent.thermalScatteringValues()[1][1] ) );
  CHECK( 1.640584e-2 == Approx( coherent.thermalScatteringValues()[1][2] ) );

  decltype(auto) incoherent = law.incoherent();

  CHECK( 2 == incoherent.LTHR() );
  CHECK( 2 == incoherent.elasticScatteringType() );
  CHECK( 2.054202 == Approx( incoherent.SB() ) );
  CHECK( 2.054202 == Approx( incoherent.boundCrossSection() ) );
  CHECK( 2 == incoherent.NP() );
  CHECK( 2 == incoherent.NT() );
  CHECK( 2 == incoherent.numberTemperatures() );
  CHECK( 1 == incoherent.NR() );
  CHECK( 1 == incoherent.interpolants().size() );
  CHECK( 1 == incoherent.boundaries().size() );
  CHECK( 2 == incoherent.interpolants()[0] );
  CHECK( 2 == incoherent.boundaries()[0] );
  CHECK( 2 == incoherent.T().size() );
  CHECK( 2 == incoherent.temperatures().size() );
  CHECK( 2 == incoherent.W().size() );
  CHECK( 2 == incoherent.debyeWallerValues().size() );
  CHECK( 293.6 == Approx( incoherent.T()[0] ) );
  CHECK( 800. == Approx( incoherent.T()[1] ) );
  CHECK( 293.6 == Approx( incoherent.temperatures()[0] ) );
  CHECK( 800. == Approx( incoherent.temperatures()[1] ) );
  CHECK( 8.937898 == Approx( incoherent.W()[0] ) );
  CHECK( 17.65328 == Approx( incoherent.W()[1] ) );
  CHECK( 8.937898 == Approx( incoherent.debyeWallerValues()[0] ) );
  CHECK( 17.65328 == Approx( incoherent.debyeWallerValues()[1] ) );

  CHECK( 9 == chunk.NC() );
}

std::string chunkWithInvalidLTHR() {
  return
    " 1.070000+2 1.000000+0          3          0          0          0  27 7  2     \n"
    " 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
}

std::string validSEND() {
  return
    "                                                                    27 7  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                    27 7  4     \n";
}
