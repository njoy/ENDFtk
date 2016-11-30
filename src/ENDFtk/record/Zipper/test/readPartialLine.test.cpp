#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

SCENARIO( "The Zipper readPartialLine function", "[ENDFtk], [Zipper]" ){
  GIVEN("a partial line with zipped default values" ){
    std::string line = 
      " 1.000000+0          1 2.000000+0          2 0.000000+0          0 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, Integer<11> >;

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    std::array< double, 2 > dsink;
    std::array< long, 2 > isink;

    auto iteratorTuple = std::make_tuple( dsink.begin(), isink.begin() );

    WHEN("passed to the zipper's readPartialLine function"){
      THEN( "values will be correct"){
        Zipper::readPartialLine< Zip >
          ( 2, iteratorTuple, it, end, lineNumber, 125, 1, 451,
            Zip::tupleIndices );
        for ( int i = 0; i < 2; ++i ){
          REQUIRE( dsink[i] == double(i + 1) );
          REQUIRE( isink[i] == i + 1 );
        }
      }

      THEN( "the function will throw if the line contains too many tuples"){
        REQUIRE_THROWS( Zipper::readPartialLine< Zip >
                        ( 1, iteratorTuple, it, end, lineNumber, 125, 1, 451,
                          Zip::tupleIndices ) );
      }
    }
  }
}
