#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation::record;

SCENARIO( "The Zipper unzip function", "[ENDFtk], [Zipper]" ){
  GIVEN("a record with zipped values" ){
    std::string line = 
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n"
      " 4.000000+0          4 5.000000+0          5 6.000000+0          6 125 1451    1\n"
      " 7.000000+0          7                                             125 1451    1\n";

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    WHEN("passed to the zipper's unzip function"){
      THEN( "extracted values will be correct"){
        auto vectors = Zipper::unzip< Real, Integer<11> >
          ( 7, it, end, lineNumber, 125, 1, 451 );
        for ( int i = 0; i < 7; ++i ){
          REQUIRE( std::get< 0 >( vectors )[i] == double(i + 1) );
          REQUIRE( std::get< 1 >( vectors )[i] == i + 1 );
        }
      }
    }
  }
}
