#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/tree/File.hpp"

// other includes
#include "range/v3/algorithm/equal.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunkMT1();
std::string chunkMT2();
std::string chunkMT5();
std::string chunkMT5v2();
std::string chunkMT102();
std::string chunkMF4();
std::string chunk();
std::string validSEND();
std::string validFEND();
std::string invalidFEND();

SCENARIO( "tree::Section" ) {

  GIVEN( "valid data for a tree::Section" ) {

    std::string fileString = chunk() + validFEND();

    WHEN( "the data is read from a string/stream with a valid FEND" ) {

      auto position = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::File file( head, start, position, end, lineNumber );

      THEN( "the File is populated correctly" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( false == file.hasSection( 5 ) );
        CHECK( false == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 3 == file.size() );
        CHECK( 3 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( fileString == file.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( fileString.end() == position );
        CHECK( fileString.begin() == start );
        CHECK( fileString.end() == end );
        CHECK( 109 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with duplicate SENDs" ) {

      std::string duplicates = chunkMT1() + validSEND() + validSEND() +
                               chunkMT2() + validSEND() + validSEND() +
                               chunkMT102() + validSEND() + validFEND();

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::File file( head, start, position, end, lineNumber );

      THEN( "the File is populated correctly and duplicate SENDs are removed" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( false == file.hasSection( 5 ) );
        CHECK( false == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 3 == file.size() );
        CHECK( 3 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( fileString == file.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( duplicates.end() == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 111 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with duplicate FENDs" ) {

      std::string duplicates = chunkMT1() + validSEND() +
                               chunkMT2() + validSEND() +
                               chunkMT102() + validSEND() +
                               validFEND();

      auto stop = duplicates.end();
      duplicates += validFEND();

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::File file( head, start, position, end, lineNumber );

      THEN( "the File is populated correctly and duplicate FENDs are removed" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( false == file.hasSection( 5 ) );
        CHECK( false == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 3 == file.size() );
        CHECK( 3 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( fileString == file.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( stop == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 109 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a missing FEND" ) {

      std::string duplicates = chunkMT1() + validSEND() +
                               chunkMT2() + validSEND() +
                               chunkMT102() + validSEND();

      auto stop = duplicates.end();
      duplicates += chunkMF4();

      auto position = duplicates.begin();
      auto start = duplicates.begin();
      auto end = duplicates.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::File file( head, start, position, end, lineNumber );

      THEN( "the File is populated correctly and a FEND is added" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( false == file.hasSection( 5 ) );
        CHECK( false == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 3 == file.size() );
        CHECK( 3 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( fileString == file.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( stop == position );
        CHECK( duplicates.begin() == start );
        CHECK( duplicates.end() == end );
        CHECK( 109 == lineNumber );
      } // THEN
    } // WHEN

    WHEN( "a section is inserted" ) {

      auto position = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::File file( head, start, position, end, lineNumber );

      file.insert( tree::Section( 125, 3, 5, chunkMT5() + validSEND() ) );

      THEN( "the File is populated correctly when a new section was inserted" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( true == file.hasSection( 5 ) );
        CHECK( true == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 4 == file.size() );
        CHECK( 4 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 5 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( chunkMT1() + validSEND() +
               chunkMT2() + validSEND() +
               chunkMT5() + validSEND() +
               chunkMT102() + validSEND() + validFEND() == file.content() );
      } // THEN

      THEN( "an exception is thrown if the section is already there" ) {

        CHECK_THROWS( file.insert(
                          tree::Section( 125, 3, 5,
                                         chunkMT5() + validSEND() ) ) );
      } // THEN

      file.insertOrReplace( tree::Section( 125, 3, 5,
                                           chunkMT5v2() + validSEND() ) );

      THEN( "the File is populated correctly when replacing a section" ) {

        CHECK( 125 == file.MAT() );
        CHECK( 125 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        CHECK( true == file.hasSection( 1 ) );
        CHECK( true == file.hasMT( 1 ) );
        CHECK( true == file.hasSection( 2 ) );
        CHECK( true == file.hasMT( 2 ) );
        CHECK( true == file.hasSection( 5 ) );
        CHECK( true == file.hasMT( 5 ) );
        CHECK( true == file.hasSection( 102 ) );
        CHECK( true == file.hasMT( 102 ) );
        CHECK( false == file.hasSection( 107 ) );
        CHECK( false == file.hasMT( 107 ) );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 4 == file.size() );
        CHECK( 4 == sectionNumbers.size() );

        auto iter = std::begin( sectionNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 2 == *iter ); ++iter;
        CHECK( 5 == *iter ); ++iter;
        CHECK( 102 == *iter ); ++iter;

        CHECK( chunkMT1() + validSEND() +
               chunkMT2() + validSEND() +
               chunkMT5v2() + validSEND() +
               chunkMT102() + validSEND() + validFEND() == file.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a tree::File" ) {

    WHEN( "the data is read from a string/stream with an invalid FEND" ) {

      std::string sectionString = chunk() + invalidFEND();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::File( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream without a SEND" ) {

      std::string sectionString = chunk();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::File( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "the data contains a duplicate section" ) {

      std::string sectionString = chunk() + chunk() + validFEND();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::File( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkMT1() {

  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 0.000000+0 0.000000+0          0          0          2         96 125 3  1     \n"
    "         30          5         96          2                       125 3  1     \n"
    " 1.000000-5 3.713628+1 2.000000-5 3.224498+1 5.000000-5 2.790478+1 125 3  1     \n"
    " 1.000000-4 2.571732+1 2.000000-4 2.417056+1 5.000000-4 2.279806+1 125 3  1     \n"
    " 1.000000-3 2.210633+1 2.000000-3 2.161720+1 5.000000-3 2.118318+1 125 3  1     \n"
    " 1.000000-2 2.096443+1 2.530000-2 2.076834+1 5.000000-2 2.067250+1 125 3  1     \n"
    " 1.000000-1 2.060332+1 2.000000-1 2.055439+1 5.000000-1 2.051095+1 125 3  1     \n"
    " 1.000000+0 2.048901+1 2.000000+0 2.047341+1 5.000000+0 2.045928+1 125 3  1     \n"
    " 1.000000+1 2.045169+1 2.000000+1 2.044545+1 5.000000+1 2.043707+1 125 3  1     \n"
    " 1.000000+2 2.042815+1 2.000000+2 2.041317+1 5.000000+2 2.037161+1 125 3  1     \n"
    " 1.000000+3 2.030435+1 2.000000+3 2.017221+1 4.000000+3 1.991433+1 125 3  1     \n"
    " 6.000000+3 1.966407+1 8.000000+3 1.942096+1 1.000000+4 1.918468+1 125 3  1     \n"
    " 1.500000+4 1.862195+1 2.000000+4 1.809600+1 4.000000+4 1.629575+1 125 3  1     \n"
    " 6.000000+4 1.486744+1 8.000000+4 1.370595+1 1.000000+5 1.274239+1 125 3  1     \n"
    " 1.500000+5 1.092347+1 2.000000+5 9.643237+0 3.000000+5 7.951994+0 125 3  1     \n"
    " 4.000000+5 6.876451+0 5.000000+5 6.125481+0 6.000000+5 5.566913+0 125 3  1     \n"
    " 7.000000+5 5.132043+0 8.000000+5 4.781603+0 9.000000+5 4.491504+0 125 3  1     \n"
    " 1.000000+6 4.246138+0 1.200000+6 3.850489+0 1.400000+6 3.541783+0 125 3  1     \n"
    " 1.600000+6 3.291349+0 1.800000+6 3.082224+0 2.000000+6 2.903682+0 125 3  1     \n"
    " 2.200000+6 2.748580+0 2.400000+6 2.611955+0 2.600000+6 2.490235+0 125 3  1     \n"
    " 2.800000+6 2.380773+0 3.000000+6 2.281558+0 3.200000+6 2.191030+0 125 3  1     \n"
    " 3.400000+6 2.107954+0 3.600000+6 2.031337+0 3.800000+6 1.960371+0 125 3  1     \n"
    " 4.000000+6 1.894386+0 4.200000+6 1.832823+0 4.400000+6 1.775213+0 125 3  1     \n"
    " 4.600000+6 1.721153+0 4.800000+6 1.670299+0 5.000000+6 1.622354+0 125 3  1     \n"
    " 5.500000+6 1.513587+0 6.000000+6 1.418191+0 6.500000+6 1.333743+0 125 3  1     \n"
    " 7.000000+6 1.258400+0 7.500000+6 1.190730+0 8.000000+6 1.129596+0 125 3  1     \n"
    " 8.500000+6 1.074084+0 9.000000+6 1.023447+0 9.500000+6 9.770666-1 125 3  1     \n"
    " 1.000000+7 9.344290-1 1.050000+7 8.950999-1 1.100000+7 8.587108-1 125 3  1     \n"
    " 1.150000+7 8.249463-1 1.200000+7 7.935351-1 1.250000+7 7.642418-1 125 3  1     \n"
    " 1.300000+7 7.368615-1 1.350000+7 7.112148-1 1.400000+7 6.871439-1 125 3  1     \n"
    " 1.450000+7 6.645095-1 1.500000+7 6.431880-1 1.550000+7 6.230693-1 125 3  1     \n"
    " 1.600000+7 6.040552-1 1.650000+7 5.860577-1 1.700000+7 5.689977-1 125 3  1     \n"
    " 1.750000+7 5.528040-1 1.800000+7 5.374121-1 1.850000+7 5.227637-1 125 3  1     \n"
    " 1.900000+7 5.088059-1 1.950000+7 4.954905-1 2.000000+7 4.827735-1 125 3  1     \n";
}

std::string chunkMT2() {

  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  2     \n"
    " 0.000000+0 0.000000+0          0          0          1         96 125 3  2     \n"
    "         96          2                                             125 3  2     \n"
    " 1.000000-5 2.043634+1 2.000000-5 2.043634+1 5.000000-5 2.043634+1 125 3  2     \n"
    " 1.000000-4 2.043633+1 2.000000-4 2.043633+1 5.000000-4 2.043633+1 125 3  2     \n"
    " 1.000000-3 2.043633+1 2.000000-3 2.043633+1 5.000000-3 2.043633+1 125 3  2     \n"
    " 1.000000-2 2.043633+1 2.530000-2 2.043633+1 5.000000-2 2.043633+1 125 3  2     \n"
    " 1.000000-1 2.043632+1 2.000000-1 2.043631+1 5.000000-1 2.043627+1 125 3  2     \n"
    " 1.000000+0 2.043620+1 2.000000+0 2.043606+1 5.000000+0 2.043566+1 125 3  2     \n"
    " 1.000000+1 2.043499+1 2.000000+1 2.043364+1 5.000000+1 2.042960+1 125 3  2     \n"
    " 1.000000+2 2.042288+1 2.000000+2 2.040944+1 5.000000+2 2.036926+1 125 3  2     \n"
    " 1.000000+3 2.030269+1 2.000000+3 2.017105+1 4.000000+3 1.991352+1 125 3  2     \n"
    " 6.000000+3 1.966341+1 8.000000+3 1.942040+1 1.000000+4 1.918418+1 125 3  2     \n"
    " 1.500000+4 1.862156+1 2.000000+4 1.809567+1 4.000000+4 1.629554+1 125 3  2     \n"
    " 6.000000+4 1.486728+1 8.000000+4 1.370583+1 1.000000+5 1.274229+1 125 3  2     \n"
    " 1.500000+5 1.092340+1 2.000000+5 9.643178+0 3.000000+5 7.951949+0 125 3  2     \n"
    " 4.000000+5 6.876412+0 5.000000+5 6.125445+0 6.000000+5 5.566879+0 125 3  2     \n"
    " 7.000000+5 5.132010+0 8.000000+5 4.781570+0 9.000000+5 4.491471+0 125 3  2     \n"
    " 1.000000+6 4.246104+0 1.200000+6 3.850454+0 1.400000+6 3.541748+0 125 3  2     \n"
    " 1.600000+6 3.291314+0 1.800000+6 3.082187+0 2.000000+6 2.903645+0 125 3  2     \n"
    " 2.200000+6 2.748543+0 2.400000+6 2.611918+0 2.600000+6 2.490197+0 125 3  2     \n"
    " 2.800000+6 2.380736+0 3.000000+6 2.281521+0 3.200000+6 2.190993+0 125 3  2     \n"
    " 3.400000+6 2.107917+0 3.600000+6 2.031301+0 3.800000+6 1.960334+0 125 3  2     \n"
    " 4.000000+6 1.894349+0 4.200000+6 1.832787+0 4.400000+6 1.775177+0 125 3  2     \n"
    " 4.600000+6 1.721118+0 4.800000+6 1.670264+0 5.000000+6 1.622318+0 125 3  2     \n"
    " 5.500000+6 1.513553+0 6.000000+6 1.418157+0 6.500000+6 1.333709+0 125 3  2     \n"
    " 7.000000+6 1.258367+0 7.500000+6 1.190697+0 8.000000+6 1.129564+0 125 3  2     \n"
    " 8.500000+6 1.074052+0 9.000000+6 1.023415+0 9.500000+6 9.770347-1 125 3  2     \n"
    " 1.000000+7 9.343974-1 1.050000+7 8.950685-1 1.100000+7 8.586796-1 125 3  2     \n"
    " 1.150000+7 8.249154-1 1.200000+7 7.935044-1 1.250000+7 7.642113-1 125 3  2     \n"
    " 1.300000+7 7.368313-1 1.350000+7 7.111848-1 1.400000+7 6.871141-1 125 3  2     \n"
    " 1.450000+7 6.644799-1 1.500000+7 6.431586-1 1.550000+7 6.230401-1 125 3  2     \n"
    " 1.600000+7 6.040262-1 1.650000+7 5.860290-1 1.700000+7 5.689692-1 125 3  2     \n"
    " 1.750000+7 5.527757-1 1.800000+7 5.373840-1 1.850000+7 5.227359-1 125 3  2     \n"
    " 1.900000+7 5.087783-1 1.950000+7 4.954630-1 2.000000+7 4.827462-1 125 3  2     \n";
}

std::string chunkMT5() {

    return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n";
}

std::string chunkMT5v2() {

    return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 2.000000+0 2.000000+7 1.000000+0                       125 3  5     \n";
}

std::string chunkMT102() {

    return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224631+6 2.224631+6          0          0          2         96 125 3102     \n"
    "         30          5         96          2                       125 3102     \n"
    " 1.000000-5 1.669994+1 2.000000-5 1.180864+1 5.000000-5 7.468441+0 125 3102     \n"
    " 1.000000-4 5.280985+0 2.000000-4 3.734221+0 5.000000-4 2.361728+0 125 3102     \n"
    " 1.000000-3 1.669994+0 2.000000-3 1.180864+0 5.000000-3 7.468441-1 125 3102     \n"
    " 1.000000-2 5.280985-1 2.530000-2 3.320126-1 5.000000-2 2.361728-1 125 3102     \n"
    " 1.000000-1 1.669993-1 2.000000-1 1.180863-1 5.000000-1 7.468415-2 125 3102     \n"
    " 1.000000+0 5.280948-2 2.000000+0 3.734168-2 5.000000+0 2.361645-2 125 3102     \n"
    " 1.000000+1 1.669877-2 2.000000+1 1.180698-2 5.000000+1 7.465816-3 125 3102     \n"
    " 1.000000+2 5.277275-3 2.000000+2 3.728978-3 5.000000+2 2.353460-3 125 3102     \n"
    " 1.000000+3 1.658348-3 2.000000+3 1.164526-3 4.000000+3 8.122556-4 125 3102     \n"
    " 6.000000+3 6.543522-4 8.000000+3 5.592552-4 1.000000+4 4.937688-4 125 3102     \n"
    " 1.500000+4 3.906824-4 2.000000+4 3.283054-4 4.000000+4 2.082663-4 125 3102     \n"
    " 6.000000+4 1.550608-4 8.000000+4 1.241126-4 1.000000+5 1.037740-4 125 3102     \n"
    " 1.500000+5 7.450778-5 2.000000+5 5.927795-5 3.000000+5 4.460357-5 125 3102     \n"
    " 4.000000+5 3.827476-5 5.000000+5 3.529043-5 6.000000+5 3.389904-5 125 3102     \n"
    " 7.000000+5 3.334204-5 8.000000+5 3.324413-5 9.000000+5 3.340211-5 125 3102     \n"
    " 1.000000+6 3.369898-5 1.200000+6 3.445546-5 1.400000+6 3.521705-5 125 3102     \n"
    " 1.600000+6 3.587303-5 1.800000+6 3.638957-5 2.000000+6 3.676631-5 125 3102     \n"
    " 2.200000+6 3.701693-5 2.400000+6 3.715993-5 2.600000+6 3.721435-5 125 3102     \n"
    " 2.800000+6 3.719773-5 3.000000+6 3.712539-5 3.200000+6 3.701023-5 125 3102     \n"
    " 3.400000+6 3.686289-5 3.600000+6 3.669203-5 3.800000+6 3.650457-5 125 3102     \n"
    " 4.000000+6 3.630600-5 4.200000+6 3.610063-5 4.400000+6 3.589183-5 125 3102     \n"
    " 4.600000+6 3.568218-5 4.800000+6 3.547364-5 5.000000+6 3.526769-5 125 3102     \n"
    " 5.500000+6 3.477049-5 6.000000+6 3.430506-5 6.500000+6 3.387418-5 125 3102     \n"
    " 7.000000+6 3.347699-5 7.500000+6 3.311084-5 8.000000+6 3.277233-5 125 3102     \n"
    " 8.500000+6 3.245788-5 9.000000+6 3.216400-5 9.500000+6 3.188749-5 125 3102     \n"
    " 1.000000+7 3.162545-5 1.050000+7 3.137531-5 1.100000+7 3.113485-5 125 3102     \n"
    " 1.150000+7 3.090214-5 1.200000+7 3.067552-5 1.250000+7 3.045360-5 125 3102     \n"
    " 1.300000+7 3.023518-5 1.350000+7 3.001928-5 1.400000+7 2.980507-5 125 3102     \n"
    " 1.450000+7 2.959190-5 1.500000+7 2.937920-5 1.550000+7 2.916656-5 125 3102     \n"
    " 1.600000+7 2.895363-5 1.650000+7 2.874018-5 1.700000+7 2.852603-5 125 3102     \n"
    " 1.750000+7 2.831107-5 1.800000+7 2.809523-5 1.850000+7 2.787851-5 125 3102     \n"
    " 1.900000+7 2.766095-5 1.950000+7 2.744259-5 2.000000+7 2.722354-5 125 3102     \n";
}

std::string chunkMF4() {

  // this is a dummy MF4, not ENDF legal
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 4  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 4  5     \n"
    "          2          2                                             125 4  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 4  5     \n";
}

std::string chunk() {

  return chunkMT1() + validSEND() +
         chunkMT2() + validSEND() +
         chunkMT102() + validSEND();
}

std::string validSEND(){
  return "                                                                   125 3  0     \n";
}

std::string validFEND(){
  return "                                                                   125 0  0     \n";
}

std::string invalidFEND(){
  return "                                                                   125 3  0     \n";
}
