#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/27.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const section::Type< 27 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 27 >" ) {

  GIVEN( "valid data for a section::Type< 27 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 502;
      int zaid = 1000;
      double awr = 0.9992414;
      std::vector< long > interpolants = { 2 };
      std::vector< long > boundaries = { 2 };
      std::vector< double > energies = { 0., 1e+9 };
      std::vector< double > values = { 1., 2. };

      section::Type< 27 > chunk( mt, zaid, awr,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ), std::move( values ) );

      THEN( "a section::Type< 27 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 27 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 27 > chunk( head, begin, end, lineNumber, 100 );

      THEN( "a section::Type< 27 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 27 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 125, 27, 502, std::string( sectionString ) );

      section::Type< 27 > chunk = section.parse< 27 >();

      THEN( "a section::Type< 27 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 27 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 27 >" ) {

    WHEN( "a string representation of a section::Type< 27 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 27 >( head, begin, end,
                                            lineNumber, 100 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+3 9.992414-1          0          0          0          0 10027502     \n"
    " 0.000000+0 1.000000+0          0          0          1          2 10027502     \n"
    "          2          2                                             10027502     \n"
    " 0.000000+0 1.000000+0 1.000000+9 2.000000+0                       10027502     \n";
}

void verifyChunk( const section::Type< 27 >& chunk ) {

  CHECK( 502 == chunk.MT() );
  CHECK( 1000 == chunk.ZA() );
  CHECK( 0.9992414 == Approx( chunk.AWR() ) );
  CHECK( 0.9992414 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.Z() );
  CHECK( 1. == chunk.atomZ() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.values().size() );
  CHECK( 0. == Approx( chunk.energies()[0] ) );
  CHECK( 1e+9 == Approx( chunk.energies()[1] ) );
  CHECK( 1 == Approx( chunk.values()[0] ) );
  CHECK( 2 == Approx( chunk.values()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                   10027  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   10027  1     \n";
}
