// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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
      int zaid = 92235;
      double awr = 2.330250e+2;

      PartialCrossSection partial = { 0.0, 0.0, 0, 1,
                                      { 2 }, { 2 },
                                      { 1e-5, 3e+7 },
                                      { 8.579050e+0, 1.487778e+1 } };

      section::Type< 13 > chunk( mt, zaid, awr, std::move( partial ) );

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

      tree::Section section( 9228, 13, 18, std::string( sectionString ) );

      section::Type< 13 > chunk = section.parse< 13 >();

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

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( std::nullopt == chunk.totalCrossSection() );
  CHECK( 1 == chunk.photonPartialCrossSections().size() );

  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberPhotons() );

  auto partial = chunk.photonPartialCrossSections()[0];
  CHECK_THAT( 0.0, WithinRel( partial.EG() ) );
  CHECK_THAT( 0.0, WithinRel( partial.photonOrBindingEnergy() ) );
  CHECK_THAT( 0.0, WithinRel( partial.ES() ) );
  CHECK_THAT( 0.0, WithinRel( partial.levelEnergy() ) );
  CHECK( 0 == partial.LP() );
  CHECK( 0 == partial.primaryPhotonFlag() );
  CHECK( 1 == partial.LF() );
  CHECK( 1 == partial.LAW() );
  CHECK( 2 == partial.NP() );
  CHECK( 2 == partial.numberPoints() );
  CHECK( 1 == partial.NR() );
  CHECK( 1 == partial.numberInterpolationRegions() );
  CHECK( 1 == partial.INT().size() );
  CHECK( 1 == partial.NBT().size() );
  CHECK( 2 == partial.INT()[0] );
  CHECK( 2 == partial.NBT()[0] );
  CHECK( 1 == partial.interpolants().size() );
  CHECK( 1 == partial.boundaries().size() );
  CHECK( 2 == partial.interpolants()[0] );
  CHECK( 2 == partial.boundaries()[0] );
  CHECK( 2 == partial.energies().size() );
  CHECK( 2 == partial.crossSections().size() );
  CHECK_THAT( 1e-5, WithinRel( partial.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( partial.energies()[1] ) );
  CHECK_THAT( 8.579050e+0, WithinRel( partial.crossSections()[0] ) );
  CHECK_THAT( 1.487778e+1, WithinRel( partial.crossSections()[1] ) );

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
