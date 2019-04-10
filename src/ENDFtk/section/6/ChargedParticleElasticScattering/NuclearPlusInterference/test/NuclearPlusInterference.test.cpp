#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using NuclearPlusInterference = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;

std::string chunk();
void verifyChunk( const NuclearPlusInterference& );
std::string invalidLTP();
std::string invalidSize();

SCENARIO( "NuclearPlusInterference" ) {

  GIVEN( "valid data for a NuclearPlusInterference" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int ltp = 12;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "a NuclearPlusInterference can be constructed using a list and "
            "members can be tested" ) {

        NuclearPlusInterference chunk( energy, ltp, std::move( values ) );
        verifyChunk( chunk );
      } // THEN

      THEN( "a NuclearPlusInterference can be constructed using mu and p "
            "arrays and members can be tested" ) {

        NuclearPlusInterference chunk( energy, ltp, std::move( cosines ),
                                       std::move( probabilities ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a NuclearPlusInterference can "
            "be constructed and members can be tested" ) {

        NuclearPlusInterference chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of NuclearPlusInterference" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    NuclearPlusInterference chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a NuclearPlusInterference" ) {

    WHEN( "data with inconsistent sizes are used" ) {

      double energy = 1e-5;
      int ltp = 12;
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };
      std::vector< double > wrong = { 8, 10 };
      std::vector< double > wrongsize = { 1, 2, 3 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( NuclearPlusInterference( energy, ltp,
                                                 std::move( wrong ),
                                                 std::move( probabilities ) ) );
        REQUIRE_THROWS( NuclearPlusInterference( energy, ltp,
                                                 std::move( cosines ),
                                                 std::move( wrong ) ) );
        REQUIRE_THROWS( NuclearPlusInterference( energy, ltp,
                                                 std::move( wrongsize ) ) );
      } // THEN
    } // WHEN

    WHEN( "data with an invalid LTP is used" ) {

      double energy = 1e-5;
      int ltp = 1;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( NuclearPlusInterference( energy, ltp,
                                                 std::move( values ) ) );
        REQUIRE_THROWS( NuclearPlusInterference( energy, ltp,
                                                 std::move( cosines ),
                                                 std::move( probabilities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with an invalid LTP" ) {

      std::string string = invalidLTP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( NuclearPlusInterference( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW and NL" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( NuclearPlusInterference( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunk( const NuclearPlusInterference& chunk ) {

  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( 12 == chunk.LTP() );
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

std::string invalidLTP() {
  return
    " 0.000000+0 1.000000-5          1          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5         12          0          6          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
