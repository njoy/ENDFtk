#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
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

      REQUIRE( 0 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of NoLawDataGiven" ) {

    TestNoLawDataGiven chunk;

    THEN( "it does not print anything" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer.size() == 0 );
    }
  } // GIVEN
} // SCENARIO

