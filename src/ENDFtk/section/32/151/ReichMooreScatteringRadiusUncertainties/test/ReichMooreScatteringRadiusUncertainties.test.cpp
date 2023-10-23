// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReichMooreScatteringRadiusUncertainties =
section::Type< 32, 151 >::ReichMooreScatteringRadiusUncertainties;

std::string chunk();
void verifyChunk( const ReichMooreScatteringRadiusUncertainties& );

SCENARIO( "ReichMooreScatteringRadiusUncertainties" ) {

  GIVEN( "valid data for a ReichMooreScatteringRadiusUncertainties" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double dap = 1.0;
      std::vector< double > uncertainties = { 2., 3., 4. };

      ReichMooreScatteringRadiusUncertainties chunk( dap, std::move( uncertainties ) );

      THEN( "a ReichMooreScatteringRadiusUncertainties can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReichMooreScatteringRadiusUncertainties chunk( begin, end, lineNumber,
                                                     1025, 32, 151 );

      THEN( "a ReichMooreScatteringRadiusUncertainties can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          4          0102532151     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      102532151     \n";
}

void verifyChunk( const ReichMooreScatteringRadiusUncertainties& chunk ) {

  CHECK_THAT( 1., WithinRel( chunk.DAP() ) );
  CHECK_THAT( 1., WithinRel( chunk.defaultUncertainty() ) );

  CHECK( 3 == chunk.DAPL().size() );
  CHECK( 3 == chunk.uncertainties().size() );

  CHECK_THAT( 2., WithinRel( chunk.DAPL()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.DAPL()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.DAPL()[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.uncertainties()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.uncertainties()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.uncertainties()[2] ) );

  CHECK( 2 == chunk.NC() );
}
