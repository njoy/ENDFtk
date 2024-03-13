// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/record/skip.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

SCENARIO( "Skipping records" ) {

  GIVEN( "A string with a number of lines" ) {

    std::string line =
      " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 1451    1\n"
      " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1 125 1451    1\n"
      " 1.300000+1 1.400000+1                                             125 1451    1\n";

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    WHEN( "skipping records" ) {

      THEN( "The records can be skipped" ) {

        record::skip(it, end, lineNumber);
        record::skip(it, end, lineNumber);
        record::skip(it, end, lineNumber);
        CHECK( it == end );
        CHECK( 3 == lineNumber );
      } // THEN

      THEN( "an exception is thrown with there isn't enough characters" ) {

        std::string line =
          " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0 125 14";
        auto it = line.begin();
        auto end = line.end();
        auto lineNumber = 0l;
        CHECK_THROWS( record::skip(it, end, lineNumber) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
