#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Tabulated =
section::Type< 6 >::ContinuumEnergyAngle::Tabulated;

std::string chunk();
void checkTabulated( const Tabulated& );
std::string invalidSize();

SCENARIO( "Tabulated" ) {

  GIVEN( "valid data for a Tabulated" ) {

    std::vector< int > langs = { 11, 12, 13, 14, 15 };

    WHEN( "the data is given explicitly" ) {

      THEN( "a Tabulated can "
            "be constructed using a list and members can be tested "
            "for each LANG value" ) {

        for ( auto lang : langs ) {

          double energy = 1e-5;
          int nd = 0;
          int na = 4;
          int nep = 2;

          std::vector< double > list = {  1.,  2.,  3.,  4.,  5.,  6.,
                                          7.,  8.,  9., 10., 11., 12. };

          Tabulated chunk( lang, energy, nd, na, nep, std::move( list ) );
          CHECK( lang == chunk.LANG() );
          checkTabulated( chunk );
        }
      }

      THEN( "a Tabulated can "
            "be constructed using vectors and members can be tested "
            "for each LANG value" ) {

        for ( auto lang : langs ) {

          double energy = 1e-5;
          int nd = 0;
          int na = 4;
          int nep = 2;

          std::vector< double > energies = { 1., 7. };
          std::vector< double > totalEmissionProbabilities = { 2., 8. };
          std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                           { 9., 11. } };
          std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                                 { 10., 12. } };
          Tabulated chunk( lang, energy, nd, na, nep, std::move( energies ),
                           std::move( totalEmissionProbabilities ),
                           std::move( cosines ),
                           std::move( probabilities ) );
          checkTabulated( chunk );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();

      THEN( "a Tabulated can "
            "be constructed and members can be tested "
            "for each LANG value" ) {

        for ( auto lang : langs ) {

          auto begin = string.begin();
          auto end = string.end();
          long lineNumber = 1;

          Tabulated chunk( lang, begin, end, lineNumber, 9228, 6, 5 );
          checkTabulated( chunk );
        }
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of Tabulated" ) {

    int lang = 14;

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    Tabulated chunk( lang, begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a Tabulated" ) {

    int lang = 14; // LANG is not on a Tabulated section but we do store it

    WHEN( "data with inconsistent sizes is given" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 4;
      int nep = 2;
      std::vector< double > list = {  1.,  2.,  3.,  4.,  5.,  6.,
                                      7.,  8.,  9., 10., 11., 12. };
      std::vector< double > energies = { 1., 7. };
      std::vector< double > wrongEnergies = { 1., 7., 8. };
      std::vector< double > totalEmissionProbabilities = { 2., 8. };
      std::vector< double > wrongTotalEmissionProbabilities = { 2., 8., 3. };
      std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                     { 9., 11. } };
      std::vector< std::vector< double > > wrongCosines = { { 3., 5., 6. },
                                                            { 9., 11. } };
      std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                           { 10., 12. } };
      std::vector< std::vector< double > > wrongProbabilities =
                                             { { 4., 6., 7. }, { 10., 12. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                 std::move( wrongEnergies ),
                                 std::move( totalEmissionProbabilities ),
                                 std::move( cosines ),
                                 std::move( probabilities ) ) );
        CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                 std::move( energies ),
                                 std::move( wrongTotalEmissionProbabilities ),
                                 std::move( cosines ),
                                 std::move( probabilities ) ) );
        CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                 std::move( energies ),
                                 std::move( totalEmissionProbabilities ),
                                 std::move( wrongCosines ),
                                 std::move( probabilities ) ) );
        CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                 std::move( energies ),
                                 std::move( totalEmissionProbabilities ),
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

        CHECK_THROWS( Tabulated( lang, begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "invalid LANG values are given" ) {

      std::vector< int > invalidLANGs = { -1, 0, 10, 16, 20 };

      THEN( "an exception is thrown" ) {

        for ( auto lang : invalidLANGs ) {

          double energy = 1e-5;
          int nd = 0;
          int na = 4;
          int nep = 2;
          std::vector< double > list = {  1.,  2.,  3.,  4.,  5.,  6.,
                                      7.,  8.,  9., 10., 11., 12. };
          std::vector< double > energies = { 1., 7. };
          std::vector< double > totalEmissionProbabilities = { 2., 8. };
          std::vector< std::vector< double > > cosines = { { 3., 5. },
                                                           { 9., 11. } };
          std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                                 { 10., 12. } };

          std::string string = chunk();

          auto begin = string.begin();
          auto end = string.end();
          long lineNumber = 1;

          CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                   std::move( list  ) ) );
          CHECK_THROWS( Tabulated( lang, energy, nd, na, nep,
                                   std::move( energies ),
                                   std::move( totalEmissionProbabilities ),
                                   std::move( cosines ),
                                   std::move( probabilities ) ) );
          CHECK_THROWS(
            Tabulated( lang, begin, end, lineNumber, 9228, 6, 5 ) );
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

void checkTabulated( const Tabulated& chunk ) {

  CHECK( 1e-5 == Approx( chunk.E() ) );
  CHECK( 1e-5 == Approx( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 4 == chunk.NA() );
  CHECK( 4 == chunk.numberAngularParameters() );
  CHECK( 12 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 7. == Approx( chunk.energies()[1] ) );
  CHECK( 2 == chunk.totalEmissionProbabilities().size() );
  CHECK( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
  CHECK( 8. == Approx( chunk.totalEmissionProbabilities()[1] ) );
  CHECK( 2 == chunk.cosines().size() );
  CHECK( 3. == Approx( chunk.cosines()[0][0] ) );
  CHECK( 5. == Approx( chunk.cosines()[0][1] ) );
  CHECK( 9. == Approx( chunk.cosines()[1][0] ) );
  CHECK( 11. == Approx( chunk.cosines()[1][1] ) );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK( 4. == Approx( chunk.probabilities()[0][0] ) );
  CHECK( 6. == Approx( chunk.probabilities()[0][1] ) );
  CHECK( 10. == Approx( chunk.probabilities()[1][0] ) );
  CHECK( 12. == Approx( chunk.probabilities()[1][1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          4         13          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+0                                                       9228 6  5     \n";
}
