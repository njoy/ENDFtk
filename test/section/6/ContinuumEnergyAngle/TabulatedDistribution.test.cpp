// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedDistribution =
section::Type< 6 >::ContinuumEnergyAngle::TabulatedDistribution;

std::string chunk();
void verifyChunk( int, const TabulatedDistribution& );
std::string invalidSize();

SCENARIO( "TabulatedDistribution" ) {

  GIVEN( "valid data for a TabulatedDistribution" ) {

    std::string string = chunk();
    std::vector< int > langs = { 11, 12, 13, 14, 15 };

    WHEN( "the data is given explicitly" ) {

      for ( auto lang : langs ) {

        double energy = 1e-5;
        int nd = 0;
        int na = 4;

        std::vector< double > energies = { 1., 7. };
        std::vector< double > emissions = { 2., 8. };
        std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                         { 9., 11. } };
        std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                               { 10., 12. } };
        TabulatedDistribution chunk( lang, energy, nd, na,
                                     std::move( energies ),
                                     std::move( emissions ),
                                     std::move( cosines ),
                                     std::move( probabilities ) );

        THEN( "a TabulatedDistribution can  be constructed and members can "
              "be tested for each LANG value" ) {

          verifyChunk( lang, chunk );
        } // THEN

        THEN( "it can be printed" ) {

          std::string buffer;
          auto output = std::back_inserter( buffer );
          chunk.print( output, 9228, 6, 5 );
          CHECK( buffer == string );
        } // THEN
      }
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      for ( auto lang : langs ) {

        auto begin = string.begin();
        auto end = string.end();
        long lineNumber = 1;

        TabulatedDistribution chunk( lang, begin, end, lineNumber, 9228, 6, 5 );

        THEN( "a TabulatedDistribution can be constructed and members can "
              "be tested for each LANG value" ) {

          verifyChunk( lang, chunk );
        } // THEN

        THEN( "it can be printed" ) {

          std::string buffer;
          auto output = std::back_inserter( buffer );
          chunk.print( output, 9228, 6, 5 );
          CHECK( buffer == string );
        } // THEN
      }
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedDistribution" ) {

    // LANG is not on a TabulatedDistribution section but we do store it
    int lang = 14;

    WHEN( "data with inconsistent sizes is given" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 4;
      std::vector< double > energies = { 1., 7. };
      std::vector< double > wrongEnergies = { 1., 7., 8. };
      std::vector< double > emissions = { 2., 8. };
      std::vector< double > wrongEmissions = { 2., 8., 3. };
      std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                     { 9., 11. } };
      std::vector< std::vector< double > > wrongCosines = { { 3., 5., 6. },
                                                            { 9., 11. } };
      std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                           { 10., 12. } };
      std::vector< std::vector< double > > wrongProbabilities =
                                             { { 4., 6., 7. }, { 10., 12. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( lang, energy, nd, na,
                                              std::move( wrongEnergies ),
                                              std::move( emissions ),
                                              std::move( cosines ),
                                              std::move( probabilities ) ) );
        CHECK_THROWS( TabulatedDistribution( lang, energy, nd, na,
                                              std::move( energies ),
                                              std::move( wrongEmissions ),
                                              std::move( cosines ),
                                              std::move( probabilities ) ) );
        CHECK_THROWS( TabulatedDistribution( lang, energy, nd, na,
                                              std::move( energies ),
                                              std::move( emissions ),
                                              std::move( wrongCosines ),
                                              std::move( probabilities ) ) );
        CHECK_THROWS( TabulatedDistribution( lang, energy, nd, na,
                                             std::move( energies ),
                                             std::move( emissions ),
                                             std::move( cosines ),
                                             std::move( wrongProbabilities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NW, NA, NEP is given" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( lang, begin, end, lineNumber,
                                             9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "invalid LANG values are given" ) {

      std::vector< int > invalidLANGs = { -1, 0, 10, 16, 20 };

      THEN( "an exception is thrown" ) {

        for ( auto lang : invalidLANGs ) {

          double energy = 1e-5;
          int nd = 0;
          int na = 4;
          std::vector< double > energies = { 1., 7. };
          std::vector< double > emissions = { 2., 8. };
          std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                           { 9., 11. } };
          std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                                 { 10., 12. } };

          std::string string = chunk();

          auto begin = string.begin();
          auto end = string.end();
          long lineNumber = 1;

          CHECK_THROWS( TabulatedDistribution( lang, energy, nd, na,
                                               std::move( energies ),
                                               std::move( emissions ),
                                               std::move( cosines ),
                                               std::move( probabilities ) ) );
          CHECK_THROWS(
            TabulatedDistribution( lang, begin, end, lineNumber, 9228, 6, 5 ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n";
}

void verifyChunk( int lang, const TabulatedDistribution& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( lang == chunk.LANG() );
  CHECK( lang == chunk.representation() );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 4 == chunk.NA() );
  CHECK( 4 == chunk.numberAngularParameters() );
  CHECK( 12 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.EP().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK_THAT( 1., WithinRel( chunk.EP()[0] ) );
  CHECK_THAT( 7., WithinRel( chunk.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 7., WithinRel( chunk.energies()[1] ) );
  CHECK( 2 == chunk.F0().size() );
  CHECK( 2 == chunk.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( chunk.F0()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.totalEmissionProbabilities()[1] ) );
  CHECK( 2 == chunk.MU().size() );
  CHECK( 2 == chunk.cosines().size() );
  CHECK_THAT( 3., WithinRel( chunk.MU()[0][0] ) );
  CHECK_THAT( 5., WithinRel( chunk.MU()[0][1] ) );
  CHECK_THAT( 9., WithinRel( chunk.MU()[1][0] ) );
  CHECK_THAT( 11., WithinRel( chunk.MU()[1][1] ) );
  CHECK_THAT( 3., WithinRel( chunk.cosines()[0][0] ) );
  CHECK_THAT( 5., WithinRel( chunk.cosines()[0][1] ) );
  CHECK_THAT( 9., WithinRel( chunk.cosines()[1][0] ) );
  CHECK_THAT( 11., WithinRel( chunk.cosines()[1][1] ) );
  CHECK( 2 == chunk.F().size() );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK_THAT( 4., WithinRel( chunk.F()[0][0] ) );
  CHECK_THAT( 6., WithinRel( chunk.F()[0][1] ) );
  CHECK_THAT( 10., WithinRel( chunk.F()[1][0] ) );
  CHECK_THAT( 12., WithinRel( chunk.F()[1][1] ) );
  CHECK_THAT( 4., WithinRel( chunk.probabilities()[0][0] ) );
  CHECK_THAT( 6., WithinRel( chunk.probabilities()[0][1] ) );
  CHECK_THAT( 10., WithinRel( chunk.probabilities()[1][0] ) );
  CHECK_THAT( 12., WithinRel( chunk.probabilities()[1][1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          4         13          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+0                                                       9228 6  5     \n";
}
