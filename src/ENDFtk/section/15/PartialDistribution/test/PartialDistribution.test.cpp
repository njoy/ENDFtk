#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/15.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialDistribution =
section::Type< 15 >::PartialDistribution;
using Probability =
section::Type< 15 >::Probability;
using TabulatedSpectrum =
section::Type< 15 >::TabulatedSpectrum;

std::string chunkLF1();
void verifyChunkLF1( const PartialDistribution& );
std::string invalidLF();

SCENARIO( "PartialDistribution" ) {

  GIVEN( "valid data for a PartialDistribution using TabulatedSpectrum (LF=1)" ) {

    std::string string = chunkLF1();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 1, { 2 }, { 2 },
                                         { 1e-5, 3e+7 },
                                         { 1.0, 1.0 } );
      TabulatedSpectrum spectrum( { 2 }, { 4 },
                                  { { 1e-5, { 3 }, { 2 },
                                    { 0.0, 1e+5, 3e+7 },
                                    { 0.0, 1.757570e-9, 1.843350e-9 } },
                                  { 3e+7, { 4 }, { 2 },
                                    { 0.0, 10., 11., 3e+7 },
                                    { 0.0, 1.733405e-9,
                                      1.818010e-9, 1.898849e-9 } } } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF1( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 15, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9437, 15, 18 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 15, 18 );

        CHECK( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "invalid data for a PartialDistribution" ) {

    WHEN( "an inconsistent LF between the partial probability and spectrum" ) {

      Probability probability( 2, { 2 }, { 2 },                 // LF=2
                                         { 1e-5, 3e+7 },
                                         { 1.0, 1.0 } );
      TabulatedSpectrum spectrum( { 2 }, { 4 },                 // LF=1
                                  { { 1e-5, { 3 }, { 2 },
                                    { 0.0, 1e+5, 3e+7 },
                                    { 0.0, 1.757570e-9, 1.843350e-9 } },
                                  { 3e+7, { 4 }, { 2 },
                                    { 0.0, 10., 11., 3e+7 },
                                    { 0.0, 1.733405e-9,
                                      1.818010e-9, 1.898849e-9 } } } );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PartialDistribution( std::move( probability ),
                                           std::move( spectrum )) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LF number" ) {

      std::string string = invalidLF();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PartialDistribution(begin, end, lineNumber, 9222, 15, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLF1() {
  return
    " 0.000000+0 0.000000+0          0          1          1          2943715 18     \n"
    "          2          2                                            943715 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      943715 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          2943715 18     \n"
    "          2          4                                            943715 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          3943715 18     \n"
    "          3          2                                            943715 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-9943715 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          4943715 18     \n"
    "          4          2                                            943715 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-9943715 18     \n"
    " 3.000000+7 1.898849-9                                            943715 18     \n";
}

void verifyChunkLF1( const PartialDistribution& chunk ) {

  auto p = chunk.probability();

  CHECK( 1 == p.LF() );
  CHECK( 1 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK( 1e-5 == Approx( p.E()[0] ) );
  CHECK( 3e+7 == Approx( p.E()[1] ) );
  CHECK( 1e-5 == Approx( p.energies()[0] ) );
  CHECK( 3e+7 == Approx( p.energies()[1] ) );
  CHECK( 1. == Approx( p.P()[0] ) );
  CHECK( 1. == Approx( p.P()[1] ) );
  CHECK( 1. == Approx( p.probabilities()[0] ) );
  CHECK( 1. == Approx( p.probabilities()[1] ) );

  auto d = chunk.distribution();

  CHECK( 1 == d.NR() );
  CHECK( 2 == d.NE() );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 2 == d.boundaries()[0] );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 4 == d.interpolants()[0] );

  CHECK( 2 == d.incidentEnergies().size() );
  CHECK( 1e-5 == Approx( d.incidentEnergies()[0] ) );
  CHECK( 3e+7 == Approx( d.incidentEnergies()[1] ) );

  auto value = d.outgoingDistributions()[0];
  CHECK( 1e-5 == Approx( value.incidentEnergy() ) );
  CHECK( 3 == value.NP() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 3 == value.boundaries()[0] );
  CHECK( 3 == value.EP().size() );
  CHECK( 3 == value.outgoingEnergies().size() );
  CHECK( 3 == value.G().size() );
  CHECK( 3 == value.probabilities().size() );
  CHECK( 0.0 == Approx( value.EP()[0] ) );
  CHECK( 1e+5 == Approx( value.EP()[1] ) );
  CHECK( 3e+7 == Approx( value.EP()[2] ) );
  CHECK( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  CHECK( 1e+5 == Approx( value.outgoingEnergies()[1] ) );
  CHECK( 3e+7 == Approx( value.outgoingEnergies()[2] ) );
  CHECK( 0. == Approx( value.G()[0] ) );
  CHECK( 1.757570e-9 == Approx( value.G()[1] ) );
  CHECK( 1.843350e-9 == Approx( value.G()[2] ) );
  CHECK( 0. == Approx( value.probabilities()[0] ) );
  CHECK( 1.757570e-9 == Approx( value.probabilities()[1] ) );
  CHECK( 1.843350e-9 == Approx( value.probabilities()[2] ) );

  value = d.outgoingDistributions()[1];
  CHECK( 3e+7 == Approx( value.incidentEnergy() ) );
  CHECK( 4 == value.NP() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 4 == value.boundaries()[0] );
  CHECK( 4 == value.EP().size() );
  CHECK( 4 == value.outgoingEnergies().size() );
  CHECK( 4 == value.G().size() );
  CHECK( 4 == value.probabilities().size() );
  CHECK( 0.0 == Approx( value.EP()[0] ) );
  CHECK( 10. == Approx( value.EP()[1] ) );
  CHECK( 11. == Approx( value.EP()[2] ) );
  CHECK( 3e+7 == Approx( value.EP()[3] ) );
  CHECK( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  CHECK( 10. == Approx( value.outgoingEnergies()[1] ) );
  CHECK( 11. == Approx( value.outgoingEnergies()[2] ) );
  CHECK( 3e+7 == Approx( value.outgoingEnergies()[3] ) );
  CHECK( 0. == Approx( value.G()[0] ) );
  CHECK( 1.733405e-9 == Approx( value.G()[1] ) );
  CHECK( 1.818010e-9 == Approx( value.G()[2] ) );
  CHECK( 1.898849e-9 == Approx( value.G()[3] ) );
  CHECK( 0. == Approx( value.probabilities()[0] ) );
  CHECK( 1.733405e-9 == Approx( value.probabilities()[1] ) );
  CHECK( 1.818010e-9 == Approx( value.probabilities()[2] ) );
  CHECK( 1.898849e-9 == Approx( value.probabilities()[3] ) );

  CHECK( 12 == chunk.NC() );
}

std::string invalidLF() {
  return
    " 0.000000+0 0.000000+0          0          2          1          2922215 18     \n"
    "          2          2                                            922215 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      922215 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          3922215 18     \n"
    "          3          2                                            922215 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+6922215 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          5922215 18     \n"
    "          5          2                                            922215 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-6922215 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      922215 18     \n";
}
