// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK_THROWS( PartialDistribution(begin, end, lineNumber, 9222, 5, 18 ) );
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

  CHECK_THAT( 0.0, WithinRel( chunk.U() ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 1 == p.LF() );
  CHECK( 1 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( p.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( p.P()[0] ) );
  CHECK_THAT( 1., WithinRel( p.P()[1] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[1] ) );

  auto d =
       std::get< TabulatedSpectrum >( chunk.distribution() );

  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 2 == d.NE() );
  CHECK( 2 == d.numberIncidentEnergies() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 2 == d.NBT()[0] );
  CHECK( 1 == d.INT().size() );
  CHECK( 4 == d.INT()[0] );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 2 == d.boundaries()[0] );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 4 == d.interpolants()[0] );

  CHECK( 2 == d.incidentEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( d.incidentEnergies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( d.incidentEnergies()[1] ) );

  auto value = d.outgoingDistributions()[0];
  CHECK_THAT( 1e-5, WithinRel( value.incidentEnergy() ) );
  CHECK( 3 == value.NP() );
  CHECK( 3 == value.numberPoints() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.numberInterpolationRegions() );
  CHECK( 1 == value.INT().size() );
  CHECK( 1 == value.NBT().size() );
  CHECK( 2 == value.INT()[0] );
  CHECK( 3 == value.NBT()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 3 == value.boundaries()[0] );
  CHECK( 3 == value.EP().size() );
  CHECK( 3 == value.outgoingEnergies().size() );
  CHECK( 3 == value.G().size() );
  CHECK( 3 == value.probabilities().size() );
  CHECK_THAT( 0.0, WithinRel( value.EP()[0] ) );
  CHECK_THAT( 1e+5, WithinRel( value.EP()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( value.EP()[2] ) );
  CHECK_THAT( 0.0, WithinRel( value.outgoingEnergies()[0] ) );
  CHECK_THAT( 1e+5, WithinRel( value.outgoingEnergies()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( value.outgoingEnergies()[2] ) );
  CHECK_THAT( 0., WithinRel( value.G()[0] ) );
  CHECK_THAT( 1.757570e-9, WithinRel( value.G()[1] ) );
  CHECK_THAT( 1.843350e-9, WithinRel( value.G()[2] ) );
  CHECK_THAT( 0., WithinRel( value.probabilities()[0] ) );
  CHECK_THAT( 1.757570e-9, WithinRel( value.probabilities()[1] ) );
  CHECK_THAT( 1.843350e-9, WithinRel( value.probabilities()[2] ) );

  value = d.outgoingDistributions()[1];
  CHECK_THAT( 3e+7, WithinRel( value.incidentEnergy() ) );
  CHECK( 4 == value.NP() );
  CHECK( 4 == value.numberPoints() );
  CHECK( 1 == value.NR() );
  CHECK( 1 == value.numberInterpolationRegions() );
  CHECK( 1 == value.INT().size() );
  CHECK( 1 == value.NBT().size() );
  CHECK( 2 == value.INT()[0] );
  CHECK( 4 == value.NBT()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 2 == value.interpolants()[0] );
  CHECK( 4 == value.boundaries()[0] );
  CHECK( 4 == value.EP().size() );
  CHECK( 4 == value.outgoingEnergies().size() );
  CHECK( 4 == value.G().size() );
  CHECK( 4 == value.probabilities().size() );
  CHECK_THAT( 0.0, WithinRel( value.EP()[0] ) );
  CHECK_THAT( 10., WithinRel( value.EP()[1] ) );
  CHECK_THAT( 11., WithinRel( value.EP()[2] ) );
  CHECK_THAT( 3e+7, WithinRel( value.EP()[3] ) );
  CHECK_THAT( 0.0, WithinRel( value.outgoingEnergies()[0] ) );
  CHECK_THAT( 10., WithinRel( value.outgoingEnergies()[1] ) );
  CHECK_THAT( 11., WithinRel( value.outgoingEnergies()[2] ) );
  CHECK_THAT( 3e+7, WithinRel( value.outgoingEnergies()[3] ) );
  CHECK_THAT( 0., WithinRel( value.G()[0] ) );
  CHECK_THAT( 1.733405e-9, WithinRel( value.G()[1] ) );
  CHECK_THAT( 1.818010e-9, WithinRel( value.G()[2] ) );
  CHECK_THAT( 1.898849e-9, WithinRel( value.G()[3] ) );
  CHECK_THAT( 0., WithinRel( value.probabilities()[0] ) );
  CHECK_THAT( 1.733405e-9, WithinRel( value.probabilities()[1] ) );
  CHECK_THAT( 1.818010e-9, WithinRel( value.probabilities()[2] ) );
  CHECK_THAT( 1.898849e-9, WithinRel( value.probabilities()[3] ) );

  CHECK( 12 == chunk.NC() );
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

  CHECK_THAT( -3e+7, WithinRel( chunk.U() ) );
  CHECK_THAT( -3e+7, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 5 == p.LF() );
  CHECK( 5 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( p.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1.804944e-2, WithinRel( p.P()[0] ) );
  CHECK_THAT( 1.804944e-2, WithinRel( p.P()[1] ) );
  CHECK_THAT( 1.804944e-2, WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1.804944e-2, WithinRel( p.probabilities()[1] ) );

  auto d =
       std::get< GeneralEvaporationSpectrum >
             ( chunk.distribution() );

  CHECK( 5 == d.LF() );
  CHECK( 5 == d.LAW() );

  auto t = d.effectiveTemperature();
  CHECK( 2 == t.NP() );
  CHECK( 2 == t.numberPoints() );
  CHECK( 1 == t.NR() );
  CHECK( 1 == t.numberInterpolationRegions() );
  CHECK( 1 == t.INT().size() );
  CHECK( 1 == t.NBT().size() );
  CHECK( 2 == t.INT()[0] );
  CHECK( 2 == t.NBT()[0] );
  CHECK( 1 == t.interpolants().size() );
  CHECK( 1 == t.boundaries().size() );
  CHECK( 2 == t.interpolants()[0] );
  CHECK( 2 == t.boundaries()[0] );
  CHECK( 2 == t.E().size() );
  CHECK( 2 == t.energies().size() );
  CHECK( 2 == t.thetas().size() );
  CHECK_THAT( 1e-5, WithinRel( t.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( t.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( t.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( t.energies()[1] ) );
  CHECK_THAT( 1.0, WithinRel( t.thetas()[0] ) );
  CHECK_THAT( 1.0, WithinRel( t.thetas()[1] ) );

  auto df = d.distributionFunction();
  CHECK( 6 == df.NP() );
  CHECK( 6 == df.numberPoints() );
  CHECK( 1 == df.NR() );
  CHECK( 1 == df.numberInterpolationRegions() );
  CHECK( 1 == df.INT().size() );
  CHECK( 1 == df.NBT().size() );
  CHECK( 1 == df.INT()[0] );
  CHECK( 6 == df.NBT()[0] );
  CHECK( 1 == df.interpolants().size() );
  CHECK( 1 == df.boundaries().size() );
  CHECK( 1 == df.interpolants()[0] );
  CHECK( 6 == df.boundaries()[0] );
  CHECK( 6 == df.X().size() );
  CHECK( 6 == df.G().size() );
  CHECK_THAT( 0.0, WithinRel( df.X()[0] ) );
  CHECK_THAT( 1e+4, WithinRel( df.X()[1] ) );
  CHECK_THAT( 2e+4, WithinRel( df.X()[2] ) );
  CHECK_THAT( 1.8e+6, WithinRel( df.X()[3] ) );
  CHECK_THAT( 1.81e+6, WithinRel( df.X()[4] ) );
  CHECK_THAT( 1.82e+6, WithinRel( df.X()[5] ) );
  CHECK_THAT( 1.533738e-7, WithinRel( df.G()[0] ) );
  CHECK_THAT( 1.378483e-6, WithinRel( df.G()[1] ) );
  CHECK_THAT( 1.550360e-6, WithinRel( df.G()[2] ) );
  CHECK_THAT( 7.90779e-31, WithinRel( df.G()[3] ) );
  CHECK_THAT( 0.0, WithinRel( df.G()[4] ) );
  CHECK_THAT( 0.0, WithinRel( df.G()[5] ) );

  CHECK( 10 == chunk.NC() );
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

  CHECK_THAT( -3e+7, WithinRel( chunk.U() ) );
  CHECK_THAT( -3e+7, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 7 == p.LF() );
  CHECK( 7 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( p.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( p.P()[0] ) );
  CHECK_THAT( 1., WithinRel( p.P()[1] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[1] ) );

  auto d = std::get< MaxwellianFissionSpectrum >
                  ( chunk.distribution() );
  CHECK( 7 == d.LF() );
  CHECK( 7 == d.LAW() );
  CHECK( 3 == d.NP() );
  CHECK( 3 == d.numberPoints() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 1 == d.INT().size() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 2 == d.INT()[0] );
  CHECK( 3 == d.NBT()[0] );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 2 == d.interpolants()[0] );
  CHECK( 3 == d.boundaries()[0] );
  CHECK( 3 == d.E().size() );
  CHECK( 3 == d.energies().size() );
  CHECK( 3 == d.thetas().size() );
  CHECK_THAT( 1e-5, WithinRel( d.E()[0] ) );
  CHECK_THAT( 5e+5, WithinRel( d.E()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( d.E()[2] ) );
  CHECK_THAT( 1e-5, WithinRel( d.energies()[0] ) );
  CHECK_THAT( 5e+5, WithinRel( d.energies()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( d.energies()[2] ) );
  CHECK_THAT( 1.3652e+6, WithinRel( d.thetas()[0] ) );
  CHECK_THAT( 1.3748e+6, WithinRel( d.thetas()[1] ) );
  CHECK_THAT( 1.6912e+6, WithinRel( d.thetas()[2] ) );

  CHECK( 6 == chunk.NC() );
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

  CHECK_THAT( 1.789920e+7, WithinRel( chunk.U() ) );
  CHECK_THAT( 1.789920e+7, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 9 == p.LF() );
  CHECK( 9 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1.789920e+7, WithinRel( p.E()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1.789920e+7, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 2e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1.0, WithinRel( p.P()[0] ) );
  CHECK_THAT( 1.0, WithinRel( p.P()[1] ) );
  CHECK_THAT( 1.0, WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1.0, WithinRel( p.probabilities()[1] ) );

  auto d = std::get< EvaporationSpectrum >( chunk.distribution() );
  CHECK( 9 == d.LF() );
  CHECK( 9 == d.LAW() );
  CHECK( 4 == d.NP() );
  CHECK( 4 == d.numberPoints() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 1 == d.INT().size() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 2 == d.INT()[0] );
  CHECK( 4 == d.NBT()[0] );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 2 == d.interpolants()[0] );
  CHECK( 4 == d.boundaries()[0] );
  CHECK( 4 == d.E().size() );
  CHECK( 4 == d.energies().size() );
  CHECK( 4 == d.thetas().size() );
  CHECK_THAT( 1.789920e+7, WithinRel( d.E()[0] ) );
  CHECK_THAT( 1.8e+7, WithinRel( d.E()[1] ) );
  CHECK_THAT( 1.9e+7, WithinRel( d.E()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( d.E()[3] ) );
  CHECK_THAT( 1.789920e+7, WithinRel( d.energies()[0] ) );
  CHECK_THAT( 1.8e+7, WithinRel( d.energies()[1] ) );
  CHECK_THAT( 1.9e+7, WithinRel( d.energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( d.energies()[3] ) );
  CHECK_THAT( 1.0099e+5, WithinRel( d.thetas()[0] ) );
  CHECK_THAT( 1.0099e+5, WithinRel( d.thetas()[1] ) );
  CHECK_THAT( 1.1292e+5, WithinRel( d.thetas()[2] ) );
  CHECK_THAT( 1.6143e+5, WithinRel( d.thetas()[3] ) );

  CHECK( 7 == chunk.NC() );
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

  CHECK_THAT( -3e+7, WithinRel( chunk.U() ) );
  CHECK_THAT( -3e+7, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 11 == p.LF() );
  CHECK( 11 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( p.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( p.P()[0] ) );
  CHECK_THAT( 1., WithinRel( p.P()[1] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[1] ) );

  auto d = std::get< WattSpectrum >( chunk.distribution() );

  CHECK( 11 == d.LF() );
  CHECK( 11 == d.LAW() );

  CHECK( 3 == d.a().NP() );
  CHECK( 3 == d.a().numberPoints() );
  CHECK( 1 == d.a().NR() );
  CHECK( 1 == d.a().numberInterpolationRegions() );
  CHECK( 1 == d.a().INT().size() );
  CHECK( 1 == d.a().NBT().size() );
  CHECK( 2 == d.a().INT()[0] );
  CHECK( 3 == d.a().NBT()[0] );
  CHECK( 1 == d.a().interpolants().size() );
  CHECK( 1 == d.a().boundaries().size() );
  CHECK( 2 == d.a().interpolants()[0] );
  CHECK( 3 == d.a().boundaries()[0] );
  CHECK( 3 == d.a().E().size() );
  CHECK( 3 == d.a().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( d.a().E()[0] ) );
  CHECK_THAT( 1.5e+6, WithinRel( d.a().E()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( d.a().E()[2] ) );
  CHECK_THAT( 1e-5, WithinRel( d.a().energies()[0] ) );
  CHECK_THAT( 1.5e+6, WithinRel( d.a().energies()[1] ) );
  CHECK_THAT( 3e+7, WithinRel( d.a().energies()[2] ) );

  CHECK( 5 == d.b().NP() );
  CHECK( 5 == d.b().numberPoints() );
  CHECK( 1 == d.b().NR() );
  CHECK( 1 == d.b().numberInterpolationRegions() );
  CHECK( 1 == d.b().INT().size() );
  CHECK( 1 == d.b().NBT().size() );
  CHECK( 2 == d.b().INT()[0] );
  CHECK( 5 == d.b().NBT()[0] );
  CHECK( 1 == d.b().interpolants().size() );
  CHECK( 1 == d.b().boundaries().size() );
  CHECK( 2 == d.b().interpolants()[0] );
  CHECK( 5 == d.b().boundaries()[0] );
  CHECK( 5 == d.b().E().size() );
  CHECK( 5 == d.b().energies().size() );
  CHECK_THAT( 1e-5, WithinRel( d.b().E()[0] ) );
  CHECK_THAT( 1.5e+6, WithinRel( d.b().E()[1] ) );
  CHECK_THAT( 1e+7, WithinRel( d.b().E()[2] ) );
  CHECK_THAT( 1.22e+7, WithinRel( d.b().E()[3] ) );
  CHECK_THAT( 3e+7, WithinRel( d.b().E()[4] ) );
  CHECK_THAT( 1e-5, WithinRel( d.b().energies()[0] ) );
  CHECK_THAT( 1.5e+6, WithinRel( d.b().energies()[1] ) );
  CHECK_THAT( 1e+7, WithinRel( d.b().energies()[2] ) );
  CHECK_THAT( 1.22e+7, WithinRel( d.b().energies()[3] ) );
  CHECK_THAT( 3e+7, WithinRel( d.b().energies()[4] ) );

  CHECK( 10 == chunk.NC() );
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

  CHECK_THAT( 0.0, WithinRel( chunk.U() ) );
  CHECK_THAT( 0.0, WithinRel( chunk.energyLimitConstant() ) );

  auto p = chunk.probability();

  CHECK( 12 == p.LF() );
  CHECK( 12 == p.LAW() );

  CHECK( 2 == p.NP() );
  CHECK( 2 == p.numberPoints() );
  CHECK( 1 == p.NR() );
  CHECK( 1 == p.numberInterpolationRegions() );
  CHECK( 1 == p.INT().size() );
  CHECK( 1 == p.NBT().size() );
  CHECK( 2 == p.INT()[0] );
  CHECK( 2 == p.NBT()[0] );
  CHECK( 1 == p.interpolants().size() );
  CHECK( 1 == p.boundaries().size() );
  CHECK( 2 == p.interpolants()[0] );
  CHECK( 2 == p.boundaries()[0] );
  CHECK( 2 == p.E().size() );
  CHECK( 2 == p.energies().size() );
  CHECK( 2 == p.P().size() );
  CHECK( 2 == p.probabilities().size() );
  CHECK_THAT( 1e-5, WithinRel( p.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( p.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( p.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( p.P()[0] ) );
  CHECK_THAT( 1., WithinRel( p.P()[1] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[0] ) );
  CHECK_THAT( 1., WithinRel( p.probabilities()[1] ) );

  auto d = std::get< MadlandNixSpectrum >( chunk.distribution() );

  CHECK( 12 == d.LF() );
  CHECK( 12 == d.LAW() );

  CHECK_THAT( 1.029979e+6, WithinRel( d.EFL() ) );
  CHECK_THAT( 1.029979e+6, WithinRel( d.lightFragmentEnergy() ) );
  CHECK_THAT( 5.467297e+5, WithinRel( d.EFH() ) );
  CHECK_THAT( 5.467297e+5, WithinRel( d.heavyFragmentEnergy() ) );

  CHECK( 4 == d.NP() );
  CHECK( 4 == d.numberPoints() );
  CHECK( 1 == d.NR() );
  CHECK( 1 == d.numberInterpolationRegions() );
  CHECK( 1 == d.INT().size() );
  CHECK( 1 == d.NBT().size() );
  CHECK( 5 == d.INT()[0] );
  CHECK( 4 == d.NBT()[0] );
  CHECK( 1 == d.interpolants().size() );
  CHECK( 1 == d.boundaries().size() );
  CHECK( 5 == d.interpolants()[0] );
  CHECK( 4 == d.boundaries()[0] );
  CHECK( 4 == d.E().size() );
  CHECK( 4 == d.energies().size() );
  CHECK( 4 == d.TM().size() );
  CHECK( 4 == d.maximumTemperatureValues().size() );
  CHECK_THAT( 1e-5, WithinRel( d.E()[0] ) );
  CHECK_THAT( 5.000001e+5, WithinRel( d.E()[1] ) );
  CHECK_THAT( 1.4e+7, WithinRel( d.E()[2] ) );
  CHECK_THAT( 3.0e+7, WithinRel( d.E()[3] ) );
  CHECK_THAT( 1e-5, WithinRel( d.energies()[0] ) );
  CHECK_THAT( 5.000001e+5, WithinRel( d.energies()[1] ) );
  CHECK_THAT( 1.4e+7, WithinRel( d.energies()[2] ) );
  CHECK_THAT( 3.0e+7, WithinRel( d.energies()[3] ) );
  CHECK_THAT( 1.092064e+6, WithinRel( d.TM()[0] ) );
  CHECK_THAT( 1.101483e+6, WithinRel( d.TM()[1] ) );
  CHECK_THAT( 1.129269e+6, WithinRel( d.TM()[2] ) );
  CHECK_THAT( 1.182884e+6, WithinRel( d.TM()[3] ) );
  CHECK_THAT( 1.092064e+6, WithinRel( d.maximumTemperatureValues()[0] ) );
  CHECK_THAT( 1.101483e+6, WithinRel( d.maximumTemperatureValues()[1] ) );
  CHECK_THAT( 1.129269e+6, WithinRel( d.maximumTemperatureValues()[2] ) );
  CHECK_THAT( 1.182884e+6, WithinRel( d.maximumTemperatureValues()[3] ) );

  CHECK( 7 == chunk.NC() );
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
