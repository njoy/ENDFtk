#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/152.hpp"

// other includes
#include "ENDFtk/tree/Tape.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section2152 = section::Type< 2, 152 >;

std::string chunkWithOneDilution();
void verifyChunkWithOneDilution( const section::Type< 2, 152 >& );
std::string invalidChunk();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 2, 152 >" ) {

  GIVEN( "valid data for a section::Type< 2, 152 > with one dilution" ) {

    std::string sectionString = chunkWithOneDilution() + validSEND();

    WHEN( "the data is given explicitly" ) {

      double za = 94239.;
      double awr = 2.369986e+2;
      bool lssf = true;
      int interpolation = 2;
      double temperature = 0.;

      std::vector< double > energies1 = { 2500., 2550., 30000. };
      std::vector< double > total = { 2.009120e+1, 1.923568e+1, 1.366039e+1 };
      std::vector< double > elastic = { 1.343187e+1, 1.375705e+1, 1.156033e+1 };
      std::vector< double > fission = { 4.234708e+0, 2.725074e+0, 1.572008e+0 };
      std::vector< double > capture = { 2.424629e+0, 2.753559e+0, 5.280525e-1 };
      std::vector< double > cwTotal = { 2.009120e+1, 1.923568e+1, 1.366039e+1 };

      std::vector< double > dilutions = { 1e+10 };
      std::vector< double > energies2 = { 2500., 2550., 30000. };
      std::vector< std::vector< double > > dilTotal =
          { { 2.009120e+1 }, { 1.923568e+1 }, { 1.366039e+1 } };
      std::vector< std::vector< double > > dilElastic =
          { { 1.343187e+1 }, { 1.375705e+1 }, { 1.156033e+1 } };
      std::vector< std::vector< double > > dilFission =
          { { 4.234708e+0 }, { 2.725074e+0 }, { 1.572008e+0 } };
      std::vector< std::vector< double > > dilCapture =
          { { 2.424629e+0 }, { 2.753559e+0 }, { 5.280525e-1 } };
      std::vector< std::vector< double > > dilCwTotal =
          { { 2.009120e+1 }, { 1.923568e+1 }, { 1.366039e+1 } };

      section::Type< 2, 152 > chunk1( za, awr, lssf, interpolation, temperature,
                                      std::move( energies1 ), std::move( total ),
                                      std::move( elastic ), std::move( fission ),
                                      std::move( capture ), std::move( cwTotal ) );

      section::Type< 2, 152 > chunk2( za, awr, lssf, interpolation, temperature,
                                      std::move( dilutions ),
                                      std::move( energies2 ), std::move( dilTotal ),
                                      std::move( dilElastic ), std::move( dilFission ),
                                      std::move( dilCapture ), std::move( dilCwTotal ) );

      THEN( "a section::Type< 2, 152 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneDilution( chunk1 );
        verifyChunkWithOneDilution( chunk2 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9437, 2 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk2.print( output2, 9437, 2 );

        CHECK( buffer1 == sectionString );
        CHECK( buffer2 == sectionString );
      } // THEN
    } // WHEN

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
        chunk.print( output, 9437, 2 );

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

      section::Type< 2, 152 > chunk1 = section.parse< 2, 152 >();
      section::Type< 2, 152 > chunk2 = section.parse< 2, 152 >( lineNumber );
      section::Type< 2, 152 > chunk3 = section.parse( 2_c, 152_c );
      section::Type< 2, 152 > chunk4 = section.parse( 2_c, 152_c, lineNumber );

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
        chunk1.print( output1, 9437, 2 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk2.print( output2, 9437, 2 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk3.print( output3, 9437, 2 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk4.print( output4, 9437, 2 );

        REQUIRE( buffer1 == sectionString );
        REQUIRE( buffer2 == sectionString );
        REQUIRE( buffer3 == sectionString );
        REQUIRE( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 2, 152 >" ) {

    WHEN( "a string representation with an invalid section::Type< 2, 152 >" ) {

      std::string sectionString = invalidChunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section2152( head, begin, end, lineNumber, 9437 ) );
      } // THEN
    } // WHEN

    WHEN( "data with the wrong size is used" ) {

      double za = 94239.;
      double awr = 2.369986e+2;
      bool lssf = true;
      int interpolation = 2;
      double temperature = 0.;

      std::vector< double > dilutions = { 1e+10 };
      std::vector< double > wrong = { 2500., 30000. };
      std::vector< std::vector< double > > dilTotal =
          { { 2.009120e+1 }, { 1.923568e+1 }, { 1.366039e+1 } };
      std::vector< std::vector< double > > dilElastic =
          { { 1.343187e+1 }, { 1.375705e+1 }, { 1.156033e+1 } };
      std::vector< std::vector< double > > dilFission =
          { { 4.234708e+0 }, { 2.725074e+0 }, { 1.572008e+0 } };
      std::vector< std::vector< double > > dilCapture =
          { { 2.424629e+0 }, { 2.753559e+0 }, { 5.280525e-1 } };
      std::vector< std::vector< double > > dilCwTotal =
          { { 2.009120e+1 }, { 1.923568e+1 }, { 1.366039e+1 } };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section2152(
                            za, awr, lssf, interpolation, temperature,
                            std::move( dilutions ),
                            std::move( wrong ), std::move( dilTotal ),
                            std::move( dilElastic ), std::move( dilFission ),
                            std::move( dilCapture ), std::move( dilCwTotal ) ) );
      } // THEN
    } // WHEN

    WHEN( "data with the wrong size is used in the no dilution constructor" ) {

      double za = 94239.;
      double awr = 2.369986e+2;
      bool lssf = true;
      int interpolation = 2;
      double temperature = 0.;

      std::vector< double > wrong = { 2500., 2550. };
      std::vector< double > total = { 2.009120e+1, 1.923568e+1, 1.366039e+1 };
      std::vector< double > elastic = { 1.343187e+1, 1.375705e+1, 1.156033e+1 };
      std::vector< double > fission = { 4.234708e+0, 2.725074e+0, 1.572008e+0 };
      std::vector< double > capture = { 2.424629e+0, 2.753559e+0, 5.280525e-1 };
      std::vector< double > cwTotal = { 2.009120e+1, 1.923568e+1, 1.366039e+1 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section2152(
                            za, awr, lssf, interpolation, temperature,
                            std::move( wrong ), std::move( total ),
                            std::move( elastic ), std::move( fission ),
                            std::move( capture ), std::move( cwTotal ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 2, 152 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunkWithOneDilution() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section2152( head, begin, end, lineNumber, 9437 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOneDilution() {
  return
    " 9.423900+4 2.369986+2          1          0          0          29437 2152     \n"
    " 0.000000+0 0.000000+0          5          1         19          39437 2152     \n"
    " 1.00000+10 2.500000+3 2.009120+1 1.343187+1 4.234708+0 2.424629+09437 2152     \n"
    " 2.009120+1 2.550000+3 1.923568+1 1.375705+1 2.725074+0 2.753559+09437 2152     \n"
    " 1.923568+1 3.000000+4 1.366039+1 1.156033+1 1.572008+0 5.280525-19437 2152     \n"
    " 1.366039+1                                                       9437 2152     \n";
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
  CHECK( 3 == chunk.NUNR() );
  CHECK( 3 == chunk.numberEnergies() );

  CHECK( 0. == Approx( chunk.TEMZ() ) );
  CHECK( 0. == Approx( chunk.temperature() ) );

  CHECK( 1 == chunk.SIGZ().size() );
  CHECK( 1 == chunk.dilutions().size() );
  CHECK( 1e+10 == Approx( chunk.SIGZ()[0] ) );
  CHECK( 1e+10 == Approx( chunk.dilutions()[0] ) );

  CHECK( 3 == chunk.EUNR().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 2500. == Approx( chunk.EUNR()[0] ) );
  CHECK( 2550. == Approx( chunk.EUNR()[1] ) );
  CHECK( 30000. == Approx( chunk.EUNR()[2] ) );
  CHECK( 2500. == Approx( chunk.energies()[0] ) );
  CHECK( 2550. == Approx( chunk.energies()[1] ) );
  CHECK( 30000. == Approx( chunk.energies()[2] ) );

  CHECK( 3 == chunk.total().size() );
  CHECK( 3 == chunk.elastic().size() );
  CHECK( 3 == chunk.fission().size() );
  CHECK( 3 == chunk.capture().size() );
  CHECK( 1 == chunk.total()[0].size() );
  CHECK( 2.009120e+1 == Approx( chunk.total()[0][0] ) );
  CHECK( 1.923568e+1 == Approx( chunk.total()[1][0] ) );
  CHECK( 1.366039e+1 == Approx( chunk.total()[2][0] ) );
  CHECK( 1.343187e+1 == Approx( chunk.elastic()[0][0] ) );
  CHECK( 1.375705e+1 == Approx( chunk.elastic()[1][0] ) );
  CHECK( 1.156033e+1 == Approx( chunk.elastic()[2][0] ) );
  CHECK( 4.234708e+0 == Approx( chunk.fission()[0][0] ) );
  CHECK( 2.725074e+0 == Approx( chunk.fission()[1][0] ) );
  CHECK( 1.572008e+0 == Approx( chunk.fission()[2][0] ) );
  CHECK( 2.424629e+0 == Approx( chunk.capture()[0][0] ) );
  CHECK( 2.753559e+0 == Approx( chunk.capture()[1][0] ) );
  CHECK( 5.280525e-1 == Approx( chunk.capture()[2][0] ) );
  CHECK( 2.009120e+1 == Approx( chunk.currentWeightedTotal()[0][0] ) );
  CHECK( 1.923568e+1 == Approx( chunk.currentWeightedTotal()[1][0] ) );
  CHECK( 1.366039e+1 == Approx( chunk.currentWeightedTotal()[2][0] ) );

  REQUIRE( 6 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 9.423900+4 2.369986+2          1          0          0          29437 2152     \n"
    " 0.000000+0 0.000000+0          5          2         19          39437 2152     \n"
    " 1.00000+10 2.500000+3 2.009120+1 1.343187+1 4.234708+0 2.424629+09437 2152     \n"
    " 2.009120+1 2.550000+3 1.923568+1 1.375705+1 2.725074+0 2.753559+09437 2152     \n"
    " 1.923568+1 3.000000+4 1.366039+1 1.156033+1 1.572008+0 5.280525-19437 2152     \n"
    " 1.366039+1                                                       9437 2152     \n";
}

std::string validSEND() {
  return
    "                                                                  9437 2  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9437 2  4     \n";
}
