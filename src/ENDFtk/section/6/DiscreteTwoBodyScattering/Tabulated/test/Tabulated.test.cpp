#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using Tabulated = 
section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated;

std::string chunk();
std::string invalidLANG();
std::string invalidSize();

SCENARIO( "Tabulated" ) {

  GIVEN( "valid data for a Tabulated" ) {

    double energy = 1e-5;
    int lang = 12;
    std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
    std::vector< double > cosines = { 1, 3, 5 };
    std::vector< double > probabilities = { 2, 4, 6 };

    THEN( "a Tabulated can "
          "be constructed using a list and members can be tested" ) {
      Tabulated chunk( energy, lang, std::move( values ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 12 == chunk.LANG() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 3 == chunk.cosines().size() );
      REQUIRE( 1. == Approx( chunk.cosines()[0] ) );
      REQUIRE( 3. == Approx( chunk.cosines()[1] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[2] ) );
      REQUIRE( 3 == chunk.probabilities().size() );
      REQUIRE( 2. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 4. == Approx( chunk.probabilities()[1] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[2] ) );

      REQUIRE( 2 == chunk.NC() );
    }

    THEN( "a Tabulated can "
          "be constructed using mu and p arrays and members can be tested" ) {
      Tabulated chunk( energy, lang, std::move( cosines ),
                       std::move( probabilities ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 12 == chunk.LANG() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 3 == chunk.cosines().size() );
      REQUIRE( 1. == Approx( chunk.cosines()[0] ) );
      REQUIRE( 3. == Approx( chunk.cosines()[1] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[2] ) );
      REQUIRE( 3 == chunk.probabilities().size() );
      REQUIRE( 2. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 4. == Approx( chunk.probabilities()[1] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[2] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a Tabulated can "
          "be constructed and members can be tested" ) {
      Tabulated chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 12 == chunk.LANG() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 3 == chunk.cosines().size() );
      REQUIRE( 3 == chunk.probabilities().size() );
      REQUIRE( 1. == Approx( chunk.cosines()[0] ) );
      REQUIRE( 3. == Approx( chunk.cosines()[1] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[2] ) );
      REQUIRE( 2. == Approx( chunk.probabilities()[0] ) );
      REQUIRE( 4. == Approx( chunk.probabilities()[1] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[2] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "data with inconsistent sizes" ) {

    double energy = 1e-5;
    int lang = 12;
    std::vector< double > cosines = { 1, 3, 5 };
    std::vector< double > probabilities = { 2, 4, 6 };
    std::vector< double > wrong = { 8, 10 };
    std::vector< double > wrongsize = { 1, 2, 3 };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Tabulated( energy, lang, std::move( wrong ),
                                 std::move( probabilities ) ) );
      REQUIRE_THROWS( Tabulated( energy, lang, std::move( cosines ),
                                 std::move( wrong ) ) );
      REQUIRE_THROWS( Tabulated( energy, lang, std::move( wrongsize ) ) );
    }
  } // GIVEN

  GIVEN( "data with an invalid LANG" ) {

    double energy = 1e-5;
    int lang = 1;
    std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
    std::vector< double > cosines = { 1, 3, 5 };
    std::vector< double > probabilities = { 2, 4, 6 };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Tabulated( energy, lang, std::move( values ) ) );
      REQUIRE_THROWS( Tabulated( energy, lang, std::move( cosines ),
                                 std::move( probabilities ) ) );
    }
  } // GIVEN

  GIVEN( "a string with an invalid LANG" ) {

    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Tabulated( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW and NL" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( Tabulated( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    Tabulated
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
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
