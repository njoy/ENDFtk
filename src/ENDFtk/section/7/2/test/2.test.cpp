#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ScatteringLaw = section::Type< 7, 2 >::ScatteringLaw;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;

// macros don't like multiple template arguments
using section72 = section::Type< 7, 2 >;

std::string chunkWithCoherentElasticAndOneTemperature();
std::string chunkWithCoherentElasticAndTwoTemperatures();
std::string chunkWithIncoherentElastic();
std::string chunkWithInvalidLTHR();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 7, 2 >" ) {

  GIVEN( "valid data for a section::Type< 7, 2 > with coherent elastic "
         "scattering and one temperature" ) {

    double za = 107.;
    double awr = 1.;
    ScatteringLaw law(
        CoherentElastic( 293.6, { 3 }, { 1 },
                         { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                         { 0.0, 9.364524e-3, 1.548925e-2 } ) );

    THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      REQUIRE( 107. == Approx( chunk.ZA() ) );
      REQUIRE( 1. == Approx( chunk.AWR() ) );
      REQUIRE( 1 == chunk.LTHR() );

      auto law =
          std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
      REQUIRE( 0 == law.LT() );
      REQUIRE( 1 == law.NT() );

      REQUIRE( 1 == law.NR() );
      REQUIRE( 3 == law.NP() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 3 == law.boundaries()[0] );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.interpolants()[0] );

      REQUIRE( 1 == law.temperatures().size() );
      REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );

      REQUIRE( 3 == law.energies().size() );
      REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
      REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
      REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

      REQUIRE( 0 == law.LI().size() );

      REQUIRE( 1 == law.thermalScatteringValues().size() );
      REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
      REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
      REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
      REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid section::Type< 7, 2 > with "
         "coherent elastic scattering and one temperature" ) {

    WHEN( "there is a valid SEND record" ){

      std::string sectionString = chunkWithCoherentElasticAndOneTemperature() + 
                                  validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {
        section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 1 == chunk.LTHR() );

        auto law =
            std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 0 == law.LT() );
        REQUIRE( 1 == law.NT() );

        REQUIRE( 1 == law.NR() );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.interpolants()[0] );

        REQUIRE( 1 == law.temperatures().size() );
        REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );

        REQUIRE( 3 == law.energies().size() );
        REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
        REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
        REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

        REQUIRE( 0 == law.LI().size() );

        REQUIRE( 1 == law.thermalScatteringValues().size() );
        REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
        REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
        REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
        REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );

        REQUIRE( 4 == chunk.NC() );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = chunkWithCoherentElasticAndOneTemperature() + 
                                  validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ){
        section::Type< 7, 2 > chunk = section.parse< 7, 2 >( lineNumber );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 1 == chunk.LTHR() );

        auto law =
            std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 0 == law.LT() );
        REQUIRE( 1 == law.NT() );

        REQUIRE( 1 == law.NR() );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.interpolants()[0] );

        REQUIRE( 1 == law.temperatures().size() );
        REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );

        REQUIRE( 3 == law.energies().size() );
        REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
        REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
        REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

        REQUIRE( 0 == law.LI().size() );

        REQUIRE( 1 == law.thermalScatteringValues().size() );
        REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
        REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
        REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
        REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );

        REQUIRE( 4 == chunk.NC() );
      } // THEN
    } // WHEN

    WHEN( "the SEND Record is not valid" ){

      std::string sectionString = chunkWithCoherentElasticAndOneTemperature() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 2 > with coherent elastic "
         "scattering and two temperatures" ) {

    double za = 107.;
    double awr = 1.;
    ScatteringLaw law(
        CoherentElastic( { 3 }, { 1 },
                         { 293.6, 400. },
                         { 2 },
                         { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                         { { 0.0, 9.364524e-3, 1.548925e-2 },
                           { 0.5, 8.318414e-3, 1.640584e-2 } } ) );

    THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      REQUIRE( 107. == Approx( chunk.ZA() ) );
      REQUIRE( 1. == Approx( chunk.AWR() ) );
      REQUIRE( 1 == chunk.LTHR() );

      auto law =
          std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
      REQUIRE( 1 == law.LT() );
      REQUIRE( 2 == law.NT() );

      REQUIRE( 1 == law.NR() );
      REQUIRE( 3 == law.NP() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 3 == law.boundaries()[0] );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.interpolants()[0] );

      REQUIRE( 2 == law.temperatures().size() );
      REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );
      REQUIRE( 400. == Approx( law.temperatures()[1] ) );

      REQUIRE( 3 == law.energies().size() );
      REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
      REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
      REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

      REQUIRE( 1 == law.LI().size() );
      REQUIRE( 2 == law.LI()[0] );

      REQUIRE( 2 == law.thermalScatteringValues().size() );
      REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
      REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
      REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
      REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );
      REQUIRE( 3 == law.thermalScatteringValues()[1].size() );
      REQUIRE( 0.5 == Approx( law.thermalScatteringValues()[1][0] ) );
      REQUIRE( 8.318414e-3 == Approx( law.thermalScatteringValues()[1][1] ) );
      REQUIRE( 1.640584e-2 == Approx( law.thermalScatteringValues()[1][2] ) );

      REQUIRE( 6 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid section::Type< 7, 2 > with "
         "coherent elastic scattering and two temperatures" ) {

    WHEN( "there is a valid SEND record" ){

      std::string sectionString = chunkWithCoherentElasticAndTwoTemperatures() + 
                                  validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ) {
        section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 1 == chunk.LTHR() );

        auto law =
            std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 1 == law.LT() );
        REQUIRE( 2 == law.NT() );

        REQUIRE( 1 == law.NR() );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.interpolants()[0] );

        REQUIRE( 2 == law.temperatures().size() );
        REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );
        REQUIRE( 400. == Approx( law.temperatures()[1] ) );

        REQUIRE( 3 == law.energies().size() );
        REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
        REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
        REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

        REQUIRE( 1 == law.LI().size() );
        REQUIRE( 2 == law.LI()[0] );

        REQUIRE( 2 == law.thermalScatteringValues().size() );
        REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
        REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
        REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
        REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );
        REQUIRE( 3 == law.thermalScatteringValues()[1].size() );
        REQUIRE( 0.5 == Approx( law.thermalScatteringValues()[1][0] ) );
        REQUIRE( 8.318414e-3 == Approx( law.thermalScatteringValues()[1][1] ) );
        REQUIRE( 1.640584e-2 == Approx( law.thermalScatteringValues()[1][2] ) );

        REQUIRE( 6 == chunk.NC() );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = chunkWithCoherentElasticAndTwoTemperatures() + 
                                  validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      
      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ){
        section::Type< 7, 2 > chunk = section.parse< 7, 2 >( lineNumber );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 1 == chunk.LTHR() );

        auto law =
            std::experimental::get< CoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 1 == law.LT() );
        REQUIRE( 2 == law.NT() );

        REQUIRE( 1 == law.NR() );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.interpolants()[0] );

        REQUIRE( 2 == law.temperatures().size() );
        REQUIRE( 293.6 == Approx( law.temperatures()[0] ) );
        REQUIRE( 400. == Approx( law.temperatures()[1] ) );

        REQUIRE( 3 == law.energies().size() );
        REQUIRE( 1.059427e-3 == Approx( law.energies()[0] ) );
        REQUIRE( 3.718355e-3 == Approx( law.energies()[1] ) );
        REQUIRE( 4.237708e-3 == Approx( law.energies()[2] ) );

        REQUIRE( 1 == law.LI().size() );
        REQUIRE( 2 == law.LI()[0] );

        REQUIRE( 2 == law.thermalScatteringValues().size() );
        REQUIRE( 3 == law.thermalScatteringValues()[0].size() );
        REQUIRE( 0.0 == Approx( law.thermalScatteringValues()[0][0] ) );
        REQUIRE( 9.364524e-3 == Approx( law.thermalScatteringValues()[0][1] ) );
        REQUIRE( 1.548925e-2 == Approx( law.thermalScatteringValues()[0][2] ) );
        REQUIRE( 3 == law.thermalScatteringValues()[1].size() );
        REQUIRE( 0.5 == Approx( law.thermalScatteringValues()[1][0] ) );
        REQUIRE( 8.318414e-3 == Approx( law.thermalScatteringValues()[1][1] ) );
        REQUIRE( 1.640584e-2 == Approx( law.thermalScatteringValues()[1][2] ) );

        REQUIRE( 6 == chunk.NC() );
      } // THEN
    } //WHEN

    WHEN( "the SEND Record is not valid" ){

      std::string sectionString = chunkWithCoherentElasticAndTwoTemperatures() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 2 > with incoherent elastic "
         "scattering" ) {

    double za = 107.;
    double awr = 1.;
    ScatteringLaw law(
        IncoherentElastic( 8.198006e+1, { 3 }, { 2 },
                           { 296., 400., 500. },
                           { 8.486993e+0, 9.093191e+0, 9.828159e+0 } ) );

    THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 2 > chunk( za, awr, std::move( law ) );

      REQUIRE( 107. == Approx( chunk.ZA() ) );
      REQUIRE( 1. == Approx( chunk.AWR() ) );
      REQUIRE( 2 == chunk.LTHR() );

      auto law =
          std::experimental::get< IncoherentElastic >( chunk.scatteringLaw() );
      REQUIRE( 8.198006e+1 == Approx( law.SB() ) );
      REQUIRE( 3 == law.NP() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 2 == law.interpolants()[0] );
      REQUIRE( 3 == law.boundaries()[0] );
      REQUIRE( 3 == law.temperatures().size() );
      REQUIRE( 3 == law.debyeWallerValues().size() );
      REQUIRE( 296. == Approx( law.temperatures()[0] ) );
      REQUIRE( 400. == Approx( law.temperatures()[1] ) );
      REQUIRE( 500. == Approx( law.temperatures()[2] ) );
      REQUIRE( 8.486993e+0 == Approx( law.debyeWallerValues()[0] ) );
      REQUIRE( 9.093191e+0 == Approx( law.debyeWallerValues()[1] ) );
      REQUIRE( 9.828159e+0 == Approx( law.debyeWallerValues()[2] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid section::Type< 7, 2 > with "
         "incoherent elastic scattering" ) {

    WHEN( "there is a valid SEND record" ){

      std::string sectionString = chunkWithIncoherentElastic() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
          "tested" ) {
        section::Type< 7, 2 > chunk( head, begin, end, lineNumber, 27 );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 2 == chunk.LTHR() );

        auto law =
          std::experimental::get< IncoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 8.198006e+1 == Approx( law.SB() ) );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.NR() );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 2 == law.interpolants()[0] );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 3 == law.temperatures().size() );
        REQUIRE( 3 == law.debyeWallerValues().size() );
        REQUIRE( 296. == Approx( law.temperatures()[0] ) );
        REQUIRE( 400. == Approx( law.temperatures()[1] ) );
        REQUIRE( 500. == Approx( law.temperatures()[2] ) );
        REQUIRE( 8.486993e+0 == Approx( law.debyeWallerValues()[0] ) );
        REQUIRE( 9.093191e+0 == Approx( law.debyeWallerValues()[1] ) );
        REQUIRE( 9.828159e+0 == Approx( law.debyeWallerValues()[2] ) );

        REQUIRE( 4 == chunk.NC() );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = chunkWithIncoherentElastic() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 7, 2 > can be constructed and members can be "
            "tested" ){
        section::Type< 7, 2 > chunk = section.parse< 7, 2 >( lineNumber );

        REQUIRE( 107. == Approx( chunk.ZA() ) );
        REQUIRE( 1. == Approx( chunk.AWR() ) );
        REQUIRE( 2 == chunk.LTHR() );

        auto law =
          std::experimental::get< IncoherentElastic >( chunk.scatteringLaw() );
        REQUIRE( 8.198006e+1 == Approx( law.SB() ) );
        REQUIRE( 3 == law.NP() );
        REQUIRE( 1 == law.NR() );
        REQUIRE( 1 == law.interpolants().size() );
        REQUIRE( 1 == law.boundaries().size() );
        REQUIRE( 2 == law.interpolants()[0] );
        REQUIRE( 3 == law.boundaries()[0] );
        REQUIRE( 3 == law.temperatures().size() );
        REQUIRE( 3 == law.debyeWallerValues().size() );
        REQUIRE( 296. == Approx( law.temperatures()[0] ) );
        REQUIRE( 400. == Approx( law.temperatures()[1] ) );
        REQUIRE( 500. == Approx( law.temperatures()[2] ) );
        REQUIRE( 8.486993e+0 == Approx( law.debyeWallerValues()[0] ) );
        REQUIRE( 9.093191e+0 == Approx( law.debyeWallerValues()[1] ) );
        REQUIRE( 9.828159e+0 == Approx( law.debyeWallerValues()[2] ) );

        REQUIRE( 4 == chunk.NC() );
      } // THEN
    } // WHEN

    WHEN( "the SEND Record is not valid" ){

      std::string sectionString = chunkWithIncoherentElastic() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section72( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid section::Type< 7, 2 > with coherent elastic scattering and "
         "one temperature" ) {

    std::string string = chunkWithCoherentElasticAndOneTemperature() + 
                         validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 7, 2 > section( head, begin, end, lineNumber, 27 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 27, 7 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid section::Type< 7, 2 > with coherent elastic scattering and "
         "two temperatures" ) {

    std::string string = chunkWithCoherentElasticAndTwoTemperatures() + 
                         validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 7, 2 > section( head, begin, end, lineNumber, 27 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 27, 7 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid section::Type< 7, 2 > with incoherent elastic scattering" ) {

    std::string string = chunkWithIncoherentElastic() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 7, 2 > section( head, begin, end, lineNumber, 27 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 27, 7 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 7, 2 > with an "
         "illegal LTHR" ) {

    std::string sectionString = chunkWithInvalidLTHR() +
                                validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
      
    THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section72( head, begin, end, lineNumber, 27 ) );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkWithCoherentElasticAndOneTemperature() {
  return
    " 1.070000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n";
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

std::string chunkWithIncoherentElastic() {
  return
    " 1.070000+2 1.000000+0          2          0          0          0  27 7  2     \n"
    " 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          2                                              27 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n";
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

