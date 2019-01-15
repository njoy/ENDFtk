#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1451 = section::Type< 1, 451 >;

std::string chunk();
std::string invalidNWD();
std::string invalidNXC();
std::string description();
std::vector< TextRecord > textRecords();
std::vector< DirectoryRecord > index();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 451 >" ) {

  GIVEN( "valid data for a section::Type< 3 >" ) {

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
    std::array< ControlRecord, 3 > parameters = 
        {{ ControlRecord( elis, sta, lis, liso, 0, nfor ),
           ControlRecord( awi, emax, lrel, 0, nsub, nver ),
           ControlRecord( temp, 0.0, ldrv, 0, 9, 10 ) }};
    std::string text = description();
    std::vector< TextRecord > records = textRecords();

    THEN( "a section::Type< 1, 451 > can be constructed and "
          "members can be tested" ) {

      section::Type< 1, 451 > chunk( zaid, awr, lrp, lfi, nlib, nmod,
                                     elis, sta, lis, liso, nfor,
                                     awi, emax, lrel, nsub, nver,
                                     temp, ldrv,
                                     text,
                                     index() );

      REQUIRE( 451 == chunk.MT() );
      REQUIRE( 1001 == chunk.ZA() );
      REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
      REQUIRE( 1 == chunk.LRP() );
      REQUIRE( 2 == chunk.LFI() );
      REQUIRE( 3 == chunk.NLIB() );
      REQUIRE( 4 == chunk.NMOD() );
      REQUIRE( 5.0 == Approx( chunk.ELIS() ) );
      REQUIRE( 6.0 == Approx( chunk.STA() ) );
      REQUIRE( 7 == chunk.LIS() );
      REQUIRE( 8 == chunk.LISO() );
      REQUIRE( 12 == chunk.NFOR() );
      REQUIRE( 13.0 == Approx( chunk.AWI() ) );
      REQUIRE( 14.0 == Approx( chunk.EMAX() ) );
      REQUIRE( 15 == chunk.LREL() );
      REQUIRE( 17 == chunk.NSUB() );
      REQUIRE( 18 == chunk.NVER() );
      REQUIRE( 19.0 == Approx( chunk.TEMP() ) );
      REQUIRE( 21 == chunk.LDRV() );
      REQUIRE( 9 == chunk.NWD() );
      REQUIRE( ranges::equal( description(), chunk.description() ) );

      auto entries = index();
      REQUIRE( entries.size() == chunk.NXC() );
      for ( unsigned int i = 0; i < entries.size(); ++i ) {

        REQUIRE( entries[i].MF() == chunk.index()[i].MF() );
        REQUIRE( entries[i].MT() == chunk.index()[i].MT() );
        REQUIRE( entries[i].NC() == chunk.index()[i].NC() );
        REQUIRE( entries[i].MOD() == chunk.index()[i].MOD() );
      }

      REQUIRE( 23 == chunk.NC() );
    } // THEN

    THEN( "a section::Type< 1, 451 > can be constructed and "
          "members can be tested" ) {

      section::Type< 1, 451 > chunk( zaid, awr, lrp, lfi, nlib, nmod,
                                     std::move( parameters ),
                                     std::move( records ),
                                     index() );

      REQUIRE( 451 == chunk.MT() );
      REQUIRE( 1001 == chunk.ZA() );
      REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
      REQUIRE( 1 == chunk.LRP() );
      REQUIRE( 2 == chunk.LFI() );
      REQUIRE( 3 == chunk.NLIB() );
      REQUIRE( 4 == chunk.NMOD() );
      REQUIRE( 5.0 == Approx( chunk.ELIS() ) );
      REQUIRE( 6.0 == Approx( chunk.STA() ) );
      REQUIRE( 7 == chunk.LIS() );
      REQUIRE( 8 == chunk.LISO() );
      REQUIRE( 12 == chunk.NFOR() );
      REQUIRE( 13.0 == Approx( chunk.AWI() ) );
      REQUIRE( 14.0 == Approx( chunk.EMAX() ) );
      REQUIRE( 15 == chunk.LREL() );
      REQUIRE( 17 == chunk.NSUB() );
      REQUIRE( 18 == chunk.NVER() );
      REQUIRE( 19.0 == Approx( chunk.TEMP() ) );
      REQUIRE( 21 == chunk.LDRV() );
      REQUIRE( 9 == chunk.NWD() );
      REQUIRE( ranges::equal( description(), chunk.description() ) );

      auto entries = index();
      REQUIRE( entries.size() == chunk.NXC() );
      for ( unsigned int i = 0; i < entries.size(); ++i ) {

        REQUIRE( entries[i].MF() == chunk.index()[i].MF() );
        REQUIRE( entries[i].MT() == chunk.index()[i].MT() );
        REQUIRE( entries[i].NC() == chunk.index()[i].NC() );
        REQUIRE( entries[i].MOD() == chunk.index()[i].MOD() );
      }

      REQUIRE( 23 == chunk.NC() );
    } // THEN
  } // GIVEN

  GIVEN( "a valid string representation of a section::Type< 1, 451 >" ) {

    WHEN( "there is a valid SEND record" ){

      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 451 > can be constructed and "
            "members can be tested" ) {

        section::Type< 1, 451 > chunk( head, begin, end, lineNumber, 125 );

        REQUIRE( 451 == chunk.MT() );
        REQUIRE( 1001 == chunk.ZA() );
        REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
        REQUIRE( 1 == chunk.LRP() );
        REQUIRE( 2 == chunk.LFI() );
        REQUIRE( 3 == chunk.NLIB() );
        REQUIRE( 4 == chunk.NMOD() );
        REQUIRE( 5.0 == Approx( chunk.ELIS() ) );
        REQUIRE( 6.0 == Approx( chunk.STA() ) );
        REQUIRE( 7 == chunk.LIS() );
        REQUIRE( 8 == chunk.LISO() );
        REQUIRE( 12 == chunk.NFOR() );
        REQUIRE( 13.0 == Approx( chunk.AWI() ) );
        REQUIRE( 14.0 == Approx( chunk.EMAX() ) );
        REQUIRE( 15 == chunk.LREL() );
        REQUIRE( 17 == chunk.NSUB() );
        REQUIRE( 18 == chunk.NVER() );
        REQUIRE( 19.0 == Approx( chunk.TEMP() ) );
        REQUIRE( 21 == chunk.LDRV() );
        REQUIRE( 9 == chunk.NWD() );
        REQUIRE( ranges::equal( description(), chunk.description() ) );

        auto entries = index();
        REQUIRE( entries.size() == chunk.NXC() );
        for ( unsigned int i = 0; i < entries.size(); ++i ) {

          REQUIRE( entries[i].MF() == chunk.index()[i].MF() );
          REQUIRE( entries[i].MT() == chunk.index()[i].MT() );
          REQUIRE( entries[i].NC() == chunk.index()[i].NC() );
          REQUIRE( entries[i].MOD() == chunk.index()[i].MOD() );
        }

        REQUIRE( 23 == chunk.NC() );
      } // THEN
    } // WHEN

    WHEN( "there is a syntaxTree::Section" ){

      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 451 > can be constructed and "
            "members can be tested" ) {

        section::Type< 1, 451 > chunk = section.parse< 1, 451 >( lineNumber );

        REQUIRE( 451 == chunk.MT() );
        REQUIRE( 1001 == chunk.ZA() );
        REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
        REQUIRE( 1 == chunk.LRP() );
        REQUIRE( 2 == chunk.LFI() );
        REQUIRE( 3 == chunk.NLIB() );
        REQUIRE( 4 == chunk.NMOD() );
        REQUIRE( 5.0 == Approx( chunk.ELIS() ) );
        REQUIRE( 6.0 == Approx( chunk.STA() ) );
        REQUIRE( 7 == chunk.LIS() );
        REQUIRE( 8 == chunk.LISO() );
        REQUIRE( 12 == chunk.NFOR() );
        REQUIRE( 13.0 == Approx( chunk.AWI() ) );
        REQUIRE( 14.0 == Approx( chunk.EMAX() ) );
        REQUIRE( 15 == chunk.LREL() );
        REQUIRE( 17 == chunk.NSUB() );
        REQUIRE( 18 == chunk.NVER() );
        REQUIRE( 19.0 == Approx( chunk.TEMP() ) );
        REQUIRE( 21 == chunk.LDRV() );
        REQUIRE( 9 == chunk.NWD() );

        REQUIRE( ranges::equal( description(), chunk.description() ) );

        auto entries = index();
        REQUIRE( entries.size() == chunk.NXC() );
        for ( unsigned int i = 0; i < entries.size(); ++i ) {

          REQUIRE( entries[i].MF() == chunk.index()[i].MF() );
          REQUIRE( entries[i].MT() == chunk.index()[i].MT() );
          REQUIRE( entries[i].NC() == chunk.index()[i].NC() );
          REQUIRE( entries[i].MOD() == chunk.index()[i].MOD() );
        }

        REQUIRE( 23 == chunk.NC() );
      } // THEN
    } // WHEN
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){

        REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 451 >" ) {

    std::string string = chunk() + validSEND();
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
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 451"
         " with an invalid NWD (comment lines)" ) {

    std::string sectionString = invalidNWD() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ) {

      REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 451"
         " with an invalid NXC (index lines)" ) {

    std::string sectionString = invalidNXC() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){

      REQUIRE_THROWS( section1451( head, begin, end, lineNumber, 125 ) );
    } // THEN
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

std::vector< TextRecord > textRecords() {
  return
    { { "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         " },
      { "                      DIST-JAN17                       20170124   " },
      { "----ENDF/B-VIII.0     MATERIAL  125                               " },
      { "-----INCIDENT NEUTRON DATA                                        " },
      { "------ENDF-6 FORMAT                                               " },
      { "                                                                  " },
      { " **************************************************************** " },
      { "                                                                  " },
      { " **************************************************************** " } };
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

