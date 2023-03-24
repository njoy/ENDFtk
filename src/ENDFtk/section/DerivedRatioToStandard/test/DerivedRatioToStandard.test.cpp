#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/DerivedRatioToStandard.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DerivedRatioToStandard = section::DerivedRatioToStandard;

std::string chunk();
void verifyChunk( const DerivedRatioToStandard& );


SCENARIO( "DerivedRatioToStandard" ) {

  GIVEN( "valid data for a DerivedRatioToStandard" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = {1, 2};
      std::vector< double > weights = {3, 4};


      DerivedRatioToStandard chunk( 1, 2.5e+3, 2.0e+7,
                              325, 102, 3, 0,
                              std::move(energies),
                              std::move(weights) );

      THEN( "a DerivedRatioToStandard can be constructed "
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

      DerivedRatioToStandard chunk( begin, end, lineNumber, 9437, 33, 2 );

      THEN( "a DerivedRatioToStandard object can be constructed "
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


  GIVEN( "invalid data for a DerivedRatioToStandard" ) {

    WHEN( "inconsistent lengths are given" ) {

      double lower = 2.500000e+3;
      double upper = 2.000000e+7;
      std::vector< double > energies = {1, -1, -1, -1, -1, -1};
      std::vector< double > weights = {1, 4, 16, 17, 18, 37, 102};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          DerivedRatioToStandard( 1, lower, upper,
                            325, 102, 3., 0.,
                            std::move(energies),
                            std::move(weights) ) );
      } // THEN
    } // WHEN

  } // GIVEN


} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          1          0          0943733  2     \n"
    " 2.500000+3 2.000000+7        325        102          6          2943733  2     \n"
    " 3.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+0 4.000000+0943733  2     \n";
}

void verifyChunk( const DerivedRatioToStandard& chunk ) {

  // metadata
  CHECK( 1 == chunk.LTY() );
  CHECK( 1 == chunk.procedure() );
  CHECK( 2.5e3 == Approx( chunk.E1() ) );
  CHECK( 2.5e3 == Approx( chunk.lowerEnergy() ) );
  CHECK( 2.0e7 == Approx( chunk.E2() ) );
  CHECK( 2.0e7 == Approx( chunk.upperEnergy() ) );
  CHECK( 325 == chunk.MATS() );
  CHECK( 325 == chunk.standardMaterialNumber() );
  CHECK( 102 == chunk.MTS() );
  CHECK( 102 == chunk.standardSectionNumber() );
  CHECK( 3 == Approx( chunk.XMFS() ) );
  CHECK( 3 == Approx( chunk.standardFileNumber() ) );
  CHECK( 0 == Approx( chunk.XLFSS() ) );
  CHECK( 0 == Approx( chunk.standardFinalExcitedState() ) );

  // values
  CHECK( 1.0 == Approx( chunk.energies()[0] ) );
  CHECK( 2.0 == Approx( chunk.energies()[1] ) );
  CHECK( 2.0 == Approx( chunk.EI()[1] ) );
  CHECK( 3.0 == Approx( chunk.weights()[0] ) );
  CHECK( 4.0 == Approx( chunk.weights()[1] ) );
  CHECK( 4.0 == Approx( chunk.WEI()[1] ) );

  CHECK( 3 == chunk.NC() );

}
