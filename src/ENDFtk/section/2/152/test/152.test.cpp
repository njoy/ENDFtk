#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs

std::string chunkWithOneDilution();
void verifyChunkWithOneDilution( const section::Type< 2, 152 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 2, 152 >" ) {

  GIVEN( "valid data for a section::Type< 2, 152 > with one dilution" ) {

    std::string sectionString = chunkWithOneDilution() + validSEND();

/*    WHEN( "the data is given explicitly" ) {

      double za = 94239.;
      double awr = 2.369986e+2;

      section::Type< 2, 152 > chunk( za, awr ) );

      THEN( "a section::Type< 2, 152 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneDilution( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
*/
    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 2, 152 > chunk( head, begin, end, lineNumber, 9437 );

      THEN( "a section::Type< 2, 152 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneDilution( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 12 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a syntaxTree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 2, 152 > chunk1 = section.parse< 2, 152 >();
      section::Type< 2, 152 > chunk2 = section.parse< 2, 152 >( lineNumber );
      section::Type< 2, 152 > chunk3 = section.parse( 12_c );
      section::Type< 2, 152 > chunk4 = section.parse( 12_c, lineNumber );

      THEN( "a section::Type< 2, 152 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneDilution( chunk1 );
        verifyChunkWithOneDilution( chunk2 );
        verifyChunkWithOneDilution( chunk3 );
        verifyChunkWithOneDilution( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9437, 12 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9437, 12 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9437, 12 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9437, 12 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 2, 152 >" ) {

    WHEN( "a string representation of a valid section::Type< 2, 152 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunkWithOneDilution() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section::Type< 2, 152 >( head, begin, end,
                                                 lineNumber, 9437 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOneDilution() {
  return
  "9.423900+4 2.369986+2          1          0          0          29437 2152     "
  "0.000000+0 0.000000+0          5          1        433         729437 2152     "
  "1.00000+10 2.500000+3 2.009120+1 1.343187+1 4.234708+0 2.424629+09437 2152     "
  "2.009120+1 2.550000+3 1.923568+1 1.375705+1 2.725074+0 2.753559+09437 2152     "
  "1.923568+1 2.999999+4 1.366039+1 1.156033+1 1.572008+0 5.280525-19437 2152     "
  "1.366039+1                                                       9437 2152     ";
}

void verifyChunkWithOneDilution( const section::Type< 2, 152 >& chunk ) {

  CHECK( 152 == chunk.MT() );
  CHECK( 152 == chunk.sectionNumber() );

  CHECK( 94239. == Approx( chunk.ZA() ) );
  CHECK( 2.369986e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.369986e+2 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( 1 == chunk.LSSF() );
  CHECK( 2 == chunk.interpolation() );

  CHECK( 5 == chunk.NREAC() );
  CHECK( 5 == chunk.numberReactions() );
  CHECK( 1 == chunk.NSIGZ() );
  CHECK( 1 == chunk.numberDilutions() );

  CHECK( 0. == Approx( chunk.TEMZ() ) );
  CHECK( 0. == Approx( chunk.temperature() ) );

  CHECK( 1 == chunk.SIGZ().size() );
  CHECK( 1 == chunk.dilutions().size() );
  CHECK( 1e-5 == Approx( chunk.SIGZ()[0] ) );
  CHECK( 1e-5 == Approx( chunk.dilutions()[0] ) );

  REQUIRE( 6 == chunk.NC() );
}

std::string validSEND() {
  return
    "                                                                  943712  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  943712  4     \n";
}
