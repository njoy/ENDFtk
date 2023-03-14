#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreCoefficients =
section::Type< 26 >::ContinuumEnergyAngle::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreCoefficients& );
std::string invalidSize();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      std::vector< double > energies = { 1., 4. };
      std::vector< std::vector< double > > coefficients = { { 2., 3. },
                                                            { 5., 6. } };

      LegendreCoefficients chunk( energy, nd, na,
                                  std::move( energies ),
                                  std::move( coefficients ) );

      THEN( "a LegendreCoefficients can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 26, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LegendreCoefficients chunk( begin, end, lineNumber, 9228, 26, 5 );

      THEN( "a LegendreCoefficients can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 26, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "data is used with inconsistent sizes" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      std::vector< double > energies = { 1., 4. };
      std::vector< std::vector< double > > wrongcoefficients1 = { { 2., 3. },
                                                                  { 5. } };
      std::vector< std::vector< double > > wrongcoefficients2 = { { 2., 3. },
                                                                  { 5., 6. },
                                                                  { 8., 9. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreCoefficients( energy, nd, na,
                                            std::move( energies ),
                                            std::move( wrongcoefficients1 ) ) );
        CHECK_THROWS( LegendreCoefficients( energy, nd, na,
                                            std::move( energies ),
                                            std::move( wrongcoefficients1 ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string is used with inconsistent NW, NA" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                            9228, 26, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          1          6          2922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n";
}

void verifyChunk( const LegendreCoefficients& chunk ) {

  CHECK( 1 == chunk.LANG() );
  CHECK( 1 == chunk.representation() );
  CHECK( 1e-5 == Approx( chunk.E() ) );
  CHECK( 1e-5 == Approx( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.ND() );
  CHECK( 0 == chunk.numberDiscreteEnergies() );
  CHECK( 1 == chunk.NA() );
  CHECK( 1 == chunk.numberAngularParameters() );
  CHECK( 1 == chunk.NL() );
  CHECK( 1 == chunk.legendreOrder() );
  CHECK( 6 == chunk.NW() );
  CHECK( 2 == chunk.NEP() );
  CHECK( 2 == chunk.numberSecondaryEnergies() );
  CHECK( 2 == chunk.EP().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 1. == Approx( chunk.EP()[0] ) );
  CHECK( 4. == Approx( chunk.EP()[1] ) );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 4. == Approx( chunk.energies()[1] ) );
  CHECK( 2 == chunk.A().size() );
  CHECK( 2 == chunk.coefficients().size() );
  CHECK( 2. == Approx( chunk.A()[0][0] ) );
  CHECK( 3. == Approx( chunk.A()[0][1] ) );
  CHECK( 5. == Approx( chunk.A()[1][0] ) );
  CHECK( 6. == Approx( chunk.A()[1][1] ) );
  CHECK( 2. == Approx( chunk.coefficients()[0][0] ) );
  CHECK( 3. == Approx( chunk.coefficients()[0][1] ) );
  CHECK( 5. == Approx( chunk.coefficients()[1][0] ) );
  CHECK( 6. == Approx( chunk.coefficients()[1][1] ) );
  CHECK( 2 == chunk.F0().size() );
  CHECK( 2 == chunk.totalEmissionProbabilities().size() );
  CHECK( 2. == Approx( chunk.F0()[0] ) );
  CHECK( 5. == Approx( chunk.F0()[1] ) );
  CHECK( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          1          5          2922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           922826  5     \n";
}
