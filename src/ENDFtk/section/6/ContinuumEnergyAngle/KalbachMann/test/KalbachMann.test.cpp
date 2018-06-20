#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using KalbachMann = 
section::Type< 6 >::ContinuumEnergyAngle::KalbachMann;

std::string chunk1();
std::string chunk2();
std::string invalidSize();
std::string invalidNA();

SCENARIO( "KalbachMann" ) {

  GIVEN( "valid data for a KalbachMann with na=1" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > list = { 1., 2., 3., 4., 5., 6. };
    std::vector< std::tuple< double, double, double > > data = { 
      { 1., 2., 3. },
      { 4., 5., 6. } };

    THEN( "a KalbachMann can "
          "be constructed using a list and members can be tested" ) {
      KalbachMann chunk( energy, nd, na, nep, std::move( list ) );

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

    THEN( "a KalbachMann can "
          "be constructed using tuples and members can be tested" ) {
      KalbachMann chunk( energy, nd, nep, std::move( data ) );

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

  GIVEN( "valid data for a KalbachMann with na=2" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 2;
    int nep = 2;
    std::vector< double > list = { 1., 2., 3., 4., 5., 6., 7., 8. };
    std::vector< std::tuple< double, double, double, double > > data = { 
      { 1., 2., 3., 4. },
      { 5., 6., 7., 8. } };

    THEN( "a KalbachMann can "
          "be constructed using a list and members can be tested" ) {
      KalbachMann chunk( energy, nd, na, nep, std::move( list ) );

      REQUIRE( 2 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 2 == chunk.NA() );
      REQUIRE( 8 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 5. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.parameters().size() );
      REQUIRE( 2. == Approx( chunk.parameters()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.parameters()[0][1] ) );
      REQUIRE( 4. == Approx( chunk.parameters()[0][2] ) );
      REQUIRE( 6. == Approx( chunk.parameters()[1][0] ) );
      REQUIRE( 7. == Approx( chunk.parameters()[1][1] ) );
      REQUIRE( 8. == Approx( chunk.parameters()[1][2] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 6. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }

    THEN( "a KalbachMann can "
          "be constructed using tuples and members can be tested" ) {
      KalbachMann chunk( energy, nd, nep, std::move( data ) );

      REQUIRE( 2 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 2 == chunk.NA() );
      REQUIRE( 8 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 5. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.parameters().size() );
      REQUIRE( 2. == Approx( chunk.parameters()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.parameters()[0][1] ) );
      REQUIRE( 4. == Approx( chunk.parameters()[0][2] ) );
      REQUIRE( 6. == Approx( chunk.parameters()[1][0] ) );
      REQUIRE( 7. == Approx( chunk.parameters()[1][1] ) );
      REQUIRE( 8. == Approx( chunk.parameters()[1][2] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 6. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid KalbachMann with na=1" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a KalbachMann can "
          "be constructed and members can be tested" ) {
      KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );

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

  GIVEN( "a string representation of a valid KalbachMann with na=2" ) {

    std::string string = chunk2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a KalbachMann can "
          "be constructed and members can be tested" ) {
      KalbachMann chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 2 == chunk.LANG() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.ND() );
      REQUIRE( 2 == chunk.NA() );
      REQUIRE( 8 == chunk.NW() );
      REQUIRE( 2 == chunk.NEP() );
      REQUIRE( 2 == chunk.energies().size() );
      REQUIRE( 1. == Approx( chunk.energies()[0] ) );
      REQUIRE( 5. == Approx( chunk.energies()[1] ) );
      REQUIRE( 2 == chunk.parameters().size() );
      REQUIRE( 2. == Approx( chunk.parameters()[0][0] ) );
      REQUIRE( 3. == Approx( chunk.parameters()[0][1] ) );
      REQUIRE( 4. == Approx( chunk.parameters()[0][2] ) );
      REQUIRE( 6. == Approx( chunk.parameters()[1][0] ) );
      REQUIRE( 7. == Approx( chunk.parameters()[1][1] ) );
      REQUIRE( 8. == Approx( chunk.parameters()[1][2] ) );
      REQUIRE( 2 == Approx( chunk.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( chunk.totalEmissionProbabilities()[0] ) );
      REQUIRE( 6. == Approx( chunk.totalEmissionProbabilities()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "data with an invalid na" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 0;
    int nep = 2;
    std::vector< double > wronglist = { 1., 2., 3., 4. };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( KalbachMann( energy, nd, na, nep,
                                   std::move( wronglist ) ) );
    }
  } // GIVEN

  GIVEN( "data with inconsistent sizes" ) {

    double energy = 1e-5;
    int nd = 0;
    int na = 1;
    int nep = 2;
    std::vector< double > wronglist = { 1., 2., 3., 4., 5. };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( KalbachMann( energy, nd, na, nep,
                                   std::move( wronglist ) ) );
    }
  } // GIVEN

  GIVEN( "a string with invalid na" ) {

    std::string string = invalidNA();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW, NA, NEP" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( KalbachMann( begin, end, lineNumber, 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of KalbachMann with na=1" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    KalbachMann
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of KalbachMann with na=2" ) {

    std::string string = chunk2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    KalbachMann
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk1() {
  return
    " 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunk2() {
  return
    " 0.000000+0 1.000000-5          0          2          8          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0                                            9228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          1          5          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           9228 6  5     \n";
}

std::string invalidNA() {
  return
    " 0.000000+0 1.000000-5          0          3         10          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                      9228 6  5     \n";
}
