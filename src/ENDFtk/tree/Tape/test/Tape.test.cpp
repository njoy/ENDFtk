#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/tree/Tape.hpp"

// other includes
#include "header-utilities/copy.hpp"
#include "header-utilities/slurpFileToMemory.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
std::string chunkMaterial125();
std::string chunkTPID();
std::string validTEND();
std::string invalidTEND();

SCENARIO( "tree::Tape" ) {

  GIVEN( "an empty tree::Tape" ) {

    WHEN( "it is created" ) {

      tree::Tape tape( TapeIdentification( "this is my tape identification" ) );

      THEN( "it is empty except for the tape ID" ) {

        auto numbers = tape.materialNumbers();
        CHECK( 0 == tape.size() );
        CHECK( 0 == numbers.size() );

        CHECK( "this is my tape identification                                       0 0  0     \n"
               "                                                                    -1 0  0     \n" == tape.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::Tape" ) {

    std::string tapeString = chunk() + validTEND();

    WHEN( "the data is read from a string/stream with a valid TEND" ) {

      tree::Tape tape( tapeString );

      THEN( "the tape is populated correctly" ) {

        CHECK( true == tape.hasMaterial( 125 ) );
        CHECK( true == tape.hasMAT( 125 ) );
        CHECK( 1 == ranges::distance( tape.MAT( 125 ) ) );
        CHECK( 1 == ranges::distance( tape.MAT( 125 ) ) );

        CHECK( false == tape.hasMaterial( 128 ) );
        CHECK( false == tape.hasMAT( 128 ) );

        auto materialNumbers = tape.materialNumbers();
        CHECK( 1 == tape.size() );
        CHECK( 1 == materialNumbers.size() );

        auto iter = std::begin( materialNumbers );
        CHECK( 125 == *iter ); ++iter;

        CHECK( tapeString == tape.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid tree tape" ) {

    std::string tapeString = chunk() + validTEND();
    tree::Tape tape( tapeString );

    WHEN( "a material with the same MAT is inserted" ) {

      std::string materialString = chunkMaterial125();
      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      tape.insert( std::move( material ) );

      THEN( "the tape is populated correctly" ) {

        CHECK( true == tape.hasMaterial( 125 ) );
        CHECK( true == tape.hasMAT( 125 ) );
        CHECK( 2 == ranges::distance( tape.MAT( 125 ) ) );
        CHECK( 2 == ranges::distance( tape.MAT( 125 ) ) );

        CHECK( false == tape.hasMaterial( 128 ) );
        CHECK( false == tape.hasMAT( 128 ) );

        auto materialNumbers = tape.materialNumbers();
        CHECK( 2 == tape.size() );
        CHECK( 1 == materialNumbers.size() );

        auto iter = std::begin( materialNumbers );
        CHECK( 125 == *iter ); ++iter;

        CHECK( chunk() + chunkMaterial125() + validTEND() == tape.content() );
      } // THEN
    } // WHEN

    WHEN( "replacing a material" ) {

      std::string materialString = chunkMaterial125();
      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      tape.replace( std::move( material ) );

      THEN( "the tape is populated correctly" ) {

        CHECK( true == tape.hasMaterial( 125 ) );
        CHECK( true == tape.hasMAT( 125 ) );
        CHECK( 1 == ranges::distance( tape.MAT( 125 ) ) );
        CHECK( 1 == ranges::distance( tape.MAT( 125 ) ) );

        CHECK( false == tape.hasMaterial( 128 ) );
        CHECK( false == tape.hasMAT( 128 ) );

        auto materialNumbers = tape.materialNumbers();
        CHECK( 1 == tape.size() );
        CHECK( 1 == materialNumbers.size() );

        auto iter = std::begin( materialNumbers );
        CHECK( 125 == *iter ); ++iter;

        CHECK( chunkTPID() + chunkMaterial125() + validTEND() == tape.content() );
      } // THEN
    } // WHEN

    WHEN( "a material is removed" ) {

      tape.remove( 125 );

      THEN( "the tape is populated correctly" ) {

        CHECK( false == tape.hasMaterial( 125 ) );
        CHECK( false == tape.hasMAT( 125 ) );

        CHECK( false == tape.hasMaterial( 128 ) );
        CHECK( false == tape.hasMAT( 128 ) );

        auto materialNumbers = tape.materialNumbers();
        CHECK( 0 == tape.size() );
        CHECK( 0 == materialNumbers.size() );

        CHECK( chunkTPID() + validTEND() == tape.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a tree::Tape" ) {

    WHEN( "the data is read from a string/stream with an invalid TEND" ) {

      std::string tapeString = chunk() + invalidTEND();

      CHECK_THROWS( tree::Tape{ std::move( tapeString ) } );
    } // WHEN

    WHEN( "the data is read from a string/stream without TEND" ) {

      std::string tapeString = chunk();

      CHECK_THROWS( tree::Tape{ std::move( tapeString ) } );
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkTPID() {

  return
    "this is my tape identification                                       0 0  0     \n";
}

std::string chunk() {

  return
    "this is my tape identification                                       0 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          4 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         16          0 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1          4          0 125 1451     \n"
    "                                3          5          4          0 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n"
    "                                                                   125 2  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  1     \n"
    "          2          2                                             125 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n"
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n"
    "                                                                     0 0  0     \n";
}

std::string chunkMaterial125() {

  return
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          4 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         16          0 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1          4          0 125 1451     \n"
    "                                3          5          4          0 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n"
    "                                                                   125 2  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  1     \n"
    "          2          2                                             125 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n"
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n"
    "                                                                     0 0  0     \n";
}

std::string chunkMaterial128() {

  return
    " 1.001000+3 9.991673-1          0          0          0          3 128 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 128 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 128 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          4 128 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          128 1451     \n"
    "                      DIST-DEC06                       20111222    128 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                128 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         128 1451     \n"
    "------ENDF-6 FORMAT                                                128 1451     \n"
    "                                                                   128 1451     \n"
    " ****************************************************************  128 1451     \n"
    " ****************************************************************  128 1451     \n"
    "                                1        451         16          0 128 1451     \n"
    "                                2        151          4          0 128 1451     \n"
    "                                3          1          4          0 128 1451     \n"
    "                                3          5          4          0 128 1451     \n"
    "                                                                   128 1  0     \n"
    "                                                                   128 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          1          0 128 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 128 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 128 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 128 2151     \n"
    "                                                                   128 2  0     \n"
    "                                                                   128 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 128 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 128 3  1     \n"
    "          2          2                                             128 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       128 3  1     \n"
    "                                                                   128 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 128 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 128 3  5     \n"
    "          2          2                                             128 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       128 3  5     \n"
    "                                                                   128 3  0     \n"
    "                                                                   128 0  0     \n"
    "                                                                     0 0  0     \n";
}

std::string validTEND(){
  return "                                                                    -1 0  0     \n";
}

std::string invalidTEND(){
  return "                                                                     2 0  0     \n";
}
