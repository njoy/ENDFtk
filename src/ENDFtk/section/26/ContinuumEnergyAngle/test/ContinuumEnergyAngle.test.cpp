#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ContinuumEnergyAngle =
section::Type< 26 >::ContinuumEnergyAngle;
using LegendreCoefficients =
section::Type< 26 >::ContinuumEnergyAngle::LegendreCoefficients;

std::string chunk();
void verifyChunk( const ContinuumEnergyAngle& );
std::string invalidLANG();

SCENARIO( "ContinuumEnergyAngle" ) {

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=1" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< LegendreCoefficients > distributions = {
          LegendreCoefficients( 1e-5, 0, 1, { 1., 4., 7., 10. },
                                { { 2., 3. }, { 5., 6. },
                                  { 8., 9. }, {  11., 12. } } ),
          LegendreCoefficients( 2e+7, 0, 1, { 1., 4. },
                                { { 2., 3. }, { 5., 6. } } ) };

      ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( distributions ) );

      THEN( "a ContinuumEnergyAngle can be constructed and members can be "
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

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 26, 5 );

      THEN( "a ContinuumEnergyAngle can be constructed and members can be "
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
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "a string representation is used with an invalid LANG" ) {

      std::string string = invalidLANG();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( ContinuumEnergyAngle( begin, end, lineNumber,
                                              9228, 26, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          2          1          2922826  5     \n"
    "          2          1                                            922826  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          4922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1922826  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          2922826  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n";
}

void verifyChunk( const ContinuumEnergyAngle& chunk ) {

  CHECK( 1 == chunk.LAW() );
  CHECK( 2 == chunk.LEP() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  auto energies = chunk.distributions();

  auto subsection1 = energies[0];
  CHECK( 1e-5 == Approx( subsection1.E() ) );
  CHECK( 1e-5 == Approx( subsection1.incidentEnergy() ) );
  CHECK( 1 == subsection1.LANG() );
  CHECK( 1 == subsection1.representation() );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 1 == subsection1.NA() );
  CHECK( 1 == subsection1.numberAngularParameters() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 4 == subsection1.NEP() );
  CHECK( 4 == subsection1.numberSecondaryEnergies() );
  CHECK( 4 == subsection1.EP().size() );
  CHECK( 4 == subsection1.energies().size() );
  CHECK( 1. == Approx( subsection1.EP()[0] ) );
  CHECK( 4. == Approx( subsection1.EP()[1] ) );
  CHECK( 7. == Approx( subsection1.EP()[2] ) );
  CHECK( 10. == Approx( subsection1.EP()[3] ) );
  CHECK( 1. == Approx( subsection1.energies()[0] ) );
  CHECK( 4. == Approx( subsection1.energies()[1] ) );
  CHECK( 7. == Approx( subsection1.energies()[2] ) );
  CHECK( 10. == Approx( subsection1.energies()[3] ) );
  CHECK( 4 == subsection1.A().size() );
  CHECK( 4 == subsection1.coefficients().size() );
  CHECK( 2. == Approx( subsection1.A()[0][0] ) );
  CHECK( 3. == Approx( subsection1.A()[0][1] ) );
  CHECK( 5. == Approx( subsection1.A()[1][0] ) );
  CHECK( 6. == Approx( subsection1.A()[1][1] ) );
  CHECK( 8. == Approx( subsection1.A()[2][0] ) );
  CHECK( 9. == Approx( subsection1.A()[2][1] ) );
  CHECK( 11. == Approx( subsection1.A()[3][0] ) );
  CHECK( 12. == Approx( subsection1.A()[3][1] ) );
  CHECK( 2. == Approx( subsection1.coefficients()[0][0] ) );
  CHECK( 3. == Approx( subsection1.coefficients()[0][1] ) );
  CHECK( 5. == Approx( subsection1.coefficients()[1][0] ) );
  CHECK( 6. == Approx( subsection1.coefficients()[1][1] ) );
  CHECK( 8. == Approx( subsection1.coefficients()[2][0] ) );
  CHECK( 9. == Approx( subsection1.coefficients()[2][1] ) );
  CHECK( 11. == Approx( subsection1.coefficients()[3][0] ) );
  CHECK( 12. == Approx( subsection1.coefficients()[3][1] ) );
  CHECK( 4 == Approx( subsection1.F0().size() ) );
  CHECK( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( subsection1.F0()[0] ) );
  CHECK( 5. == Approx( subsection1.F0()[1] ) );
  CHECK( 8. == Approx( subsection1.F0()[2] ) );
  CHECK( 11. == Approx( subsection1.F0()[3] ) );
  CHECK( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
  CHECK( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

  auto subsection2 = energies[1];
  CHECK( 2e+7 == Approx( subsection2.E() ) );
  CHECK( 2e+7 == Approx( subsection2.incidentEnergy() ) );
  CHECK( 1 == subsection2.LANG() );
  CHECK( 1 == subsection2.representation() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 1 == subsection2.NA() );
  CHECK( 1 == subsection2.numberAngularParameters() );
  CHECK( 6 == subsection2.NW() );
  CHECK( 2 == subsection2.NEP() );
  CHECK( 2 == subsection2.numberSecondaryEnergies() );
  CHECK( 2 == subsection2.EP().size() );
  CHECK( 2 == subsection2.energies().size() );
  CHECK( 1. == Approx( subsection2.EP()[0] ) );
  CHECK( 4. == Approx( subsection2.EP()[1] ) );
  CHECK( 1. == Approx( subsection2.energies()[0] ) );
  CHECK( 4. == Approx( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.A().size() );
  CHECK( 2 == subsection2.coefficients().size() );
  CHECK( 2. == Approx( subsection2.A()[0][0] ) );
  CHECK( 3. == Approx( subsection2.A()[0][1] ) );
  CHECK( 5. == Approx( subsection2.A()[1][0] ) );
  CHECK( 6. == Approx( subsection2.A()[1][1] ) );
  CHECK( 2. == Approx( subsection2.coefficients()[0][0] ) );
  CHECK( 3. == Approx( subsection2.coefficients()[0][1] ) );
  CHECK( 5. == Approx( subsection2.coefficients()[1][0] ) );
  CHECK( 6. == Approx( subsection2.coefficients()[1][1] ) );
  CHECK( 2 == Approx( subsection2.F0().size() ) );
  CHECK( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
  CHECK( 2. == Approx( subsection2.F0()[0] ) );
  CHECK( 5. == Approx( subsection2.F0()[1] ) );
  CHECK( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidLANG() {
  return
    " 5.000000-1 0.000000+0          4          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}
