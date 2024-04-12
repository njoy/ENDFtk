// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/7/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;
using MixedElastic = section::Type< 7, 2 >::MixedElastic;

std::string chunk();
void verifyChunk( const MixedElastic& );
std::string invalidChunk();

SCENARIO( "MixedElastic" ) {

  GIVEN( "valid data for a MixedElastic" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      // coherent elastic
      CoherentElastic coherent( { 3 }, { 1 }, { 293.6, 800.0 }, { 2 },
                                { 1.059427e-3, 3.718355e-3, 4.237708e-3 },
                                { { 0.0, 9.364524e-3, 1.548925e-2 },
                                  { 0.5, 8.318414e-3, 1.640584e-2 } } );

      // incoherent elastic
      IncoherentElastic incoherent( 2.054202, { 2 }, { 2 },
                                    { 293.6, 800. },
                                    { 8.937898, 17.65328 } );

      MixedElastic chunk( std::move( coherent ), std::move( incoherent ) );

      THEN( "a MixedElastic can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      MixedElastic chunk( begin, end, lineNumber, 27, 7, 2 );

      THEN( "a MixedElastic can "
            "be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a MixedElastic" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MixedElastic( begin, end, lineNumber, 27, 7, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    " 8.000000+2 0.000000+0          2          0          3          0  27 7  2     \n"
    " 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n"
    " 2.054202+0 0.000000+0          0          0          1          2  27 7  2     \n"
    "          2          2                                              27 7  2     \n"
    " 2.936000+2 8.937898+0 8.000000+2 1.765328+1                        27 7  2     \n";
}

void verifyChunk( const MixedElastic& chunk ) {

  CHECK( 3 == chunk.LTHR() );
  CHECK( 3 == chunk.elasticScatteringType() );

  decltype(auto) coherent = chunk.coherent();

  CHECK( 1 == coherent.LTHR() );
  CHECK( 1 == coherent.elasticScatteringType() );
  CHECK( 1 == coherent.LT() );
  CHECK( 1 == coherent.temperatureDependenceFlag() );
  CHECK( 2 == coherent.NT() );
  CHECK( 2 == coherent.numberTemperatures() );
  CHECK( 3 == coherent.NP() );
  CHECK( 3 == coherent.numberBraggEdges() );

  CHECK( 1 == coherent.NR() );
  CHECK( 1 == coherent.numberInterpolationRegions() );
  CHECK( 1 == coherent.NBT().size() );
  CHECK( 3 == coherent.NBT()[0] );
  CHECK( 1 == coherent.INT().size() );
  CHECK( 1 == coherent.INT()[0] );
  CHECK( 1 == coherent.boundaries().size() );
  CHECK( 3 == coherent.boundaries()[0] );
  CHECK( 1 == coherent.interpolants().size() );
  CHECK( 1 == coherent.interpolants()[0] );

  CHECK( 2 == coherent.T().size() );
  CHECK( 2 == coherent.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( coherent.T()[0] ) );
  CHECK_THAT( 800., WithinRel( coherent.T()[1] ) );
  CHECK_THAT( 293.6, WithinRel( coherent.temperatures()[0] ) );
  CHECK_THAT( 800., WithinRel( coherent.temperatures()[1] ) );

  CHECK( 3 == coherent.E().size() );
  CHECK( 3 == coherent.energies().size() );
  CHECK_THAT( 1.059427e-3, WithinRel( coherent.E()[0] ) );
  CHECK_THAT( 3.718355e-3, WithinRel( coherent.E()[1] ) );
  CHECK_THAT( 4.237708e-3, WithinRel( coherent.E()[2] ) );
  CHECK_THAT( 1.059427e-3, WithinRel( coherent.energies()[0] ) );
  CHECK_THAT( 3.718355e-3, WithinRel( coherent.energies()[1] ) );
  CHECK_THAT( 4.237708e-3, WithinRel( coherent.energies()[2] ) );

  CHECK( 1 == coherent.LI().size() );
  CHECK( 2 == coherent.LI()[0] );
  CHECK( 1 == coherent.temperatureInterpolants().size() );
  CHECK( 2 == coherent.temperatureInterpolants()[0] );

  CHECK( 2 == coherent.S().size() );
  CHECK( 3 == coherent.S()[0].size() );
  CHECK_THAT( 0.0, WithinRel( coherent.S()[0][0] ) );
  CHECK_THAT( 9.364524e-3, WithinRel( coherent.S()[0][1] ) );
  CHECK_THAT( 1.548925e-2, WithinRel( coherent.S()[0][2] ) );
  CHECK( 3 == coherent.S()[1].size() );
  CHECK_THAT( 0.5, WithinRel( coherent.S()[1][0] ) );
  CHECK_THAT( 8.318414e-3, WithinRel( coherent.S()[1][1] ) );
  CHECK_THAT( 1.640584e-2, WithinRel( coherent.S()[1][2] ) );

  CHECK( 2 == coherent.thermalScatteringValues().size() );
  CHECK( 3 == coherent.thermalScatteringValues()[0].size() );
  CHECK_THAT( 0.0, WithinRel( coherent.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 9.364524e-3, WithinRel( coherent.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 1.548925e-2, WithinRel( coherent.thermalScatteringValues()[0][2] ) );
  CHECK( 3 == coherent.thermalScatteringValues()[1].size() );
  CHECK_THAT( 0.5, WithinRel( coherent.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 8.318414e-3, WithinRel( coherent.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 1.640584e-2, WithinRel( coherent.thermalScatteringValues()[1][2] ) );

  decltype(auto) incoherent = chunk.incoherent();

  CHECK( 2 == incoherent.LTHR() );
  CHECK( 2 == incoherent.elasticScatteringType() );
  CHECK_THAT( 2.054202, WithinRel( incoherent.SB() ) );
  CHECK_THAT( 2.054202, WithinRel( incoherent.boundCrossSection() ) );
  CHECK( 2 == incoherent.NP() );
  CHECK( 2 == incoherent.numberPoints() );
  CHECK( 2 == incoherent.NT() );
  CHECK( 2 == incoherent.numberTemperatures() );
  CHECK( 1 == incoherent.NR() );
  CHECK( 1 == incoherent.numberInterpolationRegions() );
  CHECK( 1 == incoherent.INT().size() );
  CHECK( 1 == incoherent.NBT().size() );
  CHECK( 2 == incoherent.INT()[0] );
  CHECK( 2 == incoherent.NBT()[0] );
  CHECK( 1 == incoherent.interpolants().size() );
  CHECK( 1 == incoherent.boundaries().size() );
  CHECK( 2 == incoherent.interpolants()[0] );
  CHECK( 2 == incoherent.boundaries()[0] );
  CHECK( 2 == incoherent.T().size() );
  CHECK( 2 == incoherent.temperatures().size() );
  CHECK( 2 == incoherent.W().size() );
  CHECK( 2 == incoherent.debyeWallerValues().size() );
  CHECK_THAT( 293.6, WithinRel( incoherent.T()[0] ) );
  CHECK_THAT( 800., WithinRel( incoherent.T()[1] ) );
  CHECK_THAT( 293.6, WithinRel( incoherent.temperatures()[0] ) );
  CHECK_THAT( 800., WithinRel( incoherent.temperatures()[1] ) );
  CHECK_THAT( 8.937898, WithinRel( incoherent.W()[0] ) );
  CHECK_THAT( 17.65328, WithinRel( incoherent.W()[1] ) );
  CHECK_THAT( 8.937898, WithinRel( incoherent.debyeWallerValues()[0] ) );
  CHECK_THAT( 17.65328, WithinRel( incoherent.debyeWallerValues()[1] ) );

  CHECK( 8 == chunk.NC() );
}

std::string invalidChunk() {
  return
  " 2.936000+2 0.000000+0          1          0          1          2  27 7  2     \n"
  "          3          1                                              27 7  2     \n"
  " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
  " 8.000000+2 0.000000+0          2          0          3          0  27 7  2     \n"
  " 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n"
  " 2.054202+0 0.000000+0          0          0          1          6  27 7  2     \n"
  "          2          2                                              27 7  2     \n"
  " 2.936000+2 8.937898+0 8.000000+2 1.765328+1                        27 7  2     \n";
}
