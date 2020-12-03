#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/455.hpp"

#include "ENDFtk/tree/Tape.hpp"

using namespace njoy::ENDFtk;

using section1455 = section::Type< 1, 455 >;
using EnergyIndependentConstants = section::Type< 1, 455 >::EnergyIndependentConstants;
using EnergyDependent = section::Type< 1, 455 >::EnergyDependent;
using PolynomialMultiplicity = section::PolynomialMultiplicity;
using TabulatedMultiplicity = section::TabulatedMultiplicity;

std::string baseLDG0LNU1();
std::string baseLDG0LNU2();
std::string baseLDG1LNU1();
std::string baseLDG1LNU2();
std::string invalidLDG();
std::string invalidLNU();
std::string oddNPL();
std::string inconsistentNPL();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 455 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 455 with LDG=0 & LNU=1" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLDG0LNU1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ) {
        section::Type< 1, 455 > MF1MT455( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::get< EnergyIndependentConstants >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< PolynomialMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyIndependentConstants >
                             ( MF1MT455.lambda() );
        auto lambdas = lambda.lambdas();
        const auto& data = std::get< PolynomialMultiplicity >
                           ( MF1MT455.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 0 == MF1MT455.LDG() );
        REQUIRE( 1 == MF1MT455.LNU() );
        REQUIRE( 0 == lambda.LDG() );
        REQUIRE( 1 == data.LNU() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );
        REQUIRE( 2 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

        REQUIRE( 5 == MF1MT455.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLDG0LNU1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ){
        section::Type< 1, 455 > MF1MT455 = section.parse< 1, 455 >( lineNumber );

        REQUIRE_NOTHROW( std::get< EnergyIndependentConstants >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< PolynomialMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyIndependentConstants >
                             ( MF1MT455.lambda() );
        auto lambdas = lambda.lambdas();
        const auto& data = std::get< PolynomialMultiplicity >
                           ( MF1MT455.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 0 == MF1MT455.LDG() );
        REQUIRE( 1 == MF1MT455.LNU() );
        REQUIRE( 0 == lambda.LDG() );
        REQUIRE( 1 == data.LNU() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );
        REQUIRE( 2 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

        REQUIRE( 5 == MF1MT455.NC() );
      }
    }

    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLDG0LNU1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      }
    }
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 455 with LDG=0 & LNU=2" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLDG0LNU2() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ) {
        section::Type< 1, 455 > MF1MT455( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::get< EnergyIndependentConstants >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< TabulatedMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyIndependentConstants >
                             ( MF1MT455.lambda() );
        auto lambdas = lambda.lambdas();
        const auto& data = std::get< TabulatedMultiplicity >
                           ( MF1MT455.nubar() );
        auto energy = data.E();
        auto nubar = data.NU();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 0 == MF1MT455.LDG() );
        REQUIRE( 2 == MF1MT455.LNU() );
        REQUIRE( 0 == lambda.LDG() );
        REQUIRE( 2 == data.LNU() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 7 == MF1MT455.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLDG0LNU2() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ){
        section::Type< 1, 455 > MF1MT455 = section.parse< 1, 455 >( lineNumber );

        REQUIRE_NOTHROW( std::get< EnergyIndependentConstants >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< TabulatedMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyIndependentConstants >
                             ( MF1MT455.lambda() );
        auto lambdas = lambda.lambdas();
        const auto& data = std::get< TabulatedMultiplicity >
                           ( MF1MT455.nubar() );
        auto energy = data.E();
        auto nubar = data.NU();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 0 == MF1MT455.LDG() );
        REQUIRE( 2 == MF1MT455.LNU() );
        REQUIRE( 0 == lambda.LDG() );
        REQUIRE( 2 == data.LNU() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 7 == MF1MT455.NC() );
      }
    }

    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLDG0LNU2() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 455 > with LDG=0 & LNU=1" ) {
    std::string string = baseLDG0LNU1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 455 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 455 with LDG=1 & LNU=1" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLDG1LNU1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ) {
        section::Type< 1, 455 > MF1MT455( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::get< EnergyDependent >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< PolynomialMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyDependent >
                             ( MF1MT455.lambda() );
        auto l_interpolants = lambda.interpolants();
        auto l_boundaries = lambda.boundaries();
        auto l_constants = lambda.constants();

        const auto& data = std::get< PolynomialMultiplicity >
                           ( MF1MT455.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 1 == MF1MT455.LDG() );
        REQUIRE( 1 == MF1MT455.LNU() );
        REQUIRE( 1 == lambda.LDG() );
        REQUIRE( 1 == data.LNU() );
        REQUIRE( 1 == lambda.NR() );
        REQUIRE( 2 == lambda.NE() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 1 == l_interpolants.size() );
        REQUIRE( 1 == l_boundaries.size() );
        REQUIRE( 4 == l_interpolants[0] );
        REQUIRE( 2 == l_boundaries[0] );
        REQUIRE( 2 == l_constants.size() );
        REQUIRE( 1e-5 == Approx( l_constants[0].energy() ) );
        REQUIRE( 2e+7 == Approx( l_constants[1].energy() ) );
        auto lambdas = l_constants[0].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 1. == Approx( lambdas[0] ) );
        REQUIRE( 2. == Approx( lambdas[1] ) );
        REQUIRE( 3. == Approx( lambdas[2] ) );
        REQUIRE( 4. == Approx( lambdas[3] ) );
        REQUIRE( 5. == Approx( lambdas[4] ) );
        REQUIRE( 6. == Approx( lambdas[5] ) );
        lambdas = l_constants[1].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6. == Approx( lambdas[0] ) );
        REQUIRE( 5. == Approx( lambdas[1] ) );
        REQUIRE( 4. == Approx( lambdas[2] ) );
        REQUIRE( 3. == Approx( lambdas[3] ) );
        REQUIRE( 2. == Approx( lambdas[4] ) );
        REQUIRE( 1. == Approx( lambdas[5] ) );
        auto alphas = l_constants[0].alphas();
        REQUIRE( 6 == alphas.size() );
        REQUIRE( 1.1 == Approx( alphas[0] ) );
        REQUIRE( 2.1 == Approx( alphas[1] ) );
        REQUIRE( 3.1 == Approx( alphas[2] ) );
        REQUIRE( 4.1 == Approx( alphas[3] ) );
        REQUIRE( 5.1 == Approx( alphas[4] ) );
        REQUIRE( 6.1 == Approx( alphas[5] ) );
        alphas = l_constants[1].alphas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6.1 == Approx( alphas[0] ) );
        REQUIRE( 5.1 == Approx( alphas[1] ) );
        REQUIRE( 4.1 == Approx( alphas[2] ) );
        REQUIRE( 3.1 == Approx( alphas[3] ) );
        REQUIRE( 2.1 == Approx( alphas[4] ) );
        REQUIRE( 1.1 == Approx( alphas[5] ) );
        REQUIRE( 2 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

        REQUIRE( 11 == MF1MT455.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLDG1LNU1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ){
        section::Type< 1, 455 > MF1MT455 = section.parse< 1, 455 >( lineNumber );

        REQUIRE_NOTHROW( std::get< EnergyDependent >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< PolynomialMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyDependent >
                             ( MF1MT455.lambda() );
        auto l_interpolants = lambda.interpolants();
        auto l_boundaries = lambda.boundaries();
        auto l_constants = lambda.constants();

        const auto& data = std::get< PolynomialMultiplicity >
                           ( MF1MT455.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 1 == MF1MT455.LDG() );
        REQUIRE( 1 == MF1MT455.LNU() );
        REQUIRE( 1 == lambda.LDG() );
        REQUIRE( 1 == data.LNU() );
        REQUIRE( 1 == lambda.NR() );
        REQUIRE( 2 == lambda.NE() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 1 == l_interpolants.size() );
        REQUIRE( 1 == l_boundaries.size() );
        REQUIRE( 4 == l_interpolants[0] );
        REQUIRE( 2 == l_boundaries[0] );
        REQUIRE( 2 == l_constants.size() );
        REQUIRE( 1e-5 == Approx( l_constants[0].energy() ) );
        REQUIRE( 2e+7 == Approx( l_constants[1].energy() ) );
        auto lambdas = l_constants[0].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 1. == Approx( lambdas[0] ) );
        REQUIRE( 2. == Approx( lambdas[1] ) );
        REQUIRE( 3. == Approx( lambdas[2] ) );
        REQUIRE( 4. == Approx( lambdas[3] ) );
        REQUIRE( 5. == Approx( lambdas[4] ) );
        REQUIRE( 6. == Approx( lambdas[5] ) );
        lambdas = l_constants[1].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6. == Approx( lambdas[0] ) );
        REQUIRE( 5. == Approx( lambdas[1] ) );
        REQUIRE( 4. == Approx( lambdas[2] ) );
        REQUIRE( 3. == Approx( lambdas[3] ) );
        REQUIRE( 2. == Approx( lambdas[4] ) );
        REQUIRE( 1. == Approx( lambdas[5] ) );
        auto alphas = l_constants[0].alphas();
        REQUIRE( 6 == alphas.size() );
        REQUIRE( 1.1 == Approx( alphas[0] ) );
        REQUIRE( 2.1 == Approx( alphas[1] ) );
        REQUIRE( 3.1 == Approx( alphas[2] ) );
        REQUIRE( 4.1 == Approx( alphas[3] ) );
        REQUIRE( 5.1 == Approx( alphas[4] ) );
        REQUIRE( 6.1 == Approx( alphas[5] ) );
        alphas = l_constants[1].alphas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6.1 == Approx( alphas[0] ) );
        REQUIRE( 5.1 == Approx( alphas[1] ) );
        REQUIRE( 4.1 == Approx( alphas[2] ) );
        REQUIRE( 3.1 == Approx( alphas[3] ) );
        REQUIRE( 2.1 == Approx( alphas[4] ) );
        REQUIRE( 1.1 == Approx( alphas[5] ) );
        REQUIRE( 2 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

        REQUIRE( 11 == MF1MT455.NC() );
      }
    }

    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLDG1LNU1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      }
    }
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 455 with LDG=1 & LNU=2" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLDG1LNU2() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ) {
        section::Type< 1, 455 > MF1MT455( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::get< EnergyDependent >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< TabulatedMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyDependent >
                             ( MF1MT455.lambda() );
        auto l_interpolants = lambda.interpolants();
        auto l_boundaries = lambda.boundaries();
        auto l_constants = lambda.constants();

        const auto& data = std::get< TabulatedMultiplicity >
                           ( MF1MT455.nubar() );
        auto energy = data.E();
        auto nubar = data.NU();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 1 == MF1MT455.LDG() );
        REQUIRE( 2 == MF1MT455.LNU() );
        REQUIRE( 1 == lambda.LDG() );
        REQUIRE( 2 == data.LNU() );
        REQUIRE( 1 == lambda.NR() );
        REQUIRE( 2 == lambda.NE() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 1 == l_interpolants.size() );
        REQUIRE( 1 == l_boundaries.size() );
        REQUIRE( 4 == l_interpolants[0] );
        REQUIRE( 2 == l_boundaries[0] );
        REQUIRE( 2 == l_constants.size() );
        REQUIRE( 1e-5 == Approx( l_constants[0].energy() ) );
        REQUIRE( 2e+7 == Approx( l_constants[1].energy() ) );
        auto lambdas = l_constants[0].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 1. == Approx( lambdas[0] ) );
        REQUIRE( 2. == Approx( lambdas[1] ) );
        REQUIRE( 3. == Approx( lambdas[2] ) );
        REQUIRE( 4. == Approx( lambdas[3] ) );
        REQUIRE( 5. == Approx( lambdas[4] ) );
        REQUIRE( 6. == Approx( lambdas[5] ) );
        lambdas = l_constants[1].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6. == Approx( lambdas[0] ) );
        REQUIRE( 5. == Approx( lambdas[1] ) );
        REQUIRE( 4. == Approx( lambdas[2] ) );
        REQUIRE( 3. == Approx( lambdas[3] ) );
        REQUIRE( 2. == Approx( lambdas[4] ) );
        REQUIRE( 1. == Approx( lambdas[5] ) );
        auto alphas = l_constants[0].alphas();
        REQUIRE( 6 == alphas.size() );
        REQUIRE( 1.1 == Approx( alphas[0] ) );
        REQUIRE( 2.1 == Approx( alphas[1] ) );
        REQUIRE( 3.1 == Approx( alphas[2] ) );
        REQUIRE( 4.1 == Approx( alphas[3] ) );
        REQUIRE( 5.1 == Approx( alphas[4] ) );
        REQUIRE( 6.1 == Approx( alphas[5] ) );
        alphas = l_constants[1].alphas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6.1 == Approx( alphas[0] ) );
        REQUIRE( 5.1 == Approx( alphas[1] ) );
        REQUIRE( 4.1 == Approx( alphas[2] ) );
        REQUIRE( 3.1 == Approx( alphas[3] ) );
        REQUIRE( 2.1 == Approx( alphas[4] ) );
        REQUIRE( 1.1 == Approx( alphas[5] ) );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 13 == MF1MT455.NC() );
      }
    }

    WHEN( "there is a tree::Section" ){
      std::string sectionString = baseLDG1LNU2() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and members can be tested" ){
        section::Type< 1, 455 > MF1MT455 = section.parse< 1, 455 >( lineNumber );

        REQUIRE_NOTHROW( std::get< EnergyDependent >
                         ( MF1MT455.lambda() ) );
        REQUIRE_NOTHROW( std::get< TabulatedMultiplicity >
                         ( MF1MT455.nubar() ) );

        const auto& lambda = std::get< EnergyDependent >
                             ( MF1MT455.lambda() );
        auto l_interpolants = lambda.interpolants();
        auto l_boundaries = lambda.boundaries();
        auto l_constants = lambda.constants();

        const auto& data = std::get< TabulatedMultiplicity >
                           ( MF1MT455.nubar() );
        auto energy = data.E();
        auto nubar = data.NU();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 455 == MF1MT455.MT() );
        REQUIRE( 455 == MF1MT455.sectionNumber() );
        REQUIRE( 92235 == MF1MT455.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT455.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT455.AWR() ) );
        REQUIRE( 1 == MF1MT455.LDG() );
        REQUIRE( 2 == MF1MT455.LNU() );
        REQUIRE( 1 == lambda.LDG() );
        REQUIRE( 2 == data.LNU() );
        REQUIRE( 1 == lambda.NR() );
        REQUIRE( 2 == lambda.NE() );
        REQUIRE( 6 == lambda.NNF() );
        REQUIRE( 1 == l_interpolants.size() );
        REQUIRE( 1 == l_boundaries.size() );
        REQUIRE( 4 == l_interpolants[0] );
        REQUIRE( 2 == l_boundaries[0] );
        REQUIRE( 2 == l_constants.size() );
        REQUIRE( 1e-5 == Approx( l_constants[0].energy() ) );
        REQUIRE( 2e+7 == Approx( l_constants[1].energy() ) );
        auto lambdas = l_constants[0].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 1. == Approx( lambdas[0] ) );
        REQUIRE( 2. == Approx( lambdas[1] ) );
        REQUIRE( 3. == Approx( lambdas[2] ) );
        REQUIRE( 4. == Approx( lambdas[3] ) );
        REQUIRE( 5. == Approx( lambdas[4] ) );
        REQUIRE( 6. == Approx( lambdas[5] ) );
        lambdas = l_constants[1].lambdas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6. == Approx( lambdas[0] ) );
        REQUIRE( 5. == Approx( lambdas[1] ) );
        REQUIRE( 4. == Approx( lambdas[2] ) );
        REQUIRE( 3. == Approx( lambdas[3] ) );
        REQUIRE( 2. == Approx( lambdas[4] ) );
        REQUIRE( 1. == Approx( lambdas[5] ) );
        auto alphas = l_constants[0].alphas();
        REQUIRE( 6 == alphas.size() );
        REQUIRE( 1.1 == Approx( alphas[0] ) );
        REQUIRE( 2.1 == Approx( alphas[1] ) );
        REQUIRE( 3.1 == Approx( alphas[2] ) );
        REQUIRE( 4.1 == Approx( alphas[3] ) );
        REQUIRE( 5.1 == Approx( alphas[4] ) );
        REQUIRE( 6.1 == Approx( alphas[5] ) );
        alphas = l_constants[1].alphas();
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 6.1 == Approx( alphas[0] ) );
        REQUIRE( 5.1 == Approx( alphas[1] ) );
        REQUIRE( 4.1 == Approx( alphas[2] ) );
        REQUIRE( 3.1 == Approx( alphas[3] ) );
        REQUIRE( 2.1 == Approx( alphas[4] ) );
        REQUIRE( 1.1 == Approx( alphas[5] ) );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 13 == MF1MT455.NC() );
      }
    }

    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLDG1LNU2() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 455 > with LDG=0 & LNU=1" ) {
    std::string string = baseLDG0LNU1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 455 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 455 > with LDG=0 & LNU=2" ) {
    std::string string = baseLDG0LNU2() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 455 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 455 > with LDG=1 & LNU=1" ) {
    std::string string = baseLDG1LNU1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 455 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 455 > with LDG=1 & LNU=2" ) {
    std::string string = baseLDG1LNU2() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 455 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 455"
         " with an invalid LDG" ){
    std::string sectionString = invalidLDG() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 455"
         " with an invalid LNU" ){
    std::string sectionString = invalidLNU() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 455"
         " with an inconsistent NPL" ){
    std::string sectionString = inconsistentNPL() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 455"
         " with an odd NPL" ){
    std::string sectionString = oddNPL() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseLDG0LNU1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

std::string baseLDG0LNU2() {
  return
    " 9.223500+4 2.330248+2          0          2          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

std::string baseLDG1LNU1() {
  return
    " 9.223500+4 2.330248+2          1          1          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         12          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

std::string baseLDG1LNU2() {
  return
    " 9.223500+4 2.330248+2          1          2          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         12          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

std::string invalidLDG() {
  return
    " 9.223500+4 2.330248+2          2          2          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

std::string invalidLNU() {
  return
    " 9.223500+4 2.330248+2          0          3          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

std::string oddNPL() {
  return
    " 9.223500+4 2.330248+2          1          1          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         11          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0           9228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         11          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0           9228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

std::string inconsistentNPL() {
  return
    " 9.223500+4 2.330248+2          1          1          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 0.000000+0 2.000000+7          0          0         11          09228 1455     \n"
    " 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n"
    " 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0           9228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}
