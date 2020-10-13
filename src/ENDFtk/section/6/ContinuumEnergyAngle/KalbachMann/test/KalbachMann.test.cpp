#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      int nep = 2;
      std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
      std::vector< std::array< double, 3 > > data = {
          {{ 1., 2., 3. }},
          {{ 4., 5., 6. }} };

      THEN( "a KalbachMann can be constructed using a list and members can be "
            "tested" ) {

        KalbachMann chunk( energy, nd, na, nep, std::move( list ) );
        verifyChunkNA1( chunk );
      }

      THEN( "a KalbachMann can be constructed using arrays and members can be "
            "tested" ) {

        KalbachMann chunk( energy, nd, nep, std::move( data ) );
        verifyChunkNA1( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkNA1();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a KalbachMann can be constructed and members can be tested" ) {

        KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkNA1( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a KalbachMann with na=2" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 2;
      int nep = 2;
      std::vector< double > list = { 1., 2., 3., 4., 5., 6., 7., 8. };
      std::vector< std::array< double, 4 > > data = {
          {{ 1., 2., 3., 4. }},
          {{ 5., 6., 7., 8. }} };

      THEN( "a KalbachMann can  be constructed using a list and members can be "
            "tested" ) {

        KalbachMann chunk( energy, nd, na, nep, std::move( list ) );
        verifyChunkNA2( chunk );
      }

      THEN( "a KalbachMann can be constructed using arrays and members can be "
            "tested" ) {

        KalbachMann chunk( energy, nd, nep, std::move( data ) );
        verifyChunkNA2( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkNA2();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a KalbachMann can be constructed and members can be tested" ) {

        KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkNA2( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of KalbachMann with na=1" ) {

    std::string string = chunkNA1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    KalbachMann chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of KalbachMann with na=2" ) {

    std::string string = chunkNA2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    KalbachMann chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "data is used with an invalid na" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 0;
      int nep = 2;
      std::vector< double > list = { 1., 2., 3., 4., 5., 6. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( KalbachMann( energy, nd, na, nep,
                                     std::move( list ) ) );
      } // THEN
    } // WHEN

    WHEN( "data is used with inconsistent sizes" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      int nep = 2;
      std::vector< double > wronglist = { 1., 2., 3., 4., 5. };
      std::vector< std::array< double, 3 > > datana1 = {
          {{ 1., 2., 3. }} };
      std::vector< std::array< double, 4 > > datana2 = {
          {{ 1., 2., 3., 4. }} };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( KalbachMann( energy, nd, na, nep,
                                   std::move( wronglist ) ) );
        CHECK_THROWS( KalbachMann( energy, nd, nep,
                                   std::move( datana1 ) ) );
        CHECK_THROWS( KalbachMann( energy, nd, nep,
                                   std::move( datana2 ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with invalid na" ) {

      std::string string = invalidNA();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW, NA, NEP" ) {

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
  CHECK( 1e-5 == Approx( chunk.energy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 1 == chunk.NA() );
  CHECK( 1 == chunk.numberAngularParameters() );
  CHECK( 6 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 4. == Approx( chunk.energies()[1] ) );
  CHECK( 2 == chunk.parameters().size() );
  CHECK( 2. == Approx( chunk.parameters()[0][0] ) );
  CHECK( 3. == Approx( chunk.parameters()[0][1] ) );
  CHECK( 5. == Approx( chunk.parameters()[1][0] ) );
  CHECK( 6. == Approx( chunk.parameters()[1][1] ) );
  CHECK( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

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
  CHECK( 1e-5 == Approx( chunk.energy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 2 == chunk.NA() );
  CHECK( 2 == chunk.numberAngularParameters() );
  CHECK( 8 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 5. == Approx( chunk.energies()[1] ) );
  CHECK( 2 == chunk.parameters().size() );
  CHECK( 2. == Approx( chunk.parameters()[0][0] ) );
  CHECK( 3. == Approx( chunk.parameters()[0][1] ) );
  CHECK( 4. == Approx( chunk.parameters()[0][2] ) );
  CHECK( 6. == Approx( chunk.parameters()[1][0] ) );
  CHECK( 7. == Approx( chunk.parameters()[1][1] ) );
  CHECK( 8. == Approx( chunk.parameters()[1][2] ) );
  CHECK( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
  CHECK( 6. == Approx( chunk.totalEmissionProbabilities()[1] ) );

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
