#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/5.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialDistribution =
section::Type< 5 >::PartialDistribution;
using Probability =
section::Type< 5 >::Probability;
using TabulatedSpectrum =
section::Type< 5 >::TabulatedSpectrum;
using GeneralEvaporationSpectrum =
section::Type< 5 >::GeneralEvaporationSpectrum;
using MaxwellianFissionSpectrum =
section::Type< 5 >::MaxwellianFissionSpectrum;
using EvaporationSpectrum =
section::Type< 5 >::EvaporationSpectrum;
using WattSpectrum =
section::Type< 5 >::WattSpectrum;
using MadlandNixSpectrum =
section::Type< 5 >::MadlandNixSpectrum;

std::string chunkLF1();
void verifyChunkLF1( const PartialDistribution& );
std::string chunkLF5();
void verifyChunkLF5( const PartialDistribution& );
std::string chunkLF7();
void verifyChunkLF7( const PartialDistribution& );
std::string chunkLF9();
void verifyChunkLF9( const PartialDistribution& );
std::string chunkLF11();
void verifyChunkLF11( const PartialDistribution& );
std::string chunkLF12();
void verifyChunkLF12( const PartialDistribution& );
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
        chunk.print( output, 9437, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9437, 5, 18 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF1( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a PartialDistribution using "
         "GeneralEvaporationSpectrum (LF=5)" ) {

    std::string string = chunkLF5();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 5, { 2 }, { 2 },
                                         { 1e-5, 3e+7 },
                                         { 1.804944e-2, 1.804944e-2 }, -3e+7 );
      GeneralEvaporationSpectrum spectrum( { { 2 }, { 2 },
                                             { 1e-5, 3e+7 }, { 1.0, 1.0 } },
                                           { { 6 }, { 1 },
                                             { 0.0, 1e+4, 2e+4,
                                               1.8e+6, 1.81e+6, 1.82e+6 },
                                             { 1.533738e-7, 1.378483e-6,
                                               1.550360e-6, 7.90779e-31,
                                               0.0, 0.0 } } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9443, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9443, 5, 455 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF5( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9443, 5, 455 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a PartialDistribution using "
         "MaxwellianFissionSpectrum (LF=7)" ) {

    std::string string = chunkLF7();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 7, { 2 }, { 2 },
                                      { 1e-5, 3e+7 },
                                      { 1.0, 1.0 }, -3e+7 );
      MaxwellianFissionSpectrum spectrum( { 3 }, { 2 },
                                          { 1e-5, 5e+5, 3e+7 },
                                          { 1.3652e+6, 1.3748e+6,
                                            1.6912e+6 } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed" ) {

        verifyChunkLF7( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9455, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9455, 5, 18 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF7( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9455, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a PartialDistribution using EvaporationSpectrum (LF=9)" ) {

    std::string string = chunkLF9();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 9, { 2 }, { 2 },
                                         { 1.789920e+7, 2e+7 },
                                         { 1.0, 1.0 }, 1.789920e+7 );
      EvaporationSpectrum spectrum( { 4 }, { 2 },
                                    { 1.78992e+7, 1.8e+7,
                                      1.9e+7, 2e+7 },
                                    { 1.0099e+5, 1.0099e+5,
                                      1.1292e+5, 1.6143e+5 } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed" ) {

        verifyChunkLF9( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9237, 5, 37 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9237, 5, 37 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF9( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9237, 5, 37 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a PartialDistribution using WattSpectrum (LF=11)" ) {

    std::string string = chunkLF11();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 11, { 2 }, { 2 },
                                          { 1e-5, 3e+7 },
                                          { 1.0, 1.0 }, -3e+7 );
      WattSpectrum spectrum( { {3}, {2},
                               { 1e-5, 1.5e+6, 3e+7 },
                               { 9.77e+5, 1e+6, 1.06e+6 } },
                             { {5}, {2},
                               { 1e-5, 1.5e+6, 1e+7,
                                 1.22e+7, 3e+7 },
                               { 2.546e-6, 2.546e-6, 2.474e-6,
                                 2.612e-6, 2.62e-6 } } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed" ) {

        verifyChunkLF11( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9222, 5, 18 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF11( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9222, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a PartialDistribution using MadlandNixSpectrum (LF=12)" ) {

    std::string string = chunkLF12();

    WHEN( "the data is given explicitly" ) {

      Probability probability( 12, { 2 }, { 2 },
                                          { 1e-5, 3e+7 },
                                          { 1.0, 1.0 } );
      MadlandNixSpectrum spectrum(  1.029979e+6, 5.467297e+5, { 4 }, { 5 },
                                    { 1e-5, 5.000001e+5, 1.4e+7, 3e+7 },
                                    { 1.092064e+6, 1.101483e+6,
                                      1.129269e+6, 1.182884e+6 } );

      PartialDistribution chunk( std::move( probability ), std::move( spectrum ) );

      THEN( "a PartialDistribution can be constructed" ) {

        verifyChunkLF12( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    }  // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      PartialDistribution chunk( begin, end, lineNumber, 9543, 5, 18 );

      THEN( "a PartialDistribution can be constructed and members can be tested" ) {

        verifyChunkLF12( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 5, 18 );

        REQUIRE( buffer == string );
      } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "invalid data for a PartialDistribution" ) {

    WHEN( "an inconsistent LF between the partial probability and spectrum" ) {

      Probability probability( 1, { 2 }, { 2 },                 // LF=1
                                         { 1e-5, 3e+7 },
                                         { 1.0, 1.0 } );
      MaxwellianFissionSpectrum spectrum( { { 3 }, { 2 },              // LF=7
                                            { 1e-5, 5e+5, 3e+7 },
                                            { 1.3652e+6, 1.3748e+6,
                                              1.6912e+6 } } );

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( PartialDistribution( std::move( probability ),
                                    std::move( spectrum )) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LF number" ) {

      std::string string = invalidLF();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( PartialDistribution(begin, end, lineNumber, 9222, 5, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLF1() {
  return
    " 0.000000+0 0.000000+0          0          1          1          29437 5 18     \n"
    "          2          2                                            9437 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n"
    "          2          4                                            9437 5 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n"
    "          4          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n"
    " 3.000000+7 1.898849-9                                            9437 5 18     \n";
}

void verifyChunkLF1( const PartialDistribution& chunk ) {

  REQUIRE( 0.0 == Approx ( chunk.U() ) );
  REQUIRE( 0.0 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 1 == p.LF() );
  REQUIRE( 1 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1e-5 == Approx( p.E()[0] ) );
  REQUIRE( 3e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1e-5 == Approx( p.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1. == Approx( p.p()[0] ) );
  REQUIRE( 1. == Approx( p.p()[1] ) );
  REQUIRE( 1. == Approx( p.probabilities()[0] ) );
  REQUIRE( 1. == Approx( p.probabilities()[1] ) );

  auto d =
       std::get< TabulatedSpectrum >( chunk.distribution() );

  REQUIRE( 1 == d.NR() );
  REQUIRE( 2 == d.NE() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 2 == d.boundaries()[0] );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 4 == d.interpolants()[0] );

  REQUIRE( 2 == d.incomingEnergies().size() );
  REQUIRE( 1e-5 == Approx( d.incomingEnergies()[0] ) );
  REQUIRE( 3e+7 == Approx( d.incomingEnergies()[1] ) );

  auto value = d.outgoingDistributions()[0];
  REQUIRE( 1e-5 == Approx( value.incomingEnergy() ) );
  REQUIRE( 3 == value.NF() );
  REQUIRE( 1 == value.NR() );
  REQUIRE( 1 == value.interpolants().size() );
  REQUIRE( 1 == value.boundaries().size() );
  REQUIRE( 2 == value.interpolants()[0] );
  REQUIRE( 3 == value.boundaries()[0] );
  REQUIRE( 3 == value.EPRIME().size() );
  REQUIRE( 3 == value.outgoingEnergies().size() );
  REQUIRE( 3 == value.g().size() );
  REQUIRE( 3 == value.probabilities().size() );
  REQUIRE( 0.0 == Approx( value.EPRIME()[0] ) );
  REQUIRE( 1e+5 == Approx( value.EPRIME()[1] ) );
  REQUIRE( 3e+7 == Approx( value.EPRIME()[2] ) );
  REQUIRE( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  REQUIRE( 1e+5 == Approx( value.outgoingEnergies()[1] ) );
  REQUIRE( 3e+7 == Approx( value.outgoingEnergies()[2] ) );
  REQUIRE( 0. == Approx( value.g()[0] ) );
  REQUIRE( 1.757570e-9 == Approx( value.g()[1] ) );
  REQUIRE( 1.843350e-9 == Approx( value.g()[2] ) );
  REQUIRE( 0. == Approx( value.probabilities()[0] ) );
  REQUIRE( 1.757570e-9 == Approx( value.probabilities()[1] ) );
  REQUIRE( 1.843350e-9 == Approx( value.probabilities()[2] ) );

  value = d.outgoingDistributions()[1];
  REQUIRE( 3e+7 == Approx( value.incomingEnergy() ) );
  REQUIRE( 4 == value.NF() );
  REQUIRE( 1 == value.NR() );
  REQUIRE( 1 == value.interpolants().size() );
  REQUIRE( 1 == value.boundaries().size() );
  REQUIRE( 2 == value.interpolants()[0] );
  REQUIRE( 4 == value.boundaries()[0] );
  REQUIRE( 4 == value.EPRIME().size() );
  REQUIRE( 4 == value.outgoingEnergies().size() );
  REQUIRE( 4 == value.g().size() );
  REQUIRE( 4 == value.probabilities().size() );
  REQUIRE( 0.0 == Approx( value.EPRIME()[0] ) );
  REQUIRE( 10. == Approx( value.EPRIME()[1] ) );
  REQUIRE( 11. == Approx( value.EPRIME()[2] ) );
  REQUIRE( 3e+7 == Approx( value.EPRIME()[3] ) );
  REQUIRE( 0.0 == Approx( value.outgoingEnergies()[0] ) );
  REQUIRE( 10. == Approx( value.outgoingEnergies()[1] ) );
  REQUIRE( 11. == Approx( value.outgoingEnergies()[2] ) );
  REQUIRE( 3e+7 == Approx( value.outgoingEnergies()[3] ) );
  REQUIRE( 0. == Approx( value.g()[0] ) );
  REQUIRE( 1.733405e-9 == Approx( value.g()[1] ) );
  REQUIRE( 1.818010e-9 == Approx( value.g()[2] ) );
  REQUIRE( 1.898849e-9 == Approx( value.g()[3] ) );
  REQUIRE( 0. == Approx( value.probabilities()[0] ) );
  REQUIRE( 1.733405e-9 == Approx( value.probabilities()[1] ) );
  REQUIRE( 1.818010e-9 == Approx( value.probabilities()[2] ) );
  REQUIRE( 1.898849e-9 == Approx( value.probabilities()[3] ) );

  REQUIRE( 12 == chunk.NC() );
}

std::string chunkLF5() {
  return
    "-3.000000+7 0.000000+0          0          5          1          29443 5455     \n"
    "          2          2                                            9443 5455     \n"
    " 1.000000-5 1.804944-2 3.000000+7 1.804944-2                      9443 5455     \n"
    " 0.000000+0 0.000000+0          0          0          1          29443 5455     \n"
    "          2          2                                            9443 5455     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n"
    " 0.000000+0 0.000000+0          0          0          1          69443 5455     \n"
    "          6          1                                            9443 5455     \n"
    " 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n"
    " 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n";
}

void verifyChunkLF5( const PartialDistribution& chunk ) {

  REQUIRE( -3e+7 == Approx ( chunk.U() ) );
  REQUIRE( -3e+7 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 5 == p.LF() );
  REQUIRE( 5 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1e-5 == Approx( p.E()[0] ) );
  REQUIRE( 3e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1e-5 == Approx( p.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1.804944e-2 == Approx( p.p()[0] ) );
  REQUIRE( 1.804944e-2 == Approx( p.p()[1] ) );
  REQUIRE( 1.804944e-2 == Approx( p.probabilities()[0] ) );
  REQUIRE( 1.804944e-2 == Approx( p.probabilities()[1] ) );

  auto d =
       std::get< GeneralEvaporationSpectrum >
             ( chunk.distribution() );

  REQUIRE( 5 == d.LF() );
  REQUIRE( 5 == d.LAW() );

  auto t = d.effectiveTemperature();
  REQUIRE( 2 == t.NE() );
  REQUIRE( 1 == t.NR() );
  REQUIRE( 1 == t.interpolants().size() );
  REQUIRE( 1 == t.boundaries().size() );
  REQUIRE( 2 == t.interpolants()[0] );
  REQUIRE( 2 == t.boundaries()[0] );
  REQUIRE( 2 == t.E().size() );
  REQUIRE( 2 == t.energies().size() );
  REQUIRE( 2 == t.thetas().size() );
  REQUIRE( 2 == t.values().size() );
  REQUIRE( 1e-5 == Approx( t.E()[0] ) );
  REQUIRE( 3e+7 == Approx( t.E()[1] ) );
  REQUIRE( 1e-5 == Approx( t.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( t.energies()[1] ) );
  REQUIRE( 1.0 == Approx( t.thetas()[0] ) );
  REQUIRE( 1.0 == Approx( t.thetas()[1] ) );
  REQUIRE( 1.0 == Approx( t.values()[0] ) );
  REQUIRE( 1.0 == Approx( t.values()[1] ) );

  auto df = d.distributionFunction();
  REQUIRE( 6 == df.NF() );
  REQUIRE( 1 == df.NR() );
  REQUIRE( 1 == df.interpolants().size() );
  REQUIRE( 1 == df.boundaries().size() );
  REQUIRE( 1 == df.interpolants()[0] );
  REQUIRE( 6 == df.boundaries()[0] );
  REQUIRE( 6 == df.x().size() );
  REQUIRE( 6 == df.values().size() );
  REQUIRE( 0.0 == Approx( df.x()[0] ) );
  REQUIRE( 1e+4 == Approx( df.x()[1] ) );
  REQUIRE( 2e+4 == Approx( df.x()[2] ) );
  REQUIRE( 1.8e+6 == Approx( df.x()[3] ) );
  REQUIRE( 1.81e+6 == Approx( df.x()[4] ) );
  REQUIRE( 1.82e+6 == Approx( df.x()[5] ) );
  REQUIRE( 1.533738e-7 == Approx( df.values()[0] ) );
  REQUIRE( 1.378483e-6 == Approx( df.values()[1] ) );
  REQUIRE( 1.550360e-6 == Approx( df.values()[2] ) );
  REQUIRE( 7.90779e-31 == Approx( df.values()[3] ) );
  REQUIRE( 0.0 == Approx( df.values()[4] ) );
  REQUIRE( 0.0 == Approx( df.values()[5] ) );

  REQUIRE( 10 == chunk.NC() );
}

std::string chunkLF7() {
  return
    "-3.000000+7 0.000000+0          0          7          1          29455 5 18     \n"
    "          2          2                                            9455 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9455 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39455 5 18     \n"
    "          3          2                                            9455 5 18     \n"
    " 1.000000-5 1.365200+6 5.000000+5 1.374800+6 3.000000+7 1.691200+69455 5 18     \n";
}

void verifyChunkLF7( const PartialDistribution& chunk ) {

  REQUIRE( -3e+7 == Approx ( chunk.U() ) );
  REQUIRE( -3e+7 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 7 == p.LF() );
  REQUIRE( 7 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1e-5 == Approx( p.E()[0] ) );
  REQUIRE( 3e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1e-5 == Approx( p.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1. == Approx( p.p()[0] ) );
  REQUIRE( 1. == Approx( p.p()[1] ) );
  REQUIRE( 1. == Approx( p.probabilities()[0] ) );
  REQUIRE( 1. == Approx( p.probabilities()[1] ) );

  auto d = std::get< MaxwellianFissionSpectrum >
                  ( chunk.distribution() );
  REQUIRE( 7 == d.LF() );
  REQUIRE( 7 == d.LAW() );
  REQUIRE( 3 == d.NE() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 3 == d.boundaries()[0] );
  REQUIRE( 3 == d.E().size() );
  REQUIRE( 3 == d.energies().size() );
  REQUIRE( 3 == d.thetas().size() );
  REQUIRE( 3 == d.values().size() );
  REQUIRE( 1e-5 == Approx( d.E()[0] ) );
  REQUIRE( 5e+5 == Approx( d.E()[1] ) );
  REQUIRE( 3e+7 == Approx( d.E()[2] ) );
  REQUIRE( 1e-5 == Approx( d.energies()[0] ) );
  REQUIRE( 5e+5 == Approx( d.energies()[1] ) );
  REQUIRE( 3e+7 == Approx( d.energies()[2] ) );
  REQUIRE( 1.3652e+6 == Approx( d.thetas()[0] ) );
  REQUIRE( 1.3748e+6 == Approx( d.thetas()[1] ) );
  REQUIRE( 1.6912e+6 == Approx( d.thetas()[2] ) );
  REQUIRE( 1.3652e+6 == Approx( d.values()[0] ) );
  REQUIRE( 1.3748e+6 == Approx( d.values()[1] ) );
  REQUIRE( 1.6912e+6 == Approx( d.values()[2] ) );

  REQUIRE( 6 == chunk.NC() );
}

std::string chunkLF9() {
  return
    " 1.789920+7 0.000000+0          0          9          1          29237 5 37     \n"
    "          2          2                                            9237 5 37     \n"
    " 1.789920+7 1.000000+0 2.000000+7 1.000000+0                      9237 5 37     \n"
    " 0.000000+0 0.000000+0          0          0          1          49237 5 37     \n"
    "          4          2                                            9237 5 37     \n"
    " 1.789920+7 1.009900+5 1.800000+7 1.009900+5 1.900000+7 1.129200+59237 5 37     \n"
    " 2.000000+7 1.614300+5                                            9237 5 37     \n";
}

void verifyChunkLF9( const PartialDistribution& chunk ) {

  REQUIRE( 1.789920e+7 == Approx ( chunk.U() ) );
  REQUIRE( 1.789920e+7 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 9 == p.LF() );
  REQUIRE( 9 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1.789920e+7 == Approx( p.E()[0] ) );
  REQUIRE( 2e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1.789920e+7 == Approx( p.energies()[0] ) );
  REQUIRE( 2e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1.0 == Approx( p.p()[0] ) );
  REQUIRE( 1.0 == Approx( p.p()[1] ) );
  REQUIRE( 1.0 == Approx( p.probabilities()[0] ) );
  REQUIRE( 1.0 == Approx( p.probabilities()[1] ) );

  auto d = std::get< EvaporationSpectrum >( chunk.distribution() );
  REQUIRE( 9 == d.LF() );
  REQUIRE( 9 == d.LAW() );
  REQUIRE( 4 == d.NE() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 4 == d.boundaries()[0] );
  REQUIRE( 4 == d.E().size() );
  REQUIRE( 4 == d.energies().size() );
  REQUIRE( 4 == d.thetas().size() );
  REQUIRE( 4 == d.values().size() );
  REQUIRE( 1.789920e+7 == Approx( d.E()[0] ) );
  REQUIRE( 1.8e+7 == Approx( d.E()[1] ) );
  REQUIRE( 1.9e+7 == Approx( d.E()[2] ) );
  REQUIRE( 2e+7 == Approx( d.E()[3] ) );
  REQUIRE( 1.789920e+7 == Approx( d.energies()[0] ) );
  REQUIRE( 1.8e+7 == Approx( d.energies()[1] ) );
  REQUIRE( 1.9e+7 == Approx( d.energies()[2] ) );
  REQUIRE( 2e+7 == Approx( d.energies()[3] ) );
  REQUIRE( 1.0099e+5 == Approx( d.thetas()[0] ) );
  REQUIRE( 1.0099e+5 == Approx( d.thetas()[1] ) );
  REQUIRE( 1.1292e+5 == Approx( d.thetas()[2] ) );
  REQUIRE( 1.6143e+5 == Approx( d.thetas()[3] ) );
  REQUIRE( 1.0099e+5 == Approx( d.values()[0] ) );
  REQUIRE( 1.0099e+5 == Approx( d.values()[1] ) );
  REQUIRE( 1.1292e+5 == Approx( d.values()[2] ) );
  REQUIRE( 1.6143e+5 == Approx( d.values()[3] ) );

  REQUIRE( 7 == chunk.NC() );
}

std::string chunkLF11() {
  return
    "-3.000000+7 0.000000+0          0         11          1          29222 5 18     \n"
    "          2          2                                            9222 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n"
    "          3          2                                            9222 5 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n"
    "          5          2                                            9222 5 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n";
}

void verifyChunkLF11( const PartialDistribution& chunk ) {

  REQUIRE( -3e+7 == Approx ( chunk.U() ) );
  REQUIRE( -3e+7 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 11 == p.LF() );
  REQUIRE( 11 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1e-5 == Approx( p.E()[0] ) );
  REQUIRE( 3e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1e-5 == Approx( p.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1. == Approx( p.p()[0] ) );
  REQUIRE( 1. == Approx( p.p()[1] ) );
  REQUIRE( 1. == Approx( p.probabilities()[0] ) );
  REQUIRE( 1. == Approx( p.probabilities()[1] ) );

  auto d = std::get< WattSpectrum >( chunk.distribution() );

  REQUIRE( 11 == d.LF() );
  REQUIRE( 11 == d.LAW() );

  REQUIRE( 3 == d.a().NE() );
  REQUIRE( 1 == d.a().NR() );
  REQUIRE( 1 == d.a().interpolants().size() );
  REQUIRE( 1 == d.a().boundaries().size() );
  REQUIRE( 2 == d.a().interpolants()[0] );
  REQUIRE( 3 == d.a().boundaries()[0] );
  REQUIRE( 3 == d.a().E().size() );
  REQUIRE( 3 == d.a().energies().size() );
  REQUIRE( 3 == d.a().values().size() );
  REQUIRE( 1e-5 == Approx( d.a().E()[0] ) );
  REQUIRE( 1.5e+6 == Approx( d.a().E()[1] ) );
  REQUIRE( 3e+7 == Approx( d.a().E()[2] ) );
  REQUIRE( 1e-5 == Approx( d.a().energies()[0] ) );
  REQUIRE( 1.5e+6 == Approx( d.a().energies()[1] ) );
  REQUIRE( 3e+7 == Approx( d.a().energies()[2] ) );
  REQUIRE( 9.77e+5 == Approx( d.a().values()[0] ) );
  REQUIRE( 1e+6 == Approx( d.a().values()[1] ) );
  REQUIRE( 1.06e+6 == Approx( d.a().values()[2] ) );

  REQUIRE( 5 == d.b().NE() );
  REQUIRE( 1 == d.b().NR() );
  REQUIRE( 1 == d.b().interpolants().size() );
  REQUIRE( 1 == d.b().boundaries().size() );
  REQUIRE( 2 == d.b().interpolants()[0] );
  REQUIRE( 5 == d.b().boundaries()[0] );
  REQUIRE( 5 == d.b().E().size() );
  REQUIRE( 5 == d.b().energies().size() );
  REQUIRE( 5 == d.b().values().size() );
  REQUIRE( 1e-5 == Approx( d.b().E()[0] ) );
  REQUIRE( 1.5e+6 == Approx( d.b().E()[1] ) );
  REQUIRE( 1e+7 == Approx( d.b().E()[2] ) );
  REQUIRE( 1.22e+7 == Approx( d.b().E()[3] ) );
  REQUIRE( 3e+7 == Approx( d.b().E()[4] ) );
  REQUIRE( 1e-5 == Approx( d.b().energies()[0] ) );
  REQUIRE( 1.5e+6 == Approx( d.b().energies()[1] ) );
  REQUIRE( 1e+7 == Approx( d.b().energies()[2] ) );
  REQUIRE( 1.22e+7 == Approx( d.b().energies()[3] ) );
  REQUIRE( 3e+7 == Approx( d.b().energies()[4] ) );
  REQUIRE( 2.546e-6 == Approx( d.b().values()[0] ) );
  REQUIRE( 2.546e-6 == Approx( d.b().values()[1] ) );
  REQUIRE( 2.474e-6 == Approx( d.b().values()[2] ) );
  REQUIRE( 2.612e-6 == Approx( d.b().values()[3] ) );
  REQUIRE( 2.62e-6 == Approx( d.b().values()[4] ) );

  REQUIRE( 10 == chunk.NC() );
}

std::string chunkLF12() {
  return
    " 0.000000+0 0.000000+0          0         12          1          29543 5 18     \n"
    "          2          2                                            9543 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9543 5 18     \n"
    " 1.029979+6 5.467297+5          0          0          1          49543 5 18     \n"
    "          4          5                                            9543 5 18     \n"
    " 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n"
    " 3.000000+7 1.182884+6                                            9543 5 18     \n";
}

void verifyChunkLF12( const PartialDistribution& chunk ) {

  REQUIRE( 0.0 == Approx ( chunk.U() ) );
  REQUIRE( 0.0 == Approx ( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  REQUIRE( 12 == p.LF() );
  REQUIRE( 12 == p.LAW() );

  REQUIRE( 2 == p.NP() );
  REQUIRE( 1 == p.NR() );
  REQUIRE( 1 == p.interpolants().size() );
  REQUIRE( 1 == p.boundaries().size() );
  REQUIRE( 2 == p.interpolants()[0] );
  REQUIRE( 2 == p.boundaries()[0] );
  REQUIRE( 2 == p.E().size() );
  REQUIRE( 2 == p.energies().size() );
  REQUIRE( 2 == p.p().size() );
  REQUIRE( 2 == p.probabilities().size() );
  REQUIRE( 1e-5 == Approx( p.E()[0] ) );
  REQUIRE( 3e+7 == Approx( p.E()[1] ) );
  REQUIRE( 1e-5 == Approx( p.energies()[0] ) );
  REQUIRE( 3e+7 == Approx( p.energies()[1] ) );
  REQUIRE( 1. == Approx( p.p()[0] ) );
  REQUIRE( 1. == Approx( p.p()[1] ) );
  REQUIRE( 1. == Approx( p.probabilities()[0] ) );
  REQUIRE( 1. == Approx( p.probabilities()[1] ) );

  auto d = std::get< MadlandNixSpectrum >( chunk.distribution() );

  REQUIRE( 12 == d.LF() );
  REQUIRE( 12 == d.LAW() );

  REQUIRE( 1.029979e+6 == Approx( d.EFL() ) );
  REQUIRE( 1.029979e+6 == Approx( d.lightFragmentEnergy() ) );
  REQUIRE( 5.467297e+5 == Approx( d.EFH() ) );
  REQUIRE( 5.467297e+5 == Approx( d.heavyFragmentEnergy() ) );

  REQUIRE( 4 == d.NE() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 5 == d.interpolants()[0] );
  REQUIRE( 4 == d.boundaries()[0] );
  REQUIRE( 4 == d.E().size() );
  REQUIRE( 4 == d.energies().size() );
  REQUIRE( 4 == d.TM().size() );
  REQUIRE( 4 == d.maximumTemperatureValues().size() );
  REQUIRE( 1e-5 == Approx( d.E()[0] ) );
  REQUIRE( 5.000001e+5 == Approx( d.E()[1] ) );
  REQUIRE( 1.4e+7 == Approx( d.E()[2] ) );
  REQUIRE( 3.0e+7 == Approx( d.E()[3] ) );
  REQUIRE( 1e-5 == Approx( d.energies()[0] ) );
  REQUIRE( 5.000001e+5 == Approx( d.energies()[1] ) );
  REQUIRE( 1.4e+7 == Approx( d.energies()[2] ) );
  REQUIRE( 3.0e+7 == Approx( d.energies()[3] ) );
  REQUIRE( 1.092064e+6 == Approx( d.TM()[0] ) );
  REQUIRE( 1.101483e+6 == Approx( d.TM()[1] ) );
  REQUIRE( 1.129269e+6 == Approx( d.TM()[2] ) );
  REQUIRE( 1.182884e+6 == Approx( d.TM()[3] ) );
  REQUIRE( 1.092064e+6 == Approx( d.maximumTemperatureValues()[0] ) );
  REQUIRE( 1.101483e+6 == Approx( d.maximumTemperatureValues()[1] ) );
  REQUIRE( 1.129269e+6 == Approx( d.maximumTemperatureValues()[2] ) );
  REQUIRE( 1.182884e+6 == Approx( d.maximumTemperatureValues()[3] ) );

  REQUIRE( 7 == chunk.NC() );
}

std::string invalidLF() {
  return
    " 0.000000+0 0.000000+0          0          2          1          29222 5 18     \n"
    "          2          2                                            9222 5 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n"
    "          3          2                                            9222 5 18     \n"
    " 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n"
    "          5          2                                            9222 5 18     \n"
    " 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n"
    " 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n";
}
