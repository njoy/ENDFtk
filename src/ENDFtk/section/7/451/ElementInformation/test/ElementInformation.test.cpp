// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/7/451.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ElementInformation = section::Type< 7, 451 >::ElementInformation;

std::string chunk();
void verifyChunk( const ElementInformation& );
std::string invalidChunk();

SCENARIO( "ElementInformation" ) {

  GIVEN( "valid data for a ElementInformation" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int atoms = 2;
      std::vector< unsigned int > identifiers = { 8016, 8017, 8018 };
      std::vector< unsigned int > states = { 0, 0, 0 };
      std::vector< double > abundances = { .99762, 3.8e-4, 2e-3 };
      std::vector< double > weights = { 15.85751, 16.8531, 17.8445 };
      std::vector< double > xs = { 3.744801, 3.642671, 3.846775 };

      ElementInformation chunk( atoms,
                                std::move( identifiers ), std::move( states ),
                                std::move( abundances ), std::move( weights ),
                                std::move( xs ) );

      THEN( "an ElementInformation can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 22, 7, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ElementInformation chunk( begin, end, lineNumber, 22, 7, 451 );

      THEN( "a ElementInformation can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 22, 7, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ElementInformation" ) {

    WHEN( "a string representation with an error is given" ) {

      // NPL != 6*NI
      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ElementInformation( begin, end, lineNumber, 22, 7, 451 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          0         18          3  22 7451     \n"
    " 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n"
    " 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n"
    " 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0 0.000000+0  22 7451     \n";
}

void verifyChunk( const ElementInformation& chunk ) {

  CHECK( 2 == chunk.NAS() );
  CHECK( 2 == chunk.numberAtoms() );
  CHECK( 3 == chunk.NI() );
  CHECK( 3 == chunk.numberIsotopes() );

  CHECK( 3 == chunk.ZAI().size() );
  CHECK( 3 == chunk.isotopeIdentifiers().size() );
  CHECK( 3 == chunk.LISI().size() );
  CHECK( 3 == chunk.isomericStates().size() );
  CHECK( 3 == chunk.AFI().size() );
  CHECK( 3 == chunk.abundances().size() );
  CHECK( 3 == chunk.AWRI().size() );
  CHECK( 3 == chunk.atomicWeightRatios().size() );
  CHECK( 3 == chunk.SFI().size() );
  CHECK( 3 == chunk.freeScatteringCrossSections().size() );
  CHECK( 8016 == chunk.ZAI()[0] );
  CHECK( 8017 == chunk.ZAI()[1] );
  CHECK( 8018 == chunk.ZAI()[2] );
  CHECK( 8016 == chunk.isotopeIdentifiers()[0] );
  CHECK( 8017 == chunk.isotopeIdentifiers()[1] );
  CHECK( 8018 == chunk.isotopeIdentifiers()[2] );
  CHECK( 0 == chunk.LISI()[0] );
  CHECK( 0 == chunk.LISI()[1] );
  CHECK( 0 == chunk.LISI()[2] );
  CHECK( 0 == chunk.isomericStates()[0] );
  CHECK( 0 == chunk.isomericStates()[1] );
  CHECK( 0 == chunk.isomericStates()[2] );
  CHECK_THAT( 9.976200e-1, WithinRel( chunk.AFI()[0] ) );
  CHECK_THAT( 3.800000e-4, WithinRel( chunk.AFI()[1] ) );
  CHECK_THAT( 2.000000e-3, WithinRel( chunk.AFI()[2] ) );
  CHECK_THAT( 9.976200e-1, WithinRel( chunk.abundances()[0] ) );
  CHECK_THAT( 3.800000e-4, WithinRel( chunk.abundances()[1] ) );
  CHECK_THAT( 2.000000e-3, WithinRel( chunk.abundances()[2] ) );
  CHECK_THAT(    15.85751, WithinRel( chunk.AWRI()[0] ) );
  CHECK_THAT(    16.85310, WithinRel( chunk.AWRI()[1] ) );
  CHECK_THAT(    17.84450, WithinRel( chunk.AWRI()[2] ) );
  CHECK_THAT(    15.85751, WithinRel( chunk.atomicWeightRatios()[0] ) );
  CHECK_THAT(    16.85310, WithinRel( chunk.atomicWeightRatios()[1] ) );
  CHECK_THAT(    17.84450, WithinRel( chunk.atomicWeightRatios()[2] ) );
  CHECK_THAT(    3.744801, WithinRel( chunk.SFI()[0] ) );
  CHECK_THAT(    3.642671, WithinRel( chunk.SFI()[1] ) );
  CHECK_THAT(    3.846775, WithinRel( chunk.SFI()[2] ) );
  CHECK_THAT(    3.744801, WithinRel( chunk.freeScatteringCrossSections()[0] ) );
  CHECK_THAT(    3.642671, WithinRel( chunk.freeScatteringCrossSections()[1] ) );
  CHECK_THAT(    3.846775, WithinRel( chunk.freeScatteringCrossSections()[2] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
  " 0.000000+0 0.000000+0          2          0         17          3  22 7451     \n"
  " 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n"
  " 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n"
  " 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0             22 7451     \n";
}
