#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/12.hpp"

// other includes
#include "ENDFtk/tree/Tape.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using Multiplicities = section::Type< 12 >::Multiplicities;
using PartialMultiplicity = section::Type< 12 >::PartialMultiplicity;
using TotalMultiplicity = section::Type< 12 >::TotalMultiplicity;
using TransitionProbabilities = section::Type< 12 >::TransitionProbabilities;

std::string chunkWithLO1();
void verifyChunkWithLO1( const section::Type< 12 >& );
std::string chunkWithLO2LG1();
void verifyChunkWithLO2LG1( const section::Type< 12 >& );
std::string chunkWithLO2LG2();
void verifyChunkWithLO2LG2( const section::Type< 12 >& );
std::string invalidChunk();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 12 >" ) {

  GIVEN( "valid data for a section::Type< 12 > with LO = 1" ) {

    std::string sectionString = chunkWithLO1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      double za = 92235.;
      double awr = 2.330250e+2;

      Multiplicities multiplicities( { 0.0, 0.0, 0, 1,
                                       { 2 }, { 2 },
                                       { 1e-5, 3e+7 },
                                       { 8.579050e+0, 1.487778e+1 } } );

      section::Type< 12 > chunk( mt, za, awr, std::move( multiplicities ) );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 12 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 12 > chunk1 = section.parse< 12 >();
      section::Type< 12 > chunk2 = section.parse< 12 >( lineNumber );
      section::Type< 12 > chunk3 = section.parse( 12_c );
      section::Type< 12 > chunk4 = section.parse( 12_c, lineNumber );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO1( chunk1 );
        verifyChunkWithLO1( chunk2 );
        verifyChunkWithLO1( chunk3 );
        verifyChunkWithLO1( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9228, 12 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9228, 12 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9228, 12 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9228, 12 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 12 > with LO = 2 and LG = 1" ) {

    std::string sectionString = chunkWithLO2LG1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 51;
      double za = 92235.;
      double awr = 2.330250e+2;

      TransitionProbabilities probs( 5.170900e+4,
                                     { 1.304000e+4, 7.700000e+1 },
                                     { 2.709000e-1, 7.291000e-1 } );

      section::Type< 12 > chunk( mt, za, awr, std::move( probs ) );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 12 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 12 > chunk1 = section.parse< 12 >();
      section::Type< 12 > chunk2 = section.parse< 12 >( lineNumber );
      section::Type< 12 > chunk3 = section.parse( 12_c );
      section::Type< 12 > chunk4 = section.parse( 12_c, lineNumber );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG1( chunk1 );
        verifyChunkWithLO2LG1( chunk2 );
        verifyChunkWithLO2LG1( chunk3 );
        verifyChunkWithLO2LG1( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9228, 12 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9228, 12 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9228, 12 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9228, 12 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 12 > with LO = 2 amd LG = 2" ) {

    std::string sectionString = chunkWithLO2LG2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 51;
      double za = 92235.;
      double awr = 2.330250e+2;

      TransitionProbabilities probs( 5.170900e+4,
                                     { 1.304000e+4, 7.700000e+1 },
                                     { 2.709000e-1, 7.291000e-1 },
                                     { 3.215434e-3, 3.144654e-3 } );

      section::Type< 12 > chunk( mt, za, awr, std::move( probs ) );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 12 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 12 > chunk1 = section.parse< 12 >();
      section::Type< 12 > chunk2 = section.parse< 12 >( lineNumber );
      section::Type< 12 > chunk3 = section.parse( 12_c );
      section::Type< 12 > chunk4 = section.parse( 12_c, lineNumber );

      THEN( "a section::Type< 12 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLO2LG2( chunk1 );
        verifyChunkWithLO2LG2( chunk2 );
        verifyChunkWithLO2LG2( chunk3 );
        verifyChunkWithLO2LG2( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9228, 12 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9228, 12 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9228, 12 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9228, 12 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 12 >" ) {

    WHEN( "a string representation of a section::Type< 12 > with an invalid LO" ) {

      std::string sectionString = invalidChunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 12 >( head, begin, end,
                                             lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 12 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunkWithLO1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 12 >( head, begin, end,
                                             lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLO1() {
  return
  " 9.223500+4 2.330250+2          1          0          1          0922812 18     \n"
  " 0.000000+0 0.000000+0          0          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}

void verifyChunkWithLO1( const section::Type< 12 >& chunk ) {

  REQUIRE( 18 == chunk.MT() );
  REQUIRE( 18 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 1 == chunk.LO() );
  REQUIRE( 1 == chunk.representation() );

  auto data = std::get< Multiplicities >( chunk.photonProduction() );
  CHECK( std::nullopt == data.totalMultiplicity() );
  CHECK( 1 == data.partialMultiplicities().size() );

  CHECK( 1 == data.NK() );
  CHECK( 1 == data.numberPartials() );
  CHECK( 1 == data.LO() );
  CHECK( 1 == data.representation() );

  auto partial = data.partialMultiplicities()[0];
  CHECK( 0.0 == Approx( partial.EG() ) );
  CHECK( 0.0 == Approx( partial.photonOrBindingEnergy() ) );
  CHECK( 0.0 == Approx( partial.ES() ) );
  CHECK( 0.0 == Approx( partial.levelEnergy() ) );
  CHECK( 0 == partial.LP() );
  CHECK( 0 == partial.primaryPhotonFlag() );
  CHECK( 1 == partial.LF() );
  CHECK( 1 == partial.LAW() );
  CHECK( 2 == partial.NP() );
  CHECK( 1 == partial.NR() );
  CHECK( 1 == partial.interpolants().size() );
  CHECK( 1 == partial.boundaries().size() );
  CHECK( 2 == partial.interpolants()[0] );
  CHECK( 2 == partial.boundaries()[0] );
  CHECK( 2 == partial.energies().size() );
  CHECK( 2 == partial.multiplicities().size() );
  CHECK( 1e-5 == Approx( partial.energies()[0] ) );
  CHECK( 3e+7 == Approx( partial.energies()[1] ) );
  CHECK( 8.579050e+0 == Approx( partial.multiplicities()[0] ) );
  CHECK( 1.487778e+1 == Approx( partial.multiplicities()[1] ) );

  REQUIRE( 4 == chunk.NC() );
}

std::string chunkWithLO2LG1() {
  return
  " 9.223500+4 2.330250+2          2          1          4          0922812 51     \n"
  " 5.170900+4 0.000000+0          0          0          4          2922812 51     \n"
  " 1.304000+4 2.709000-1 7.700000+1 7.291000-1                      922812 51     \n";
}

void verifyChunkWithLO2LG1( const section::Type< 12 >& chunk ) {

  REQUIRE( 51 == chunk.MT() );
  REQUIRE( 51 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 2 == chunk.LO() );
  REQUIRE( 2 == chunk.representation() );

  auto data = std::get< TransitionProbabilities >( chunk.photonProduction() );
  CHECK( 2 == data.LO() );
  CHECK( 2 == data.representation() );

  CHECK( 5.170900e+4 == Approx( data.ES() ) );
  CHECK( 5.170900e+4 == Approx( data.energy() ) );
  CHECK( 1 == data.LG() );
  CHECK( 1 == data.transitionType() );
  CHECK( 2 == data.NT() );
  CHECK( 2 == data.numberTransitions() );

  CHECK( 2 == data.E().size() );
  CHECK( 2 == data.energies().size() );
  CHECK( 2 == data.TP().size() );
  CHECK( 2 == data.transitionProbabilities().size() );
  CHECK( 2 == data.GP().size() );
  CHECK( 2 == data.conditionalProbabilities().size() );
  CHECK( 1.304000e+4 == Approx( data.E()[0] ) );
  CHECK( 7.700000e+1 == Approx( data.E()[1] ) );
  CHECK( 1.304000e+4 == Approx( data.energies()[0] ) );
  CHECK( 7.700000e+1 == Approx( data.energies()[1] ) );
  CHECK( 2.709000e-1 == Approx( data.TP()[0] ) );
  CHECK( 7.291000e-1 == Approx( data.TP()[1] ) );
  CHECK( 2.709000e-1 == Approx( data.transitionProbabilities()[0] ) );
  CHECK( 7.291000e-1 == Approx( data.transitionProbabilities()[1] ) );
  CHECK( 1.0 == Approx( data.GP()[0] ) );
  CHECK( 1.0 == Approx( data.GP()[1] ) );
  CHECK( 1.0 == Approx( data.conditionalProbabilities()[0] ) );
  CHECK( 1.0 == Approx( data.conditionalProbabilities()[1] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string chunkWithLO2LG2() {
  return
  " 9.223500+4 2.330250+2          2          2          4          0922812 51     \n"
  " 5.170900+4 0.000000+0          0          0          6          2922812 51     \n"
  " 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n";
}

void verifyChunkWithLO2LG2( const section::Type< 12 >& chunk ) {

  REQUIRE( 51 == chunk.MT() );
  REQUIRE( 51 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 2 == chunk.LO() );
  REQUIRE( 2 == chunk.representation() );

  auto data = std::get< TransitionProbabilities >( chunk.photonProduction() );
  CHECK( 2 == data.LO() );
  CHECK( 2 == data.representation() );

  CHECK( 5.170900e+4 == Approx( data.ES() ) );
  CHECK( 5.170900e+4 == Approx( data.energy() ) );
  CHECK( 2 == data.LG() );
  CHECK( 2 == data.transitionType() );
  CHECK( 2 == data.NT() );
  CHECK( 2 == data.numberTransitions() );

  CHECK( 2 == data.E().size() );
  CHECK( 2 == data.energies().size() );
  CHECK( 2 == data.TP().size() );
  CHECK( 2 == data.transitionProbabilities().size() );
  CHECK( 2 == data.GP().size() );
  CHECK( 2 == data.conditionalProbabilities().size() );
  CHECK( 1.304000e+4 == Approx( data.E()[0] ) );
  CHECK( 7.700000e+1 == Approx( data.E()[1] ) );
  CHECK( 1.304000e+4 == Approx( data.energies()[0] ) );
  CHECK( 7.700000e+1 == Approx( data.energies()[1] ) );
  CHECK( 2.709000e-1 == Approx( data.TP()[0] ) );
  CHECK( 7.291000e-1 == Approx( data.TP()[1] ) );
  CHECK( 2.709000e-1 == Approx( data.transitionProbabilities()[0] ) );
  CHECK( 7.291000e-1 == Approx( data.transitionProbabilities()[1] ) );
  CHECK( 3.215434e-3 == Approx( data.GP()[0] ) );
  CHECK( 3.144654e-3 == Approx( data.GP()[1] ) );
  CHECK( 3.215434e-3 == Approx( data.conditionalProbabilities()[0] ) );
  CHECK( 3.144654e-3 == Approx( data.conditionalProbabilities()[1] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
  " 9.223500+4 2.330250+2          3          0          1          0922812 18     \n"
  " 0.000000+0 0.000000+0          0          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}

std::string validSEND() {
  return
    "                                                                  922812  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  922812  4     \n";
}
