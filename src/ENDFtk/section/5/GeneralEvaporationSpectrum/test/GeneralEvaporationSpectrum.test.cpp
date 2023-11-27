// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK_THROWS( GeneralEvaporationSpectrum( begin, end, lineNumber,
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

  CHECK( 5 == chunk.LF() );
  CHECK( 5 == chunk.LAW() );

  const auto& t = chunk.effectiveTemperature();
  CHECK( 2 == t.NP() );
  CHECK( 1 == t.NR() );
  CHECK( 1 == t.interpolants().size() );
  CHECK( 1 == t.boundaries().size() );
  CHECK( 2 == t.interpolants()[0] );
  CHECK( 2 == t.boundaries()[0] );
  CHECK( 2 == t.E().size() );
  CHECK( 2 == t.energies().size() );
  CHECK( 2 == t.thetas().size() );
  CHECK_THAT( 1e-5, WithinRel( t.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( t.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( t.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( t.energies()[1] ) );
  CHECK_THAT( 1.0, WithinRel( t.thetas()[0] ) );
  CHECK_THAT( 1.0, WithinRel( t.thetas()[1] ) );

  const auto& df = chunk.distributionFunction();
  CHECK( 6 == df.NP() );
  CHECK( 1 == df.NR() );
  CHECK( 1 == df.interpolants().size() );
  CHECK( 1 == df.boundaries().size() );
  CHECK( 1 == df.interpolants()[0] );
  CHECK( 6 == df.boundaries()[0] );
  CHECK( 6 == df.X().size() );
  CHECK( 6 == df.G().size() );
  CHECK_THAT( 0.0, WithinRel( df.X()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( df.X()[1] ) );
  CHECK_THAT( 2e+4, WithinRel( df.X()[2] ) );
  CHECK_THAT( 1.8e+6, WithinRel( df.X()[3] ) );
  CHECK_THAT( 1.81e+6, WithinRel( df.X()[4] ) );
  CHECK_THAT( 1.82e+6, WithinRel( df.X()[5] ) );
  CHECK_THAT( 1.533738e-7, WithinRel( df.G()[0] ) );
  CHECK_THAT( 1.378483e-6, WithinRel( df.G()[1] ) );
  CHECK_THAT( 1.550360e-6, WithinRel( df.G()[2] ) );
  CHECK_THAT( 7.90779e-31, WithinRel( df.G()[3] ) );
  CHECK_THAT( 0.0, WithinRel( df.G()[4] ) );
  CHECK_THAT( 0.0, WithinRel( df.G()[5] ) );

  CHECK( 7 == chunk.NC() );
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
