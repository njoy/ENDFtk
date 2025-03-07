// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/13.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TotalCrossSection = section::Type< 13 >::TotalCrossSection;

std::string chunk();
void verifyChunk( const TotalCrossSection& );
std::string invalidChunk();

SCENARIO( "TotalCrossSection" ) {

  GIVEN( "valid data for a TotalCrossSection" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 5 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      TotalCrossSection chunk( std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( x ),
                               std::move( y ) );

      THEN( "a TotalCrossSection can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 13, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TotalCrossSection chunk( begin, end, lineNumber, 9228, 13, 18 );

      THEN( "a TotalCrossSection can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 13, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TotalCrossSection" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 5, 2 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TotalCrossSection( std::move( boundaries ),
                                         std::move( wrongInterpolants ),
                                         std::move( x ),
                                         std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TotalCrossSection( begin, end, lineNumber,
                                         9228, 13, 18 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
  " 0.000000+0 0.000000+0          0          0          1          2922813 18     \n"
  "          2          5                                            922813 18     \n"
  " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922813 18     \n";
}

void verifyChunk( const TotalCrossSection& chunk ) {

  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 5 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 5 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.x().size() );
  CHECK( 2 == chunk.XS().size() );
  CHECK( 2 == chunk.crossSections().size() );
  CHECK( 2 == chunk.y().size() );
  CHECK_THAT( 1., WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.x()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.XS()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.XS()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSections()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.y()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.y()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          2922813 18     \n"
    "          2          2                                            922813 18     \n"
    " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n";
}
