// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/ReactionBlock.hpp"

// other includes

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

std::string chunkNCOnly();
std::string chunkNIOnly();
std::string chunkBoth();
void verifyChunkNCOnly( const ReactionBlock& );
void verifyChunkNIOnly( const ReactionBlock& );
void verifyChunkBoth( const ReactionBlock& );


SCENARIO( "ReactionBlock" ) {

  GIVEN( "valid data for a ReactionBlock with an NC-Type Sub-ReactionBlock" ) {

    std::string string = chunkNCOnly();

    WHEN( "the data is given explicitly" ) {

      double lower = 2.500000e+3;
      double upper = 2.000000e+7;
      std::vector< double > coefficients = {1, -1, -1, -1, -1, -1, -1};
      std::vector< int > reactions = {1, 4, 16, 17, 18, 37, 102};
      std::vector< double > energies = {1, 2};
      std::vector< double > weights = {3, 4};

      std::vector< DerivedCovariance > nc = {
        DerivedRedundant( lower, upper,
                          std::move(coefficients),
                          std::move(reactions) ),
        DerivedRatioToStandard( 1, 2.5e+3, 2.0e+7, 325, 102, 3, 0,
                                std::move(energies),
                                std::move(weights) ) };

      auto chunk = ReactionBlock( 0, 0, 0, 2, std::move( nc ) );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkNCOnly( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionBlock chunk( begin, end, lineNumber, 9437, 33, 2 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunkNCOnly( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN


  GIVEN( "valid data for a ReactionBlock with NI-Type Subsections" ) {

    std::string string = chunkNIOnly();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > rowEnergies = { 1.1, 1.2, 1.3 };
      std::vector< double > columnEnergies = { 2.1, 2.2, 2.3, 2.4 };
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > energies = { 0, 100, 200 };
      std::vector< double > svalues = { 1, 2, 3, 4 };

      std::vector< ExplicitCovariance > ni = {
        SquareMatrix( 0, std::move(energies), std::move(svalues) ),
        RectangularMatrix( std::move(rowEnergies),
                           std::move(columnEnergies),
                           std::move(values) ),
        CovariancePairs( 1, { 1., 3. }, { 2., 4. } ) };

      auto chunk = ReactionBlock( 1., 2., 3, 4, std::move( ni ) );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkNIOnly( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionBlock chunk( begin, end, lineNumber, 9437, 33, 2 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunkNIOnly( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN

  GIVEN( "valid data for a ReactionBlock with both Subsection types" ) {

    std::string string = chunkBoth();

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

      auto chunk = ReactionBlock( 1., 2., 3, 4, std::move( nc ), std::move( ni ) );

      THEN( "a ReactionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkBoth( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionBlock chunk( begin, end, lineNumber, 9437, 33, 2 );

      THEN( "a ReactionBlock object can be constructed "
            "and members can be tested" ) {

        verifyChunkBoth( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

std::string chunkNCOnly() {
  return
    " 0.000000+0 0.000000+0          0          2          2          0943733  2     \n"
    " 0.000000+0 0.000000+0          0          0          0          0943733  2     \n"
    " 2.500000+3 2.000000+7          0          0         14          7943733  2     \n"
    " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943733  2     \n"
    "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943733  2     \n"
    "-1.000000+0 1.020000+2                                            943733  2     \n"
    " 0.000000+0 0.000000+0          0          1          0          0943733  2     \n"
    " 2.500000+3 2.000000+7        325        102          6          2943733  2     \n"
    " 3.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+0 4.000000+0943733  2     \n";
}

std::string chunkNIOnly() {
  return
    " 1.000000+0 2.000000+0          3          4          0          3943733  2     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943733  2     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943733  2     \n"
    " 4.000000+0                                                       943733  2     \n"
    " 0.000000+0 0.000000+0          0          6         13          3943733  2     \n"
    " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0943733  2     \n"
    " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0943733  2     \n"
    " 6.000000+0                                                       943733  2     \n"
    " 0.000000+0 0.000000+0          0          1          4          2943733  2     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      943733  2     \n";
}

std::string chunkBoth() {
  return
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


void verifyChunkNCOnly( const ReactionBlock& chunk ) {

  // ReactionBlock CONT record
  CHECK( 0 == chunk.XMF1() );
  CHECK( 0 == chunk.secondFileNumber() );
  CHECK( 0 == chunk.XLFS1() );
  CHECK( 0 == chunk.secondFinalExcitedState() );
  CHECK( 0 == chunk.MAT1() );
  CHECK( 0 == chunk.secondMaterialNumber() );
  CHECK( 2 == chunk.MT1() );
  CHECK( 2 == chunk.secondSectionNumber() );
  CHECK( 2 == chunk.NK() );
  CHECK( 2 == chunk.numberDerived() );
  CHECK( 0 == chunk.NI() );
  CHECK( 0 == chunk.numberExplicit() );
  CHECK( 2 == chunk.derivedCovariances().size() );
  CHECK( 0 == chunk.explicitCovariances().size() );

  auto chunky = std::get< DerivedRedundant >( chunk.derivedCovariances()[0] );

  // metadata
  CHECK( 0 == chunky.LTY() );
  CHECK( 0 == chunky.procedure() );
  CHECK_THAT( 2.5e3, WithinRel( chunky.E1() ) );
  CHECK_THAT( 2.5e3, WithinRel( chunky.lowerEnergy() ) );
  CHECK_THAT( 2.0e7, WithinRel( chunky.E2() ) );
  CHECK_THAT( 2.0e7, WithinRel( chunky.upperEnergy() ) );
  CHECK( 7 == chunky.NCI() );
  CHECK( 7 == chunky.numberReactions() );

  // values
  CHECK_THAT( 1.0, WithinRel( chunky.coefficients()[0] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[1] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[2] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[3] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[4] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[5] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.coefficients()[6] ) );
  CHECK_THAT( -1.0, WithinRel( chunky.CI()[6] ) );
  CHECK_THAT( 1., WithinRel( chunky.reactions()[0] ) );
  CHECK_THAT( 4., WithinRel( chunky.reactions()[1] ) );
  CHECK_THAT( 16., WithinRel( chunky.reactions()[2] ) );
  CHECK_THAT( 17., WithinRel( chunky.reactions()[3] ) );
  CHECK_THAT( 18., WithinRel( chunky.reactions()[4] ) );
  CHECK_THAT( 37., WithinRel( chunky.reactions()[5] ) );
  CHECK_THAT( 102., WithinRel( chunky.reactions()[6] ) );
  CHECK_THAT( 102., WithinRel( chunky.XMTI()[6] ) );

  CHECK( 9 == chunk.NC() );
}

void verifyChunkNIOnly( const ReactionBlock& chunk ) {

  // ReactionBlock CONT record
  CHECK( 1 == chunk.XMF1() );
  CHECK( 1 == chunk.secondFileNumber() );
  CHECK( 2 == chunk.XLFS1() );
  CHECK( 2 == chunk.secondFinalExcitedState() );
  CHECK( 3 == chunk.MAT1() );
  CHECK( 3 == chunk.secondMaterialNumber() );
  CHECK( 4 == chunk.MT1() );
  CHECK( 4 == chunk.secondSectionNumber() );
  CHECK( 0 == chunk.NK() );
  CHECK( 0 == chunk.numberDerived() );
  CHECK( 3 == chunk.NI() );
  CHECK( 3 == chunk.numberExplicit() );
  CHECK( 0 == chunk.derivedCovariances().size() );
  CHECK( 3 == chunk.explicitCovariances().size() );

  auto stuff = std::get< SquareMatrix >( chunk.explicitCovariances()[0] );

  // metadata
  CHECK( 0 == stuff.LS() );
  CHECK( 0 == stuff.symmetryFlag() );
  CHECK( !stuff.isSymmetric() );
  CHECK( 5 == stuff.LB() );
  CHECK( 5 == stuff.procedure() );
  CHECK( 7 == stuff.NT() );
  CHECK( 7 == stuff.numberValues() );
  CHECK( 3 == stuff.NE() );
  CHECK( 3 == stuff.numberEnergies() );

  // values
  CHECK_THAT( 0., WithinRel( stuff.energies()[0] ) );
  CHECK_THAT( 100., WithinRel( stuff.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( stuff.energies()[2] ) );
  CHECK_THAT( 1., WithinRel( stuff.values()[0] ) );
  CHECK_THAT( 2., WithinRel( stuff.values()[1] ) );
  CHECK_THAT( 3., WithinRel( stuff.values()[2] ) );
  CHECK_THAT( 4., WithinRel( stuff.values()[3] ) );

  CHECK( 10 == chunk.NC() );

}

void verifyChunkBoth( const ReactionBlock& chunk ) {

  // ReactionBlock CONT record
  CHECK( 1 == chunk.XMF1() );
  CHECK( 1 == chunk.secondFileNumber() );
  CHECK( 2 == chunk.XLFS1() );
  CHECK( 2 == chunk.secondFinalExcitedState() );
  CHECK( 3 == chunk.MAT1() );
  CHECK( 3 == chunk.secondMaterialNumber() );
  CHECK( 4 == chunk.MT1() );
  CHECK( 4 == chunk.secondSectionNumber() );
  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberDerived() );
  CHECK( 1 == chunk.NI() );
  CHECK( 1 == chunk.numberExplicit() );
  CHECK( 1 == chunk.derivedCovariances().size() );
  CHECK( 1 == chunk.explicitCovariances().size() );

  CHECK( 9 == chunk.NC() );

}
