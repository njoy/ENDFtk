// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/26.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using EnergyTransfer =
section::Type< 26 >::EnergyTransfer;

std::string chunk();
void verifyChunk( const EnergyTransfer& );
std::string invalidChunk();

SCENARIO( "EnergyTransfer" ) {

  GIVEN( "valid data for an EnergyTransfer" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 10., 1.e+11 };
      std::vector< double > transfer = { 1.e-5, 2e+4 };

      EnergyTransfer chunk( std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( transfer ) );

      THEN( "an EnergyTransfer can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 26, 525 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyTransfer chunk( begin, end, lineNumber, 100, 26, 525 );

      THEN( "an EnergyTransfer can be constructed and members can be tested" ) {

        verifyChunk( chunk );
     } // THEN

     THEN( "it can be printed" ) {

       std::string buffer;
       auto output = std::back_inserter( buffer );
       chunk.print( output, 100, 26, 525 );

       CHECK( buffer == string );
     } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an EnergyTransfer" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > wrongBoundaries = { 4, 2 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 10., 1.e+11 };
      std::vector< double > transfer = { 1.e-5, 2e+4 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyTransfer( std::move( wrongBoundaries ),
                                      std::move( interpolants ),
                                      std::move( energies ),
                                      std::move( transfer ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyTransfer( begin, end, lineNumber, 100, 26, 525 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 0.000000+0 0.000000+0          0          0          1          2 10026525     \n"
    "          2          2                                             10026525     \n"
    " 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n";
}

void verifyChunk( const EnergyTransfer& chunk ) {

  CHECK( 8 == chunk.LAW() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.ET().size() );
  CHECK( 2 == chunk.energyTransferValues().size() );
  CHECK_THAT( 10., WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 1.e+11, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1.e+11, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1.e-5, WithinRel( chunk.ET()[0] ) );
  CHECK_THAT( 2e+4, WithinRel( chunk.ET()[1] ) );
  CHECK_THAT( 1.e-5, WithinRel( chunk.energyTransferValues()[0] ) );
  CHECK_THAT( 2e+4, WithinRel( chunk.energyTransferValues()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {

  return
  " 0.000000+0 0.000000+0          0          0          2          2 10026525     \n"
  "          2          2                                             10026525     \n"
  " 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n";
}
