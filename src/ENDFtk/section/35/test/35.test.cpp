// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/35.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using SquareMatrix = section::Type< 35 >::SquareMatrix;

std::string chunk();
void verifyChunk( const section::Type< 35 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 35 >" ) {

  GIVEN( "valid data for a section::Type< 35 > with data" ) {

    std::string string = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      // SquareMatrix (energyBlock)
      auto block = SquareMatrix( 0., 1.0e6, { 0, 100, 200 }, { 1, 2, 3 } );

      // Section
      auto chunk = section::Type< 35 >( 18, 94239., 2.369986e+2, {block} );

      THEN( "a Section can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 35 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 35 > chunk( head, begin, end, lineNumber, 9437 );

      THEN( "a Section object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 35 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "there is a tree::Section" ) {

      auto begin = string.begin();
      auto position = begin;
      auto end = string.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      tree::Section section( head, begin, position, end, lineNumber );

      section::Type< 35 > chunk = section.parse< 35 >( lineNumber );

      THEN( "a section::Type< 35 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 35 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "a string representation with an invalid SEND" ) {

    std::string sectionString = chunk() + invalidSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );

    THEN( "an exception is thrown upon construction" ) {

      CHECK_THROWS( section::Type< 35 >( head, begin, end, lineNumber, 9437 ) );
    } // THEN

  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 9.423900+4 2.369986+2          0          0          1          0943735 18     \n"
    " 0.000000+0 1.000000+6          1          7          6          3943735 18     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943735 18     \n";
}

std::string validSEND() {
  return
    "                                                                  943735  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  943735  2     \n";
}

void verifyChunk( const section::Type< 35 >& chunk ) {

  // HEAD record
  CHECK( 94239 == chunk.ZA() );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberEnergyBlocks() );
  CHECK( 1 == chunk.energyBlocks().size() );

  auto sub = chunk.energyBlocks()[0];

  // subsection
  CHECK( 7 == sub.LB() );
  CHECK( 7 == sub.procedure() );
  CHECK( 6 == sub.NT() );
  CHECK( 6 == sub.numberValues() );
  CHECK( 3 == sub.NE() );
  CHECK( 3 == sub.numberEnergies() );
  CHECK_THAT( 0., WithinRel( sub.energies()[0] ) );
  CHECK_THAT( 100., WithinRel( sub.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( sub.energies()[2] ) );
  CHECK_THAT( 1., WithinRel( sub.values()[0] ) );
  CHECK_THAT( 2., WithinRel( sub.values()[1] ) );
  CHECK_THAT( 3., WithinRel( sub.values()[2] ) );

  CHECK( 3 == chunk.NC() );

}
