#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;
using section62 = section::Type< 6 >::DiscreteTwoBodyScattering;

std::string chunkLANG1();
std::string chunkLANG12();
std::string chunkLANG14();
std::string invalidLANG();

SCENARIO( "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection" ) {

  GIVEN( "valid data for a "
         "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=1" ) {

    double energy = 1e-5;
    std::vector< double > coefficients = { 1., 2., 3., 4. };

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
        subsection( section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients( energy, std::move( coefficients ) ) );

      auto chunk = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients >( subsection );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.LANG() );
      REQUIRE( 4 == chunk.NW() );
      REQUIRE( 4 == chunk.NL() );
      REQUIRE( 4 == chunk.coefficients().size() );
      REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

      REQUIRE( 0 == subsection.LANG() );
      REQUIRE( 1e-5 == Approx( subsection.energy() ) );
      REQUIRE( 4 == subsection.NW() );
      REQUIRE( 4 == subsection.NL() );
      REQUIRE( 2 == subsection.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=1" ) {

    std::string string = chunkLANG1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
        subsection( begin, end, lineNumber, 9228, 6, 5 );

      auto chunk = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients >( subsection );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.LANG() );
      REQUIRE( 4 == chunk.NW() );
      REQUIRE( 4 == chunk.NL() );
      REQUIRE( 4 == chunk.coefficients().size() );
      REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

      REQUIRE( 0 == subsection.LANG() );
      REQUIRE( 1e-5 == Approx( subsection.energy() ) );
      REQUIRE( 4 == subsection.NW() );
      REQUIRE( 4 == subsection.NL() );
      REQUIRE( 2 == subsection.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=1" ) {

    std::string string = chunkLANG1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
      subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "valid data for a "
         "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=12" ) {

    double energy = 1e-5;
    int lang = 12;
    std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
    std::vector< double > cosines = { 1, 3, 5 };
    std::vector< double > probabilities = { 2, 4, 6 };

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
        subsection( section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated( energy, lang, std::move( values ) ) );

      auto chunk = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated >( subsection );
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

      REQUIRE( 12 == subsection.LANG() );
      REQUIRE( 1e-5 == Approx( subsection.energy() ) );
      REQUIRE( 6 == subsection.NW() );
      REQUIRE( 3 == subsection.NL() );
      REQUIRE( 2 == subsection.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=12" ) {

    std::string string = chunkLANG12();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
        subsection( begin, end, lineNumber, 9228, 6, 5 );

      auto chunk = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated >( subsection );
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

      REQUIRE( 12 == subsection.LANG() );
      REQUIRE( 1e-5 == Approx( subsection.energy() ) );
      REQUIRE( 6 == subsection.NW() );
      REQUIRE( 3 == subsection.NL() );
      REQUIRE( 2 == subsection.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=12" ) {

    std::string string = chunkLANG12();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
      subsection(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid "
         "section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=14" ) {

    std::string string = chunkLANG14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
        subsection(begin, end, lineNumber, 9228, 6, 5 );

      auto chunk = std::experimental::get< section::Type< 6 >::DiscreteTwoBodyScattering::Tabulated >( subsection );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 14 == chunk.LANG() );
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

      REQUIRE( 14 == subsection.LANG() );
      REQUIRE( 1e-5 == Approx( subsection.energy() ) );
      REQUIRE( 6 == subsection.NW() );
      REQUIRE( 3 == subsection.NL() );
      REQUIRE( 2 == subsection.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         "with LANG=14" ) {

    std::string string = chunkLANG14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::DiscreteTwoBodyScattering::SubSection
      subsection(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a section::Type< 6 >::DiscreteTwoBodyScattering::SubSection"
         " with an invalid LANG" ){
    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section62::SubSection( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunkLANG1() {
  return
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

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

std::string invalidLANG() {
  return
    " 0.000000+0 1.000000-5          1          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
