// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/tree/GSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
std::string chunkDirty();
std::string validEND();
std::string invalidEND();

SCENARIO( "tree::GSection" ) {

  GIVEN( "valid data for a tree::GSection" ) {

    std::string sectionString = chunk() + validEND();

    WHEN( "the data is given explicitly" ) {

      int mat = 9228;
      int mf = 3;
      int mt = 16;

      tree::GSection section( mat, mf, mt, std::string( sectionString ) );

      THEN( "the Section is populated correctly" ) {

        CHECK( 9228 == section.MAT() );
        CHECK( 9228 == section.materialNumber() );
        CHECK( 3 == section.MF() );
        CHECK( 3 == section.fileNumber() );
        CHECK( 16 == section.MT() );
        CHECK( 16 == section.sectionNumber() );

        CHECK( 15 == section.NC() );

        CHECK( sectionString == section.content() );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid END" ) {

      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::GSection section( head, start, position, end, lineNumber );

      THEN( "the Section is populated correctly" ) {

        CHECK( 9228 == section.MAT() );
        CHECK( 9228 == section.materialNumber() );
        CHECK( 3 == section.MF() );
        CHECK( 3 == section.fileNumber() );
        CHECK( 16 == section.MT() );
        CHECK( 16 == section.sectionNumber() );

        CHECK( 15 == section.NC() );

        CHECK( sectionString == section.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( sectionString.end() == position );
        CHECK( sectionString.begin() == start );
        CHECK( sectionString.end() == end );

        CHECK( 16 == lineNumber ); // one number beyond the number of lines
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a dirty buffer for a tree::GSection" ) {

    int mat = 9228;
    int mf = 3;
    int mt = 16;
    std::string sectionString = chunkDirty() + validEND();

    tree::GSection section( mat, mf, mt, std::string( sectionString ) );

    WHEN( "the section is cleaned" ) {

      section.clean();

      THEN( "the sequence numbers will be removed" ) {

        CHECK( chunk() + validEND() == section.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a tree::GSection" ) {

    WHEN( "the data is read from a string/stream with an invalid END" ) {

      std::string sectionString = chunk() + invalidEND();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::GSection( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream without an END" ) {

      std::string sectionString = chunk();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( position, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( tree::GSection( head, start, position, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

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
    " 3.724272+3 3.717841-1                                            9228 3 16     \n";
}

std::string chunkDirty() {

  return
    " 9.223500+4 0.000000+0          1          1          0         309228 3 16    1\n"
    " 2.936000+2 0.000000+0          2          1          2         249228 3 16    2\n"
    " 2.235493+5 1.047471-2                                            9228 3 16    3\n"
    " 2.936000+2 0.000000+0          2          1          2         259228 3 16    4\n"
    " 4.396216+4 3.690336-1                                            9228 3 16    5\n"
    " 2.936000+2 0.000000+0          2          1          2         269228 3 16    6\n"
    " 2.311833+4 6.475546-1                                            9228 3 16    7\n"
    " 2.936000+2 0.000000+0          2          1          2         279228 3 16    8\n"
    " 1.410474+4 8.511604-1                                            9228 3 16    9\n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3 16   10\n"
    " 1.905167+4 7.647669-1                                            9228 3 16   11\n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3 16   12\n"
    " 7.393531+4 5.483544-1                                            9228 3 16   13\n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3 16   14\n"
    " 3.724272+3 3.717841-1                                            9228 3 16   15\n";
}

std::string validEND(){
  return
    "                                                                  9228 3  0     \n";
}

std::string invalidEND(){
  return
    "                                                                  9228 3 16     \n";
}
