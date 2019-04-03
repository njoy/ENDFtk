#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ScatteringLawConstants = 
section::Type< 7, 4 >::ScatteringLawConstants;

std::string chunkWithOnlyPrincipalScatterer();
void verifyChunkWithOnlyPrincipalScatterer( const ScatteringLawConstants& );
std::string chunkWithBothPrincipalAndSecondaryScatterer();
void verifyChunkWithBothPrincipalAndSecondaryScatterer(
       const ScatteringLawConstants& );
std::string invalidSize();
std::string invalidLLN();

SCENARIO( "ScatteringLawConstants" ) {

  GIVEN( "valid data for a ScatteringLawConstants with only a principal "
         "scatterer" ) {

    WHEN( "the data is given explicitly" ) {

      int lln = 0;
      int ns = 0;
      std::vector< double > values = { 6.153875e+0, 1.976285e+2, 8.934780e+0,
                                       5.000001e+0, 0.000000e+0, 1.000000e+0 };
      double epsilon = 1.976285e+2;
      double emax = 5.000001e+0;
      std::vector< double > crossSections = { 6.153875e+0 };
      std::vector< double > weightRatios = { 8.934780e+0 };
      std::vector< unsigned int > numberAtoms = { 1 };
      std::vector< unsigned int > functionTypes = {};
      double crossSection = 6.153875e+0;
      double weightRatio = 8.934780e+0;
      unsigned int numberAtom = 1;

      THEN( "a ScatteringLawConstants can be constructed using a list and "
            "members can be tested" ) {

        ScatteringLawConstants chunk( lln, ns, std::move( values ) );
        verifyChunkWithOnlyPrincipalScatterer( chunk );
      } // THEN

      THEN( "a ScatteringLawConstants can be constructed using separate arrays "
            "and members can be tested" ) {

        ScatteringLawConstants chunk( lln, ns, epsilon, emax,
                                      std::move( crossSections ),
                                      std::move( weightRatios ),
                                      std::move( numberAtoms ),
                                      std::move( functionTypes ) );
        verifyChunkWithOnlyPrincipalScatterer( chunk );
      } // THEN

      THEN( "a ScatteringLawConstants can be constructed using individual "
            "values and members can be tested" ) {

        ScatteringLawConstants chunk( lln, epsilon, emax, crossSection,
                                      weightRatio, numberAtom );
        verifyChunkWithOnlyPrincipalScatterer( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithOnlyPrincipalScatterer();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a ScatteringLawConstants can be constructed and members can be "
            "tested" ) {

        ScatteringLawConstants chunk( begin, end, lineNumber, 27, 7, 4 );
        verifyChunkWithOnlyPrincipalScatterer( chunk );
      }
    } // GIVEN
  } // GIVEN

  GIVEN( "valid data for a ScatteringLawConstants with both principal and "
         "secondary scatterers" ) {

    WHEN( "the data is given explicitly" ) {

      int lln = 0;
      int ns = 1;
      std::vector< double > values = { 2.021000e+0, 9.750000e+1, 2.784423e+1,
                                       2.466750e+0, 0.000000e+0, 1.000000e+0,
                                       0.000000e+0, 3.748750e+0, 1.586200e+1,
                                       0.000000e+0, 0.000000e+0, 2.000000e+0 };
      double epsilon = 9.750000e+1;
      double emax = 2.466750e+0;
      std::vector< double > crossSections = { 2.021000e+0, 3.748750e+0 };
      std::vector< double > weightRatios = { 2.784423e+1, 1.586200e+1 };
      std::vector< unsigned int > numberAtoms = { 1, 2 };
      std::vector< unsigned int > functionTypes = { 0 };

      THEN( "a ScatteringLawConstants can be constructed using a list and "
            "members can be tested" ) {

        ScatteringLawConstants chunk( lln, ns, std::move( values ) );
        verifyChunkWithBothPrincipalAndSecondaryScatterer( chunk );
      } // THEN

      THEN( "a ScatteringLawConstants can be constructed using separate arrays "
            "and members can be tested" ) {

        ScatteringLawConstants chunk( lln, ns, epsilon, emax,
                                      std::move( crossSections ),
                                      std::move( weightRatios ),
                                      std::move( numberAtoms ),
                                      std::move( functionTypes ) );
        verifyChunkWithBothPrincipalAndSecondaryScatterer( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithBothPrincipalAndSecondaryScatterer();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a ScatteringLawConstants can be constructed and members can be "
            "tested" ) {

        ScatteringLawConstants chunk( begin, end, lineNumber, 27, 7, 4 );
        verifyChunkWithBothPrincipalAndSecondaryScatterer( chunk );
      }
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "data with inconsistent sizes are used" ) {

      int lln = 0;
      int ns = 0;
      double epsilon = 1.976285e+2;
      double emax = 5.000001e+0;
      std::vector< double > crossSections = { 6.153875e+0 };
      std::vector< double > weightRatios = { 8.934780e+0 };
      std::vector< unsigned int > numberAtoms = { 1 };
      std::vector< unsigned int > functionTypes = {};

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( ScatteringLawConstants( lln, ns, epsilon, emax,
                                                {},
                                                std::move( weightRatios ),
                                                std::move( numberAtoms ),
                                                std::move( functionTypes ) ) );
        REQUIRE_THROWS( ScatteringLawConstants( lln, ns, epsilon, emax,
                                                std::move( crossSections ),
                                                {},
                                                std::move( numberAtoms ),
                                                std::move( functionTypes ) ) );
        REQUIRE_THROWS( ScatteringLawConstants( lln, ns, epsilon, emax,
                                                std::move( crossSections ),
                                                std::move( weightRatios ),
                                                {},
                                                std::move( functionTypes ) ) );
        REQUIRE_THROWS( ScatteringLawConstants( lln, ns, epsilon, emax,
                                                std::move( crossSections ),
                                                std::move( weightRatios ),
                                                std::move( numberAtoms ),
                                                { 1 } ) );
      } // THEN
    } // WHEN

    WHEN( "data with inconsistent NI and NS is used" ) {

      int lln = 0;
      int ns = 0;
      std::vector< double > values = { 6.153875e+0, 1.976285e+2, 8.934780e+0,
                                       5.000001e+0, 0.000000e+0, 1.000000e+0 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( ScatteringLawConstants( lln, 1, std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NI and NS is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( ScatteringLawConstants( begin, end, lineNumber,
                                                27, 7, 4 ) );
      } // THEN
    } // WHEN

    WHEN( "invalid LLN values are given" ) {

      std::vector< int > invalid = { -1, 2, 5, 10 };
      
      THEN( "an exception is thrown" ){

        for ( auto lln : invalid ) {

          int ns = 0;
          std::vector< double > values = { 6.153875e+0, 1.976285e+2,
                                           8.934780e+0, 5.000001e+0,
                                           0.000000e+0, 1.000000e+0 };

          REQUIRE_THROWS(
            ScatteringLawConstants( lln, ns, std::move( values ) ) );
        } // THEN
      } // THEN
    } // WHEN

    WHEN( "a string with an invalid LLN is used" ) {

      std::string string = invalidLLN();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( ScatteringLawConstants( begin, end, lineNumber,
                                                27, 7, 4 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of ScatteringLawConstants with only a principal "
         "scatterer" ) {

    std::string string = chunkWithOnlyPrincipalScatterer();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    ScatteringLawConstants chunk(begin, end, lineNumber, 27, 7, 4 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 4 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "a valid instance of ScatteringLawConstants with both principal "
         "and secondary scatterers" ) {

    std::string string = chunkWithBothPrincipalAndSecondaryScatterer();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    ScatteringLawConstants chunk(begin, end, lineNumber, 27, 7, 4 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 27, 7, 4 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOnlyPrincipalScatterer() {
  return
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n";
}

void
verifyChunkWithOnlyPrincipalScatterer( const ScatteringLawConstants& chunk ) {

      REQUIRE( 0 == chunk.LLN() );
      REQUIRE( 0 == chunk.sabStorageType() );
      REQUIRE( 6 == chunk.NI() );
      REQUIRE( 6 == chunk.numberConstants() );
      REQUIRE( 0 == chunk.NS() );
      REQUIRE( 0 == chunk.numberNonPrincipalScatterers() );

      REQUIRE( 1.976285e+2 == Approx( chunk.epsilon() ) );
      REQUIRE( 5.000001e+0 == Approx( chunk.upperEnergyLimit() ) );
      REQUIRE( 1 == chunk.totalFreeCrossSections().size() );
      REQUIRE( 6.153875e+0 == Approx( chunk.totalFreeCrossSections()[0] ) );
      REQUIRE( 1 == chunk.atomicWeightRatios().size() );
      REQUIRE( 8.934780e+0 == Approx( chunk.atomicWeightRatios()[0] ) );
      REQUIRE( 1 == chunk.numberAtoms().size() );
      REQUIRE( 1. == Approx( chunk.numberAtoms()[0] ) );
      REQUIRE( 0 == chunk.analyticalFunctionTypes().size() );

      REQUIRE( 2 == chunk.NC() );
}

std::string chunkWithBothPrincipalAndSecondaryScatterer() {
  return
    " 0.000000+0 0.000000+0          0          0         12          1  27 7  4     \n"
    " 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n";
}

void verifyChunkWithBothPrincipalAndSecondaryScatterer(
       const ScatteringLawConstants& chunk ) {

  REQUIRE( 0 == chunk.LLN() );
  REQUIRE( 0 == chunk.sabStorageType() );
  REQUIRE( 12 == chunk.NI() );
  REQUIRE( 12 == chunk.numberConstants() );
  REQUIRE( 1 == chunk.NS() );
  REQUIRE( 1 == chunk.numberNonPrincipalScatterers() );

  REQUIRE( 9.750000e+1 == Approx( chunk.epsilon() ) );
  REQUIRE( 2.466750e+0 == Approx( chunk.upperEnergyLimit() ) );
  REQUIRE( 2 == chunk.totalFreeCrossSections().size() );
  REQUIRE( 2.021000e+0 == Approx( chunk.totalFreeCrossSections()[0] ) );
  REQUIRE( 3.748750e+0 == Approx( chunk.totalFreeCrossSections()[1] ) );
  REQUIRE( 2 == chunk.atomicWeightRatios().size() );
  REQUIRE( 2.784423e+1 == Approx( chunk.atomicWeightRatios()[0] ) );
  REQUIRE( 1.586200e+1 == Approx( chunk.atomicWeightRatios()[1] ) );
  REQUIRE( 2 == chunk.numberAtoms().size() );
  REQUIRE( 1. == Approx( chunk.numberAtoms()[0] ) );
  REQUIRE( 2. == Approx( chunk.numberAtoms()[1] ) );
  REQUIRE( 1 == chunk.analyticalFunctionTypes().size() );
  REQUIRE( 0. == chunk.analyticalFunctionTypes()[0] );

  REQUIRE( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 0.000000+0          0          0         12          0  27 7  4     \n"
    " 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n";
}

std::string invalidLLN() {
  return
    " 0.000000+0 0.000000+0          2          0         12          0  27 7  4     \n"
    " 2.021000+0 9.750000+1 2.784423+1 2.466750+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n";
}
