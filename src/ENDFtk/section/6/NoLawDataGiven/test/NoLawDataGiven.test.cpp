// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using NoLawDataGiven =
section::Type< 6 >::NoLawDataGiven;

class TestNoLawDataGiven : public NoLawDataGiven {
public:
  TestNoLawDataGiven() : NoLawDataGiven() {};
};

SCENARIO( "NoLawDataGiven" ) {

  GIVEN( "a string representation of a valid NoLawDataGiven" ) {

    THEN( "a NoLawDataGiven can be constructed and members can be tested" ) {
      TestNoLawDataGiven chunk;

      CHECK( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of NoLawDataGiven" ) {

    TestNoLawDataGiven chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      CHECK( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO
