#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DistributionFunction = 
section::Type< 5 >::DistributionFunction;
using EffectiveTemperature =
section::Type< 5 >:: EffectiveTemperature;
using GeneralEvaporationSpectrum =
section::Type< 5 >::GeneralEvaporationSpectrum;

std::string chunk();
void verifyChunk( const GeneralEvaporationSpectrum& );
std::string invalidChunk();

SCENARIO( "GeneralEvaporationSpectrum" ) {

  GIVEN( "valid data for a GeneralEvaporationSpectrum" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      EffectiveTemperature temperature = { { 2 }, { 2 },
                                           { 1e-5, 3e+7 }, { 1.0, 1.0 } };
      DistributionFunction gFunction = { { 6 }, { 1 },
                                         { 0.0, 1e+4, 2e+4,
                                           1.8e+6, 1.81e+6, 1.82e+6 },
                                         { 1.533738e-7, 1.378483e-6,
                                           1.550360e-6, 7.90779e-31,
                                           0.0, 0.0 } };

      GeneralEvaporationSpectrum chunk( std::move( temperature ),
                                        std::move( gFunction ) );

      THEN( "an GeneralEvaporationSpectrum can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9443, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      GeneralEvaporationSpectrum chunk( begin, end, lineNumber, 9443, 5, 455 );

      THEN( "a GeneralEvaporationSpectrum can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9443, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a GeneralEvaporationSpectrum" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( GeneralEvaporationSpectrum( begin, end, lineNumber,
                                                    9443, 5, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29443 5455     \n"
    "          2          2                                            9443 5455     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n"
    " 0.000000+0 0.000000+0          0          0          1          69443 5455     \n"
    "          6          1                                            9443 5455     \n"
    " 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n"
    " 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n";
}

void verifyChunk( const GeneralEvaporationSpectrum& chunk ) {

  REQUIRE( 5 == chunk.LF() );
  REQUIRE( 5 == chunk.LAW() );

  const auto& t = chunk.effectiveTemperature();
  REQUIRE( 2 == t.NE() );
  REQUIRE( 1 == t.NR() );
  REQUIRE( 1 == t.interpolants().size() );
  REQUIRE( 1 == t.boundaries().size() );
  REQUIRE( 2 == t.interpolants()[0] );
  REQUIRE( 2 == t.boundaries()[0] );
  REQUIRE( 2 == t.E().size() );
  REQUIRE( 2 == t.energies().size() );
  REQUIRE( 2 == t.thetas().size() );
  REQUIRE( 2 == t.values().size() );
  REQUIRE( 1e-5 == Approx( t.E()[0] ) );
  REQUIRE( 3e+7 == Approx( t.E()[1] ) );
  REQUIRE( 1e-5 == Approx( t.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( t.energies()[1] ) );
  REQUIRE( 1.0 == Approx( t.thetas()[0] ) );
  REQUIRE( 1.0 == Approx( t.thetas()[1] ) );
  REQUIRE( 1.0 == Approx( t.values()[0] ) );
  REQUIRE( 1.0 == Approx( t.values()[1] ) );

  const auto& df = chunk.distributionFunction();
  REQUIRE( 6 == df.NF() );
  REQUIRE( 1 == df.NR() );
  REQUIRE( 1 == df.interpolants().size() );
  REQUIRE( 1 == df.boundaries().size() );
  REQUIRE( 1 == df.interpolants()[0] );
  REQUIRE( 6 == df.boundaries()[0] );
  REQUIRE( 6 == df.x().size() );
  REQUIRE( 6 == df.values().size() );
  REQUIRE( 0.0 == Approx( df.x()[0] ) );
  REQUIRE( 1e+4 == Approx( df.x()[1] ) );
  REQUIRE( 2e+4 == Approx( df.x()[2] ) );
  REQUIRE( 1.8e+6 == Approx( df.x()[3] ) );
  REQUIRE( 1.81e+6 == Approx( df.x()[4] ) );
  REQUIRE( 1.82e+6 == Approx( df.x()[5] ) );
  REQUIRE( 1.533738e-7 == Approx( df.values()[0] ) );
  REQUIRE( 1.378483e-6 == Approx( df.values()[1] ) );
  REQUIRE( 1.550360e-6 == Approx( df.values()[2] ) );
  REQUIRE( 7.90779e-31 == Approx( df.values()[3] ) );
  REQUIRE( 0.0 == Approx( df.values()[4] ) );
  REQUIRE( 0.0 == Approx( df.values()[5] ) );

  REQUIRE( 7 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          29443 5455     \n"
    "          2          2                                            9443 5455     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n"
    " 0.000000+0 0.000000+0          0          0          1          69443 5455     \n"
    "          6          1                                            9443 5455     \n"
    " 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n"
    " 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n";
}
