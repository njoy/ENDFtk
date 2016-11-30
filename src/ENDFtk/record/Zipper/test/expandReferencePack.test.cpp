#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

SCENARIO( "The Zipper expandReferencePack function", "[ENDFtk], [Zipper]" ){
  GIVEN("a line with zipped values" ){
    std::string line = 
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, Integer<11> >;

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    auto pack =
      Zipper::ReadingPack< decltype(it) >( it, end, lineNumber, 125, 1, 451 );
    std::array< double, 3 > dsink;
    std::array< long, 3 > isink;

    auto iteratorTuple = std::make_tuple( dsink.begin(), isink.begin() );

    WHEN("passed to the zipper's expandReferencePack function"){
      THEN( "values will be correct"){
        Zipper::expandReferencePack< Zip >
          ( pack, iteratorTuple, std::true_type(), Zip::tupleIndices );
        for ( int i = 0; i < 3; ++i ){
          REQUIRE( dsink[i] == double(i + 1) );
          REQUIRE( isink[i] == i + 1 );
        }
      }
    }
  }
}
