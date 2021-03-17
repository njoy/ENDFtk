#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/13.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialCrossSection = section::Type< 13 >::PartialCrossSection;
using TotalCrossSection = section::Type< 13 >::TotalCrossSection;

std::string chunk();
void verifyChunk( const section::Type< 13 >& );
std::string invalidChunk();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 13 >" ) {

  GIVEN( "valid data for a section::Type< 13 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      double za = 92235.;
      double awr = 2.330250e+2;

      PartialCrossSection partial = { 0.0, 0.0, 0, 1,
                                      { 2 }, { 2 },
                                      { 1e-5, 3e+7 },
                                      { 8.579050e+0, 1.487778e+1 } };

      section::Type< 13 > chunk( mt, za, awr, std::move( partial ) );

      THEN( "a section::Type< 13 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 13 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 13 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 13 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 13 );

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

      section::Type< 13 > chunk1 = section.parse< 13 >();
      section::Type< 13 > chunk2 = section.parse< 13 >( lineNumber );
      section::Type< 13 > chunk3 = section.parse( 13_c );
      section::Type< 13 > chunk4 = section.parse( 13_c, lineNumber );

      THEN( "a section::Type< 13 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk1 );
        verifyChunk( chunk2 );
        verifyChunk( chunk3 );
        verifyChunk( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1;
        auto output1 = std::back_inserter( buffer1 );
        chunk1.print( output1, 9228, 13 );

        std::string buffer2;
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output2, 9228, 13 );

        std::string buffer3;
        auto output3 = std::back_inserter( buffer3 );
        chunk1.print( output3, 9228, 13 );

        std::string buffer4;
        auto output4 = std::back_inserter( buffer4 );
        chunk1.print( output4, 9228, 13 );

        CHECK( buffer1 == sectionString );
        CHECK( buffer2 == sectionString );
        CHECK( buffer3 == sectionString );
        CHECK( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 13 >" ) {

    WHEN( "a string representation with an invalid section::Type< 13 >" ) {

      std::string sectionString = invalidChunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 13 >( head, begin, end,
                                             lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 13 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 13 >( head, begin, end,
                                             lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
  " 9.223500+4 2.330250+2          0          0          1          0922813 18     \n"
  " 0.000000+0 0.000000+0          0          1          1          2922813 18     \n"
  "          2          2                                            922813 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n";
}

void verifyChunk( const section::Type< 13 >& chunk ) {

  CHECK( 18 == chunk.MT() );
  CHECK( 18 == chunk.sectionNumber() );

  CHECK( 92235. == Approx( chunk.ZA() ) );
  CHECK( 2.330250e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.330250e+2 == Approx( chunk.atomicWeightRatio() ) );

  CHECK( std::nullopt == chunk.totalCrossSection() );
  CHECK( 1 == chunk.photonPartialCrossSections().size() );

  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberPartials() );

  auto partial = chunk.photonPartialCrossSections()[0];
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
  CHECK( 2 == partial.crossSections().size() );
  CHECK( 1e-5 == Approx( partial.energies()[0] ) );
  CHECK( 3e+7 == Approx( partial.energies()[1] ) );
  CHECK( 8.579050e+0 == Approx( partial.crossSections()[0] ) );
  CHECK( 1.487778e+1 == Approx( partial.crossSections()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
  " 9.223500+4 2.330250+2          0          0          1          0922813 18     \n"
  " 0.000000+0 0.000000+0          0          1          2          2922813 18     \n"
  "          2          2                                            922813 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n";
}

std::string validSEND() {
  return
    "                                                                  922813  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  922813  4     \n";
}
