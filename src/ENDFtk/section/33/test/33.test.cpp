// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/33.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionBlock = section::ReactionBlock;
using DerivedCovariance = section::DerivedCovariance;
using DerivedRedundant = section::DerivedRedundant;
using DerivedRatioToStandard = section::DerivedRatioToStandard;
using SquareMatrix = section::SquareMatrix;
using RectangularMatrix = section::RectangularMatrix;
using CovariancePairs = section::CovariancePairs;
using ExplicitCovariance = section::ExplicitCovariance;

std::string chunk();
void verifyChunk( const section::Type< 33 >& );
std::string lump();
void verifyLump( const section::Type< 33 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 33 >" ) {

  GIVEN( "valid data for a section::Type< 33 > with data" ) {

    std::string string = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      // NC Type
      double lower = 2.500000e+3;
      double upper = 2.000000e+7;
      std::vector< double > coefficients = {1, -1, -1, -1, -1, -1, -1};
      std::vector< int > reactions = {1, 4, 16, 17, 18, 37, 102};
      std::vector< DerivedCovariance > nc = {
        DerivedRedundant( lower, upper,
                          std::move(coefficients),
                          std::move(reactions) ) };

      // NI Type
      std::vector< double > energies = { 0, 100, 200 };
      std::vector< double > svalues = { 1, 2, 3, 4 };
      std::vector< ExplicitCovariance > ni = {
        SquareMatrix( 0, std::move(energies), std::move(svalues) ) };

      // ReactionBlock
      auto sub = ReactionBlock( 1., 2., 3, 4, std::move( nc ), std::move( ni ) );

      // Section
      auto chunk = section::Type< 33 >( 2, 94239., 2.369986e+2, {sub} );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 33 > chunk( head, begin, end, lineNumber, 9437 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33 );
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

      section::Type< 33 > chunk = section.parse< 33 >( lineNumber );

      THEN( "a section::Type< 33 > can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "valid data for a lumped covariance section::Type< 33 >" ) {

    std::string string = lump() + validSEND();

    WHEN( "the data is given explicitly" ) {

      // Section
      auto lump = section::Type< 33 >( 51, 94239., 2.369986e+2, 850 );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyLump( lump );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        lump.print( output, 9437, 33 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 33 > lump( head, begin, end, lineNumber, 9437 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyLump( lump );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        lump.print( output, 9437, 33 );
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

      CHECK_THROWS( section::Type< 33 >( head, begin, end, lineNumber, 9437 ) );
    } // THEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 9.423900+4 2.369986+2          0          0          0          1943733  2     \n"
    " 1.000000+0 2.000000+0          3          4          1          1943733  2     \n"
    " 0.000000+0 0.000000+0          0          0          0          0943733  2     \n"
    " 2.500000+3 2.000000+7          0          0         14          7943733  2     \n"
    " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943733  2     \n"
    "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943733  2     \n"
    "-1.000000+0 1.020000+2                                            943733  2     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943733  2     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943733  2     \n"
    " 4.000000+0                                                       943733  2     \n";
}

std::string lump() {
  return
    " 9.423900+4 2.369986+2          0        850          0          0943733 51     \n";
}

std::string validSEND() {
  return
    "                                                                  943733  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  943733  2     \n";
}

void verifyChunk( const section::Type< 33 >& chunk ) {

  // HEAD record
  CHECK( 94239 == chunk.ZA() );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.369986e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.MTL() );
  CHECK( 0 == chunk.lumpedCovarianceIndex() );
  CHECK( 1 == chunk.NL() );
  CHECK( 1 == chunk.numberReactions() );
  CHECK( 1 == chunk.reactions().size() );
  CHECK( 2 == chunk.MT() );
  CHECK( 2 == chunk.sectionNumber() );

  auto sub = chunk.reactions()[0];

  // subsection CONT record
  CHECK( 1 == sub.XMF1() );
  CHECK( 1 == sub.secondFileNumber() );
  CHECK( 2 == sub.XLFS1() );
  CHECK( 2 == sub.secondFinalExcitedState() );
  CHECK( 3 == sub.MAT1() );
  CHECK( 3 == sub.secondMaterialNumber() );
  CHECK( 4 == sub.MT1() );
  CHECK( 4 == sub.secondSectionNumber() );
  CHECK( 1 == sub.NK() );
  CHECK( 1 == sub.numberDerived() );
  CHECK( 1 == sub.NI() );
  CHECK( 1 == sub.numberExplicit() );
  CHECK( 1 == sub.derivedCovariances().size() );
  CHECK( 1 == sub.explicitCovariances().size() );

  CHECK( 10 == chunk.NC() );

}

void verifyLump( const section::Type< 33 >& lump ) {

  // HEAD record
  CHECK( 94239 == lump.ZA() );
  CHECK_THAT( 2.369986e+2, WithinRel( lump.AWR() ) );
  CHECK_THAT( 2.369986e+2, WithinRel( lump.atomicWeightRatio() ) );
  CHECK( 850 == lump.MTL() );
  CHECK( 850 == lump.lumpedCovarianceIndex() );
  CHECK( 0 == lump.NL() );
  CHECK( 0 == lump.numberReactions() );
  CHECK( 0 == lump.reactions().size() );
  CHECK( 51 == lump.MT() );
  CHECK( 51 == lump.sectionNumber() );

  CHECK( 1 == lump.NC() );

}
