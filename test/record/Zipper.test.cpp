// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/record/Zipper.hpp"

// other includes

// convenience typedefs
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
          CHECK_THAT( dsink[i], WithinRel( double(i + 1) ) );
          CHECK( isink[i] == i + 1 );
        }
      }
    }
  }
}

SCENARIO( "The Zipper makeIteratorTuple function ", "[ENDFtk], [Zipper]" ){
  GIVEN("a tuple of vectors" ){
    auto vid = std::make_tuple( std::vector< int >{0, 1, 2},
                                std::vector< double >{0.0, 1.0, 2.0} );
    WHEN("passed to the zipper's reserve function"){
      auto tuple =
        Zipper::makeIteratorTuple
        ( vid, std::make_index_sequence< 2 >() );
      THEN( "the values referenced by the iterator will be correct"){
        for ( int i = 0; i < 3; ++i ){
          CHECK( std::get<0>( tuple )[i] == i );
          CHECK_THAT( std::get<1>( tuple )[i], WithinRel( double(i) ) );
        }
      }
    }
  }
}

SCENARIO( "The Zipper process function ", "[ENDFtk], [Zipper]" ){
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

    WHEN("passed to the zipper's process function"){
      THEN( "the extracted values will be correct"){
        Zipper::process< Zip >( pack, dsink[0], isink[0],
                                      dsink[1], isink[1],
                                      dsink[2], isink[2] );
        for ( int i = 0; i < 3; ++i ){
          CHECK_THAT( dsink[i], WithinRel( double(i + 1) ) );
          CHECK( isink[i] == i + 1 );
        }
      }
    }
  }
}

SCENARIO( "The Zipper readLine function", "[ENDFtk], [Zipper]" ){
  GIVEN("a line with zipped values" ){
    std::string line =
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, Integer<11> >;

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    std::array< double, 3 > dsink;
    std::array< long, 3 > isink;

    auto iteratorTuple = std::make_tuple( dsink.begin(), isink.begin() );

    WHEN("passed to the zipper's readLine function"){
      THEN( "values will be correct"){
        Zipper::readLine< Zip >
          ( iteratorTuple, it, end, lineNumber, 125, 1, 451 );
        for ( int i = 0; i < 3; ++i ){
          CHECK_THAT( dsink[i], WithinRel( double(i + 1) ) );
          CHECK( isink[i] == i + 1 );
        }
      }
    }
  }
}

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
          CHECK_THAT( dsink[i], WithinRel( double(i + 1) ) );
          CHECK( isink[i] == i + 1 );
        }
      }

      THEN( "the function will throw if the line contains too many tuples"){
        CHECK_THROWS( Zipper::readPartialLine< Zip >
                      ( 1, iteratorTuple, it, end, lineNumber, 125, 1, 451,
                        Zip::tupleIndices ) );
      }
    }
  }
}

SCENARIO( "The Zipper reserve function ", "[ENDFtk], [Zipper]" ){
  GIVEN("a tuple a vectors" ){
    std::tuple< std::vector< int >,
                std::vector< double > > vid;
    WHEN("passed to the zipper's reserve function"){
      Zipper::reserve( 10, vid );
      THEN( "the size will be nonzero"){
        CHECK( std::get<1>( vid ).size() == 10ul );
        CHECK( std::get<0>( vid ).size() == 10ul );
      }
    }
  }
}

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
          CHECK_THAT( std::get< 0 >( vectors )[i], WithinRel( double(i + 1) ) );
          CHECK( std::get< 1 >( vectors )[i] == i + 1 );
        }
      }
    }
  }
}
