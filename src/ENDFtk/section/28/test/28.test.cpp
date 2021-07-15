#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/28.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const section::Type< 28 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 28 >" ) {

  GIVEN( "valid data for a section::Type< 28 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

//      int mt = 533;
//      int zaid = 1000;
//      double awr = 0.9992414;
//      std::vector< long > interpolants = { 2 };
//      std::vector< long > boundaries = { 2 };
//      std::vector< double > energies = { 0., 1e+9 };
//      std::vector< double > values = { 1., 2. };
//
//      section::Type< 28 > chunk( mt, zaid, awr,
//                                std::move( boundaries ),
//                                std::move( interpolants ),
//                                std::move( energies ), std::move( values ) );
//
//      THEN( "a section::Type< 28 > can be constructed and "
//            "members can be tested" ) {
//
//        verifyChunk( chunk );
//      } // THEN
//
//      THEN( "it can be printed" ) {
//
//        std::string buffer;
//        auto output = std::back_inserter( buffer );
//        chunk.print( output, 100, 28 );
//
//        CHECK( buffer == sectionString );
//      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 28 > chunk( head, begin, end, lineNumber, 100 );

      THEN( "a section::Type< 28 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 28 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 125, 28, 533, std::string( sectionString ) );

      section::Type< 28 > chunk = section.parse< 28 >();

      THEN( "a section::Type< 28 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 28 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 28 >" ) {

    WHEN( "a string representation of a section::Type< 28 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 28 >( head, begin, end,
                                            lineNumber, 100 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+3 9.992414-1          0          0          2          0 10028533     \n"
    " 1.000000+0 0.000000+0          0          0         18          2 10028533     \n"
    " 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n"
    " 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n"
    " 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n"
    " 2.000000+0 0.000000+0          0          0         12          1 10028533     \n"
    " 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n"
    " 1.000000+0 0.000000+0 1.000000+3 1.000000+0 0.000000+0 0.000000+0 10028533     \n";
;
}

void verifyChunk( const section::Type< 28 >& chunk ) {

  CHECK( 533 == chunk.MT() );
  CHECK( 1000 == chunk.ZA() );
  CHECK( 0.9992414 == Approx( chunk.AWR() ) );
  CHECK( 0.9992414 == Approx( chunk.atomicWeightRatio() ) );


  CHECK( 8 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                   10028  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   10028  1     \n";
}
