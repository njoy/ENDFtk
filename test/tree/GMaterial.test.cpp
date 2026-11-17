// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/tree/GMaterial.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

void verifyChunk( const tree::GMaterial& );
std::string chunkMF1();
std::string chunkMF3MT16();
std::string chunkMF3MT17();
std::string chunkMF3();
std::string chunkMF6MT17();
std::string chunkMF6MT89();
std::string chunkMF6();
std::string chunk();
std::string chunkUnordered();
std::string chunkUnorderedWithDuplicates();
std::string validMEND();

SCENARIO( "tree::GMaterial" ) {

  GIVEN( "an empty tree::GMaterial" ) {

    WHEN( "it is created" ) {

      tree::GMaterial material( 9228 );

      THEN( "it is empty except for the MAT and MF" ) {

        CHECK( 9228 == material.MAT() );
        CHECK( 9228 == material.materialNumber() );

        auto fileNumbers = material.fileNumbers();
        CHECK( 0 == material.size() );
        CHECK( 0 == fileNumbers.size() );

        CHECK( "" == material.content() );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::GMaterial with data in order and unique" ) {

    std::string materialString = chunk() + validMEND();

    WHEN( "the data is read from a string/stream with a valid MEND" ) {

      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::GMaterial material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly" ) {

        verifyChunk( material );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( materialString.end() == position );
        CHECK( materialString.begin() == start );
        CHECK( materialString.end() == end );
        CHECK( 147 == lineNumber ); // last line read is the MEND record
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::GMaterial with data not in order and with duplicates" ) {

    std::string materialString = chunkUnordered() + validMEND();
    std::string finalString = chunk() + validMEND();

    WHEN( "the data is read from a string/stream with a valid MEND" ) {

      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::GMaterial material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly" ) {

        verifyChunk( material );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( materialString.end() == position );
        CHECK( materialString.begin() == start );
        CHECK( materialString.end() == end );
        CHECK( 147 == lineNumber ); // last line read is the MEND record
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::GMaterial with data not in order and with duplicates" ) {

    std::string materialString = chunkUnorderedWithDuplicates() + validMEND();

    WHEN( "the data is read from a string/stream with a valid MEND" ) {

      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::GMaterial material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly" ) {

        verifyChunk( material );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( materialString.end() == position );
        CHECK( materialString.begin() == start );
        CHECK( materialString.end() == end );
        CHECK( 215 == lineNumber ); // last line read is the MEND record
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a tree::GMaterial" ) {

    WHEN( "the data is read from a string/stream that abruptly ends (no END record)" ) {

      std::string materialString = chunk();
      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::GMaterial( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const tree::GMaterial& material ) {

  std::string finalString = chunk() + validMEND();

  CHECK( 9228 == material.MAT() );
  CHECK( 9228 == material.materialNumber() );

  CHECK( true == material.hasFile( 1 ) );
  CHECK( true == material.hasMF( 1 ) );
  CHECK( true == material.file( 1 ).hasSection( 451 ) );
  CHECK( true == material.MF( 1 ).hasMT( 451 ) );
  CHECK( 1 == material.file( 1 ).size() );
  CHECK( 1 == material.MF( 1 ).size() );
  CHECK( chunkMF1() == material.file( 1 ).content() );
  CHECK( chunkMF1() == material.MF( 1 ).content() );
  CHECK( chunkMF1() == material.file( 1 ).section( 451 ).content() );
  CHECK( chunkMF1() == material.MF( 1 ).section( 451 ).content() );

  CHECK( false == material.hasFile( 2 ) );
  CHECK( false == material.hasMF( 2 ) );

  CHECK( true == material.hasFile( 3 ) );
  CHECK( true == material.hasMF( 3 ) );
  CHECK( true == material.file( 3 ).hasSection( 16 ) );
  CHECK( true == material.MF( 3 ).hasMT( 16 ) );
  CHECK( true == material.hasSection( 3, 16 ) );
  CHECK( true == material.hasMFMT( 3, 16 ) );
  CHECK( true == material.file( 3 ).hasSection( 17 ) );
  CHECK( true == material.MF( 3 ).hasMT( 17 ) );
  CHECK( true == material.hasSection( 3, 17 ) );
  CHECK( true == material.hasMFMT( 3, 17 ) );
  CHECK( false == material.file( 3 ).hasSection( 3 ) );
  CHECK( false == material.MF( 3 ).hasMT( 3 ) );
  CHECK( false == material.hasSection( 3, 3 ) );
  CHECK( false == material.hasMFMT( 3, 3 ) );
  CHECK( 2 == material.file( 3 ).size() );
  CHECK( 2 == material.MF( 3 ).size() );
  CHECK( chunkMF3() == material.file( 3 ).content() );
  CHECK( chunkMF3() == material.MF( 3 ).content() );
  CHECK( chunkMF3MT16() == material.file( 3 ).section( 16 ).content() );
  CHECK( chunkMF3MT16() == material.MF( 3 ).section( 16 ).content() );
  CHECK( chunkMF3MT17() == material.file( 3 ).section( 17 ).content() );
  CHECK( chunkMF3MT17() == material.MF( 3 ).section( 17 ).content() );

  CHECK( false == material.hasFile( 5 ) );
  CHECK( false == material.hasMF( 5 ) );

  CHECK( true == material.hasFile( 6 ) );
  CHECK( true == material.hasMF( 6 ) );
  CHECK( true == material.file( 6 ).hasSection( 17 ) );
  CHECK( true == material.MF( 6 ).hasMT( 17 ) );
  CHECK( true == material.hasSection( 6, 17 ) );
  CHECK( true == material.hasMFMT( 6, 17 ) );
  CHECK( true == material.file( 6 ).hasSection( 89 ) );
  CHECK( true == material.MF( 6 ).hasMT( 89 ) );
  CHECK( true == material.hasSection( 6, 89 ) );
  CHECK( true == material.hasMFMT( 6, 89 ) );
  CHECK( false == material.file( 6 ).hasSection( 3 ) );
  CHECK( false == material.MF( 6 ).hasMT( 3 ) );
  CHECK( false == material.hasSection( 6, 3 ) );
  CHECK( false == material.hasMFMT( 6, 3 ) );
  CHECK( 2 == material.file( 6 ).size() );
  CHECK( 2 == material.MF( 6 ).size() );
  CHECK( chunkMF6() == material.file( 6 ).content() );
  CHECK( chunkMF6() == material.MF( 6 ).content() );
  CHECK( chunkMF6MT17() == material.file( 6 ).section( 17 ).content() );
  CHECK( chunkMF6MT17() == material.MF( 6 ).section( 17 ).content() );
  CHECK( chunkMF6MT89() == material.file( 6 ).section( 89 ).content() );
  CHECK( chunkMF6MT89() == material.MF( 6 ).section( 89 ).content() );

  auto fileNumbers = material.fileNumbers();
  CHECK( 3 == material.size() );
  CHECK( 3 == fileNumbers.size() );

  auto iter = std::begin( fileNumbers );
  CHECK( 1 == *iter ); ++iter;
  CHECK( 3 == *iter ); ++iter;
  CHECK( 6 == *iter ); ++iter;

  CHECK( finalString == material.content() ); // the data is now in order
}

std::string chunkMF1() {

  // this is a legal MF1
  return
    " 9.223500+4 2.330248+2          0          3         -1          19228 1451     \n"
    " 2.936000+2 0.000000+0         30         12         48          09228 1451     \n"
    " 0.000000+0 1.00000+10 1.000000+4 1.000000+2 1.390000-4 1.520000-19228 1451     \n"
    " 4.140000-1 1.130000+0 3.060000+0 8.320000+0 2.260000+1 6.140000+19228 1451     \n"
    " 1.670000+2 4.540000+2 1.235000+3 3.350000+3 9.120000+3 2.480000+49228 1451     \n"
    " 6.760000+4 1.840000+5 3.030000+5 5.000000+5 8.230000+5 1.353000+69228 1451     \n"
    " 1.738000+6 2.232000+6 2.865000+6 3.680000+6 6.070000+6 7.790000+69228 1451     \n"
    " 1.000000+7 1.200000+7 1.350000+7 1.500000+7 1.700000+7 1.000000+49228 1451     \n"
    " 1.000000+5 5.000000+5 1.000000+6 2.000000+6 3.000000+6 4.000000+69228 1451     \n"
    " 5.000000+6 6.000000+6 7.000000+6 8.000000+6 9.000000+6 2.000000+79228 1451     \n"
    "                                                                  9228 1  0     \n";
}

std::string chunkMF3MT16() {

  // this is a legal MF3 MT16
  return
    " 9.223500+4 0.000000+0          1          1          0         309228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         249228 3 16     \n"
    " 2.235493+5 1.047471-2                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         259228 3 16     \n"
    " 4.396216+4 3.690336-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         269228 3 16     \n"
    " 2.311833+4 6.475546-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         279228 3 16     \n"
    " 1.410474+4 8.511604-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3 16     \n"
    " 1.905167+4 7.647669-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3 16     \n"
    " 7.393531+4 5.483544-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3 16     \n"
    " 3.724272+3 3.717841-1                                            9228 3 16     \n"
    "                                                                  9228 3  0     \n";
}

std::string chunkMF3MT17() {

  // this is a legal MF3 MT17
  return
    " 9.223500+4 0.000000+0          1          1          0         309228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3 17     \n"
    " 1.905167+4 3.145908-3                                            9228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3 17     \n"
    " 7.393531+4 3.879856-2                                            9228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3 17     \n"
    " 3.724272+3 1.593517-1                                            9228 3 17     \n"
    "                                                                  9228 3  0     \n";
}

std::string chunkMF3() {

  return chunkMF3MT16() + chunkMF3MT17();
}

std::string chunkMF6MT17() {

  // this is a legal MF6 MT17
  return
    " 9.223500+4 0.000000+0          6          1          0         309228 6 17     \n"
    " 2.936000+2 0.000000+0         15          6         90         289228 6 17     \n"
    " 1.905167+4 1.905167+4 1.905167+4 1.905167+4 1.905167+4 1.905167+49228 6 17     \n"
    " 2.203840-9 2.05421-12 6.41740-15-5.25132-13-1.42015-14 2.60463-139228 6 17     \n"
    " 9.882530-9 9.02148-12 5.55041-14-2.33669-12-1.64743-13 1.12592-129228 6 17     \n"
    " 4.432625-8-4.44601-13-4.89096-11-6.07220-11-2.80024-11-4.74050-119228 6 17     \n"
    " 1.986455-7-5.45118-10-6.43008-10-8.53278-10-6.02164-10-6.41804-109228 6 17     \n"
    " 8.956620-7 6.41046-10-4.18134-12-2.54393-10-7.30791-11 5.53860-119228 6 17     \n"
    " 4.001541-6 2.744956-9 1.35468-10-8.35303-10-2.92421-10 3.41728-109228 6 17     \n"
    " 1.800800-5 1.092844-8 1.339063-9-3.094132-9-1.782198-9 9.71300-109228 6 17     \n"
    " 8.093037-5 3.107080-8 1.163997-8-7.623088-9-9.628708-9-1.792690-99228 6 17     \n"
    " 4.189883-4-3.358186-6 7.216055-8 1.495774-8-1.677087-8-2.138656-89228 6 17     \n"
    " 2.207501-3 4.504314-6 1.151425-7 7.460737-8 3.574144-8 9.716117-99228 6 17     \n"
    " 2.555957-3 5.137234-5 2.727736-8 7.619444-9 6.661020-9 5.498861-99228 6 17     \n"
    " 2.785632-3 1.057907-4 1.584618-7 1.825057-9-3.87710-11 4.52858-119228 6 17     \n"
    " 1.281462-3 8.403838-5 1.138329-6 1.967934-8 1.920029-9 3.67760-109228 6 17     \n"
    " 8.409190-5 1.086226-5 7.214802-7 3.488904-8 2.356965-8 1.493760-89228 6 17     \n"
    " 2.936000+2 0.000000+0         19          5        114         299228 6 17     \n"
    " 7.393531+4 7.393531+4 7.393531+4 7.393531+4 7.393531+4 7.393531+49228 6 17     \n"
    " 1.639907-9 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.026086-8 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 4.688103-8 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 2.103058-7-2.83686-11-4.26555-11-5.55004-11-8.85221-12-5.06198-119228 6 17     \n"
    " 9.415104-7-3.711632-9-3.065168-9-4.107321-9-3.056089-9-3.132205-99228 6 17     \n"
    " 4.247563-6 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.897699-5 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 8.539473-5 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 3.825076-4-3.163375-9 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 2.051777-3-3.088200-5 1.568381-8 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.292418-2-5.436818-5 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.903277-2 1.493050-4 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 3.017323-2 5.945471-4 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 3.152281-2 9.663147-4 3.295696-9 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.803804-2 8.625647-4 2.186155-6 1.676786-8 7.370893-9 2.155757-99228 6 17     \n"
    " 1.955203-3 1.719683-4 4.872267-6 1.064294-7 1.182637-7 2.652592-89228 6 17     \n"
    " 2.020879-4 2.599897-5 1.894601-6 9.678948-8 1.984584-7 8.769127-89228 6 17     \n"
    " 3.242740-6 7.261987-7 1.152493-7 1.507389-8 3.135450-8 1.714577-89228 6 17     \n"
    " 2.936000+2 0.000000+0         21          5        126         309228 6 17     \n"
    " 3.724272+3 3.724272+3 3.724272+3 3.724272+3 3.724272+3 3.724272+39228 6 17     \n"
    " 2.019739-9 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.475651-8 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 7.769979-8 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 3.491481-7-3.17364-12-6.32945-12-1.75463-11-3.11336-16-1.72370-119228 6 17     \n"
    " 1.562890-6-6.512102-9-5.365195-9-7.803484-9-5.908382-9-5.789732-99228 6 17     \n"
    " 7.055829-6-1.04520-12 0.000000+0-9.03927-12-1.05828-11-6.78559-179228 6 17     \n"
    " 3.151966-5 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.419671-4 7.051739-9 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 6.370055-4 5.758774-7 1.42645-10 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 3.522219-3-7.285876-5 1.531499-6 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 2.475527-2-1.635973-4 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 4.051482-2 9.404605-5 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 7.565839-2 1.031200-3 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.090313-1 2.245251-3 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.282670-1 3.700016-3 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 5.272721-2 2.512680-3 1.637231-7 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 2.983580-2 2.031329-3 2.820918-5 0.000000+0 0.000000+0 0.000000+09228 6 17     \n"
    " 1.071361-2 1.027324-3 7.237668-5 6.804056-8 2.501269-7 4.158869-89228 6 17     \n"
    " 2.110492-3 2.904715-4 2.968963-5 2.122901-7 5.429006-7 3.089222-79228 6 17     \n"
    " 9.946224-5 2.177884-5 3.304800-6 1.539063-7 3.308517-7 2.022797-79228 6 17     \n"
    "                                                                  9228 6  0     \n";
}

std::string chunkMF6MT89() {

  return
    " 9.223500+4 0.000000+0          6          1          0         309228 6 89     \n"
    " 2.936000+2 0.000000+0         10          8         60         189228 6 89     \n"
    " 1.030736+6 1.030736+6 1.030736+6 1.030736+6 1.030736+6 1.030736+69228 6 89     \n"
    " 5.896639-9-6.05147-10-3.81146-11-8.64613-12 6.28384-13 9.96033-129228 6 89     \n"
    " 4.283246-8-2.706820-9-1.14268-10-2.99019-11-3.32449-11 1.91158-109228 6 89     \n"
    " 3.148515-7-1.215541-8-4.77537-10-5.32208-11-5.08977-11 6.31840-109228 6 89     \n"
    " 2.306735-6-5.399006-8-4.927595-9-5.75685-11-1.01106-11 1.072581-99228 6 89     \n"
    " 1.774208-5-2.853260-7-5.317370-8-1.043675-9 2.56345-10-5.23212-109228 6 89     \n"
    " 1.359181-4-1.231115-6-4.195993-7-5.078195-9 9.19035-10-1.229569-89228 6 89     \n"
    " 1.005133-3-5.442690-6-3.423292-6-2.042279-8 3.219094-9-8.222504-89228 6 89     \n"
    " 6.749686-3 1.117800-7-3.340392-5 4.260082-6-6.607530-7-1.286927-69228 6 89     \n"
    " 1.344476-4 6.923727-5 9.832496-6-4.780951-6 6.585710-7 9.019266-79228 6 89     \n"
    " 2.936000+2 0.000000+0          5         15         30         199228 6 89     \n"
    " 1.175655+6 1.175655+6 1.175655+6 1.175655+6 1.175655+6 1.175655+69228 6 89     \n"
    " 1.645533-5-1.343482-5 8.638945-6-3.874285-6 5.792027-7 7.850736-79228 6 89     \n"
    " 7.790013-3-3.842325-5-2.959697-5 3.671220-6-5.658864-7-1.065764-69228 6 89     \n"
    " 1.010300-2 5.420650-5-3.301538-7-9.753351-8-1.364020-8 8.342373-99228 6 89     \n"
    " 6.696966-3 1.147155-4-2.679831-6-3.170845-8 1.531925-9-2.965584-89228 6 89     \n"
    " 2.936000+2 0.000000+0          3         18         18         209228 6 89     \n"
    " 5.407962+5 5.407962+5 5.407962+5 5.407962+5 5.407962+5 5.407962+59228 6 89     \n"
    " 5.011914-3-1.015810-4 1.489630-5-4.991483-7-2.111740-9 1.454470-79228 6 89     \n"
    " 7.475743-3 1.483919-4 4.666898-5 1.089340-6 5.41965-10 4.260345-79228 6 89     \n"
    " 2.936000+2 0.000000+0          3         19         18         219228 6 89     \n"
    " 4.481702+5 4.481702+5 4.481702+5 4.481702+5 4.481702+5 4.481702+59228 6 89     \n"
    " 4.581258-3-4.348525-5 4.268122-5-4.312820-7-1.024515-8 3.791448-79228 6 89     \n"
    " 2.137440-3 6.674824-5 2.498811-5 1.038394-6 8.866448-9 2.031567-79228 6 89     \n"
    " 2.936000+2 0.000000+0          3         20         18         229228 6 89     \n"
    " 3.429532+5 3.429532+5 3.429532+5 3.429532+5 3.429532+5 3.429532+59228 6 89     \n"
    " 1.074579-3-2.804006-5 1.278545-5-3.855238-7-8.831807-9 1.051325-79228 6 89     \n"
    " 1.317873-3 3.590152-5 1.743416-5 6.439249-7 8.227599-9 1.380062-79228 6 89     \n"
    " 2.936000+2 0.000000+0          4         21         24         239228 6 89     \n"
    " 2.344895+5 2.344895+5 2.344895+5 2.344895+5 2.344895+5 2.344895+59228 6 89     \n"
    " 3.679066-5-1.200048-5 2.630907-7-2.029779-7-4.903135-9 4.07599-109228 6 89     \n"
    " 4.562610-4 1.125129-5 6.455204-6 2.295657-7 3.703643-9 4.857040-89228 6 89     \n"
    " 3.186295-5 2.410614-6 2.966100-7 3.129179-8 1.098975-9 1.746066-99228 6 89     \n"
    " 2.936000+2 0.000000+0          3         23         18         249228 6 89     \n"
    " 2.235493+5 2.235493+5 2.235493+5 2.235493+5 2.235493+5 2.235493+59228 6 89     \n"
    " 4.617688-5-9.310487-8 9.600435-8 7.97277-10-1.07356-11 8.31381-109228 6 89     \n"
    " 7.418810-6 2.600492-7 6.798187-9 3.08574-11 8.87202-12 8.46764-129228 6 89     \n"
    " 2.936000+2 0.000000+0          3         24         18         259228 6 89     \n"
    " 4.396217+4 4.396217+4 4.396217+4 4.396217+4 4.396217+4 4.396217+49228 6 89     \n"
    " 3.689824-7-3.125764-9-1.17045-10-1.11832-12 1.29730-13 9.04063-159228 6 89     \n"
    " 8.472279-8 4.492981-9 1.18901-10 1.11832-12-1.29730-13 7.82759-149228 6 89     \n"
    " 2.936000+2 0.000000+0          3         25         18         269228 6 89     \n"
    " 2.311834+4 2.311834+4 2.311834+4 2.311834+4 2.311834+4 2.311834+49228 6 89     \n"
    " 1.487018-8-1.63179-10-4.92027-12-5.34457-14 1.97043-15 3.39662-169228 6 89     \n"
    " 4.311023-9 2.20308-10 4.99692-12 5.34457-14-1.97043-15 3.29023-159228 6 89     \n"
    " 2.936000+2 0.000000+0          2         30         12         309228 6 89     \n"
    " 3.724277+3 3.724277+3 3.724277+3 3.724277+3 3.724277+3 3.724277+39228 6 89     \n"
    " 1.82496-13 1.97258-14 1.36505-15 3.81831-17 7.79578-20 2.04016-189228 6 89     \n"
    "                                                                  9228 6  0     \n";
}

std::string chunkMF6() {

  return chunkMF6MT17() + chunkMF6MT89();
}


std::string chunk() {

  return chunkMF1() + chunkMF3() + chunkMF6();
}

std::string chunkUnordered() {

  return chunkMF1() + chunkMF6MT89() + chunkMF3MT17() + chunkMF6MT17() + chunkMF3MT16();
}

std::string chunkUnorderedWithDuplicates() {

  return chunkMF1() + chunkMF3MT17() + chunkMF6MT17() + chunkMF6MT89() + chunkMF3MT17() + chunkMF6MT17() + chunkMF3MT16();
}

std::string validMEND(){

  return
    "                                                                     0 0  0     \n";
}
