// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunkMF1();
std::string chunkMF2();
std::string chunkMF3();
std::string chunkSectionMF3();
std::string chunkSectionMF3v2();
std::string chunkMF4();
std::string chunkMF6();
std::string chunkMF6v2();
std::string chunk();
std::string chunkMAT();
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string invalidMEND();

SCENARIO( "tree::Material" ) {

  GIVEN( "an empty tree::Material" ) {

    WHEN( "it is created" ) {

      tree::Material material( 125 );

      THEN( "it is empty except for the MAT and MF" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        auto fileNumbers = material.fileNumbers();
        CHECK( 0 == material.size() );
        CHECK( 0 == fileNumbers.size() );

        CHECK( "" == material.content() );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::Material" ) {

    std::string materialString = chunk() + validMEND();

    WHEN( "the data is read from a string/stream with a valid MEND" ) {

      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( materialString.end() == position );
        CHECK( materialString.begin() == start );
        CHECK( materialString.end() == end );
        CHECK( 43 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with duplicate FENDs" ) {

      std::string duplicates = chunkMF1() + validFEND() + validFEND() +
                               chunkMF2() + validFEND() + validFEND() +
                               chunkMF3() + validFEND() + validFEND() +
                               chunkMF4() + validFEND() + validMEND();

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly and duplicate FENDs are removed" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( duplicates.end() == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 46 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with duplicate MENDs" ) {

      std::string duplicates = chunkMF1() + validFEND() +
                               chunkMF2() + validFEND() +
                               chunkMF3() + validFEND() +
                               chunkMF4() + validFEND() +
                               validMEND();

      auto stop_ind = duplicates.size();
      duplicates += validMEND();
      auto stop = duplicates.begin() + stop_ind;

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly and duplicate MENDs are removed" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( stop == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 43 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a missing MEND" ) {

      std::string duplicates = chunkMF1() + validFEND() +
                               chunkMF2() + validFEND() +
                               chunkMF3() + validFEND() +
                               chunkMF4() + validFEND();

      auto stop_ind = duplicates.size();
      duplicates += chunkMAT();
      auto stop = duplicates.begin() + stop_ind;

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::Material material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly and a MEND is added" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( stop == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 43 == lineNumber );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid tree material" ) {

    std::string materialString = chunk() + validMEND();
    auto position = materialString.begin();
    auto start = materialString.begin();
    auto end = materialString.end();
    long lineNumber = 0;

    HeadRecord head( position, end, lineNumber );
    tree::Material material( head, start, position, end, lineNumber );

    WHEN( "a section is inserted, replaced or removed" ) {

      material.insert( tree::Section( 125, 3, 102, chunkSectionMF3() + validSEND() ) );

      THEN( "the Material is populated correctly when a new section was inserted" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( true == material.file( 3 ).hasSection( 102 ) );
        CHECK( true == material.MF( 3 ).hasMT( 102 ) );
        CHECK( true == material.hasSection( 3, 102 ) );
        CHECK( true == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( chunkMF1() + validFEND() +
               chunkMF2() + validFEND() +
               chunkMF3() + chunkSectionMF3() + validSEND() + validFEND() +
               chunkMF4() + validFEND() + validMEND() == material.content() );
      } // THEN

      THEN( "an exception is thrown if the section is already there" ) {

        CHECK_THROWS( material.insert(
                          tree::Section( 125, 3, 102,
                                         chunkSectionMF3() + validSEND() ) ) );
      } // THEN

      material.insertOrReplace( tree::Section( 125, 3, 102,
                                           chunkSectionMF3v2() + validSEND() ) );

      THEN( "the Material is populated correctly when replacing a section" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( true == material.file( 3 ).hasSection( 102 ) );
        CHECK( true == material.MF( 3 ).hasMT( 102 ) );
        CHECK( true == material.hasSection( 3, 102 ) );
        CHECK( true == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( chunkMF1() + validFEND() +
               chunkMF2() + validFEND() +
               chunkMF3() + chunkSectionMF3v2() + validSEND() + validFEND() +
               chunkMF4() + validFEND() + validMEND() == material.content() );
      } // THEN

      material.remove( 3, 102 );

      THEN( "the Material is populated correctly when removing a section" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN
    } // WHEN

    WHEN( "a file is inserted, replaced or removed" ) {

      tree::File file( 125, 6 );
      file.insert( tree::Section( 125, 6, 5, chunkMF6() ) );

      material.insert( std::move( file ) );

      THEN( "the Material is populated correctly when a new file was inserted" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );

        CHECK( true == material.hasFile( 6 ) );
        CHECK( true == material.hasMF( 6 ) );
        CHECK( true == material.file( 6 ).hasSection( 5 ) );
        CHECK( true == material.MF( 6 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 6, 5 ) );
        CHECK( true == material.hasMFMT( 6, 5 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 5 == material.size() );
        CHECK( 5 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;
        CHECK( 6 == *iter ); ++iter;

        CHECK( chunkMF1() + validFEND() +
               chunkMF2() + validFEND() +
               chunkMF3() + validFEND() +
               chunkMF4() + validFEND() +
               chunkMF6() + validFEND() + validMEND() == material.content() );
      } // THEN

      THEN( "an exception is thrown if the file is already there" ) {

        tree::File file( 125, 6 );
        file.insert( tree::Section( 125, 6, 5, chunkMF6() ) );

        CHECK_THROWS( material.insert( std::move( file ) ) );
      } // THEN

      tree::File newfile( 125, 6 );
      newfile.insert( tree::Section( 125, 6, 5, chunkMF6v2() ) );

      material.insertOrReplace( std::move( newfile ) );

      THEN( "the Material is populated correctly when replacing a file" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );

        CHECK( true == material.hasFile( 6 ) );
        CHECK( true == material.hasMF( 6 ) );
        CHECK( true == material.file( 6 ).hasSection( 5 ) );
        CHECK( true == material.MF( 6 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 6, 5 ) );
        CHECK( true == material.hasMFMT( 6, 5 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 5 == material.size() );
        CHECK( 5 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;
        CHECK( 6 == *iter ); ++iter;

        CHECK( chunkMF1() + validFEND() +
               chunkMF2() + validFEND() +
               chunkMF3() + validFEND() +
               chunkMF4() + validFEND() +
               chunkMF6v2() + validFEND() + validMEND() == material.content() );
      } // THEN

      material.remove( 6 );

      THEN( "the Material is populated correctly when removing a file" ) {

        CHECK( 125 == material.MAT() );
        CHECK( 125 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );

        CHECK( true == material.hasFile( 2 ) );
        CHECK( true == material.hasMF( 2 ) );
        CHECK( true == material.file( 2 ).hasSection( 151 ) );
        CHECK( true == material.MF( 2 ).hasMT( 151 ) );
        CHECK( true == material.hasSection( 2, 151 ) );
        CHECK( true == material.hasMFMT( 2, 151 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 1 ) );
        CHECK( true == material.MF( 3 ).hasMT( 1 ) );
        CHECK( true == material.hasSection( 3, 1 ) );
        CHECK( true == material.hasMFMT( 3, 1 ) );
        CHECK( true == material.file( 3 ).hasSection( 5 ) );
        CHECK( true == material.MF( 3 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 3, 5 ) );
        CHECK( true == material.hasMFMT( 3, 5 ) );
        CHECK( false == material.file( 3 ).hasSection( 102 ) );
        CHECK( false == material.MF( 3 ).hasMT( 102 ) );
        CHECK( false == material.hasSection( 3, 102 ) );
        CHECK( false == material.hasMFMT( 3, 102 ) );

        CHECK( true == material.hasFile( 4 ) );
        CHECK( true == material.hasMF( 4 ) );
        CHECK( true == material.file( 4 ).hasSection( 5 ) );
        CHECK( true == material.MF( 4 ).hasMT( 5 ) );
        CHECK( true == material.hasSection( 4, 5 ) );
        CHECK( true == material.hasMFMT( 4, 5 ) );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );
        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 4 == material.size() );
        CHECK( 4 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;
        CHECK( 4 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a tree::File" ) {

    WHEN( "the data is read from a string/stream that abruptly ends (no END record)" ) {

      std::string materialString = chunk();
      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::Material( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "the data contains a duplicate file" ) {

      std::string materialString = chunk() + chunk() + validMEND();
      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::Material( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkMF1() {

  // this is a legal MF1
  return
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          5 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         17          5 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1          4          4 125 1451     \n"
    "                                3          5          4          4 125 1451     \n"
    "                                4          5          4          4 125 1451     \n"
    "                                                                   125 1  0     \n";
}

std::string chunkMF2() {

  // this is a dummy MF2, it is ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n"
    "                                                                   125 2  0     \n";
}

std::string chunkMF3() {

  // this is a dummy MF3, it is ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  1     \n"
    "          2          2                                             125 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n"
    "                                                                   125 3  0     \n";
}

std::string chunkSectionMF3() {

  // this is a dummy MF3 section, it is ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3102     \n"
    "          2          2                                             125 3102     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3102     \n";
}

std::string chunkSectionMF3v2() {

  // this is a dummy MF3 section, it is ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3102     \n"
    "          2          2                                             125 3102     \n"
    " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                       125 3102     \n";
}

std::string chunkMF4() {

  // this is a dummy MF4, not ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 4  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 4  5     \n"
    "          2          2                                             125 4  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 4  5     \n"
    "                                                                   125 4  0     \n";
}

std::string chunkMF6() {

  // this is a dummy MF6, not ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 6  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 6  5     \n"
    "          2          2                                             125 6  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 6  5     \n"
    "                                                                   125 6  0     \n";
}

std::string chunkMF6v2() {

  // this is a dummy MF6, not ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 6  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 6  5     \n"
    "          2          2                                             125 6  5     \n"
    " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                       125 6  5     \n"
    "                                                                   125 6  0     \n";
}

std::string chunk() {

  return chunkMF1() + validFEND() +
         chunkMF2() + validFEND() +
         chunkMF3() + validFEND() +
         chunkMF4() + validFEND();
}

std::string chunkMAT() {

  // this is a dummy MAT, not ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 126 1451     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 126 1451     \n"
    "          2          2                                             126 1451     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       126 1451     \n"
    "                                                                   126 1  0     \n";
}

std::string validSEND(){
  return "                                                                   125 3  0     \n";
}

std::string validSEND6(){
  return "                                                                   125 6  0     \n";
}

std::string validFEND(){
  return "                                                                   125 0  0     \n";
}

std::string validMEND(){
  return "                                                                     0 0  0     \n";
}
