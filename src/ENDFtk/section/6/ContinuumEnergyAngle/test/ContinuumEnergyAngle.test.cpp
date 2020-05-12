#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ContinuumEnergyAngle = 
section::Type< 6 >::ContinuumEnergyAngle;
using SubSection = 
section::Type< 6 >::ContinuumEnergyAngle::SubSection;
using LegendreCoefficients = 
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;
using KalbachMann = 
section::Type< 6 >::ContinuumEnergyAngle::KalbachMann;
using Tabulated = 
section::Type< 6 >::ContinuumEnergyAngle::Tabulated;

std::string chunkWithLANG1();
void verifyChunkWithLANG1( const ContinuumEnergyAngle& );
std::string chunkWithLANG2();
void verifyChunkWithLANG2( const ContinuumEnergyAngle& );
std::string chunkWithLANG14();
void verifyChunkWithLANG14( const ContinuumEnergyAngle& );
std::string invalidLANG();

SCENARIO( "ContinuumEnergyAngle" ) {

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=1" ) {

    WHEN( "the data is given explicitly" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< SubSection > sequence = {
          LegendreCoefficients( 1e-5, 0, 1, 4, { 1., 2., 3., 4., 5., 6.,
                                                 7., 8., 9., 10., 11., 12. } ),
          LegendreCoefficients( 2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) };

      THEN( "a ContinuumEnergyAngle can be constructed and members can be "
            "tested" ) {

        ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( sequence ) );
        verifyChunkWithLANG1( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLANG1();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a ContinuumEnergyAngle can be constructed and members can be "
            "tested" ) {

        ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkWithLANG1( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=2" ) {

    WHEN( "the data is given explicitly" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
       std::vector< SubSection > sequence = {
          KalbachMann( 1e-5, 0, 1, 2, { 1., 2., 3., 4., 5., 6. } ),
          KalbachMann( 2e+7, 0, 2, 2, { 7., 8., 9., 10., 11., 12., 13., 14.} ) };

      THEN( "a ContinuumEnergyAngle can "
          "be constructed and members can be tested" ) {

        ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( sequence ) );
        verifyChunkWithLANG2( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLANG2();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkWithLANG2( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuumEnergyAngle with LANG=14" ) {

    WHEN( "the data is given explicitly" ) {

      int lang = 14;
      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< SubSection > sequence = {
          Tabulated( lang, 1e-5, 0, 4, 2, {  1.,  2.,  3.,  4.,  5.,  6.,
                                             7.,  8.,  9., 10., 11., 12. } ),
          Tabulated( lang, 2e+7, 0, 4, 2, { 13., 14., 15., 16., 17., 18.,
                                            19., 20., 21., 22., 23., 24.} ) };

      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        ContinuumEnergyAngle chunk( lep, std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( sequence ) );
        verifyChunkWithLANG14( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLANG14();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a ContinuumEnergyAngle can be constructed and members can "
            "be tested" ) {

        ContinuumEnergyAngle chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkWithLANG14( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of ContinuumEnergyAngle with LANG=1" ) {

    std::string string = chunkWithLANG1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    ContinuumEnergyAngle chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of ContinuumEnergyAngle with LANG=2" ) {

    std::string string = chunkWithLANG2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    ContinuumEnergyAngle chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of ContinuumEnergyAngle with LANG=14" ) {

    std::string string = chunkWithLANG14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    ContinuumEnergyAngle chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "subsections with different LANG values are used" ) {

      long lep = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< SubSection > sequence = {
          LegendreCoefficients( 1e-5, 0, 1, 4, { 1., 2., 3., 4., 5., 6.,
                                                 7., 8., 9., 10., 11., 12. } ),
          KalbachMann( 1e-5, 0, 1, 2, { 1., 2., 3., 4., 5., 6. } ) };

      THEN( "an exception is thrown upon construction" ) {

        REQUIRE_THROWS( ContinuumEnergyAngle(
                                    lep, std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( sequence ) ) );
      } // THEN
    }

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        long lep = 2;
        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< SubSection > sequence = {
            KalbachMann( 1e-5, 0, 1, 2, { 1., 2., 3., 4., 5., 6. } ),
            KalbachMann( 2e+7, 0, 2, 2, { 7., 8., 9., 10., 11., 12., 13., 14.} ) };

        REQUIRE_THROWS(
          ContinuumEnergyAngle( lep, 
                                std::move( wrongBoundaries ),
                                std::move( interpolants ),
                                std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        long lep = 2;
        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< SubSection > sequence = {
            KalbachMann( 1e-5, 0, 1, 2, { 1., 2., 3., 4., 5., 6. } ),
            KalbachMann( 2e+7, 0, 2, 2, { 7., 8., 9., 10., 11., 12., 13., 14.} ) };

        REQUIRE_THROWS(
          ContinuumEnergyAngle( lep, 
                                std::move( boundaries ),
                                std::move( wrongInterpolants ),
                                std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        long lep = 2;
        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< SubSection > wrongSequence = {
            KalbachMann( 1e-5, 0, 1, 2, { 1., 2., 3., 4., 5., 6. } ) };

        REQUIRE_THROWS(
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

        REQUIRE_THROWS( ContinuumEnergyAngle( begin, end, lineNumber,
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

      REQUIRE( 1 == chunk.LAW() );
      REQUIRE( 2 == chunk.LEP() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 0 == energies[0].numberDiscreteEnergies() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 1 == energies[0].numberAngularParameters() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NEP() );
      REQUIRE( 4 == energies[0].numberSecondaryEnergies() );

      auto subsection1 =
          std::get< LegendreCoefficients >( energies[0].data() );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 0 == subsection1.numberDiscreteEnergies() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 1 == subsection1.numberAngularParameters() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NEP() );
      REQUIRE( 4 == subsection1.numberSecondaryEnergies() );
      REQUIRE( 4 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 7. == Approx( subsection1.energies()[2] ) );
      REQUIRE( 10. == Approx( subsection1.energies()[3] ) );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 2. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 8. == Approx( subsection1.coefficients()[2][0] ) );
      REQUIRE( 9. == Approx( subsection1.coefficients()[2][1] ) );
      REQUIRE( 11. == Approx( subsection1.coefficients()[3][0] ) );
      REQUIRE( 12. == Approx( subsection1.coefficients()[3][1] ) );
      REQUIRE( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
      REQUIRE( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
      REQUIRE( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 1 == energies[1].numberAngularParameters() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );

      auto subsection2 =
          std::get< LegendreCoefficients >( energies[1].data() );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 1 == energies[1].numberAngularParameters() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 1. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 2. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      REQUIRE( 7 == chunk.NC() );
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

      REQUIRE( 1 == chunk.LAW() );
      REQUIRE( 2 == chunk.LEP() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 2 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 0 == energies[0].numberDiscreteEnergies() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 1 == energies[0].numberAngularParameters() );
      REQUIRE( 6 == energies[0].NW() );
      REQUIRE( 2 == energies[0].NEP() );
      REQUIRE( 2 == energies[0].numberSecondaryEnergies() );

      auto subsection1 =
          std::get< KalbachMann >( energies[0].data() );
      REQUIRE( 2 == subsection1.LANG() );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 0 == energies[0].numberDiscreteEnergies() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 1 == energies[0].numberAngularParameters() );
      REQUIRE( 6 == subsection1.NW() );
      REQUIRE( 2 == subsection1.NEP() );
      REQUIRE( 2 == energies[0].numberSecondaryEnergies() );
      REQUIRE( 2 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 2 == subsection1.parameters().size() );
      REQUIRE( 2. == Approx( subsection1.parameters()[0][0] ) );
      REQUIRE( 3. == Approx( subsection1.parameters()[0][1] ) );
      REQUIRE( 5. == Approx( subsection1.parameters()[1][0] ) );
      REQUIRE( 6. == Approx( subsection1.parameters()[1][1] ) );
      REQUIRE( 2 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 2 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 2 == energies[1].NA() );
      REQUIRE( 2 == energies[1].numberAngularParameters() );
      REQUIRE( 8 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );

      auto subsection2 =
          std::get< KalbachMann >( energies[1].data() );
      REQUIRE( 2 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 2 == subsection2.NA() );
      REQUIRE( 2 == energies[1].numberAngularParameters() );
      REQUIRE( 8 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 7. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 11. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.parameters().size() );
      REQUIRE( 8. == Approx( subsection2.parameters()[0][0] ) );
      REQUIRE( 9. == Approx( subsection2.parameters()[0][1] ) );
      REQUIRE( 10. == Approx( subsection2.parameters()[0][2] ) );
      REQUIRE( 12. == Approx( subsection2.parameters()[1][0] ) );
      REQUIRE( 13. == Approx( subsection2.parameters()[1][1] ) );
      REQUIRE( 14. == Approx( subsection2.parameters()[1][2] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 8. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 12. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      REQUIRE( 7 == chunk.NC() );
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

      REQUIRE( 1 == chunk.LAW() );
      REQUIRE( 2 == chunk.LEP() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 1 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );

      auto energies = chunk.subsections();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 14 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 0 == energies[0].numberDiscreteEnergies() );
      REQUIRE( 4 == energies[0].NA() );
      REQUIRE( 4 == energies[0].numberAngularParameters() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 2 == energies[0].NEP() );
      REQUIRE( 2 == energies[0].numberSecondaryEnergies() );

      auto subsection1 =
          std::get< Tabulated >( energies[0].data() );
      REQUIRE( 14 == subsection1.LANG() );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 0 == energies[0].numberDiscreteEnergies() );
      REQUIRE( 4 == subsection1.NA() );
      REQUIRE( 4 == energies[0].numberAngularParameters() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 2 == subsection1.NEP() );
      REQUIRE( 2 == energies[0].numberSecondaryEnergies() );
      REQUIRE( 2 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 7. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 2 == subsection1.totalEmissionProbabilities().size() );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 8. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
      REQUIRE( 2 == subsection1.cosines().size() );
      REQUIRE( 3. == Approx( subsection1.cosines()[0][0] ) );
      REQUIRE( 5. == Approx( subsection1.cosines()[0][1] ) );
      REQUIRE( 9. == Approx( subsection1.cosines()[1][0] ) );
      REQUIRE( 11. == Approx( subsection1.cosines()[1][1] ) );
      REQUIRE( 2 == subsection1.probabilities().size() );
      REQUIRE( 4. == Approx( subsection1.probabilities()[0][0] ) );
      REQUIRE( 6. == Approx( subsection1.probabilities()[0][1] ) );
      REQUIRE( 10. == Approx( subsection1.probabilities()[1][0] ) );
      REQUIRE( 12. == Approx( subsection1.probabilities()[1][1] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 14 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 4 == energies[1].NA() );
      REQUIRE( 4 == energies[1].numberAngularParameters() );
      REQUIRE( 12 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );

      auto subsection2 =
          std::get< Tabulated >( energies[1].data() );
      REQUIRE( 14 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 0 == energies[1].numberDiscreteEnergies() );
      REQUIRE( 4 == subsection2.NA() );
      REQUIRE( 4 == energies[1].numberAngularParameters() );
      REQUIRE( 12 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == energies[1].numberSecondaryEnergies() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 13. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 19. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.totalEmissionProbabilities().size() );
      REQUIRE( 14. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 20. == Approx( subsection2.totalEmissionProbabilities()[1] ) );
      REQUIRE( 2 == subsection2.cosines().size() );
      REQUIRE( 15. == Approx( subsection2.cosines()[0][0] ) );
      REQUIRE( 17. == Approx( subsection2.cosines()[0][1] ) );
      REQUIRE( 21. == Approx( subsection2.cosines()[1][0] ) );
      REQUIRE( 23. == Approx( subsection2.cosines()[1][1] ) );
      REQUIRE( 2 == subsection2.probabilities().size() );
      REQUIRE( 16. == Approx( subsection2.probabilities()[0][0] ) );
      REQUIRE( 18. == Approx( subsection2.probabilities()[0][1] ) );
      REQUIRE( 22. == Approx( subsection2.probabilities()[1][0] ) );
      REQUIRE( 24. == Approx( subsection2.probabilities()[1][1] ) );

      REQUIRE( 8 == chunk.NC() );
}

std::string invalidLANG() {
  return
    " 5.000000-1 0.000000+0          3          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

