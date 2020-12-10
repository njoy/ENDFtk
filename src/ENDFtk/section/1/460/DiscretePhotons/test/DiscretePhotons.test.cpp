#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/460.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscretePhotons = section::Type< 1, 460 >::DiscretePhotons;
using DiscretePhotonMultiplicity = section::Type< 1, 460 >::DiscretePhotonMultiplicity;

std::string chunk();
void verifyChunk( const DiscretePhotons& );

SCENARIO( "DiscretePhotons" ) {

  GIVEN( "valid data for a DiscretePhotons" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DiscretePhotonMultiplicity > multiplicities = {

        DiscretePhotonMultiplicity( 0.1, 1, { 2 }, { 4 }, { 0., 4. },
                                    { 4.877451e-1, 1.715686e-1 } ),
        DiscretePhotonMultiplicity( 0.2, 2, { 3 }, { 2 }, { 0., 5., 9 },
                                    { 1.691176e-1, 2.450980e-3, 1.691176e-1 } )
      };

      DiscretePhotons chunk( std::move( multiplicities ) );

      THEN( "an DiscretePhotons can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 460 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DiscretePhotons chunk( begin, end, lineNumber, 9228, 1, 460, 2 );

      THEN( "a DiscretePhotons can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 460 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DiscretePhotons" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (LIST takes care of tests)

      std::vector< DiscretePhotonMultiplicity > empty = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DiscretePhotons( std::move( empty ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

void verifyChunk( const DiscretePhotons& chunk ) {

  CHECK( 1 == chunk.LO() );
  CHECK( 1 == chunk.representation() );
  CHECK( 2 == chunk.NG() );
  CHECK( 2 == chunk.numberDiscretePhotons() );

  CHECK( 2 == chunk.photons().size() );

  CHECK( 0.1 == Approx( chunk.photons()[0].E() ) );
  CHECK( 1 == chunk.photons()[0].index() );
  CHECK( 1 == chunk.photons()[0].NR() );
  CHECK( 2 == chunk.photons()[0].NP() );
  CHECK( 1 == chunk.photons()[0].interpolants().size() );
  CHECK( 1 == chunk.photons()[0].boundaries().size() );
  CHECK( 4 == chunk.photons()[0].interpolants()[0] );
  CHECK( 2 == chunk.photons()[0].boundaries()[0] );
  CHECK( 2 == chunk.photons()[0].time().size() );
  CHECK( 2 == chunk.photons()[0].multiplicities().size() );
  CHECK( 0. == Approx( chunk.photons()[0].time()[0] ) );
  CHECK( 4. == Approx( chunk.photons()[0].time()[1] ) );
  CHECK( 4.877451e-1 == Approx( chunk.photons()[0].multiplicities()[0] ) );
  CHECK( 1.715686e-1 == Approx( chunk.photons()[0].multiplicities()[1] ) );

  CHECK( 0.2 == Approx( chunk.photons()[1].E() ) );
  CHECK( 2 == chunk.photons()[1].index() );
  CHECK( 1 == chunk.photons()[1].NR() );
  CHECK( 3 == chunk.photons()[1].NP() );
  CHECK( 1 == chunk.photons()[1].interpolants().size() );
  CHECK( 1 == chunk.photons()[1].boundaries().size() );
  CHECK( 2 == chunk.photons()[1].interpolants()[0] );
  CHECK( 3 == chunk.photons()[1].boundaries()[0] );
  CHECK( 3 == chunk.photons()[1].time().size() );
  CHECK( 3 == chunk.photons()[1].multiplicities().size() );
  CHECK( 0. == Approx( chunk.photons()[1].time()[0] ) );
  CHECK( 5. == Approx( chunk.photons()[1].time()[1] ) );
  CHECK( 9. == Approx( chunk.photons()[1].time()[2] ) );
  CHECK( 1.691176e-1 == Approx( chunk.photons()[1].multiplicities()[0] ) );
  CHECK( 2.450980e-3 == Approx( chunk.photons()[1].multiplicities()[1] ) );
  CHECK( 1.691176e-1 == Approx( chunk.photons()[1].multiplicities()[2] ) );

  CHECK( 6 == chunk.NC() );
}
