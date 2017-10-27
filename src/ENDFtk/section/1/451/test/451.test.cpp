#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1451 = section::Type< 1, 451 >;

std::string baseSection451();
std::string invalidNWDSection451();
std::string invalidNXCSection451();
std::string description();
std::vector< DirectoryRecord > index();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 451 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 451" ) {
    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseSection451() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 451 > can be constructed and members can be tested" ) {
        section::Type< 1, 451 > MF1MT451( head, begin, end, lineNumber, 125 );
        REQUIRE( 451 == MF1MT451.MT() );
        REQUIRE( 451 == MF1MT451.sectionNumber() );
        REQUIRE( 1001 == MF1MT451.ZA() );
        REQUIRE( 0.9991673 == Approx( MF1MT451.atomicWeightRatio() ) );
        REQUIRE( 1 == MF1MT451.LRP() );
        REQUIRE( 2 == MF1MT451.LFI() );
        REQUIRE( 3 == MF1MT451.NLIB() );
        REQUIRE( 4 == MF1MT451.NMOD() );
        REQUIRE( 5.0 == Approx( MF1MT451.ELIS() ) );
        REQUIRE( 6.0 == Approx( MF1MT451.STA() ) );
        REQUIRE( 7 == MF1MT451.LIS() );
        REQUIRE( 8 == MF1MT451.LISO() );
        REQUIRE( 12 == MF1MT451.NFOR() );
        REQUIRE( 13.0 == Approx( MF1MT451.AWI() ) );
        REQUIRE( 14.0 == Approx( MF1MT451.EMAX() ) );
        REQUIRE( 15 == MF1MT451.LREL() );
        REQUIRE( 17 == MF1MT451.NSUB() );
        REQUIRE( 18 == MF1MT451.NVER() );
        REQUIRE( 19.0 == Approx( MF1MT451.TEMP() ) );
        REQUIRE( 21 == MF1MT451.LDRV() );
        REQUIRE( 9 == MF1MT451.NWD() );
        REQUIRE( ranges::equal( description(), MF1MT451.description() ) );

        auto entries = index();
        REQUIRE( entries.size() == MF1MT451.NXC() );
        for ( unsigned int i = 0; i < entries.size(); ++i ) {

          REQUIRE( entries[i].MF() == MF1MT451.index()[i].MF() );
          REQUIRE( entries[i].MT() == MF1MT451.index()[i].MT() );
          REQUIRE( entries[i].NC() == MF1MT451.index()[i].NC() );
          REQUIRE( entries[i].MOD() == MF1MT451.index()[i].MOD() );
        }

        REQUIRE( 23 == MF1MT451.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseSection451() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 451 > can be constructed and members can be tested" ){
        section::Type< 1, 451 > MF1MT451 = section.parse< 1, 451 >( lineNumber );
        REQUIRE( 451 == MF1MT451.MT() );
        REQUIRE( 451 == MF1MT451.sectionNumber() );
        REQUIRE( 1001 == MF1MT451.ZA() );
        REQUIRE( 0.9991673 == Approx( MF1MT451.atomicWeightRatio() ) );
        REQUIRE( 1 == MF1MT451.LRP() );
        REQUIRE( 2 == MF1MT451.LFI() );
        REQUIRE( 3 == MF1MT451.NLIB() );
        REQUIRE( 4 == MF1MT451.NMOD() );
        REQUIRE( 5.0 == Approx( MF1MT451.ELIS() ) );
        REQUIRE( 6.0 == Approx( MF1MT451.STA() ) );
        REQUIRE( 7 == MF1MT451.LIS() );
        REQUIRE( 8 == MF1MT451.LISO() );
        REQUIRE( 12 == MF1MT451.NFOR() );
        REQUIRE( 13.0 == Approx( MF1MT451.AWI() ) );
        REQUIRE( 14.0 == Approx( MF1MT451.EMAX() ) );
        REQUIRE( 15 == MF1MT451.LREL() );
        REQUIRE( 17 == MF1MT451.NSUB() );
        REQUIRE( 18 == MF1MT451.NVER() );
        REQUIRE( 19.0 == Approx( MF1MT451.TEMP() ) );
        REQUIRE( 21 == MF1MT451.LDRV() );
        REQUIRE( 9 == MF1MT451.NWD() );
        REQUIRE( ranges::equal( description(), MF1MT451.description() ) );

        auto entries = index();
        REQUIRE( entries.size() == MF1MT451.NXC() );
        for ( unsigned int i = 0; i < entries.size(); ++i ) {

          REQUIRE( entries[i].MF() == MF1MT451.index()[i].MF() );
          REQUIRE( entries[i].MT() == MF1MT451.index()[i].MT() );
          REQUIRE( entries[i].NC() == MF1MT451.index()[i].NC() );
          REQUIRE( entries[i].MOD() == MF1MT451.index()[i].MOD() );
        }

        REQUIRE( 23 == MF1MT451.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseSection451() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 451 >" ) {
    std::string string = baseSection451() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 451 > section( head, begin, end, lineNumber, 125 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 125, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 451"
         " with an invalid NWD (comment lines)" ){
    std::string sectionString = invalidNWDSection451() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 451"
         " with an invalid NXC (index lines)" ){
    std::string sectionString = invalidNXCSection451() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseSection451() {
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

std::string invalidNWDSection451() {
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

std::string invalidNXCSection451() {
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

