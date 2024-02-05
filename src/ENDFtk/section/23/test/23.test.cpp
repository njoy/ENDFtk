// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/23.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const section::Type< 23 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 23 >" ) {

  GIVEN( "valid data for a section::Type< 23 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 525;
      int zaid = 1000;
      double awr = 0.9992414;
      double epe = 1.;
      double efl = 2.;
      std::vector< long > interpolants = { 2 };
      std::vector< long > boundaries = { 2 };
      std::vector< double > energies = { 10., 1e+11 };
      std::vector< double > xs = { 274896000., 1.31176E-5 };

      section::Type< 23 > chunk( mt, zaid, awr, epe, efl,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ), std::move( xs ) );

      THEN( "a section::Type< 23 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 23 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 23 > chunk( head, begin, end, lineNumber, 100 );

      THEN( "a section::Type< 23 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 23 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 125, 23, 525, std::string( sectionString ) );

      section::Type< 23 > chunk = section.parse< 23 >();

      THEN( "a section::Type< 23 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 23 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 23 >" ) {

    WHEN( "a string representation of a section::Type< 23 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 23 >( head, begin, end,
                                            lineNumber, 100 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk() {

  return
    " 1.000000+3 9.992414-1          0          0          0          0 10023525     \n"
    " 1.000000+0 2.000000+0          0          0          1          2 10023525     \n"
    "          2          2                                             10023525     \n"
    " 1.000000+1 2.748960+8 1.00000+11 1.311760-5                       10023525     \n";
}

void verifyChunk( const section::Type< 23 >& chunk ) {

  CHECK( 525 == chunk.MT() );
  CHECK( 525 == chunk.sectionNumber() );
  CHECK( 1000 == chunk.ZA() );
  CHECK( 1000 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9992414, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9992414, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 1., WithinRel( chunk.EPE() ) );
  CHECK_THAT( 1., WithinRel( chunk.subshellBindingEnergy() ) );
  CHECK_THAT( 2., WithinRel( chunk.EFL() ) );
  CHECK_THAT( 2., WithinRel( chunk.fluorescenceYield() ) );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.crossSections().size() );
  CHECK_THAT( 10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+11, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2.748960e+8, WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 1.31176E-5, WithinRel( chunk.crossSections()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                   10023  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   10023  1     \n";
}
