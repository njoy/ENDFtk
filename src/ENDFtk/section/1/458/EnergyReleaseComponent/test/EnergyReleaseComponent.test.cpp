// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/458.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using EnergyReleaseComponent = section::Type< 1, 458 >::EnergyReleaseComponent;

std::string chunk();
void verifyChunk( const EnergyReleaseComponent& );
std::string invalidLDRV();
std::string invalidIFC();

SCENARIO( "EnergyReleaseComponent" ) {

  GIVEN( "valid data for a EnergyReleaseComponent" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      bool ldrv = true;
      int ifc = 1;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1.000000e-5, 2.530000e-2, 2.000000e+7 };
      std::vector< double > qvalues = { 1.691300e+8, 1.691000e+8, 1.690000e+8 };

      EnergyReleaseComponent chunk( ldrv, ifc,
                                    std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( energies ),
                                    std::move( qvalues ) );

      THEN( "an EnergyReleaseComponent can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 458 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      EnergyReleaseComponent chunk( begin, end, lineNumber, 9228, 1, 458 );

      THEN( "a EnergyReleaseComponent can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 458 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a EnergyReleaseComponent" ) {

    WHEN( "data with an invalid IFC is given" ) {

      bool ldrv = true;
      int wrong = 10;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1.000000e-5, 2.530000e-2, 2.000000e+7 };
      std::vector< double > qvalues = { 1.691300e+8, 1.691000e+8, 1.690000e+8 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyReleaseComponent( ldrv, wrong,
                                              std::move( boundaries ),
                                              std::move( interpolants ),
                                              std::move( energies ),
                                              std::move( qvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid IFC" ) {

      std::string string = invalidIFC();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyReleaseComponent( begin, end, lineNumber,
                                             9228, 1, 458 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an invalid LDRV" ) {

      std::string string = invalidLDRV();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( EnergyReleaseComponent( begin, end, lineNumber,
                                             9228, 1, 458 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          1          1          39228 1458     \n"
    "          3          2                                            9228 1458     \n"
    " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n";
}

void verifyChunk( const EnergyReleaseComponent& chunk ) {

  CHECK( true == chunk.LDRV() );
  CHECK( true == chunk.primaryEvaluationFlag() );
  CHECK( 1 == chunk.IFC() );
  CHECK( 1 == chunk.componentIndex() );

  CHECK( 3 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 3 == chunk.E().size() );
  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.EIFC().size() );
  CHECK( 3 == chunk.qValues().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.E()[2] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.6913e+8, WithinRel( chunk.EIFC()[0] ) );
  CHECK_THAT( 1.691e+8, WithinRel( chunk.EIFC()[1] ) );
  CHECK_THAT( 1.69e+8, WithinRel( chunk.EIFC()[2] ) );
  CHECK_THAT( 1.6913e+8, WithinRel( chunk.qValues()[0] ) );
  CHECK_THAT( 1.691e+8, WithinRel( chunk.qValues()[1] ) );
  CHECK_THAT( 1.69e+8, WithinRel( chunk.qValues()[2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidLDRV() {
  return
  " 0.000000+0 0.000000+0          0          1          1          39228 1458     \n"
  "          3          2                                            9228 1458     \n"
  " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n";
}

std::string invalidIFC() {
  return
  " 0.000000+0 0.000000+0          2         10          1          39228 1458     \n"
  "          3          2                                            9228 1458     \n"
  " 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n";
}
