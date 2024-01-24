// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/456.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using section1456 = section::Type< 1, 456 >;
using PolynomialMultiplicity = section::PolynomialMultiplicity;
using TabulatedMultiplicity = section::TabulatedMultiplicity;

std::string chunkLNU1();
void verifyChunkLNU1( const section::Type< 1, 456 >& );
std::string chunkLNU2();
void verifyChunkLNU2( const section::Type< 1, 456 >& );
std::string invalidLNU();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 456 >" ) {

  GIVEN( "valid data for a section::Type< 1, 456 > with LNU = 1" ) {

    std::string sectionString = chunkLNU1() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      PolynomialMultiplicity multiplicity( { 2.4367, 0.05 } );

      section::Type< 1, 456 > chunk( zaid, awr, std::move( multiplicity ) );

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 456 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 456, std::string( sectionString ) );

      section::Type< 1, 456 > chunk = section.parse< 1, 456 >();

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 1, 456 > with LNU = 2" ) {

    std::string sectionString = chunkLNU2() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 92235;
      double awr = 233.0248;
      TabulatedMultiplicity multiplicity( { 4 }, { 2 },
                                          { 1.00e-5, 2.53e-2, 5.00e-2, 2.00e+7 },
                                          { 2.436700e+0, 2.436700e+0,
                                            2.436700e+0, 5.209845e+0 } );

      section::Type< 1, 456 > chunk( zaid, awr, std::move( multiplicity ) );

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 1, 456 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ){

      tree::Section section( 9228, 1, 456, std::string( sectionString ) );

      section::Type< 1, 456 > chunk = section.parse< 1, 456 >();

      THEN( "a section::Type< 1, 456 > can be constructed and "
            "members can be tested" ) {

        verifyChunkLNU2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 1, 456 >" ) {

    WHEN( "a string representation of an File 1 Section 458 "
          "with an invalid LNU" ) {

      std::string sectionString = invalidLNU() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( section1456( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLNU1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1456     \n"
    " 2.436700+0 5.000000-2                                            9228 1456     \n";
}

void verifyChunkLNU1( const section::Type< 1, 456 >& chunk ) {

  CHECK( 456 == chunk.MT() );
  CHECK( 456 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LNU() );
  CHECK( 1 == chunk.representation() );

  const auto& nubar = std::get< PolynomialMultiplicity >( chunk.nubar() );

  CHECK( 1 == nubar.LNU() );
  CHECK( 1 == nubar.representation() );

  CHECK( 2 == nubar.NCO() );
  CHECK( 2 == nubar.numberCoefficients() );
  CHECK( 2 == nubar.C().size() );
  CHECK( 2 == nubar.coefficients().size() );
  CHECK_THAT( 2.4367, WithinRel( nubar.C()[0] ) );
  CHECK_THAT( 5e-2, WithinRel( nubar.C()[1] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.coefficients()[0] ) );
  CHECK_THAT( 5e-2, WithinRel( nubar.coefficients()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkLNU2() {
  return
    " 9.223500+4 2.330248+2          0          2          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1456     \n"
    "          4          2                                            9228 1456     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1456     \n"
    " 2.000000+7 5.209845+0                                            9228 1456     \n";
}

void verifyChunkLNU2( const section::Type< 1, 456 >& chunk ) {

  CHECK( 456 == chunk.MT() );
  CHECK( 456 == chunk.sectionNumber() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 233.0248, WithinRel( chunk.AWR() ) );
  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.representation() );

  const auto& nubar = std::get< TabulatedMultiplicity >( chunk.nubar() );

  CHECK( 2 == nubar.LNU() );
  CHECK( 2 == nubar.representation() );

  CHECK( 4 == nubar.NP() );
  CHECK( 1 == nubar.NR() );
  CHECK( 1 == nubar.interpolants().size() );
  CHECK( 1 == nubar.boundaries().size() );
  CHECK( 2 == nubar.interpolants()[0] );
  CHECK( 4 == nubar.boundaries()[0] );

  CHECK( 4 == nubar.E().size() );
  CHECK( 4 == nubar.energies().size() );
  CHECK( 4 == nubar.NU().size() );
  CHECK( 4 == nubar.multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( nubar.E()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( nubar.E()[1] ) );
  CHECK_THAT( 0.05, WithinRel( nubar.E()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( nubar.E()[3] ) );
  CHECK_THAT( 1e-5, WithinRel( nubar.energies()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( nubar.energies()[1] ) );
  CHECK_THAT( 0.05, WithinRel( nubar.energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( nubar.energies()[3] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.NU()[0] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.NU()[1] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.NU()[2] ) );
  CHECK_THAT( 5.209845, WithinRel( nubar.NU()[3] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.multiplicities()[0] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.multiplicities()[1] ) );
  CHECK_THAT( 2.4367, WithinRel( nubar.multiplicities()[2] ) );
  CHECK_THAT( 5.209845, WithinRel( nubar.multiplicities()[3] ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidLNU() {
  return
    " 9.223500+4 2.330248+2          0          3          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1456     \n"
    " 2.436700+0 5.000000-2                                            9228 1456     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}
