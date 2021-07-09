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

  GIVEN( "valid data for the DataRecord" ) {

    WHEN( "the data is given as a string" ) {

      std::string data = chunk();
      auto begin = data.begin();
      auto end = data.end();
      long lineNumber = 10;

      THEN( "the record can be constructed" ) {

        DataRecord record( begin, end, lineNumber, 9228, 3, 1 );
        verifyRecord( record );

      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly" ) {

      std::vector<double> data = { 1.0, 2.0, 3.0, 4.0 };

      THEN( "the record can be constructed" ) {

        DataRecord record( 293.6, 2, 1, 5, std::move( data ) );
        verifyRecord( record );

      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk(){

  return
    " 2.936000+2 0.000000+0          2          1          4          59228 3  1   10\n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 3  1   11\n";

}

void verifyRecord( DataRecord record ) {
  CHECK( 293.6 == Approx( record.TEMP() ) );
  CHECK( 293.6 == Approx( record.temperature() ) );
  CHECK( 2 == record.NG2() );
  CHECK( 2 == record.numberSecondaryPositions() );
  CHECK( 1 == record.IG2LO() );
  CHECK( 1 == record.lowestPosition() );
  CHECK( 4 == record.NW() );
  CHECK( 4 == record.numberWords() );
  CHECK( 5 == record.IG() );
  CHECK( 5 == record.groupIndex() );
  CHECK( 1.0 == Approx( record.list()[0] ) );
  CHECK( 2.0 == Approx( record.list()[1] ) );
  CHECK( 2.0 == Approx( record.data(0)[1] ) );
  CHECK( 4.0 == Approx( record.data(1)[1] ) );

}
