// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/5.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialDistribution = section::Type< 5 >::PartialDistribution;
using Probability = section::Type< 5 >::Probability;
using MaxwellianFissionSpectrum = section::Type< 5 >::MaxwellianFissionSpectrum;

std::string chunk();
void verifyChunk( const section::Type< 5 >& );
std::string chunkWithNK0();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 5 >" ) {

  GIVEN( "valid data for a section::Type< 5 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      double za = 92235.;
      double awr = 2.330250e+2;

      std::vector< PartialDistribution > partials =
      { { Probability( 7, { 2 }, { 2 },
                       { 3.25e+6, 2e+7 }, { 1., 1. }, -3e+7 ),
          MaxwellianFissionSpectrum( { 3 }, { 5 },
                                     { 3.25e+6, 1.5e+7, 2e+7 },
                                     { 1.2955e+6, 1.4923e+6, 1.49447e+6 } ) } };

      section::Type< 5 > chunk( mt, za, awr, std::move( partials ) );

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 5 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 5 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 5 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 5, 18, std::string( sectionString ) );

      section::Type< 5 > chunk = section.parse< 5 >();

      THEN( "a section::Type< 5 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 5 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 5 >" ) {

    WHEN( "a string representation of a section::Type< 5 > with NK=0" ) {

      std::string sectionString = chunkWithNK0() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 5 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 5 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 5 >( head, begin, end,
                                            lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 9.223500+4 2.330250+2          0          0          1          09228 5 18     \n"
    "-3.000000+7 0.000000+0          0          7          1          29228 5 18     \n"
    "          2          2                                            9228 5 18     \n"
    " 3.250000+6 1.000000+0 2.000000+7 1.000000+0                      9228 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39228 5 18     \n"
    "          3          5                                            9228 5 18     \n"
    " 3.250000+6 1.295500+6 1.500000+7 1.492300+6 2.000000+7 1.494470+69228 5 18     \n";
}

void verifyChunk( const section::Type< 5 >& chunk ) {

  CHECK( 18 == chunk.MT() );
  CHECK( 18 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberPartialDistributions() );

  const auto& partial = chunk.partialDistributions()[0];
  CHECK_THAT( -3e+7, WithinRel( partial.U() ) );
  CHECK_THAT( -3e+7, WithinRel( partial.energyLimitConstant() ) );

  const auto& p = partial.probability();

  CHECK( 7 == p.LF() );
  CHECK( 7 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 3.25e+6, WithinRel( p.E()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 3.25e+6, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( p.P()[0] ) );
  CHECK_THAT( 1., WithinRel( p.P()[1] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[1] ) );

  const auto& d = std::get< MaxwellianFissionSpectrum >
                                         ( partial.distribution() );

  CHECK( 7 == d.LF() );
  CHECK( 7 == d.LAW() );

  CHECK( 3 == d.NP() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 5 == d.interpolants()[0] );
  CHECK( 3 == d.boundaries()[0] );
  CHECK( 3 == d.E().size() );
  CHECK( 3 == d.energies().size() );
  CHECK( 3 == d.thetas().size() );
  CHECK_THAT( 3.25e+6, WithinRel( d.E()[0] ) );
  CHECK_THAT( 1.5e+7, WithinRel( d.E()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( d.E()[2] ) );
  CHECK_THAT( 3.25e+6, WithinRel( d.energies()[0] ) );
  CHECK_THAT( 1.5e+7, WithinRel( d.energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( d.energies()[2] ) );
  CHECK_THAT( 1.2955e+6, WithinRel( d.thetas()[0] ) );
  CHECK_THAT( 1.4923e+6, WithinRel( d.thetas()[1] ) );
  CHECK_THAT( 1.49447e+6, WithinRel( d.thetas()[2] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkWithNK0() {
  return
    " 9.223500+4 2.330250+2          0          0          0          09228 5 18     \n"
    "-3.000000+7 0.000000+0          0          7          1          29228 5 18     \n"
    "          2          2                                            9228 5 18     \n"
    " 3.250000+6 1.000000+0 2.000000+7 1.000000+0                      9228 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39228 5 18     \n"
    "          3          5                                            9228 5 18     \n"
    " 3.250000+6 1.295500+6 1.500000+7 1.492300+6 2.000000+7 1.494470+69228 5 18     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 5  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 5  4     \n";
}
