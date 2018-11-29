#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using WattSpectrum = 
section::Type< 5 >::WattSpectrum;
using Parameter = 
section::Type< 5 >::Parameter;

std::string chunk();

SCENARIO( "WattSpectrum" ) {

  GIVEN( "valid data for a WattSpectrum" ) {

    Parameter a{ {3}, {2},
                 { 1e-5, 1.5e+6, 3e+7 },
                 { 9.77e+5, 1e+6, 1.06e+6 } };
    Parameter b{ {5}, {2},
                 { 1e-5, 1.5e+6, 1e+7, 1.22e+7, 3e+7 },
                 { 2.546e-6, 2.546e-6, 2.474e-6, 2.612e-6, 2.62e-6 } };

    THEN( "a WattSpectrum can be constructed" ) {
      WattSpectrum chunk( std::array< Parameter, 2 >{ { std::move( a ),
                                                        std::move( b ) } } );

      auto valueA = chunk.aParameter();
      REQUIRE( 3 == valueA.NP() );
      REQUIRE( 1 == valueA.NR() );
      REQUIRE( 1 == valueA.interpolants().size() );
      REQUIRE( 1 == valueA.boundaries().size() );
      REQUIRE( 2 == valueA.interpolants()[0] );
      REQUIRE( 3 == valueA.boundaries()[0] );
      REQUIRE( 3 == valueA.x().size() );
      REQUIRE( 3 == valueA.y().size() );
      REQUIRE( 1e-5 == Approx( valueA.x()[0] ) );
      REQUIRE( 1.5e+6 == Approx( valueA.x()[1] ) );
      REQUIRE( 3e+7 == Approx( valueA.x()[2] ) );
      REQUIRE( 9.77e+5 == Approx( valueA.y()[0] ) );
      REQUIRE( 1e+6 == Approx( valueA.y()[1] ) );
      REQUIRE( 1.06e+6 == Approx( valueA.y()[2] ) );

      auto valueB = chunk.bParameter();
      REQUIRE( 5 == valueB.NP() );
      REQUIRE( 1 == valueB.NR() );
      REQUIRE( 1 == valueB.interpolants().size() );
      REQUIRE( 1 == valueB.boundaries().size() );
      REQUIRE( 2 == valueB.interpolants()[0] );
      REQUIRE( 5 == valueB.boundaries()[0] );
      REQUIRE( 5 == valueB.x().size() );
      REQUIRE( 5 == valueB.y().size() );
      REQUIRE( 1e-5 == Approx( valueB.x()[0] ) );
      REQUIRE( 1.5e+6 == Approx( valueB.x()[1] ) );
      REQUIRE( 1e+7 == Approx( valueB.x()[2] ) );
      REQUIRE( 1.22e+7 == Approx( valueB.x()[3] ) );
      REQUIRE( 3e+7 == Approx( valueB.x()[4] ) );
      REQUIRE( 2.546e-6 == Approx( valueB.y()[0] ) );
      REQUIRE( 2.546e-6 == Approx( valueB.y()[1] ) );
      REQUIRE( 2.474e-6 == Approx( valueB.y()[2] ) );
      REQUIRE( 2.612e-6 == Approx( valueB.y()[3] ) );
      REQUIRE( 2.62e-6 == Approx( valueB.y()[4] ) );

      REQUIRE( 7 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid WattSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a WattSpectrum can "
          "be constructed and members can be tested" ) {
      WattSpectrum chunk( begin, end, lineNumber, 9222, 5, 18 );

      auto valueA = chunk.aParameter();
      REQUIRE( 3 == valueA.NP() );
      REQUIRE( 1 == valueA.NR() );
      REQUIRE( 1 == valueA.interpolants().size() );
      REQUIRE( 1 == valueA.boundaries().size() );
      REQUIRE( 2 == valueA.interpolants()[0] );
      REQUIRE( 3 == valueA.boundaries()[0] );
      REQUIRE( 3 == valueA.x().size() );
      REQUIRE( 3 == valueA.y().size() );
      REQUIRE( 1e-5 == Approx( valueA.x()[0] ) );
      REQUIRE( 1.5e+6 == Approx( valueA.x()[1] ) );
      REQUIRE( 3e+7 == Approx( valueA.x()[2] ) );
      REQUIRE( 9.77e+5 == Approx( valueA.y()[0] ) );
      REQUIRE( 1e+6 == Approx( valueA.y()[1] ) );
      REQUIRE( 1.06e+6 == Approx( valueA.y()[2] ) );

      auto valueB = chunk.bParameter();
      REQUIRE( 5 == valueB.NP() );
      REQUIRE( 1 == valueB.NR() );
      REQUIRE( 1 == valueB.interpolants().size() );
      REQUIRE( 1 == valueB.boundaries().size() );
      REQUIRE( 2 == valueB.interpolants()[0] );
      REQUIRE( 5 == valueB.boundaries()[0] );
      REQUIRE( 5 == valueB.x().size() );
      REQUIRE( 5 == valueB.y().size() );
      REQUIRE( 1e-5 == Approx( valueB.x()[0] ) );
      REQUIRE( 1.5e+6 == Approx( valueB.x()[1] ) );
      REQUIRE( 1e+7 == Approx( valueB.x()[2] ) );
      REQUIRE( 1.22e+7 == Approx( valueB.x()[3] ) );
      REQUIRE( 3e+7 == Approx( valueB.x()[4] ) );
      REQUIRE( 2.546e-6 == Approx( valueB.y()[0] ) );
      REQUIRE( 2.546e-6 == Approx( valueB.y()[1] ) );
      REQUIRE( 2.474e-6 == Approx( valueB.y()[2] ) );
      REQUIRE( 2.612e-6 == Approx( valueB.y()[3] ) );
      REQUIRE( 2.62e-6 == Approx( valueB.y()[4] ) );

      REQUIRE( 7 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of WattSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    WattSpectrum chunk(begin, end, lineNumber, 9222, 5, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9222, 5, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n"
    "          3          2                                            9222 5 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n"
    "          5          2                                            9222 5 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n";
}
