// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/DerivedRedundant.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DerivedRedundant = section::DerivedRedundant;

std::string chunk();
void verifyChunk( const DerivedRedundant& );


SCENARIO( "DerivedRedundant" ) {

  GIVEN( "valid data for a DerivedRedundant" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double lower = 2.500000e+3;
      double upper = 2.000000e+7;
      std::vector< double > coefficients = {1, -1, -1, -1, -1, -1, -1};
      std::vector< int > reactions = {1, 4, 16, 17, 18, 37, 102};


      DerivedRedundant chunk( lower, upper,
                              std::move(coefficients),
                              std::move(reactions) );

      THEN( "a DerivedRedundant can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DerivedRedundant chunk( begin, end, lineNumber, 9437, 33, 2 );

      THEN( "a DerivedRedundant object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 33, 2 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

  } // GIVEN


  GIVEN( "invalid data for a DerivedRedundant" ) {

    WHEN( "inconsistent lengths are given" ) {

      double lower = 2.500000e+3;
      double upper = 2.000000e+7;
      std::vector< double > coefficients = {1, -1, -1, -1, -1, -1};
      std::vector< int > reactions = {1, 4, 16, 17, 18, 37, 102};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          DerivedRedundant( lower, upper,
                            std::move(coefficients),
                            std::move(reactions) ) );
      } // THEN
    } // WHEN

  } // GIVEN


} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          0          0943733  2     \n"
    " 2.500000+3 2.000000+7          0          0         14          7943733  2     \n"
    " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943733  2     \n"
    "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943733  2     \n"
    "-1.000000+0 1.020000+2                                            943733  2     \n";
}

void verifyChunk( const DerivedRedundant& chunk ) {

  // metadata
  CHECK( 0 == chunk.LTY() );
  CHECK( 0 == chunk.procedure() );
  CHECK_THAT( 2.5e3, WithinRel( chunk.E1() ) );
  CHECK_THAT( 2.5e3, WithinRel( chunk.lowerEnergy() ) );
  CHECK_THAT( 2.0e7, WithinRel( chunk.E2() ) );
  CHECK_THAT( 2.0e7, WithinRel( chunk.upperEnergy() ) );
  CHECK( 7 == chunk.NCI() );
  CHECK( 7 == chunk.numberReactions() );

  // values
  CHECK_THAT( 1.0, WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[1] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[2] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[3] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[4] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[5] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.coefficients()[6] ) );
  CHECK_THAT( -1.0, WithinRel( chunk.CI()[6] ) );
  CHECK_THAT( 1., WithinRel( chunk.reactions()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.reactions()[1] ) );
  CHECK_THAT( 16., WithinRel( chunk.reactions()[2] ) );
  CHECK_THAT( 17., WithinRel( chunk.reactions()[3] ) );
  CHECK_THAT( 18., WithinRel( chunk.reactions()[4] ) );
  CHECK_THAT( 37., WithinRel( chunk.reactions()[5] ) );
  CHECK_THAT( 102., WithinRel( chunk.reactions()[6] ) );
  CHECK_THAT( 102., WithinRel( chunk.XMTI()[6] ) );

  CHECK( 5 == chunk.NC() );

}
