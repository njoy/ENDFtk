#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/455.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

using section1455 = section::Type< 1, 455 >;
using EnergyIndependentConstants = section::Type< 1, 455 >::EnergyIndependentConstants;
using DecayConstants = section::Type< 1, 455 >::DecayConstants;
using EnergyDependentConstants = section::Type< 1, 455 >::EnergyDependentConstants;
using PolynomialMultiplicity = section::PolynomialMultiplicity;
using TabulatedMultiplicity = section::TabulatedMultiplicity;

std::string chunkWithLDG0LNU1();
void verifyChunkWithLDG0LNU1( const section::Type< 1, 455 >& );
std::string chunkWithLDG0LNU2();
void verifyChunkWithLDG0LNU2( const section::Type< 1, 455 >& );
std::string chunkWithLDG1LNU1();
void verifyChunkWithLDG1LNU1( const section::Type< 1, 455 >& );
std::string chunkWithLDG1LNU2();
void verifyChunkWithLDG1LNU2( const section::Type< 1, 455 >& );
std::string invalidLDG();
std::string invalidLNU();
std::string oddNPL();
std::string inconsistentNNF();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 455 >" ) {

  GIVEN( "valid data for a section::Type< 1, 455 > with LDG=0 & LNU = 1" ) {

    std::string sectionString = chunkWithLDG0LNU1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;

      EnergyIndependentConstants constants( { 1.3336e-2, 3.2739e-2,
                                              1.2078e-1, 3.0278e-1,
                                              8.4949e-1, 2.853 } );
      PolynomialMultiplicity multiplicity( { 2.4367, 0.05 } );

      section::Type< 1, 455 > chunk( zaid, awr, std::move( constants ),
                                     std::move( multiplicity ) );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 455 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 1, 455 > chunk = section.parse< 1, 455 >( lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 455 > with LDG=0 & LNU = 2" ) {

    std::string sectionString = chunkWithLDG0LNU2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;

      EnergyIndependentConstants constants( { 1.3336e-2, 3.2739e-2,
                                              1.2078e-1, 3.0278e-1,
                                              8.4949e-1, 2.853 } );
      TabulatedMultiplicity multiplicity(
        { 4 }, { 2 }, { 1e-5, 2.53e-2, 5e-2, 2e+7 },
        { 2.4367, 2.4367, 2.4367, 5.209845 } );

      section::Type< 1, 455 > chunk( zaid, awr, std::move( constants ),
                                     std::move( multiplicity ) );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 455 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 1, 455 > chunk = section.parse< 1, 455 >( lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG0LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 455 > with LDG=1 & LNU = 1" ) {

    std::string sectionString = chunkWithLDG1LNU1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;

      EnergyDependentConstants constants(
          { 2 }, { 4 },
          { DecayConstants( 1e-5, { 1., 2., 3., 4., 5., 6. },
                            { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 } ),
            DecayConstants( 2e+7, { 6., 5., 4., 3., 2., 1. },
                            { 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 } ) } );
      PolynomialMultiplicity multiplicity( { 2.4367, 0.05 } );

      section::Type< 1, 455 > chunk( zaid, awr, std::move( constants ),
                                     std::move( multiplicity ) );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 455 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 1, 455 > chunk = section.parse< 1, 455 >( lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 455 > with LDG=1 & LNU = 2" ) {

    std::string sectionString = chunkWithLDG1LNU2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;

      EnergyDependentConstants constants(
          { 2 }, { 4 },
          { DecayConstants( 1e-5, { 1., 2., 3., 4., 5., 6. },
                            { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 } ),
            DecayConstants( 2e+7, { 6., 5., 4., 3., 2., 1. },
                            { 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 } ) } );
      TabulatedMultiplicity multiplicity(
        { 4 }, { 2 }, { 1e-5, 2.53e-2, 5e-2, 2e+7 },
        { 2.4367, 2.4367, 2.4367, 5.209845 } );

      section::Type< 1, 455 > chunk( zaid, awr, std::move( constants ),
                                     std::move( multiplicity ) );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 455 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 1, 455 > chunk = section.parse< 1, 455 >( lineNumber );

      THEN( "a section::Type< 1, 455 > can be constructed and "
            "members can be tested" ) {

        verifyChunkWithLDG1LNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 1, 455 >" ) {

    WHEN( "a string representation of an File 1 Section 455 "
          "with an invalid LDG" ) {

      std::string sectionString = invalidLDG() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of an File 1 Section 455 "
          "with an invalid LNU" ) {

      std::string sectionString = invalidLNU() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of an File 1 Section 455 "
          "with an odd NPL" ) {

      std::string sectionString = oddNPL() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of an File 1 Section 455 "
          "with inconsistent NNF" ) {

      std::string sectionString = inconsistentNNF() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1455( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLDG0LNU1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

void verifyChunkWithLDG0LNU1( const section::Type< 1, 455 >& chunk ) {

  CHECK( 455 == chunk.MT() );
  CHECK( 455 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 233.0248 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 233.0248 == Approx( chunk.AWR() ) );
  CHECK( 1 == chunk.LNU() );
  CHECK( 1 == chunk.representation() );
  CHECK( 0 == chunk.LDG() );
  CHECK( 0 == chunk.type() );

  decltype(auto) constants = std::get< EnergyIndependentConstants >( chunk.lambda() );

  CHECK( 0 == constants.LDG() );
  CHECK( 0 == constants.type() );
  CHECK( 6 == constants.NNF() );
  CHECK( 6 == constants.numberPrecursors() );

  CHECK( 6 == constants.lambdas().size() );
  CHECK( 6 == constants.decayConstants().size() );
  CHECK( 0.013336 == Approx( constants.lambdas()[0] ) );
  CHECK( 0.032739 == Approx( constants.lambdas()[1] ) );
  CHECK( 0.12078 == Approx( constants.lambdas()[2] ) );
  CHECK( 0.30278 == Approx( constants.lambdas()[3] ) );
  CHECK( 0.84949 == Approx( constants.lambdas()[4] ) );
  CHECK( 2.853000 == Approx( constants.lambdas()[5] ) );
  CHECK( 0.013336 == Approx( constants.decayConstants()[0] ) );
  CHECK( 0.032739 == Approx( constants.decayConstants()[1] ) );
  CHECK( 0.12078 == Approx( constants.decayConstants()[2] ) );
  CHECK( 0.30278 == Approx( constants.decayConstants()[3] ) );
  CHECK( 0.84949 == Approx( constants.decayConstants()[4] ) );
  CHECK( 2.853000 == Approx( constants.decayConstants()[5] ) );

  decltype(auto) nubar = std::get< PolynomialMultiplicity >( chunk.nubar() );

  CHECK( 1 == nubar.LNU() );
  CHECK( 1 == nubar.representation() );

  CHECK( 2 == nubar.NCO() );
  CHECK( 2 == nubar.numberCoefficients() );
  CHECK( 2 == nubar.C().size() );
  CHECK( 2 == nubar.coefficients().size() );
  CHECK( 2.4367 == Approx( nubar.C()[0] ) );
  CHECK( 5e-2 == Approx( nubar.C()[1] ) );
  CHECK( 2.4367 == Approx( nubar.coefficients()[0] ) );
  CHECK( 5e-2 == Approx( nubar.coefficients()[1] ) );

  CHECK( 5 == chunk.NC() );
}

std::string chunkWithLDG0LNU2() {
  return
    " 9.223500+4 2.330248+2          0          2          0          09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

void verifyChunkWithLDG0LNU2( const section::Type< 1, 455 >& chunk ) {

  CHECK( 455 == chunk.MT() );
  CHECK( 455 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 233.0248 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 233.0248 == Approx( chunk.AWR() ) );
  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.representation() );
  CHECK( 0 == chunk.LDG() );
  CHECK( 0 == chunk.type() );

  decltype(auto) constants = std::get< EnergyIndependentConstants >( chunk.lambda() );

  CHECK( 0 == constants.LDG() );
  CHECK( 0 == constants.type() );
  CHECK( 6 == constants.NNF() );
  CHECK( 6 == constants.numberPrecursors() );

  CHECK( 6 == constants.lambdas().size() );
  CHECK( 6 == constants.decayConstants().size() );
  CHECK( 0.013336 == Approx( constants.lambdas()[0] ) );
  CHECK( 0.032739 == Approx( constants.lambdas()[1] ) );
  CHECK( 0.12078 == Approx( constants.lambdas()[2] ) );
  CHECK( 0.30278 == Approx( constants.lambdas()[3] ) );
  CHECK( 0.84949 == Approx( constants.lambdas()[4] ) );
  CHECK( 2.853000 == Approx( constants.lambdas()[5] ) );
  CHECK( 0.013336 == Approx( constants.decayConstants()[0] ) );
  CHECK( 0.032739 == Approx( constants.decayConstants()[1] ) );
  CHECK( 0.12078 == Approx( constants.decayConstants()[2] ) );
  CHECK( 0.30278 == Approx( constants.decayConstants()[3] ) );
  CHECK( 0.84949 == Approx( constants.decayConstants()[4] ) );
  CHECK( 2.853000 == Approx( constants.decayConstants()[5] ) );

  decltype(auto) nubar = std::get< TabulatedMultiplicity >( chunk.nubar() );

  CHECK( 2 == nubar.LNU() );
  CHECK( 2 == nubar.representation() );

  CHECK( 4 == nubar.NP() );
  CHECK( 1 == nubar.NR() );
  CHECK( 1 == nubar.interpolants().size() );
  CHECK( 1 == nubar.boundaries().size() );
  CHECK( 2 == nubar.interpolants()[0] );
  CHECK( 4 == nubar.boundaries()[0] );

  CHECK( 4 == nubar.E().size() );
  CHECK( 4 == nubar.energies().size() );
  CHECK( 4 == nubar.NU().size() );
  CHECK( 4 == nubar.multiplicities().size() );
  CHECK( 1e-5 == Approx( nubar.E()[0] ) );
  CHECK( 0.0253 == Approx( nubar.E()[1] ) );
  CHECK( 0.05 == Approx( nubar.E()[2] ) );
  CHECK( 2e+7 == Approx( nubar.E()[3] ) );
  CHECK( 1e-5 == Approx( nubar.energies()[0] ) );
  CHECK( 0.0253 == Approx( nubar.energies()[1] ) );
  CHECK( 0.05 == Approx( nubar.energies()[2] ) );
  CHECK( 2e+7 == Approx( nubar.energies()[3] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[0] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[1] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[2] ) );
  CHECK( 5.209845 == Approx( nubar.NU()[3] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[0] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[1] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[2] ) );
  CHECK( 5.209845 == Approx( nubar.multiplicities()[3] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkWithLDG1LNU1() {
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

void verifyChunkWithLDG1LNU1( const section::Type< 1, 455 >& chunk ) {

  CHECK( 455 == chunk.MT() );
  CHECK( 455 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 233.0248 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 233.0248 == Approx( chunk.AWR() ) );
  CHECK( 1 == chunk.LNU() );
  CHECK( 1 == chunk.representation() );
  CHECK( 1 == chunk.LDG() );
  CHECK( 1 == chunk.type() );

  decltype(auto) constants = std::get< EnergyDependentConstants >( chunk.lambda() );

  CHECK( 1 == constants.LDG() );
  CHECK( 1 == constants.type() );
  CHECK( 6 == constants.NNF() );
  CHECK( 6 == constants.numberPrecursors() );

  CHECK( 1 == constants.NR() );
  CHECK( 2 == constants.NE() );
  CHECK( 1 == constants.interpolants().size() );
  CHECK( 1 == constants.boundaries().size() );
  CHECK( 4 == constants.interpolants()[0] );
  CHECK( 2 == constants.boundaries()[0] );

  CHECK( 2 == constants.constants().size() );
  CHECK( 1e-5 == Approx( constants.constants()[0].incidentEnergy() ) );
  CHECK( 2e+7 == Approx( constants.constants()[1].incidentEnergy() ) );

  CHECK( 6 == constants.constants()[0].lambdas().size() );
  CHECK( 6 == constants.constants()[0].decayConstants().size() );
  CHECK( 1. == Approx( constants.constants()[0].lambdas()[0] ) );
  CHECK( 2. == Approx( constants.constants()[0].lambdas()[1] ) );
  CHECK( 3. == Approx( constants.constants()[0].lambdas()[2] ) );
  CHECK( 4. == Approx( constants.constants()[0].lambdas()[3] ) );
  CHECK( 5. == Approx( constants.constants()[0].lambdas()[4] ) );
  CHECK( 6. == Approx( constants.constants()[0].lambdas()[5] ) );
  CHECK( 1. == Approx( constants.constants()[0].decayConstants()[0] ) );
  CHECK( 2. == Approx( constants.constants()[0].decayConstants()[1] ) );
  CHECK( 3. == Approx( constants.constants()[0].decayConstants()[2] ) );
  CHECK( 4. == Approx( constants.constants()[0].decayConstants()[3] ) );
  CHECK( 5. == Approx( constants.constants()[0].decayConstants()[4] ) );
  CHECK( 6. == Approx( constants.constants()[0].decayConstants()[5] ) );

  CHECK( 6 == constants.constants()[1].lambdas().size() );
  CHECK( 6 == constants.constants()[1].decayConstants().size() );
  CHECK( 6. == Approx( constants.constants()[1].lambdas()[0] ) );
  CHECK( 5. == Approx( constants.constants()[1].lambdas()[1] ) );
  CHECK( 4. == Approx( constants.constants()[1].lambdas()[2] ) );
  CHECK( 3. == Approx( constants.constants()[1].lambdas()[3] ) );
  CHECK( 2. == Approx( constants.constants()[1].lambdas()[4] ) );
  CHECK( 1. == Approx( constants.constants()[1].lambdas()[5] ) );
  CHECK( 6. == Approx( constants.constants()[1].decayConstants()[0] ) );
  CHECK( 5. == Approx( constants.constants()[1].decayConstants()[1] ) );
  CHECK( 4. == Approx( constants.constants()[1].decayConstants()[2] ) );
  CHECK( 3. == Approx( constants.constants()[1].decayConstants()[3] ) );
  CHECK( 2. == Approx( constants.constants()[1].decayConstants()[4] ) );
  CHECK( 1. == Approx( constants.constants()[1].decayConstants()[5] ) );

  CHECK( 6 == constants.constants()[0].alphas().size() );
  CHECK( 6 == constants.constants()[0].abundances().size() );
  CHECK( 1.1 == Approx( constants.constants()[0].alphas()[0] ) );
  CHECK( 2.1 == Approx( constants.constants()[0].alphas()[1] ) );
  CHECK( 3.1 == Approx( constants.constants()[0].alphas()[2] ) );
  CHECK( 4.1 == Approx( constants.constants()[0].alphas()[3] ) );
  CHECK( 5.1 == Approx( constants.constants()[0].alphas()[4] ) );
  CHECK( 6.1 == Approx( constants.constants()[0].alphas()[5] ) );
  CHECK( 1.1 == Approx( constants.constants()[0].abundances()[0] ) );
  CHECK( 2.1 == Approx( constants.constants()[0].abundances()[1] ) );
  CHECK( 3.1 == Approx( constants.constants()[0].abundances()[2] ) );
  CHECK( 4.1 == Approx( constants.constants()[0].abundances()[3] ) );
  CHECK( 5.1 == Approx( constants.constants()[0].abundances()[4] ) );
  CHECK( 6.1 == Approx( constants.constants()[0].abundances()[5] ) );

  CHECK( 6 == constants.constants()[1].alphas().size() );
  CHECK( 6 == constants.constants()[1].abundances().size() );
  CHECK( 6.1 == Approx( constants.constants()[1].alphas()[0] ) );
  CHECK( 5.1 == Approx( constants.constants()[1].alphas()[1] ) );
  CHECK( 4.1 == Approx( constants.constants()[1].alphas()[2] ) );
  CHECK( 3.1 == Approx( constants.constants()[1].alphas()[3] ) );
  CHECK( 2.1 == Approx( constants.constants()[1].alphas()[4] ) );
  CHECK( 1.1 == Approx( constants.constants()[1].alphas()[5] ) );
  CHECK( 6.1 == Approx( constants.constants()[1].abundances()[0] ) );
  CHECK( 5.1 == Approx( constants.constants()[1].abundances()[1] ) );
  CHECK( 4.1 == Approx( constants.constants()[1].abundances()[2] ) );
  CHECK( 3.1 == Approx( constants.constants()[1].abundances()[3] ) );
  CHECK( 2.1 == Approx( constants.constants()[1].abundances()[4] ) );
  CHECK( 1.1 == Approx( constants.constants()[1].abundances()[5] ) );

  decltype(auto) nubar = std::get< PolynomialMultiplicity >( chunk.nubar() );

  CHECK( 1 == nubar.LNU() );
  CHECK( 1 == nubar.representation() );

  CHECK( 2 == nubar.NCO() );
  CHECK( 2 == nubar.numberCoefficients() );
  CHECK( 2 == nubar.C().size() );
  CHECK( 2 == nubar.coefficients().size() );
  CHECK( 2.4367 == Approx( nubar.C()[0] ) );
  CHECK( 5e-2 == Approx( nubar.C()[1] ) );
  CHECK( 2.4367 == Approx( nubar.coefficients()[0] ) );
  CHECK( 5e-2 == Approx( nubar.coefficients()[1] ) );

  CHECK( 11 == chunk.NC() );
}

std::string chunkWithLDG1LNU2() {
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

void verifyChunkWithLDG1LNU2( const section::Type< 1, 455 >& chunk ) {

  CHECK( 455 == chunk.MT() );
  CHECK( 455 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 233.0248 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 233.0248 == Approx( chunk.AWR() ) );
  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.representation() );
  CHECK( 1 == chunk.LDG() );
  CHECK( 1 == chunk.type() );

  decltype(auto) constants = std::get< EnergyDependentConstants >( chunk.lambda() );

  CHECK( 1 == constants.LDG() );
  CHECK( 1 == constants.type() );
  CHECK( 6 == constants.NNF() );
  CHECK( 6 == constants.numberPrecursors() );

  CHECK( 1 == constants.NR() );
  CHECK( 2 == constants.NE() );
  CHECK( 1 == constants.interpolants().size() );
  CHECK( 1 == constants.boundaries().size() );
  CHECK( 4 == constants.interpolants()[0] );
  CHECK( 2 == constants.boundaries()[0] );

  CHECK( 2 == constants.constants().size() );
  CHECK( 1e-5 == Approx( constants.constants()[0].incidentEnergy() ) );
  CHECK( 2e+7 == Approx( constants.constants()[1].incidentEnergy() ) );

  CHECK( 6 == constants.constants()[0].lambdas().size() );
  CHECK( 6 == constants.constants()[0].decayConstants().size() );
  CHECK( 1. == Approx( constants.constants()[0].lambdas()[0] ) );
  CHECK( 2. == Approx( constants.constants()[0].lambdas()[1] ) );
  CHECK( 3. == Approx( constants.constants()[0].lambdas()[2] ) );
  CHECK( 4. == Approx( constants.constants()[0].lambdas()[3] ) );
  CHECK( 5. == Approx( constants.constants()[0].lambdas()[4] ) );
  CHECK( 6. == Approx( constants.constants()[0].lambdas()[5] ) );
  CHECK( 1. == Approx( constants.constants()[0].decayConstants()[0] ) );
  CHECK( 2. == Approx( constants.constants()[0].decayConstants()[1] ) );
  CHECK( 3. == Approx( constants.constants()[0].decayConstants()[2] ) );
  CHECK( 4. == Approx( constants.constants()[0].decayConstants()[3] ) );
  CHECK( 5. == Approx( constants.constants()[0].decayConstants()[4] ) );
  CHECK( 6. == Approx( constants.constants()[0].decayConstants()[5] ) );

  CHECK( 6 == constants.constants()[1].lambdas().size() );
  CHECK( 6 == constants.constants()[1].decayConstants().size() );
  CHECK( 6. == Approx( constants.constants()[1].lambdas()[0] ) );
  CHECK( 5. == Approx( constants.constants()[1].lambdas()[1] ) );
  CHECK( 4. == Approx( constants.constants()[1].lambdas()[2] ) );
  CHECK( 3. == Approx( constants.constants()[1].lambdas()[3] ) );
  CHECK( 2. == Approx( constants.constants()[1].lambdas()[4] ) );
  CHECK( 1. == Approx( constants.constants()[1].lambdas()[5] ) );
  CHECK( 6. == Approx( constants.constants()[1].decayConstants()[0] ) );
  CHECK( 5. == Approx( constants.constants()[1].decayConstants()[1] ) );
  CHECK( 4. == Approx( constants.constants()[1].decayConstants()[2] ) );
  CHECK( 3. == Approx( constants.constants()[1].decayConstants()[3] ) );
  CHECK( 2. == Approx( constants.constants()[1].decayConstants()[4] ) );
  CHECK( 1. == Approx( constants.constants()[1].decayConstants()[5] ) );

  CHECK( 6 == constants.constants()[0].alphas().size() );
  CHECK( 6 == constants.constants()[0].abundances().size() );
  CHECK( 1.1 == Approx( constants.constants()[0].alphas()[0] ) );
  CHECK( 2.1 == Approx( constants.constants()[0].alphas()[1] ) );
  CHECK( 3.1 == Approx( constants.constants()[0].alphas()[2] ) );
  CHECK( 4.1 == Approx( constants.constants()[0].alphas()[3] ) );
  CHECK( 5.1 == Approx( constants.constants()[0].alphas()[4] ) );
  CHECK( 6.1 == Approx( constants.constants()[0].alphas()[5] ) );
  CHECK( 1.1 == Approx( constants.constants()[0].abundances()[0] ) );
  CHECK( 2.1 == Approx( constants.constants()[0].abundances()[1] ) );
  CHECK( 3.1 == Approx( constants.constants()[0].abundances()[2] ) );
  CHECK( 4.1 == Approx( constants.constants()[0].abundances()[3] ) );
  CHECK( 5.1 == Approx( constants.constants()[0].abundances()[4] ) );
  CHECK( 6.1 == Approx( constants.constants()[0].abundances()[5] ) );

  CHECK( 6 == constants.constants()[1].alphas().size() );
  CHECK( 6 == constants.constants()[1].abundances().size() );
  CHECK( 6.1 == Approx( constants.constants()[1].alphas()[0] ) );
  CHECK( 5.1 == Approx( constants.constants()[1].alphas()[1] ) );
  CHECK( 4.1 == Approx( constants.constants()[1].alphas()[2] ) );
  CHECK( 3.1 == Approx( constants.constants()[1].alphas()[3] ) );
  CHECK( 2.1 == Approx( constants.constants()[1].alphas()[4] ) );
  CHECK( 1.1 == Approx( constants.constants()[1].alphas()[5] ) );
  CHECK( 6.1 == Approx( constants.constants()[1].abundances()[0] ) );
  CHECK( 5.1 == Approx( constants.constants()[1].abundances()[1] ) );
  CHECK( 4.1 == Approx( constants.constants()[1].abundances()[2] ) );
  CHECK( 3.1 == Approx( constants.constants()[1].abundances()[3] ) );
  CHECK( 2.1 == Approx( constants.constants()[1].abundances()[4] ) );
  CHECK( 1.1 == Approx( constants.constants()[1].abundances()[5] ) );

  decltype(auto) nubar = std::get< TabulatedMultiplicity >( chunk.nubar() );

  CHECK( 2 == nubar.LNU() );
  CHECK( 2 == nubar.representation() );

  CHECK( 4 == nubar.NP() );
  CHECK( 1 == nubar.NR() );
  CHECK( 1 == nubar.interpolants().size() );
  CHECK( 1 == nubar.boundaries().size() );
  CHECK( 2 == nubar.interpolants()[0] );
  CHECK( 4 == nubar.boundaries()[0] );

  CHECK( 4 == nubar.E().size() );
  CHECK( 4 == nubar.energies().size() );
  CHECK( 4 == nubar.NU().size() );
  CHECK( 4 == nubar.multiplicities().size() );
  CHECK( 1e-5 == Approx( nubar.E()[0] ) );
  CHECK( 0.0253 == Approx( nubar.E()[1] ) );
  CHECK( 0.05 == Approx( nubar.E()[2] ) );
  CHECK( 2e+7 == Approx( nubar.E()[3] ) );
  CHECK( 1e-5 == Approx( nubar.energies()[0] ) );
  CHECK( 0.0253 == Approx( nubar.energies()[1] ) );
  CHECK( 0.05 == Approx( nubar.energies()[2] ) );
  CHECK( 2e+7 == Approx( nubar.energies()[3] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[0] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[1] ) );
  CHECK( 2.4367 == Approx( nubar.NU()[2] ) );
  CHECK( 5.209845 == Approx( nubar.NU()[3] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[0] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[1] ) );
  CHECK( 2.4367 == Approx( nubar.multiplicities()[2] ) );
  CHECK( 5.209845 == Approx( nubar.multiplicities()[3] ) );

  CHECK( 13 == chunk.NC() );
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

std::string inconsistentNNF() {
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
