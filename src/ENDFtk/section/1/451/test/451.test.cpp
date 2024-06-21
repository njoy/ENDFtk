// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/451.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"
#include "tools/std20/algorithm.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section1451 = section::Type< 1, 451 >;

std::string chunk();
void verifyChunk( const section::Type< 1, 451 >& );
std::string invalidNWD();
std::string invalidNXC();
std::string description();
std::vector< TextRecord > textRecords();
std::vector< DirectoryRecord > index();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 451 >" ) {

  GIVEN( "valid data for a section::Type< 1, 451 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 1001;
      double awr = 0.9991673;
      int lrp = 1;
      int lfi = 2;
      int nlib = 3;
      int nmod = 4;
      double elis = 5.;
      double sta = 6.;
      int lis = 7;
      int liso = 8;
      int nfor = 12;
      double awi = 13.;
      double emax = 14.;
      int lrel = 15;
      int nsub = 17;
      int nver = 18;
      double temp = 19.;
      int ldrv = 21;
      std::string text = description();

      section::Type< 1, 451 > chunk( zaid, awr, lrp, lfi, nlib, nmod,
                                     elis, sta, lis, liso, nfor,
                                     awi, emax, lrel, nsub, nver,
                                     temp, ldrv,
                                     text,
                                     index() );

      THEN( "a section::Type< 1, 451 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 451 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 1, 451 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 125, 1, 451, std::string( sectionString ) );

      section::Type< 1, 451 > chunk = section.parse< 1, 451 >();

      THEN( "a section::Type< 1, 451 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 1, 451 >" ) {

    WHEN( "a string representation of an File 1 Section 451 "
          "with an invalid NWD (comment lines)" ) {

      std::string sectionString = invalidNWD() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
      } // THEN
    } // GIVEN

    WHEN( "a string representation of an File 1 Section 451 "
          "with an invalid NXC (index lines)" ) {

      std::string sectionString = invalidNXC() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ){

        CHECK_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a section::Type< 1, 451 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  // Please note that the numbers in the first 4 records are actually
  // randomly set to test if the correct value is extracted instead of using
  // ENDF legal values
  return
    " 1.001000+3 9.991673-1          1          2          3          4 125 1451     \n"
    " 5.000000+0 6.000000+0          7          8          0         12 125 1451     \n"
    " 1.300000+1 1.400000+1         15          0         17         18 125 1451     \n"
    " 1.900000+1 0.000000+0         21          0          9         10 125 1451     \n"
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n"
    "                      DIST-JAN17                       20170124    125 1451     \n"
    "----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451        101          5 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1         54          4 125 1451     \n"
    "                                3          2         54          4 125 1451     \n"
    "                                3        102         54          5 125 1451     \n"
    "                                4          2        310          4 125 1451     \n"
    "                                6        102        315          4 125 1451     \n"
    "                               33          1          5          5 125 1451     \n"
    "                               33          2         21          5 125 1451     \n"
    "                               33        102         21          5 125 1451     \n";
}

void verifyChunk( const section::Type< 1, 451 >& chunk ) {

  CHECK( 451 == chunk.MT() );
  CHECK( 451 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.LRP() );
  CHECK( 1 == chunk.resonanceParameterFlag() );
  CHECK( 2 == chunk.LFI() );
  CHECK( true == chunk.isFissile() );
  CHECK( 3 == chunk.NLIB() );
  CHECK( 3 == chunk.libraryType() );
  CHECK( 4 == chunk.NMOD() );
  CHECK( 4 == chunk.modificationNumber() );
  CHECK_THAT( 5.0, WithinRel( chunk.ELIS() ) );
  CHECK_THAT( 5.0, WithinRel( chunk.excitationEnergy() ) );
  CHECK_THAT( 6.0, WithinRel( chunk.STA() ) );
  CHECK( true == chunk.isStable() );
  CHECK( 7 == chunk.LIS() );
  CHECK( 7 == chunk.excitedLevel() );
  CHECK( 8 == chunk.LISO() );
  CHECK( 8 == chunk.isomericLevel() );
  CHECK( 12 == chunk.NFOR() );
  CHECK( 12 == chunk.libraryFormat() );
  CHECK_THAT( 13.0, WithinRel( chunk.AWI() ) );
  CHECK_THAT( 13.0, WithinRel( chunk.projectileAtomicMassRatio() ) );
  CHECK_THAT( 14.0, WithinRel( chunk.EMAX() ) );
  CHECK_THAT( 14.0, WithinRel( chunk.maximumEnergy() ) );
  CHECK( 15 == chunk.LREL() );
  CHECK( 15 == chunk.releaseNumber() );
  CHECK( 17 == chunk.NSUB() );
  CHECK( 17 == chunk.subLibrary() );
  CHECK( 18 == chunk.NVER() );
  CHECK( 18 == chunk.versionNumber() );
  CHECK_THAT( 19.0, WithinRel( chunk.TEMP() ) );
  CHECK_THAT( 19.0, WithinRel( chunk.temperature() ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RTOL() ) );
  CHECK_THAT( 0.0, WithinRel( chunk.reconstructionTolerance() ) );
  CHECK( 21 == chunk.LDRV() );
  CHECK( 21 == chunk.derivedMaterial() );
  CHECK( 9 == chunk.NWD() );
  CHECK( njoy::tools::std20::ranges::equal( description(), chunk.description() ) );

  auto entries = index();
  CHECK( entries.size() == chunk.NXC() );
  for ( unsigned int i = 0; i < entries.size(); ++i ) {

    CHECK( entries[i].MF() == chunk.index()[i].MF() );
    CHECK( entries[i].MT() == chunk.index()[i].MT() );
    CHECK( entries[i].NC() == chunk.index()[i].NC() );
    CHECK( entries[i].MOD() == chunk.index()[i].MOD() );
  }

  CHECK( 23 == chunk.NC() );
}

std::string invalidNWD() {
  return
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0         -1         10 125 1451     \n"
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n"
    "                      DIST-JAN17                       20170124    125 1451     \n"
    "----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451        101          5 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1         54          4 125 1451     \n"
    "                                3          2         54          4 125 1451     \n"
    "                                3        102         54          5 125 1451     \n"
    "                                4          2        310          4 125 1451     \n"
    "                                6        102        315          4 125 1451     \n"
    "                               33          1          5          5 125 1451     \n"
    "                               33          2         21          5 125 1451     \n"
    "                               33        102         21          5 125 1451     \n";
}

std::string invalidNXC() {
  return
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          9          0 125 1451     \n"
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n"
    "                      DIST-JAN17                       20170124    125 1451     \n"
    "----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451        101          5 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1         54          4 125 1451     \n"
    "                                3          2         54          4 125 1451     \n"
    "                                3        102         54          5 125 1451     \n"
    "                                4          2        310          4 125 1451     \n"
    "                                6        102        315          4 125 1451     \n"
    "                               33          1          5          5 125 1451     \n"
    "                               33          2         21          5 125 1451     \n"
    "                               33        102         21          5 125 1451     \n";
}

std::string description() {
  return
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         \n"
    "                      DIST-JAN17                       20170124   \n"
    "----ENDF/B-VIII.0     MATERIAL  125                               \n"
    "-----INCIDENT NEUTRON DATA                                        \n"
    "------ENDF-6 FORMAT                                               \n"
    "                                                                  \n"
    " **************************************************************** \n"
    "                                                                  \n"
    " **************************************************************** \n";
}

std::vector< DirectoryRecord > index() {
  return { DirectoryRecord(  1, 451, 101, 5 ),
           DirectoryRecord(  2, 151,   4, 0 ),
           DirectoryRecord(  3,   1,  54, 4 ),
           DirectoryRecord(  3,   2,  54, 4 ),
           DirectoryRecord(  3, 102,  54, 5 ),
           DirectoryRecord(  4,   2, 310, 4 ),
           DirectoryRecord(  6, 102, 315, 4 ),
           DirectoryRecord( 33,   1,   5, 5 ),
           DirectoryRecord( 33,   2,  21, 5 ),
           DirectoryRecord( 33, 102,  21, 5 ) };
}

std::string validSEND() {
  return
    "                                                                   125 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                   125 1  1     \n";
}
