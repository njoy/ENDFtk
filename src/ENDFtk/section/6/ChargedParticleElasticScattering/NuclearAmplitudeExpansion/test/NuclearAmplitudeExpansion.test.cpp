#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using NuclearAmplitudeExpansion = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;

std::string chunk();
std::string invalidLTP();
std::string invalidSize();

SCENARIO( "NuclearAmplitudeExpansion" ) {

  GIVEN( "valid data for a NuclearAmplitudeExpansion" ) {

    double energy = 1e-5;
    int nl = 3;
    std::vector< double > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                     11, 12, 13, 14, 15 };
    std::vector< double > b = { 1, 2, 3, 4, 5, 6, 7 };
    std::vector< double > a_real = { 8, 10, 12, 14 };
    std::vector< double > a_imag = { 9, 11, 13, 15 };

    THEN( "a NuclearAmplitudeExpansion can "
          "be constructed using a list and members can be tested" ) {
      NuclearAmplitudeExpansion chunk( energy, nl, std::move( values ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 1 == chunk.LTP() );
      REQUIRE( 15 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 7 == chunk.scatteringCoefficients().size() );
      REQUIRE( 1. == Approx( chunk.scatteringCoefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.scatteringCoefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.scatteringCoefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.scatteringCoefficients()[3] ) );
      REQUIRE( 5. == Approx( chunk.scatteringCoefficients()[4] ) );
      REQUIRE( 6. == Approx( chunk.scatteringCoefficients()[5] ) );
      REQUIRE( 7. == Approx( chunk.scatteringCoefficients()[6] ) );
      REQUIRE( 4 == chunk.realInterferenceCoefficients().size() );
      REQUIRE( 8. == Approx( chunk.realInterferenceCoefficients()[0] ) );
      REQUIRE( 10. == Approx( chunk.realInterferenceCoefficients()[1] ) );
      REQUIRE( 12. == Approx( chunk.realInterferenceCoefficients()[2] ) );
      REQUIRE( 14. == Approx( chunk.realInterferenceCoefficients()[3] ) );
      REQUIRE( 4 == chunk.imaginaryInterferenceCoefficients().size() );
      REQUIRE( 9. == Approx( chunk.imaginaryInterferenceCoefficients()[0] ) );
      REQUIRE( 11. == Approx( chunk.imaginaryInterferenceCoefficients()[1] ) );
      REQUIRE( 13. == Approx( chunk.imaginaryInterferenceCoefficients()[2] ) );
      REQUIRE( 15. == Approx( chunk.imaginaryInterferenceCoefficients()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }

    THEN( "a NuclearAmplitudeExpansion can "
          "be constructed using separate arrays and members can be tested" ) {
      NuclearAmplitudeExpansion
        chunk( energy, nl, std::move( b ), std::move( a_real ),
               std::move( a_imag ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 1 == chunk.LTP() );
      REQUIRE( 15 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 7 == chunk.scatteringCoefficients().size() );
      REQUIRE( 1. == Approx( chunk.scatteringCoefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.scatteringCoefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.scatteringCoefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.scatteringCoefficients()[3] ) );
      REQUIRE( 5. == Approx( chunk.scatteringCoefficients()[4] ) );
      REQUIRE( 6. == Approx( chunk.scatteringCoefficients()[5] ) );
      REQUIRE( 7. == Approx( chunk.scatteringCoefficients()[6] ) );
      REQUIRE( 4 == chunk.realInterferenceCoefficients().size() );
      REQUIRE( 8. == Approx( chunk.realInterferenceCoefficients()[0] ) );
      REQUIRE( 10. == Approx( chunk.realInterferenceCoefficients()[1] ) );
      REQUIRE( 12. == Approx( chunk.realInterferenceCoefficients()[2] ) );
      REQUIRE( 14. == Approx( chunk.realInterferenceCoefficients()[3] ) );
      REQUIRE( 4 == chunk.imaginaryInterferenceCoefficients().size() );
      REQUIRE( 9. == Approx( chunk.imaginaryInterferenceCoefficients()[0] ) );
      REQUIRE( 11. == Approx( chunk.imaginaryInterferenceCoefficients()[1] ) );
      REQUIRE( 13. == Approx( chunk.imaginaryInterferenceCoefficients()[2] ) );
      REQUIRE( 15. == Approx( chunk.imaginaryInterferenceCoefficients()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid NuclearAmplitudeExpansion" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a NuclearAmplitudeExpansion can "
          "be constructed and members can be tested" ) {
      NuclearAmplitudeExpansion
        chunk( begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 1 == chunk.LTP() );
      REQUIRE( 15 == chunk.NW() );
      REQUIRE( 3 == chunk.NL() );
      REQUIRE( 7 == chunk.scatteringCoefficients().size() );
      REQUIRE( 1. == Approx( chunk.scatteringCoefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.scatteringCoefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.scatteringCoefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.scatteringCoefficients()[3] ) );
      REQUIRE( 5. == Approx( chunk.scatteringCoefficients()[4] ) );
      REQUIRE( 6. == Approx( chunk.scatteringCoefficients()[5] ) );
      REQUIRE( 7. == Approx( chunk.scatteringCoefficients()[6] ) );
      REQUIRE( 4 == chunk.realInterferenceCoefficients().size() );
      REQUIRE( 8. == Approx( chunk.realInterferenceCoefficients()[0] ) );
      REQUIRE( 10. == Approx( chunk.realInterferenceCoefficients()[1] ) );
      REQUIRE( 12. == Approx( chunk.realInterferenceCoefficients()[2] ) );
      REQUIRE( 14. == Approx( chunk.realInterferenceCoefficients()[3] ) );
      REQUIRE( 4 == chunk.imaginaryInterferenceCoefficients().size() );
      REQUIRE( 9. == Approx( chunk.imaginaryInterferenceCoefficients()[0] ) );
      REQUIRE( 11. == Approx( chunk.imaginaryInterferenceCoefficients()[1] ) );
      REQUIRE( 13. == Approx( chunk.imaginaryInterferenceCoefficients()[2] ) );
      REQUIRE( 15. == Approx( chunk.imaginaryInterferenceCoefficients()[3] ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "data with inconsistent sizes" ) {

    double energy = 1e-5;
    int nl = 3;
    std::vector< double > b = { 1, 2, 3, 4, 5, 6, 7 };
    std::vector< double > wrong_b = { 1, 2, 3, 4, 5, 6 };
    std::vector< double > a_real = { 8, 10, 12, 14 };
    std::vector< double > a_imag = { 9, 11, 13, 15 };
    std::vector< double > a_wrong = { 8, 10, 12 };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( NuclearAmplitudeExpansion( energy, nl,
                                                 std::move( wrong_b ),
                                                 std::move( a_real ),
                                                 std::move( a_imag ) ) );
      REQUIRE_THROWS( NuclearAmplitudeExpansion( energy, nl, std::move( b ),
                                                 std::move( a_wrong ),
                                                 std::move( a_imag ) ) );
      REQUIRE_THROWS( NuclearAmplitudeExpansion( energy, nl, std::move( b ),
                                                 std::move( a_real ),
                                                 std::move( a_wrong ) ) );
    }
  } // GIVEN

  GIVEN( "data with inconsistent NW and NL" ) {

    double energy = 1e-5;
    int nl = 6;
    std::vector< double > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                     11, 12, 13, 14, 15 };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( NuclearAmplitudeExpansion( energy, 1,
                                                 std::move( values ) ) );
    }
  } // GIVEN

  GIVEN( "a string with an invalid LTP" ) {

    std::string string = invalidLTP();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( NuclearAmplitudeExpansion( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW and NL" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( NuclearAmplitudeExpansion( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of NuclearAmplitudeExpansion" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    NuclearAmplitudeExpansion
      chunk(begin, end, lineNumber, 9228, 6, 5 );

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
    " 0.000000+0 1.000000-5          1          0         15          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}

std::string invalidLTP() {
  return
    " 0.000000+0 1.000000-5          2          0         15          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          1          0         15          69228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}
