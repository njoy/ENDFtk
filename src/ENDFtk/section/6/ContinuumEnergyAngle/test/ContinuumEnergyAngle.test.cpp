// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ContinuumEnergyAngle =
section::Type< 6 >::ContinuumEnergyAngle;
using Variant =
section::Type< 6 >::ContinuumEnergyAngle::Variant;
using LegendreCoefficients =
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;
using KalbachMann =
section::Type< 6 >::ContinuumEnergyAngle::KalbachMann;
using TabulatedDistribution =
section::Type< 6 >::ContinuumEnergyAngle::TabulatedDistribution;

std::string chunkWithLANG1();
void verifyChunkWithLANG1( const ContinuumEnergyAngle& );
std::string chunkWithLANG2();
void verifyChunkWithLANG2( const ContinuumEnergyAngle& );
std::string chunkWithLANG14();
void verifyChunkWithLANG14( const ContinuumEnergyAngle& );
std::string invalidLANG();

SCENARIO( "ContinuumEnergyAngle" ) {

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=1" ) {

    std::string string = chunkWithLANG1();

    WHEN( "the data is given explicitly" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< Variant > distributions = {
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

        verifyChunkWithLANG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ContinuumEnergyAngle can be constructed and members can be "
            "tested" ) {

        verifyChunkWithLANG1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=2" ) {

    std::string string = chunkWithLANG2();

    WHEN( "the data is given explicitly" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
       std::vector< Variant > distributions = {
          KalbachMann(
              1e-5, 0,
              std::vector< std::array< double, 3 > >{
                  {{1., 2., 3.}}, {{4., 5., 6.}} } ),
          KalbachMann(
              2e+7, 0,
              std::vector< std::array< double, 4 > >{
                  {{7., 8., 9., 10.}}, {{11., 12., 13., 14.}} } ) };

      ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( distributions ) );

      THEN( "a ContinuumEnergyAngle can "
          "be constructed and members can be tested" ) {

        verifyChunkWithLANG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        verifyChunkWithLANG2( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=14" ) {

    std::string string = chunkWithLANG14();

    WHEN( "the data is given explicitly" ) {

      int lang = 14;
      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< Variant > distributions = {
          TabulatedDistribution( lang, 1e-5, 0, 4,
                                 {  1.,  7. },  { 2., 8. },
                                 { { 3., 5. }, { 9., 11. } },
                                 { { 4., 6. }, { 10., 12. } } ),
          TabulatedDistribution( lang, 2e+7, 0, 4,
                                 {  13.,  19. },  { 14., 20. },
                                 { { 15., 17. }, { 21., 23. } },
                                 { { 16., 18. }, { 22., 24. } } ) };

      ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                  std::move( interpolants ),
                                  std::move( distributions ) );

      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        verifyChunkWithLANG14( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        verifyChunkWithLANG14( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "subsections with different LANG values are used" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< Variant > distributions = {
          LegendreCoefficients( 1e-5, 0, 1, { 1., 4., 7., 10. },
                                { { 2., 3. }, { 5., 6. },
                                  { 8., 9. }, {  11., 12. } } ),
          KalbachMann( 1e-5, 0,
                       std::vector< std::array< double, 4 > >{
                           {{1., 2., 3.}}, {{4., 5., 6.}} } ) };

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( ContinuumEnergyAngle(
                                    lep, std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( distributions ) ) );
      } // THEN
    }

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        long lep = 2;
        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< Variant > distributions = {
            KalbachMann(
                1e-5, 0,
                std::vector< std::array< double, 3 > >{
                    {{1., 2., 3.}}, {{4., 5., 6.}} } ),
            KalbachMann(
                2e+7, 0,
                std::vector< std::array< double, 4 > >{
                    {{7., 8., 9., 10.}}, {{11., 12., 13., 14.}} } ) };

        CHECK_THROWS(
          ContinuumEnergyAngle( lep,
                                std::move( wrongBoundaries ),
                                std::move( interpolants ),
                                std::move( distributions ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        long lep = 2;
        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< Variant > distributions = {
            KalbachMann(
                1e-5, 0,
                std::vector< std::array< double, 3 > >{
                    {{1., 2., 3.}}, {{4., 5., 6.}} } ),
            KalbachMann(
                2e+7, 0,
                std::vector< std::array< double, 4 > >{
                    {{7., 8., 9., 10.}}, {{11., 12., 13., 14.}} } ) };

        CHECK_THROWS(
          ContinuumEnergyAngle( lep,
                                std::move( boundaries ),
                                std::move( wrongInterpolants ),
                                std::move( distributions ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the distributions" ) {

        long lep = 2;
        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< Variant > wrongSequence = {
            KalbachMann(
                1e-5, 0,
                std::vector< std::array< double, 3 > >{
                    {{1., 2., 3.}}, {{4., 5., 6.}} } ) };

        CHECK_THROWS(
          ContinuumEnergyAngle( lep,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with an invalid LANG" ) {

      std::string string = invalidLANG();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( ContinuumEnergyAngle( begin, end, lineNumber,
                                              9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithLANG1() {
  return
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunkWithLANG1( const ContinuumEnergyAngle& chunk ) {

  CHECK( 1 == chunk.LAW() );
  CHECK( 2 == chunk.LEP() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  auto energies = chunk.distributions();

  auto subsection1 = std::get< LegendreCoefficients >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.E() ) );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
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
  CHECK_THAT( 1., WithinRel( subsection1.EP()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection1.EP()[1] ) );
  CHECK_THAT( 7., WithinRel( subsection1.EP()[2] ) );
  CHECK_THAT( 10., WithinRel( subsection1.EP()[3] ) );
  CHECK_THAT( 1., WithinRel( subsection1.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection1.energies()[1] ) );
  CHECK_THAT( 7., WithinRel( subsection1.energies()[2] ) );
  CHECK_THAT( 10., WithinRel( subsection1.energies()[3] ) );
  CHECK( 4 == subsection1.A().size() );
  CHECK( 4 == subsection1.coefficients().size() );
  CHECK_THAT( 2., WithinRel( subsection1.A()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection1.A()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection1.A()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.A()[1][1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.A()[2][0] ) );
  CHECK_THAT( 9., WithinRel( subsection1.A()[2][1] ) );
  CHECK_THAT( 11., WithinRel( subsection1.A()[3][0] ) );
  CHECK_THAT( 12., WithinRel( subsection1.A()[3][1] ) );
  CHECK_THAT( 2., WithinRel( subsection1.coefficients()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection1.coefficients()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection1.coefficients()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.coefficients()[1][1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.coefficients()[2][0] ) );
  CHECK_THAT( 9., WithinRel( subsection1.coefficients()[2][1] ) );
  CHECK_THAT( 11., WithinRel( subsection1.coefficients()[3][0] ) );
  CHECK_THAT( 12., WithinRel( subsection1.coefficients()[3][1] ) );
  CHECK( 4 == subsection1.F0().size() );
  CHECK( 4 == subsection1.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection1.F0()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.F0()[1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.F0()[2] ) );
  CHECK_THAT( 11., WithinRel( subsection1.F0()[3] ) );
  CHECK_THAT( 2., WithinRel( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK_THAT( 8., WithinRel( subsection1.totalEmissionProbabilities()[2] ) );
  CHECK_THAT( 11., WithinRel( subsection1.totalEmissionProbabilities()[3] ) );

  auto subsection2 = std::get< LegendreCoefficients >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
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
  CHECK_THAT( 1., WithinRel( subsection2.EP()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( subsection2.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.A().size() );
  CHECK( 2 == subsection2.coefficients().size() );
  CHECK_THAT( 2., WithinRel( subsection2.A()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.A()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.A()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection2.A()[1][1] ) );
  CHECK_THAT( 2., WithinRel( subsection2.coefficients()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection2.coefficients()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection2.coefficients()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection2.coefficients()[1][1] ) );
  CHECK( 2 == subsection2.F0().size() );
  CHECK( 2 == subsection2.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection2.F0()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection2.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection2.totalEmissionProbabilities()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkWithLANG2() {
  return
    " 0.000000+0 0.000000+0          2          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 0.000000+0 2.000000+7          0          2          8          29228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1                                            9228 6  5     \n";
}

void verifyChunkWithLANG2( const ContinuumEnergyAngle& chunk ) {

  CHECK( 1 == chunk.LAW() );
  CHECK( 2 == chunk.LEP() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  auto energies = chunk.distributions();

  auto subsection1 = std::get< KalbachMann >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.E() ) );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
  CHECK( 2 == subsection1.LANG() );
  CHECK( 2 == subsection1.representation() );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 1 == subsection1.NA() );
  CHECK( 1 == subsection1.numberAngularParameters() );
  CHECK( 6 == subsection1.NW() );
  CHECK( 2 == subsection1.NEP() );
  CHECK( 2 == subsection1.numberSecondaryEnergies() );
  CHECK( 2 == subsection1.EP().size() );
  CHECK( 2 == subsection1.energies().size() );
  CHECK_THAT( 1., WithinRel( subsection1.EP()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection1.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( subsection1.energies()[0] ) );
  CHECK_THAT( 4., WithinRel( subsection1.energies()[1] ) );
  CHECK( 2 == subsection1.parameters().size() );
  CHECK_THAT( 2., WithinRel( subsection1.parameters()[0][0] ) );
  CHECK_THAT( 3., WithinRel( subsection1.parameters()[0][1] ) );
  CHECK_THAT( 5., WithinRel( subsection1.parameters()[1][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.parameters()[1][1] ) );
  CHECK( 2 == subsection1.F0().size() );
  CHECK( 2 == subsection1.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection1.F0()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.totalEmissionProbabilities()[1] ) );

  auto subsection2 = std::get< KalbachMann >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
  CHECK( 2 == subsection2.LANG() );
  CHECK( 2 == subsection2.representation() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 2 == subsection2.NA() );
  CHECK( 2 == subsection2.numberAngularParameters() );
  CHECK( 8 == subsection2.NW() );
  CHECK( 2 == subsection2.NEP() );
  CHECK( 2 == subsection2.numberSecondaryEnergies() );
  CHECK( 2 == subsection2.EP().size() );
  CHECK( 2 == subsection2.energies().size() );
  CHECK_THAT( 7., WithinRel( subsection2.EP()[0] ) );
  CHECK_THAT( 11., WithinRel( subsection2.EP()[1] ) );
  CHECK_THAT( 7., WithinRel( subsection2.energies()[0] ) );
  CHECK_THAT( 11., WithinRel( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.parameters().size() );
  CHECK_THAT( 8., WithinRel( subsection2.parameters()[0][0] ) );
  CHECK_THAT( 9., WithinRel( subsection2.parameters()[0][1] ) );
  CHECK_THAT( 10., WithinRel( subsection2.parameters()[0][2] ) );
  CHECK_THAT( 12., WithinRel( subsection2.parameters()[1][0] ) );
  CHECK_THAT( 13., WithinRel( subsection2.parameters()[1][1] ) );
  CHECK_THAT( 14., WithinRel( subsection2.parameters()[1][2] ) );
  CHECK( 2 == subsection2.F0().size() );
  CHECK( 2 == subsection2.totalEmissionProbabilities().size() );
  CHECK_THAT( 8., WithinRel( subsection2.F0()[0] ) );
  CHECK_THAT( 12., WithinRel( subsection2.F0()[1] ) );
  CHECK_THAT( 8., WithinRel( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 12., WithinRel( subsection2.totalEmissionProbabilities()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkWithLANG14() {
  return
    " 0.000000+0 0.000000+0         14          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          4         12          29228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1 1.800000+19228 6  5     \n"
    " 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1 2.400000+19228 6  5     \n";
}

void verifyChunkWithLANG14( const ContinuumEnergyAngle& chunk ) {

  CHECK( 1 == chunk.LAW() );
  CHECK( 2 == chunk.LEP() );
  CHECK( 2 == chunk.NE() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );

  auto energies = chunk.distributions();

  auto subsection1 = std::get< TabulatedDistribution >( energies[0] );
  CHECK_THAT( 1e-5, WithinRel( subsection1.E() ) );
  CHECK_THAT( 1e-5, WithinRel( subsection1.incidentEnergy() ) );
  CHECK( 14 == subsection1.LANG() );
  CHECK( 14 == subsection1.representation() );
  CHECK( 0 == subsection1.ND() );
  CHECK( 0 == subsection1.numberDiscreteEnergies() );
  CHECK( 4 == subsection1.NA() );
  CHECK( 4 == subsection1.numberAngularParameters() );
  CHECK( 12 == subsection1.NW() );
  CHECK( 2 == subsection1.NEP() );
  CHECK( 2 == subsection1.numberSecondaryEnergies() );
  CHECK( 2 == subsection1.EP().size() );
  CHECK( 2 == subsection1.energies().size() );
  CHECK_THAT( 1., WithinRel( subsection1.EP()[0] ) );
  CHECK_THAT( 7., WithinRel( subsection1.EP()[1] ) );
  CHECK_THAT( 1., WithinRel( subsection1.energies()[0] ) );
  CHECK_THAT( 7., WithinRel( subsection1.energies()[1] ) );
  CHECK( 2 == subsection1.F0().size() );
  CHECK( 2 == subsection1.totalEmissionProbabilities().size() );
  CHECK_THAT( 2., WithinRel( subsection1.F0()[0] ) );
  CHECK_THAT( 8., WithinRel( subsection1.F0()[1] ) );
  CHECK_THAT( 2., WithinRel( subsection1.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 8., WithinRel( subsection1.totalEmissionProbabilities()[1] ) );
  CHECK( 2 == subsection1.MU().size() );
  CHECK( 2 == subsection1.cosines().size() );
  CHECK_THAT( 3., WithinRel( subsection1.MU()[0][0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.MU()[0][1] ) );
  CHECK_THAT( 9., WithinRel( subsection1.MU()[1][0] ) );
  CHECK_THAT( 11., WithinRel( subsection1.MU()[1][1] ) );
  CHECK_THAT( 3., WithinRel( subsection1.cosines()[0][0] ) );
  CHECK_THAT( 5., WithinRel( subsection1.cosines()[0][1] ) );
  CHECK_THAT( 9., WithinRel( subsection1.cosines()[1][0] ) );
  CHECK_THAT( 11., WithinRel( subsection1.cosines()[1][1] ) );
  CHECK( 2 == subsection1.F().size() );
  CHECK( 2 == subsection1.probabilities().size() );
  CHECK_THAT( 4., WithinRel( subsection1.F()[0][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.F()[0][1] ) );
  CHECK_THAT( 10., WithinRel( subsection1.F()[1][0] ) );
  CHECK_THAT( 12., WithinRel( subsection1.F()[1][1] ) );
  CHECK_THAT( 4., WithinRel( subsection1.probabilities()[0][0] ) );
  CHECK_THAT( 6., WithinRel( subsection1.probabilities()[0][1] ) );
  CHECK_THAT( 10., WithinRel( subsection1.probabilities()[1][0] ) );
  CHECK_THAT( 12., WithinRel( subsection1.probabilities()[1][1] ) );

  auto subsection2 = std::get< TabulatedDistribution >( energies[1] );
  CHECK_THAT( 2e+7, WithinRel( subsection2.E() ) );
  CHECK_THAT( 2e+7, WithinRel( subsection2.incidentEnergy() ) );
  CHECK( 14 == subsection2.LANG() );
  CHECK( 0 == subsection2.ND() );
  CHECK( 0 == subsection2.numberDiscreteEnergies() );
  CHECK( 4 == subsection2.NA() );
  CHECK( 4 == subsection2.numberAngularParameters() );
  CHECK( 12 == subsection2.NW() );
  CHECK( 2 == subsection2.NEP() );
  CHECK( 2 == subsection2.numberSecondaryEnergies() );
  CHECK( 2 == subsection2.EP().size() );
  CHECK( 2 == subsection2.energies().size() );
  CHECK_THAT( 13., WithinRel( subsection2.EP()[0] ) );
  CHECK_THAT( 19., WithinRel( subsection2.EP()[1] ) );
  CHECK_THAT( 13., WithinRel( subsection2.energies()[0] ) );
  CHECK_THAT( 19., WithinRel( subsection2.energies()[1] ) );
  CHECK( 2 == subsection2.F0().size() );
  CHECK( 2 == subsection2.totalEmissionProbabilities().size() );
  CHECK_THAT( 14., WithinRel( subsection2.F0()[0] ) );
  CHECK_THAT( 20., WithinRel( subsection2.F0()[1] ) );
  CHECK_THAT( 14., WithinRel( subsection2.totalEmissionProbabilities()[0] ) );
  CHECK_THAT( 20., WithinRel( subsection2.totalEmissionProbabilities()[1] ) );
  CHECK( 2 == subsection2.MU().size() );
  CHECK( 2 == subsection2.cosines().size() );
  CHECK_THAT( 15., WithinRel( subsection2.MU()[0][0] ) );
  CHECK_THAT( 17., WithinRel( subsection2.MU()[0][1] ) );
  CHECK_THAT( 21., WithinRel( subsection2.MU()[1][0] ) );
  CHECK_THAT( 23., WithinRel( subsection2.MU()[1][1] ) );
  CHECK_THAT( 15., WithinRel( subsection2.cosines()[0][0] ) );
  CHECK_THAT( 17., WithinRel( subsection2.cosines()[0][1] ) );
  CHECK_THAT( 21., WithinRel( subsection2.cosines()[1][0] ) );
  CHECK_THAT( 23., WithinRel( subsection2.cosines()[1][1] ) );
  CHECK( 2 == subsection2.F().size() );
  CHECK( 2 == subsection2.probabilities().size() );
  CHECK_THAT( 16., WithinRel( subsection2.F()[0][0] ) );
  CHECK_THAT( 18., WithinRel( subsection2.F()[0][1] ) );
  CHECK_THAT( 22., WithinRel( subsection2.F()[1][0] ) );
  CHECK_THAT( 24., WithinRel( subsection2.F()[1][1] ) );
  CHECK_THAT( 16., WithinRel( subsection2.probabilities()[0][0] ) );
  CHECK_THAT( 18., WithinRel( subsection2.probabilities()[0][1] ) );
  CHECK_THAT( 22., WithinRel( subsection2.probabilities()[1][0] ) );
  CHECK_THAT( 24., WithinRel( subsection2.probabilities()[1][1] ) );

  CHECK( 8 == chunk.NC() );
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
