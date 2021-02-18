#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/gendf/DataRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk::gendf;

// forward declarations
std::string chunk();
void verifyRecord( DataRecord );

// tests
SCENARIO( "DataRecord tests") {

  GIVEN( "a string representing the DataRecord" ) {

    std::string data = chunk();
    auto begin = data.begin();
    auto end = data.end();
    long lineNumber = 10;

    THEN( "the record can be constructed" ) {

      DataRecord record( begin, end, lineNumber, 9228, 3, 1 );

      AND_THEN( "we can get the data from it" ) {
        verifyRecord( record );

      } // AND_THEN
    } // THEN
  } // GIVEN

  WHEN( "the record is created from parameters" ) {

    THEN( "the record can be constructed" ) {

      std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
      DataRecord record( 293.6, 2, 1, 5, std::move(data) );

      AND_THEN( "we can get the data from it" ) {
        verifyRecord( record );

      } // AND_THEN
    } // THEN
  } // WHEN

} // SCENARIO

std::string chunk(){

  return
    " 2.936000+2 0.000000+0          2          1          4          59228 3  1   10\n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 3  1   11\n";

}

void verifyRecord( DataRecord record ) {
  REQUIRE( 293.6 == Approx( record.TEMP() ) );
  REQUIRE( 293.6 == Approx( record.temperature() ) );
  REQUIRE( 2 == record.NG2() );
  REQUIRE( 2 == record.numSecondaryPositions() );
  REQUIRE( 1 == record.IG2LO() );
  REQUIRE( 1 == record.lowestPosition() );
  REQUIRE( 4 == record.NW() );
  REQUIRE( 4 == record.numWords() );
  REQUIRE( 5 == record.IG() );
  REQUIRE( 5 == record.groupIndex() );
  REQUIRE( 1.0 == Approx( record.list()[0] ) );
  REQUIRE( 2.0 == Approx( record.list()[1] ) );
  REQUIRE( 2.0 == Approx( record.data(0)[1] ) );
  REQUIRE( 4.0 == Approx( record.data(1)[1] ) );

}
