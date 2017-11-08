#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string invalidLANG();

SCENARIO( "section::Type< 6 >::DiscreteTwoBodyScattering" ) {

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::DiscreteTwoBodyScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering
        chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.energies();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 4 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NL() );

      auto subsection1 = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients >( energies[0] );
      REQUIRE( 1 == subsection1.LANG() );
      REQUIRE( 4 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NL() );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 1. == Approx( subsection1.coefficients()[0] ) );
      REQUIRE( 2. == Approx( subsection1.coefficients()[1] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[2] ) );
      REQUIRE( 4. == Approx( subsection1.coefficients()[3] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 12 == energies[1].LANG() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 3 == energies[1].NL() );

      auto subsection2 = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated >( energies[1] );
      REQUIRE( 12 == subsection2.LANG() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 3 == subsection2.NL() );
      REQUIRE( 3 == subsection2.cosines().size() );
      REQUIRE( 1. == Approx( subsection2.cosines()[0] ) );
      REQUIRE( 3. == Approx( subsection2.cosines()[1] ) );
      REQUIRE( 5. == Approx( subsection2.cosines()[2] ) );
      REQUIRE( 3 == subsection2.p().size() );
      REQUIRE( 2. == Approx( subsection2.p()[0] ) );
      REQUIRE( 4. == Approx( subsection2.p()[1] ) );
      REQUIRE( 6. == Approx( subsection2.p()[2] ) );

      REQUIRE( 6 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyScattering" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::DiscreteTwoBodyScattering
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 6 >::DiscreteTwoBodyScattering"
         " with an invalid LPT" ){
    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section::Type< 6 >::DiscreteTwoBodyScattering( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          1          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string invalidLANG() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n"
    " 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
