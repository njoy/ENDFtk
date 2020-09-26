#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/12.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialMultiplicity = section::Type< 12 >::PartialMultiplicity;

std::string chunk();
void verifyChunk( const PartialMultiplicity& );
std::string invalidChunk();

SCENARIO( "PartialMultiplicity" ) {

  GIVEN( "valid data for a PartialMultiplicity" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double eg = 0.0;
      double es = 3.0;
      int lp = 2;
      int lf = 1;

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > x = { 1e-5, 3e+7 };
      std::vector< double > y = { 8.579050e+0, 1.487778e+1 };

      PartialMultiplicity chunk( eg, es, lp, lf,
                                 std::move( boundaries ),
                                 std::move( interpolants ),
                                 std::move( x ),
                                 std::move( y ) );

      THEN( "a PartialMultiplicity can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialMultiplicity chunk( begin, end, lineNumber, 9228, 12, 18 );

      THEN( "a PartialMultiplicity can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a PartialMultiplicity" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double eg = 0.0;
      double es = 3.0;
      int lp = 2;
      int lf = 1;

      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 2, 5 };
      std::vector< double > x = { 1e-5, 3e+7 };
      std::vector< double > y = { 8.579050e+0, 1.487778e+1 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( PartialMultiplicity( eg, es, lp, lf,
                                             std::move( boundaries ),
                                             std::move( wrongInterpolants ),
                                             std::move( x ),
                                             std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( PartialMultiplicity( begin, end, lineNumber,
                                             9228, 12, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
  " 0.000000+0 3.000000+0          2          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}

void verifyChunk( const PartialMultiplicity& chunk ) {

  CHECK( 0.0 == Approx( chunk.EG() ) );
  CHECK( 0.0 == Approx( chunk.photonOrBindingEnergy() ) );
  CHECK( 3.0 == Approx( chunk.ES() ) );
  CHECK( 3.0 == Approx( chunk.levelEnergy() ) );
  CHECK( 2 == chunk.LP() );
  CHECK( 2 == chunk.primaryPhotonFlag() );
  CHECK( 1 == chunk.LF() );
  CHECK( 1 == chunk.LAW() );
  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.Y().size() );
  CHECK( 2 == chunk.multiplicities().size() );
  CHECK( 1e-5 == Approx( chunk.E()[0] ) );
  CHECK( 3e+7 == Approx( chunk.E()[1] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 3e+7 == Approx( chunk.energies()[1] ) );
  CHECK( 8.579050e+0 == Approx( chunk.Y()[0] ) );
  CHECK( 1.487778e+1 == Approx( chunk.Y()[1] ) );
  CHECK( 8.579050e+0 == Approx( chunk.multiplicities()[0] ) );
  CHECK( 1.487778e+1 == Approx( chunk.multiplicities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 3.000000+0          2          1          2          2922812 18     \n"
    "          2          2                                            922812 18     \n"
    " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}
