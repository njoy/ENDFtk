// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using KalbachMann =
section::Type< 6 >::ContinuumEnergyAngle::KalbachMann;

std::string chunkNA1();
void verifyChunkNA1( const KalbachMann& );
std::string chunkNA2();
void verifyChunkNA2( const KalbachMann& );
std::string invalidSize();
std::string invalidNA();

SCENARIO( "KalbachMann" ) {

  GIVEN( "valid data for a KalbachMann with na=1" ) {

    std::string string = chunkNA1();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      std::vector< std::array< double, 3 > > data = {
          {{ 1., 2., 3. }},
          {{ 4., 5., 6. }} };

      KalbachMann chunk( energy, nd, std::move( data ) );

      THEN( "a KalbachMann can be constructed using arrays and members can be "
            "tested" ) {

        verifyChunkNA1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a KalbachMann can be constructed and members can be tested" ) {

        verifyChunkNA1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a KalbachMann with na=2" ) {

    std::string string = chunkNA2();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      std::vector< std::array< double, 4 > > data = {
          {{ 1., 2., 3., 4. }},
          {{ 5., 6., 7., 8. }} };

      KalbachMann chunk( energy, nd, std::move( data ) );

      THEN( "a KalbachMann can be constructed using arrays and members can be "
            "tested" ) {

        verifyChunkNA2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a KalbachMann can be constructed and members can be tested" ) {

        verifyChunkNA2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a KalbachMann" ) {

    WHEN( "a string representation is used with invalid na" ) {

      std::string string = invalidNA();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW, NA" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkNA1() {
  return
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunkNA1( const KalbachMann& chunk ) {

  CHECK( 2 == chunk.LANG() );
  CHECK( 2 == chunk.representation() );
  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 1 == chunk.NA() );
  CHECK( 1 == chunk.numberAngularParameters() );
  CHECK( 6 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.EP().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK_THAT( 1., WithinRel( chunk.EP()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.energies()[1] ) );
  CHECK( 2 == chunk.parameters().size() );
  CHECK_THAT( 2., WithinRel( chunk.parameters()[0][0] ) );
  CHECK_THAT( 3., WithinRel( chunk.parameters()[0][1] ) );
  CHECK_THAT( 5., WithinRel( chunk.parameters()[1][0] ) );
  CHECK_THAT( 6., WithinRel( chunk.parameters()[1][1] ) );
  CHECK( 2 == chunk.F0().size() );
  CHECK( 2 == chunk.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( chunk.F0()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.totalEmissionProbabilities()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkNA2() {
  return
    " 0.000000+0 1.000000-5          0          2          8          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0                                            9228 6  5     \n";
}

void verifyChunkNA2( const KalbachMann& chunk ) {

  CHECK( 2 == chunk.LANG() );
  CHECK( 2 == chunk.representation() );
  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 2 == chunk.NA() );
  CHECK( 2 == chunk.numberAngularParameters() );
  CHECK( 8 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.EP().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK_THAT( 1., WithinRel( chunk.EP()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 5., WithinRel( chunk.energies()[1] ) );
  CHECK( 2 == chunk.parameters().size() );
  CHECK_THAT( 2., WithinRel( chunk.parameters()[0][0] ) );
  CHECK_THAT( 3., WithinRel( chunk.parameters()[0][1] ) );
  CHECK_THAT( 4., WithinRel( chunk.parameters()[0][2] ) );
  CHECK_THAT( 6., WithinRel( chunk.parameters()[1][0] ) );
  CHECK_THAT( 7., WithinRel( chunk.parameters()[1][1] ) );
  CHECK_THAT( 8., WithinRel( chunk.parameters()[1][2] ) );
  CHECK( 2 == chunk.F0().size() );
  CHECK( 2 == chunk.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( chunk.F0()[0] ) );
  CHECK_THAT( 6., WithinRel( chunk.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 6., WithinRel( chunk.totalEmissionProbabilities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          1          5          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           9228 6  5     \n";
}

std::string invalidNA() {
  return
    " 0.000000+0 1.000000-5          0          3         10          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                      9228 6  5     \n";
}
