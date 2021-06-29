#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/14.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using IsotropicDiscretePhoton =
section::Type< 14 >::IsotropicDiscretePhoton;

std::string chunk();
void verifyChunk( const IsotropicDiscretePhoton& );

SCENARIO( "IsotropicDiscretePhoton" ) {

  GIVEN( "valid data for an IsotropicDiscretePhoton" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1.;
      double level = 2.;

      IsotropicDiscretePhoton chunk( energy, level );

      THEN( "an IsotropicDiscretePhoton can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 14, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      IsotropicDiscretePhoton chunk( begin, end, lineNumber, 2625, 14, 2 );

      THEN( "a IsotropicDiscretePhoton can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 14, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 2.000000+0          0          0          0          0262514  2     \n";
}

void verifyChunk( const IsotropicDiscretePhoton& chunk ) {

  CHECK( true == chunk.LI() );
  CHECK( true == chunk.isotropicDistributions() );
  CHECK( 0 == chunk.LTT() );
  CHECK( 0 == chunk.LAW() );

  CHECK( 1. == Approx( chunk.EG() ) );
  CHECK( 1. == Approx( chunk.photonEnergy() ) );
  CHECK( 2. == Approx( chunk.ES() ) );
  CHECK( 2. == Approx( chunk.levelEnergy() ) );

  CHECK( 1 == chunk.NC() );
}
