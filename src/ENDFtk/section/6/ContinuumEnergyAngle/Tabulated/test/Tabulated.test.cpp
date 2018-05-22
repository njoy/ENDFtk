#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::ContinuumEnergyAngle::Tabulated" ) {

  GIVEN( "valid data for a Tabulated" ) {

    int lang = 14;
    double energy = 1e-5;
    int nd = 0;
    int na = 4;
    int nep = 2;
    std::vector< double > list = {  1.,  2.,  3.,  4.,  5.,  6.,
                                    7.,  8.,  9., 10., 11., 12. };
    std::vector< double > energies = { 1., 7. };
    std::vector< double > totalEmissionProbabilities = { 2., 8. };
    std::vector< std::vector< double > > cosines = { { 3., 5. }, { 9., 11. } };
    std::vector< std::vector< double > > probabilities = { { 4., 6. },
                                                           { 10., 12. } };

    THEN( "a Tabulated can "
          "be constructed using a list and members can be tested" ) {
      section::Type< 6 >::ContinuumEnergyAngle::Tabulated
        chunk( lang, energy, nd, na, nep, std::move( list ) );

      REQUIRE( 14 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 4 == chunk.NA() );
      REQUIRE( 12 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 7. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.totalEmissionProbabilities().size() );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 8. == Approx( chunk.totalEmissionProbabilities()[1] ) );
      REQUIRE( 2 == chunk.cosines().size() );
      REQUIRE( 3. == Approx( chunk.cosines()[0][0] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[0][1] ) );
      REQUIRE( 9. == Approx( chunk.cosines()[1][0] ) );
      REQUIRE( 11. == Approx( chunk.cosines()[1][1] ) );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 4. == Approx( chunk.probabilities()[0][0] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[0][1] ) );
      REQUIRE( 10. == Approx( chunk.probabilities()[1][0] ) );
      REQUIRE( 12. == Approx( chunk.probabilities()[1][1] ) );

      REQUIRE( 3 == chunk.NC() );
    }

    THEN( "a Tabulated can "
          "be constructed using vectors and members can be tested" ) {
      section::Type< 6 >::ContinuumEnergyAngle::Tabulated
        chunk( lang, energy, nd, nep, std::move( energies ),
               std::move( totalEmissionProbabilities ), std::move( cosines ),
               std::move( probabilities ) );

      REQUIRE( 14 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 4 == chunk.NA() );
      REQUIRE( 12 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 7. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.totalEmissionProbabilities().size() );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 8. == Approx( chunk.totalEmissionProbabilities()[1] ) );
      REQUIRE( 2 == chunk.cosines().size() );
      REQUIRE( 3. == Approx( chunk.cosines()[0][0] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[0][1] ) );
      REQUIRE( 9. == Approx( chunk.cosines()[1][0] ) );
      REQUIRE( 11. == Approx( chunk.cosines()[1][1] ) );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 4. == Approx( chunk.probabilities()[0][0] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[0][1] ) );
      REQUIRE( 10. == Approx( chunk.probabilities()[1][0] ) );
      REQUIRE( 12. == Approx( chunk.probabilities()[1][1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid Tabulated" ) {

    int lang = 14;
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a Tabulated can "
          "be constructed and members can be tested" ) {
      section::Type< 6 >::ContinuumEnergyAngle::Tabulated
        chunk( lang, begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 14 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 4 == chunk.NA() );
      REQUIRE( 12 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 7. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.totalEmissionProbabilities().size() );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 8. == Approx( chunk.totalEmissionProbabilities()[1] ) );
      REQUIRE( 2 == chunk.cosines().size() );
      REQUIRE( 3. == Approx( chunk.cosines()[0][0] ) );
      REQUIRE( 5. == Approx( chunk.cosines()[0][1] ) );
      REQUIRE( 9. == Approx( chunk.cosines()[1][0] ) );
      REQUIRE( 11. == Approx( chunk.cosines()[1][1] ) );
      REQUIRE( 2 == chunk.probabilities().size() );
      REQUIRE( 4. == Approx( chunk.probabilities()[0][0] ) );
      REQUIRE( 6. == Approx( chunk.probabilities()[0][1] ) );
      REQUIRE( 10. == Approx( chunk.probabilities()[1][0] ) );
      REQUIRE( 12. == Approx( chunk.probabilities()[1][1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of Tabulated" ) {

    int lang = 14;
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 6 >::ContinuumEnergyAngle::Tabulated
      chunk( lang, begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n";
}
