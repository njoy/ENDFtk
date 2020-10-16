#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedDistribution =
section::Type< 6 >::DiscreteTwoBodyScattering::TabulatedDistribution;

std::string chunkLANG12();
std::string chunkLANG14();
void checkTabulatedDistribution( const TabulatedDistribution& );
std::string invalidLANG();
std::string invalidSize();

SCENARIO( "TabulatedDistribution" ) {

  GIVEN( "valid data for a TabulatedDistribution" ) {

    std::vector< int > langs = { 12, 14 };

    WHEN( "the data is given explicitly" ) {

      THEN( "a Tabulated can "
            "be constructed using vectors and members can be tested "
            "for each LANG value" ) {

        for ( auto lang : langs ) {

          double energy = 1e-5;
          std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
          std::vector< double > cosines = { 1, 3, 5 };
          std::vector< double > probabilities = { 2, 4, 6 };

          TabulatedDistribution chunk( energy, lang, std::move( cosines ),
                           std::move( probabilities ) );
          CHECK( lang == chunk.LANG() );
          checkTabulatedDistribution( chunk );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream for a LANG=12" ) {

      std::string string = chunkLANG12();

      THEN( "a TabulatedDistribution can "
            "be constructed and members can be tested " ) {

        auto begin = string.begin();
        auto end = string.end();
        long lineNumber = 1;

        TabulatedDistribution chunk( begin, end, lineNumber, 9228, 6, 5 );
        CHECK( 12 == chunk.LANG() );
        checkTabulatedDistribution( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream for a LANG=14" ) {

      std::string string = chunkLANG14();

      THEN( "a TabulatedDistribution can "
            "be constructed and members can be tested " ) {

        auto begin = string.begin();
        auto end = string.end();
        long lineNumber = 1;

        TabulatedDistribution chunk( begin, end, lineNumber, 9228, 6, 5 );
        CHECK( 14 == chunk.LANG() );
        checkTabulatedDistribution( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of TabulatedDistribution" ) {

    int lang = 12;

    std::string string = chunkLANG12();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    TabulatedDistribution chunk( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a TabulatedDistribution" ) {

    WHEN( "data with inconsistent sizes is given" ) {

      double energy = 1e-5;
      int lang = 12;
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };
      std::vector< double > wrong = { 8, 10 };
      std::vector< double > wrongsize = { 1, 2, 3 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( energy, lang, std::move( wrong ),
                                 std::move( probabilities ) ) );
        CHECK_THROWS( TabulatedDistribution( energy, lang, std::move( cosines ),
                                   std::move( wrong ) ) );
      }
    } // WHEN

    WHEN( "invalid LANG values are given" ) {

      double energy = 1e-5;
      int lang = 1;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( energy, lang, std::move( cosines ),
                                   std::move( probabilities ) ) );
      } // THEN
    } // GIVEN

    WHEN( "a string with an invalid LANG is given" ) {

      std::string string = invalidLANG();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // GIVEN

    WHEN( "a string with inconsistent NW and NL is given" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedDistribution( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // GIVEN
  } // WHEN
} // SCENARIO

std::string chunkLANG12() {
  return
    " 0.000000+0 1.000000-5         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkLANG14() {
  return
    " 0.000000+0 1.000000-5         14          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void checkTabulatedDistribution( const TabulatedDistribution& chunk ) {

  CHECK( 1e-5 == Approx( chunk.energy() ) );

  CHECK( 6 == chunk.NW() );
  CHECK( 3 == chunk.NL() );
  CHECK( 3 == chunk.numberCosines() );
  CHECK( 3 == chunk.cosines().size() );
  CHECK( 1. == Approx( chunk.cosines()[0] ) );
  CHECK( 3. == Approx( chunk.cosines()[1] ) );
  CHECK( 5. == Approx( chunk.cosines()[2] ) );
  CHECK( 3 == chunk.probabilities().size() );
  CHECK( 2. == Approx( chunk.probabilities()[0] ) );
  CHECK( 4. == Approx( chunk.probabilities()[1] ) );
  CHECK( 6. == Approx( chunk.probabilities()[2] ) );

  CHECK( 2 == chunk.NC() );
}

std::string invalidLANG() {
  return
    " 0.000000+0 1.000000-5          1          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5         12          0          6          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
