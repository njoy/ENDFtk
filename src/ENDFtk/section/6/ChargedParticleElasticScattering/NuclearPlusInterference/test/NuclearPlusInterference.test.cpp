// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using NuclearPlusInterference =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;

std::string chunk();
void verifyChunk( const NuclearPlusInterference& );
std::string invalidLTP();
std::string invalidSize();

SCENARIO( "NuclearPlusInterference" ) {

  GIVEN( "valid data for a NuclearPlusInterference" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int ltp = 12;
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      NuclearPlusInterference chunk( energy, ltp, std::move( cosines ),
                                     std::move( probabilities ) );

      THEN( "a NuclearPlusInterference can be constructed using mu and p "
            "arrays and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      NuclearPlusInterference chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a NuclearPlusInterference can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a NuclearPlusInterference" ) {

    WHEN( "data with inconsistent sizes are used" ) {

      double energy = 1e-5;
      int ltp = 12;
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };
      std::vector< double > wrong = { 8, 10 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearPlusInterference( energy, ltp,
                                               std::move( wrong ),
                                               std::move( probabilities ) ) );
        CHECK_THROWS( NuclearPlusInterference( energy, ltp,
                                               std::move( cosines ),
                                               std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "data with an invalid LTP is used" ) {

      double energy = 1e-5;
      int ltp = 1;
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearPlusInterference( energy, ltp,
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

        CHECK_THROWS( NuclearPlusInterference( begin, end, lineNumber,
                                               9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW and NL" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearPlusInterference( begin, end, lineNumber,
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

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 12 == chunk.LTP() );
  CHECK( 6 == chunk.NW() );
  CHECK( 3 == chunk.NL() );
  CHECK( 3 == chunk.MU().size() );
  CHECK( 3 == chunk.cosines().size() );
  CHECK_THAT( 1., WithinRel( chunk.MU()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.MU()[1] ) );
  CHECK_THAT( 5., WithinRel( chunk.MU()[2] ) );
  CHECK_THAT( 1., WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT( 5., WithinRel( chunk.cosines()[2] ) );
  CHECK( 3 == chunk.PNI().size() );
  CHECK( 3 == chunk.probabilities().size() );
  CHECK_THAT( 2., WithinRel( chunk.PNI()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.PNI()[1] ) );
  CHECK_THAT( 6., WithinRel( chunk.PNI()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.probabilities()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.probabilities()[1] ) );
  CHECK_THAT( 6., WithinRel( chunk.probabilities()[2] ) );

  CHECK( 2 == chunk.NC() );
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
