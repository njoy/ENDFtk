// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/28.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using SubshellData = section::Type< 28 >::SubshellData;

std::string chunk();
void verifyChunk( const section::Type< 28 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 28 >" ) {

  GIVEN( "valid data for a section::Type< 28 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 533;
      int zaid = 1000;
      double awr = 0.9992414;

      std::vector< SubshellData > subshells = {

        SubshellData( 1, 1.1561e+4, 2, { 3, 4 }, { 2, 3 },
                      { 9.5066e+4, 9.8928e+4 }, { 0.75, 0.25 } ),
        SubshellData( 2, 2000., 1, { 1 }, { 0 }, { 1000. }, { 1. } )
      };

      section::Type< 28 > chunk( mt, zaid, awr, std::move( subshells ) );

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
    " 2.000000+3 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n"
    " 1.000000+0 0.000000+0 1.000000+3 1.000000+0 0.000000+0 0.000000+0 10028533     \n";
;
}

void verifyChunk( const section::Type< 28 >& chunk ) {

  CHECK( 533 == chunk.MT() );
  CHECK( 533 == chunk.sectionNumber() );
  CHECK( 1000 == chunk.ZA() );
  CHECK( 1000 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9992414, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9992414, WithinRel( chunk.atomicWeightRatio() ) );

  auto shell = chunk.subshells()[0];
  CHECK( 1 == shell.SUBI() );
  CHECK( 1 == shell.subshellDesignator() );
  CHECK( 2 == shell.NTR() );
  CHECK( 2 == shell.numberTransitions() );
  CHECK_THAT( 1.156100e+4, WithinRel( shell.EBI() ) );
  CHECK_THAT( 1.156100e+4, WithinRel( shell.subshellBindingEnergy() ) );
  CHECK( 2 == shell.ELN() );
  CHECK( 2 == shell.numberSubshellElectrons() );
  CHECK( 2 == shell.transitions().size() );
  CHECK( 3 == shell.transitions()[0].SUBJ() );
  CHECK( 4 == shell.transitions()[1].SUBJ() );
  CHECK( 2 == shell.transitions()[0].SUBK() );
  CHECK( 3 == shell.transitions()[1].SUBK() );
  CHECK_THAT( 9.5066e+4, WithinRel( shell.transitions()[0].ETR() ) );
  CHECK_THAT( 9.8928e+4, WithinRel( shell.transitions()[1].ETR() ) );
  CHECK_THAT( 0.75, WithinRel( shell.transitions()[0].FTR() ) );
  CHECK_THAT( 0.25, WithinRel( shell.transitions()[1].FTR() ) );

  shell = chunk.subshells()[1];
  CHECK( 2 == shell.SUBI() );
  CHECK( 2 == shell.subshellDesignator() );
  CHECK( 1 == shell.NTR() );
  CHECK( 1 == shell.numberTransitions() );
  CHECK_THAT( 2000., WithinRel( shell.EBI() ) );
  CHECK_THAT( 2000., WithinRel( shell.subshellBindingEnergy() ) );
  CHECK( 1 == shell.ELN() );
  CHECK( 1 == shell.numberSubshellElectrons() );
  CHECK( 1 == shell.transitions().size() );
  CHECK( 1 == shell.transitions()[0].SUBJ() );
  CHECK( 0 == shell.transitions()[0].SUBK() );
  CHECK_THAT( 1000., WithinRel( shell.transitions()[0].ETR() ) );
  CHECK_THAT( 1., WithinRel( shell.transitions()[0].FTR() ) );

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
