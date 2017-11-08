#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 12 == chunk.LANG() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 3 == chunk.cosines().size() );
      REQUIRE( 3 == chunk.p().size() );
      REQUIRE( 1. == Approx( chunk.cosines()[0] ) );
      REQUIRE( 3. == Approx( chunk.cosines()[1] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[2] ) );
      REQUIRE( 2. == Approx( chunk.p()[0] ) );
      REQUIRE( 4. == Approx( chunk.p()[1] ) );
      REQUIRE( 6. == Approx( chunk.p()[2] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated
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
