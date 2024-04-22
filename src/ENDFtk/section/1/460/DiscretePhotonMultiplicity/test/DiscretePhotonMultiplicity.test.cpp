// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/460.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscretePhotonMultiplicity = section::Type< 1, 460 >::DiscretePhotonMultiplicity;

std::string chunk();
void verifyChunk( const DiscretePhotonMultiplicity& );

SCENARIO( "DiscretePhotonMultiplicity" ) {

  GIVEN( "valid data for a DiscretePhotonMultiplicity" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 0.1;
      int lph = 1;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 4 };
      std::vector< double > time = { 0., 4. };
      std::vector< double > multiplicities = { 4.877451e-1, 1.715686e-1 };

      DiscretePhotonMultiplicity chunk( energy, lph,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( time ),
                                        std::move( multiplicities ) );

      THEN( "an DiscretePhotonMultiplicity can be constructed and members can be tested" ) {

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

      DiscretePhotonMultiplicity chunk( begin, end, lineNumber, 9228, 1, 460 );

      THEN( "a DiscretePhotonMultiplicity can be constructed and members can be "
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
} // SCENARIO

std::string chunk() {
  return
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n";
}

void verifyChunk( const DiscretePhotonMultiplicity& chunk ) {

  CHECK_THAT( 0.1, WithinRel( chunk.E() ) );
  CHECK_THAT( 0.1, WithinRel( chunk.energy() ) );
  CHECK( 1 == chunk.LPH() );
  CHECK( 1 == chunk.index() );

  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 4 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 4 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.time().size() );
  CHECK( 2 == chunk.multiplicities().size() );
  CHECK_THAT( 0., WithinRel( chunk.time()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.time()[1] ) );
  CHECK_THAT( 4.877451e-1, WithinRel( chunk.multiplicities()[0] ) );
  CHECK_THAT( 1.715686e-1, WithinRel( chunk.multiplicities()[1] ) );

  CHECK( 3 == chunk.NC() );
}
