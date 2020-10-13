#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreCoefficients =
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreCoefficients& );
std::string invalidSize();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      int nep = 2;
      std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
      std::vector< double > energies = { 1., 4. };
      std::vector< std::vector< double > > coefficients = { { 2., 3. },
                                                            { 5., 6. } };

      THEN( "a LegendreCoefficients can be constructed using a list and "
            "members can be tested" ) {

        LegendreCoefficients chunk( energy, nd, na, nep, std::move( list ) );
        verifyChunk( chunk );
      }

      THEN( "a LegendreCoefficients can be constructed using energies and "
            "coefficients and members can be tested" ) {

        LegendreCoefficients chunk( energy, nd, na, nep,
                                    std::move( energies ),
                                    std::move( coefficients ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a LegendreCoefficients can be constructed and members can "
            "be tested" ) {

        LegendreCoefficients chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of LegendreCoefficients" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    LegendreCoefficients
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "data is used with inconsistent sizes" ) {

      double energy = 1e-5;
      int nd = 0;
      int na = 1;
      int nep = 2;
      std::vector< double > wronglist = { 1., 2., 3., 4., 5. };
      std::vector< double > energies = { 1., 4. };
      std::vector< std::vector< double > > wrongcoefficients1 = { { 2., 3. },
                                                                  { 5. } };
      std::vector< std::vector< double > > wrongcoefficients2 = { { 2., 3. },
                                                                  { 5., 6. },
                                                                  { 8., 9. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreCoefficients( energy, nd, na, nep,
                                            std::move( wronglist ) ) );
        CHECK_THROWS( LegendreCoefficients( energy, nd, na, nep,
                                            std::move( energies ),
                                            std::move( wrongcoefficients1 ) ) );
        CHECK_THROWS( LegendreCoefficients( energy, nd, na, nep,
                                            std::move( energies ),
                                            std::move( wrongcoefficients1 ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string is used with inconsistent NW, NA, NEP" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                            9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunk( const LegendreCoefficients& chunk ) {

      CHECK( 1 == chunk.LANG() );
      CHECK( 1e-5 == Approx( chunk.energy() ) );

      CHECK( 0 == chunk.ND() );
      CHECK( 0 == chunk.numberDiscreteEnergies() );
      CHECK( 1 == chunk.NA() );
      CHECK( 1 == chunk.numberAngularParameters() );
      CHECK( 6 == chunk.NW() );
      CHECK( 2 == chunk.NEP() );
      CHECK( 2 == chunk.numberSecondaryEnergies() );
      CHECK( 2 == chunk.energies().size() );
      CHECK( 1. == Approx( chunk.energies()[0] ) );
      CHECK( 4. == Approx( chunk.energies()[1] ) );
      CHECK( 2 == chunk.coefficients().size() );
      CHECK( 2. == Approx( chunk.coefficients()[0][0] ) );
      CHECK( 3. == Approx( chunk.coefficients()[0][1] ) );
      CHECK( 5. == Approx( chunk.coefficients()[1][0] ) );
      CHECK( 6. == Approx( chunk.coefficients()[1][1] ) );
      CHECK( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      CHECK( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      CHECK( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      CHECK( 2 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          1          5          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           9228 6  5     \n";
}
