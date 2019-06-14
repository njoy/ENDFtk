#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Subsection = section::Type< 5 >::Subsection;
using PartialProbability = section::Type< 5 >::PartialProbability;
using MaxwellianFissionSpectrum = section::Type< 5 >::MaxwellianFissionSpectrum;

std::string chunk();
void verifyChunk( const section::Type< 5 >& );
std::string chunkWithNK0();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 5 >" ) {

  GIVEN( "valid data for a section::Type< 5 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      double za = 92235.;
      double awr = 2.330250e+2;

      std::vector< Subsection > partials =
      { { PartialProbability( 7, { 2 }, { 2 },
                                 { 3.25e+6, 2e+7 }, { 1., 1. }, -3e+7 ),
          MaxwellianFissionSpectrum( { 3 }, { 5 },
                                     { 3.25e+6, 1.5e+7, 2e+7 },
                                     { 1.2955e+6, 1.4923e+6, 1.49447e+6 } ) } };

      section::Type< 5 > chunk( mt, za, awr, std::move( partials ) );

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 5 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 5 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 5 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 5 > chunk1 = section.parse< 5 >();
      section::Type< 5 > chunk2 = section.parse< 5 >( lineNumber );
      section::Type< 5 > chunk3 = section.parse( 5_c );
      section::Type< 5 > chunk4 = section.parse( 5_c, lineNumber );

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk1 );
        verifyChunk( chunk2 );
        verifyChunk( chunk3 );
        verifyChunk( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9228, 5 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9228, 5 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9228, 5 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9228, 5 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 5 >" ) {

    WHEN( "a string representation of a section::Type< 5 > with NK=0" ) {

      std::string sectionString = chunkWithNK0() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 5 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 5 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 5 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 9.223500+4 2.330250+2          0          0          1          09228 5 18     \n"
    "-3.000000+7 0.000000+0          0          7          1          29228 5 18     \n"
    "          2          2                                            9228 5 18     \n"
    " 3.250000+6 1.000000+0 2.000000+7 1.000000+0                      9228 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39228 5 18     \n"
    "          3          5                                            9228 5 18     \n"
    " 3.250000+6 1.295500+6 1.500000+7 1.492300+6 2.000000+7 1.494470+69228 5 18     \n";
}

void verifyChunk( const section::Type< 5 >& chunk ) {

  REQUIRE( 18 == chunk.MT() );
  REQUIRE( 18 == chunk.sectionNumber() );

  REQUIRE( 92235. == Approx( chunk.ZA() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 1 == chunk.NK() );
  REQUIRE( 1 == chunk.numberPartialDistributions() );

  const auto& subsection = chunk.distributions()[0];
  REQUIRE( -3e+7 == Approx ( subsection.U() ) );
  REQUIRE( -3e+7 == Approx ( subsection.energyLimitConstant() ) );

  const auto& p = subsection.probability();

  REQUIRE( 7 == p.LF() );
  REQUIRE( 7 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 3.25e+6 == Approx( p.E()[0] ) );
  REQUIRE( 2e+7 == Approx( p.E()[1] ) );
  REQUIRE( 3.25e+6 == Approx( p.energies()[0] ) );
  REQUIRE( 2e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1. == Approx( p.p()[0] ) );
  REQUIRE( 1. == Approx( p.p()[1] ) );
  REQUIRE( 1. == Approx( p.probabilities()[0] ) );
  REQUIRE( 1. == Approx( p.probabilities()[1] ) );

  const auto& d = std::experimental::get< MaxwellianFissionSpectrum >
                                         ( subsection.distribution() );

  REQUIRE( 7 == d.LF() );
  REQUIRE( 7 == d.LAW() );

  REQUIRE( 3 == d.NE() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 5 == d.interpolants()[0] );
  REQUIRE( 3 == d.boundaries()[0] );
  REQUIRE( 3 == d.E().size() );
  REQUIRE( 3 == d.energies().size() );
  REQUIRE( 3 == d.thetas().size() );
  REQUIRE( 3 == d.values().size() );
  REQUIRE( 3.25e+6 == Approx( d.E()[0] ) );
  REQUIRE( 1.5e+7 == Approx( d.E()[1] ) );
  REQUIRE( 2e+7 == Approx( d.E()[2] ) );
  REQUIRE( 3.25e+6 == Approx( d.energies()[0] ) );
  REQUIRE( 1.5e+7 == Approx( d.energies()[1] ) );
  REQUIRE( 2e+7 == Approx( d.energies()[2] ) );
  REQUIRE( 1.2955e+6 == Approx( d.thetas()[0] ) );
  REQUIRE( 1.4923e+6 == Approx( d.thetas()[1] ) );
  REQUIRE( 1.49447e+6 == Approx( d.thetas()[2] ) );
  REQUIRE( 1.2955e+6 == Approx( d.values()[0] ) );
  REQUIRE( 1.4923e+6 == Approx( d.values()[1] ) );
  REQUIRE( 1.49447e+6 == Approx( d.values()[2] ) );

  REQUIRE( 7 == chunk.NC() );
}

std::string chunkWithNK0() {
  return
    " 9.223500+4 2.330250+2          0          0          0          09228 5 18     \n"
    "-3.000000+7 0.000000+0          0          7          1          29228 5 18     \n"
    "          2          2                                            9228 5 18     \n"
    " 3.250000+6 1.000000+0 2.000000+7 1.000000+0                      9228 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39228 5 18     \n"
    "          3          5                                            9228 5 18     \n"
    " 3.250000+6 1.295500+6 1.500000+7 1.492300+6 2.000000+7 1.494470+69228 5 18     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 5  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 5  4     \n";
}
