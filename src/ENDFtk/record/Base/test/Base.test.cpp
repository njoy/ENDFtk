#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/record/Base.hpp"

// other includes
#include "header-utilities.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

SCENARIO( "Checking single field record bases" ){
  WHEN( "Trivially copyable field" ){
    using RecordBase = record::Base< record::Integer<66> >;
    WHEN("constructed from values" ){
      THEN(" arguments are passed by value"){
        auto base = RecordBase( 10 );
        REQUIRE( 10 == std::get< 0 >(base.fields) );
      }
    }
    WHEN("constructed by parsing" ){
      std::string entry(
        "                                                                10"
        );
      auto it = entry.begin();
      auto end = entry.end();
      THEN("the correct value will be stored"){
        auto base = RecordBase( it, end );
        REQUIRE( 10 == std::get< 0 >(base.fields) );
      }
    }
  }
  WHEN( "Not trivially copyable field" ){
    using RecordBase = record::Base< record::Character<66> >;
    WHEN("constructed from values" ){
      THEN(" arguments are passed by rvalue"){
        std::string entry(
          "123456789012345678901234567890123456789012345678901234567890123456"
          );
        auto base = RecordBase( njoy::utility::copy(entry) );
        REQUIRE( entry == std::get< 0 >(base.fields) );
      }
    }
    WHEN("constructed by parsing" ){
      std::string entry(
        "123456789012345678901234567890123456789012345678901234567890123456"
        );
      auto it = entry.begin();
      auto end = entry.end();
      THEN("the correct value will be stored"){
        auto base = RecordBase( it, end );
        REQUIRE( entry == std::get< 0 >(base.fields) );
      }
    }
  }
}

SCENARIO( "Checking multi field record bases" ){
  using RecordBase = record::Base< record::Real, record::Real,
           record::Integer< 11 >, record::Integer< 11 >,
           record::Integer< 11 >, record::Integer< 11 > >;
  WHEN("constructed from values" ){
    auto base = RecordBase( 0.0, 1E10, 0, 1, 2, 96 );
    THEN("stored values are correct"){
      REQUIRE( 0 == std::get< 0 >(base.fields) );
      REQUIRE( 1E10 == std::get< 1 >(base.fields) );
      REQUIRE( 0 == std::get< 2 >(base.fields) );
      REQUIRE( 1 == std::get< 3 >(base.fields) );
      REQUIRE( 2 == std::get< 4 >(base.fields) );
      REQUIRE( 96 == std::get< 5 >(base.fields) );
    }
  }
  WHEN("constructed from parsing"){
    std::string line(
      " 0.000000+0 1.00000+10          0          1          2         96"
      );
    auto it = line.begin();
    auto end = line.end();
    auto base = RecordBase( it, end );
    THEN("stored values are correct"){
      REQUIRE( 0 == std::get< 0 >(base.fields) );
      REQUIRE( 1E10 == std::get< 1 >(base.fields) );
      REQUIRE( 0 == std::get< 2 >(base.fields) );
      REQUIRE( 1 == std::get< 3 >(base.fields) );
      REQUIRE( 2 == std::get< 4 >(base.fields) );
      REQUIRE( 96 == std::get< 5 >(base.fields) );
    }
  }
}

SCENARIO( "Checking equality operator" ){
  using RecordBase = record::Base< record::Real, record::Real,
           record::Integer< 11 >, record::Integer< 11 >,
           record::Integer< 11 >, record::Integer< 11 > >;
  auto lhs = RecordBase( 0.0, 1E10, 0, 1, 2, 96 );
  WHEN("records are equal, the operator returns true" ){
    auto rhs = lhs;
    REQUIRE( lhs == rhs );
    REQUIRE( not( lhs != rhs ) );
  }
  WHEN("records are not equal, the operator returns false" ){
    std::vector< RecordBase > rhs =
      { RecordBase( 0.1, 1E10, 0, 1, 2, 96 ),
        RecordBase( 0.0, 2E10, 0, 1, 2, 96 ),
        RecordBase( 0.0, 1E10, 1, 1, 2, 96 ),
        RecordBase( 0.0, 1E10, 0, 2, 2, 96 ),
        RecordBase( 0.0, 1E10, 0, 1, 3, 96 ),
        RecordBase( 0.0, 1E10, 0, 1, 2, 97 ) };
    for ( auto& base : rhs ){
      REQUIRE( not (lhs == base) );
      REQUIRE( lhs != base );
    }
  }
}
