// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using NuclearAmplitudeExpansion =
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;

std::string chunk();
void verifyChunk( const NuclearAmplitudeExpansion& );
std::string invalidLTP();
std::string invalidSize();

SCENARIO( "NuclearAmplitudeExpansion" ) {

  GIVEN( "valid data for a NuclearAmplitudeExpansion" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nl = 3;
      std::vector< double > b1 = { 1, 2, 3, 4, 5, 6, 7 };
      std::vector< double > b2 = { 1, 2, 3, 4, 5, 6, 7 };
      std::vector< double > a_real = { 8, 10, 12, 14 };
      std::vector< double > a_imag = { 9, 11, 13, 15 };
      std::vector< std::complex< double > > a =
          { { 8, 9 }, { 10, 11 }, { 12, 13 }, { 14, 15 } };

      NuclearAmplitudeExpansion chunk1( energy, nl,
                                        std::move( b1 ),
                                        std::move( a_real ),
                                        std::move( a_imag ) );

      NuclearAmplitudeExpansion chunk2( energy, nl,
                                        std::move( b2 ),
                                        std::move( a ) );

      THEN( "a NuclearAmplitudeExpansion can be constructed using separate "
            "arrays and members can be tested" ) {

        verifyChunk( chunk1 );
      }

      THEN( "a NuclearAmplitudeExpansion can be constructed using separate "
            "arrays with on of them complex and members can be tested" ) {

        verifyChunk( chunk2 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer1, buffer2;
        auto output1 = std::back_inserter( buffer1 );
        auto output2 = std::back_inserter( buffer2 );
        chunk1.print( output1, 9228, 6, 5 );
        chunk2.print( output2, 9228, 6, 5 );
        CHECK( buffer1 == string );
        CHECK( buffer2 == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      NuclearAmplitudeExpansion chunk( begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a NuclearAmplitudeExpansion can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a NuclearAmplitudeExpansion" ) {

    WHEN( "data with inconsistent sizes are used" ) {

      double energy = 1e-5;
      int nl = 3;
      std::vector< double > b = { 1, 2, 3, 4, 5, 6, 7 };
      std::vector< double > wrong_b = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > a_real = { 8, 10, 12, 14 };
      std::vector< double > a_imag = { 9, 11, 13, 15 };
      std::vector< double > a_wrong = { 8, 10, 12 };
      std::vector< std::complex< double > > acomplex = { 9, 11, 13, 15 };
      std::vector< std::complex< double > > acomplex_wrong = { 8, 10, 12 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl,
                                                 std::move( wrong_b ),
                                                 std::move( a_real ),
                                                 std::move( a_imag ) ) );
        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl, std::move( b ),
                                                 std::move( a_wrong ),
                                                 std::move( a_imag ) ) );
        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl, std::move( b ),
                                                 std::move( a_real ),
                                                 std::move( a_wrong ) ) );
        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl, std::move( b ),
                                                 std::move( a_real ),
                                                 std::move( a_wrong ) ) );
        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl,
                                                 std::move( wrong_b ),
                                                 std::move( acomplex ) ) );
        CHECK_THROWS( NuclearAmplitudeExpansion( energy, nl,
                                                 std::move( b ),
                                                 std::move( acomplex_wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with an invalid LTP" ) {

      std::string string = invalidLTP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearAmplitudeExpansion( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW and NL" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NuclearAmplitudeExpansion( begin, end, lineNumber,
                                                 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          1          0         15          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}

void verifyChunk( const NuclearAmplitudeExpansion& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 1 == chunk.LTP() );
  CHECK( 15 == chunk.NW() );
  CHECK( 3 == chunk.NL() );
  CHECK( 7 == chunk.B().size() );
  CHECK( 7 == chunk.scatteringCoefficients().size() );
  CHECK_THAT( 1., WithinRel( chunk.B()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.B()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.B()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.B()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.B()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.B()[5] ) );
  CHECK_THAT( 7., WithinRel( chunk.B()[6] ) );
  CHECK_THAT( 1., WithinRel( chunk.scatteringCoefficients()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.scatteringCoefficients()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.scatteringCoefficients()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.scatteringCoefficients()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.scatteringCoefficients()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.scatteringCoefficients()[5] ) );
  CHECK_THAT( 7., WithinRel( chunk.scatteringCoefficients()[6] ) );
  CHECK( 4 == chunk.AR().size() );
  CHECK( 4 == chunk.realInterferenceCoefficients().size() );
  CHECK_THAT( 8., WithinRel( chunk.AR()[0] ) );
  CHECK_THAT( 10., WithinRel( chunk.AR()[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.AR()[2] ) );
  CHECK_THAT( 14., WithinRel( chunk.AR()[3] ) );
  CHECK_THAT( 8., WithinRel( chunk.realInterferenceCoefficients()[0] ) );
  CHECK_THAT( 10., WithinRel( chunk.realInterferenceCoefficients()[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.realInterferenceCoefficients()[2] ) );
  CHECK_THAT( 14., WithinRel( chunk.realInterferenceCoefficients()[3] ) );
  CHECK( 4 == chunk.AI().size() );
  CHECK( 4 == chunk.imaginaryInterferenceCoefficients().size() );
  CHECK_THAT( 9., WithinRel( chunk.AI()[0] ) );
  CHECK_THAT( 11., WithinRel( chunk.AI()[1] ) );
  CHECK_THAT( 13., WithinRel( chunk.AI()[2] ) );
  CHECK_THAT( 15., WithinRel( chunk.AI()[3] ) );
  CHECK_THAT( 9., WithinRel( chunk.imaginaryInterferenceCoefficients()[0] ) );
  CHECK_THAT( 11., WithinRel( chunk.imaginaryInterferenceCoefficients()[1] ) );
  CHECK_THAT( 13., WithinRel( chunk.imaginaryInterferenceCoefficients()[2] ) );
  CHECK_THAT( 15., WithinRel( chunk.imaginaryInterferenceCoefficients()[3] ) );
  CHECK( 4 == chunk.A().size() );
  CHECK( 4 == chunk.interferenceCoefficients().size() );
  CHECK_THAT( 8., WithinRel( chunk.A()[0].real() ) );
  CHECK_THAT( 10., WithinRel( chunk.A()[1].real() ) );
  CHECK_THAT( 12., WithinRel( chunk.A()[2].real() ) );
  CHECK_THAT( 14., WithinRel( chunk.A()[3].real() ) );
  CHECK_THAT( 9., WithinRel( chunk.A()[0].imag() ) );
  CHECK_THAT( 11., WithinRel( chunk.A()[1].imag() ) );
  CHECK_THAT( 13., WithinRel( chunk.A()[2].imag() ) );
  CHECK_THAT( 15., WithinRel( chunk.A()[3].imag() ) );
  CHECK_THAT( 8., WithinRel( chunk.interferenceCoefficients()[0].real() ) );
  CHECK_THAT( 10., WithinRel( chunk.interferenceCoefficients()[1].real() ) );
  CHECK_THAT( 12., WithinRel( chunk.interferenceCoefficients()[2].real() ) );
  CHECK_THAT( 14., WithinRel( chunk.interferenceCoefficients()[3].real() ) );
  CHECK_THAT( 9., WithinRel( chunk.interferenceCoefficients()[0].imag() ) );
  CHECK_THAT( 11., WithinRel( chunk.interferenceCoefficients()[1].imag() ) );
  CHECK_THAT( 13., WithinRel( chunk.interferenceCoefficients()[2].imag() ) );
  CHECK_THAT( 15., WithinRel( chunk.interferenceCoefficients()[3].imag() ) );

  CHECK( 4 == chunk.NC() );
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
