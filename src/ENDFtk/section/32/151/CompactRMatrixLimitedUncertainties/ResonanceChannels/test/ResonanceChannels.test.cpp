#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ResonanceChannels =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ResonanceChannels;

std::string chunk();
void verifyChunk( const ResonanceChannels& );
std::string invalidSize();
std::string zeroSize();
std::string zeroNumberChannels();

SCENARIO( "ResonanceChannels" ) {

  GIVEN( "valid data for a ResonanceChannels" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double aj = 0.5;
      double parity = 0;
      std::vector< unsigned int > ppi = { 1, 2 };
      std::vector< unsigned int > l = { 0, 1 };
      std::vector< double > s = { 0., 0.5 };
      std::vector< double > b = { 0., 2. };
      std::vector< double > ape = { 0.,  0.543731 };
      std::vector< double > apt = { 0.,  0.54373 };

      ResonanceChannels chunk( aj, parity, std::move( ppi ), std::move( l ),
                               std::move( s ), std::move( b ),
                               std::move( apt ), std::move( ape ) );

      THEN( "a ResonanceChannels can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ResonanceChannels chunk( begin, end, lineNumber, 2625, 32, 151 );

      THEN( "a ResonanceChannels can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      double aj = 0.5;
      double parity = 0;
      std::vector< unsigned int > ppi = { 1, 2 };
      std::vector< unsigned int > l = { 0, 1 };
      std::vector< double > s = { 0., 0.5 };
      std::vector< double > b = { 0., 2. };
      std::vector< double > ape = { 0.,  0.543731 };
      std::vector< double > wrong = { 0. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceChannels( aj, parity, std::move( l ),
                                         std::move( ppi ),
                                         std::move( s ), std::move( b ),
                                         std::move( wrong ), std::move( ape ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is empty" ) {

      double aj = 0.5;
      double parity = 0;
      std::vector< unsigned int > ppi = { 1, 2 };
      std::vector< unsigned int > l = {};
      std::vector< double > s = {};
      std::vector< double > b = {};
      std::vector< double > ape = {};
      std::vector< double > apt = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceChannels( aj, parity, std::move( ppi ),
                                         std::move( l ),
                                         std::move( s ), std::move( b ),
                                         std::move( apt ), std::move( ape ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NCH is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceChannels( begin, end, lineNumber,
                                         2625, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL is used" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceChannels( begin, end, lineNumber,
                                         2625, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NCH is used" ) {

      std::string string = zeroNumberChannels();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceChannels( begin, end, lineNumber,
                                         2625, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000-1 0.000000+0          0          0         12          2262532151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 2.000000+0 5.437310-1 5.437300-1262532151     \n";
}

void verifyChunk( const ResonanceChannels& chunk ) {

  CHECK( 0.5 == Approx( chunk.AJ() ) );
  CHECK( 0.5 == Approx( chunk.spin() ) );
  CHECK( 0. == Approx( chunk.PJ() ) );
  CHECK( 0. == Approx( chunk.parity() ) );
  CHECK( 2 == chunk.NCH() );
  CHECK( 2 == chunk.numberChannels() );

  CHECK( 2 == chunk.PPI().size() );
  CHECK( 2 == chunk.particlePairNumbers().size() );
  CHECK( 2 == chunk.L().size() );
  CHECK( 2 == chunk.orbitalMomentumValues().size() );
  CHECK( 2 == chunk.SCH().size() );
  CHECK( 2 == chunk.channelSpinValues().size() );
  CHECK( 2 == chunk.BND().size() );
  CHECK( 2 == chunk.boundaryConditionValues().size() );
  CHECK( 2 == chunk.APT().size() );
  CHECK( 2 == chunk.trueChannelRadii().size() );
  CHECK( 2 == chunk.APE().size() );
  CHECK( 2 == chunk.effectiveChannelRadii().size() );

  CHECK( 1 == chunk.PPI()[0] );
  CHECK( 2 == chunk.PPI()[1] );
  CHECK( 1 == chunk.particlePairNumbers()[0] );
  CHECK( 2 == chunk.particlePairNumbers()[1] );
  CHECK( 0 == Approx( chunk.L()[0] ) );
  CHECK( 1 == Approx( chunk.L()[1] ) );
  CHECK( 0 == Approx( chunk.orbitalMomentumValues()[0] ) );
  CHECK( 1 == Approx( chunk.orbitalMomentumValues()[1] ) );
  CHECK( 0. == Approx( chunk.SCH()[0] ) );
  CHECK( .5 == Approx( chunk.SCH()[1] ) );
  CHECK( 0. == Approx( chunk.channelSpinValues()[0] ) );
  CHECK( .5 == Approx( chunk.channelSpinValues()[1] ) );
  CHECK( 0. == Approx( chunk.BND()[0] ) );
  CHECK( 2. == Approx( chunk.BND()[1] ) );
  CHECK( 0. == Approx( chunk.boundaryConditionValues()[0] ) );
  CHECK( 2. == Approx( chunk.boundaryConditionValues()[1] ) );
  CHECK( 0. == Approx( chunk.APT()[0] ) );
  CHECK( 5.437300e-1 == Approx( chunk.APT()[1] ) );
  CHECK( 0. == Approx( chunk.trueChannelRadii()[0] ) );
  CHECK( 5.437300e-1 == Approx( chunk.trueChannelRadii()[1] ) );
  CHECK( 0. == Approx( chunk.APE()[0] ) );
  CHECK( 5.437310e-1 == Approx( chunk.APE()[1] ) );
  CHECK( 0. == Approx( chunk.effectiveChannelRadii()[0] ) );
  CHECK( 5.437310e-1 == Approx( chunk.effectiveChannelRadii()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 5.000000-1 0.000000+0          0          0         13          2262532151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n"
    " 3.000000+0                                                       262532151     \n";
}

std::string zeroSize() {
  return
    " 5.000000-1 0.000000+0          0          0          0          2262532151     \n";
}

std::string zeroNumberChannels() {
  return
    " 5.000000-1 0.000000+0          0          0         12          0262532151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 2.000000+0 5.437310-1 5.437300-1262532151     \n";
}
