// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/15.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using PartialDistribution = section::Type< 15 >::PartialDistribution;
using Probability = section::Type< 15 >::Probability;
using TabulatedSpectrum = section::Type< 15 >::TabulatedSpectrum;
using OutgoingEnergyDistribution =
section::Type< 15 >::TabulatedSpectrum::OutgoingEnergyDistribution;

std::string chunk();
void verifyChunk( const section::Type< 15 >& );
std::string chunkWithNK0();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 15 >" ) {

  GIVEN( "valid data for a section::Type< 15 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 18;
      int zaid = 92235;
      double awr = 2.330250e+2;

      std::vector< PartialDistribution > partials =
      { { Probability( 1, { 2 }, { 2 },
                       { 1e-5, 3e+7 }, { 1., 1. } ),
          TabulatedSpectrum(
              { 2 }, { 4 },
              { OutgoingEnergyDistribution(
                     1e-5, { 3 }, { 2 },
                     { 0.0, 1e+5, 3e+7 },
                     { 0.0, 1.757570e-9, 1.843350e-9 } ),
                OutgoingEnergyDistribution(
                     3e+7, { 4 }, { 2 },
                     { 0.0, 10., 11., 3e+7 },
                     { 0.0, 1.733405e-9, 1.818010e-9, 1.898849e-9 } ) } ) } };

      section::Type< 15 > chunk( mt, zaid, awr, std::move( partials ) );

      THEN( "a section::Type< 15 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 15 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 15 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 15 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 15 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 15, 18, std::string( sectionString ) );

      section::Type< 15 > chunk = section.parse< 15 >();

      THEN( "a section::Type< 15 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 15 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 15 >" ) {

    WHEN( "a string representation of a section::Type< 15 > with NK=0" ) {

      std::string sectionString = chunkWithNK0() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 15 >( head, begin, end,
                                           lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 15 > "
          "with an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section::Type< 15 >( head, begin, end,
                                           lineNumber, 9228 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 9.223500+4 2.330250+2          0          0          1          0922815 18     \n"
    " 0.000000+0 0.000000+0          0          1          1          2922815 18     \n"
    "          2          2                                            922815 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      922815 18     \n"
    " 0.000000+0 0.000000+0          0          0          1          2922815 18     \n"
    "          2          4                                            922815 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          3922815 18     \n"
    "          3          2                                            922815 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-9922815 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          4922815 18     \n"
    "          4          2                                            922815 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-9922815 18     \n"
    " 3.000000+7 1.898849-9                                            922815 18     \n";
}

void verifyChunk( const section::Type< 15 >& chunk ) {

  CHECK( 18 == chunk.MT() );
  CHECK( 18 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.330250e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberPartialDistributions() );

  const auto& partial = chunk.partialDistributions()[0];

  const auto& p = partial.probability();

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

  auto d = partial.distribution();

  CHECK( 1 == d.LF() );
  CHECK( 1 == d.LAW() );

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
  CHECK_THAT( 1e-5, WithinRel( value.E() ) );
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
  CHECK_THAT( 3e+7, WithinRel( value.E() ) );
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

  CHECK( 13 == chunk.NC() );
}

std::string chunkWithNK0() {
  return
    " 9.223500+4 2.330250+2          0          0          0          0922815 18     \n"
    "-3.000000+7 0.000000+0          0          1          1          2922815 18     \n"
    "          2          2                                            922815 18     \n"
    " 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      922815 18     \n"
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

std::string validSEND() {
  return
    "                                                                  922815  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  922815  4     \n";
}
