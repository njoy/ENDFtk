#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using SubSection = 
section::Type< 6 >::ContinuumEnergyAngle::SubSection;
using LegendreCoefficients = 
section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients;
using KalbachMann = 
section::Type< 6 >::ContinuumEnergyAngle::KalbachMann;
using Tabulated = 
section::Type< 6 >::ContinuumEnergyAngle::Tabulated;

std::string chunkLANG1();
std::string chunkLANG2();
std::string chunkLANG14();

SCENARIO( "SubSection" ) {

  GIVEN( "valid data for a SubSection with LANG=1" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
    std::vector< std::pair< double, std::vector< double > > > data = { 
      std::make_pair< double, std::vector< double > >( 1., { 2., 3. } ),
      std::make_pair< double, std::vector< double > >( 4., { 5., 6. } ) };

    THEN( "a SubSection can be constructed and members can be tested" ) {
      SubSection subsection(
          LegendreCoefficients( energy, nd, na, nep, std::move( list ) ) );

      auto chunk = std::experimental::get< LegendreCoefficients >( subsection );

      REQUIRE( 1 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 1 == chunk.NA() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 4. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.coefficients().size() );
      REQUIRE( 2. == Approx( chunk.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( chunk.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( chunk.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a SubSection with LANG=2" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
    std::vector< std::tuple< double, double, double > > data = { 
      { 1., 2., 3. },
      { 4., 5., 6. } };

    THEN( "a SubSection can "
          "be constructed and members can be tested" ) {
      SubSection subsection(
          KalbachMann( energy, nd, na, nep, std::move( list ) ) );

      auto chunk = std::experimental::get< KalbachMann >( subsection );

      REQUIRE( 2 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 1 == chunk.NA() );
      REQUIRE( 6 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 4. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.parameters().size() );
      REQUIRE( 2. == Approx( chunk.parameters()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.parameters()[0][1] ) );
      REQUIRE( 5. == Approx( chunk.parameters()[1][0] ) );
      REQUIRE( 6. == Approx( chunk.parameters()[1][1] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "valid data for a SubSection with LANG=14" ) {

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

    THEN( "a SubSection can be constructed and members can be tested" ) {
      SubSection subsection(
          Tabulated( lang, energy, nd, na, nep, std::move( list ) ) );

      auto chunk = std::experimental::get< Tabulated >( subsection );

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

  GIVEN( "a valid instance of SubSection"
         "with LANG=1" ) {

    std::string string = chunkLANG1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection
      subsection( LegendreCoefficients( begin, end, lineNumber, 9228, 6, 5 ) );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection"
         "with LANG=2" ) {

    std::string string = chunkLANG2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection
      subsection( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection"
         "with LANG=14" ) {

    std::string string = chunkLANG14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection
      subsection( Tabulated( 14, begin, end, lineNumber, 9228, 6, 5 ) );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunkLANG1() {
  return
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkLANG2() {
  return
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkLANG14() {
  return
    " 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n";
}

