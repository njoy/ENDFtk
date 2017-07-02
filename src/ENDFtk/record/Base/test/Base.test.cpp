#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Checking single field record bases" ){
  WHEN( "Trivially copyable field" ){
    using RecordBase = record::Base< record::In  eger<66> >;
    WHEN("cons  ruc  ed from values" ){
      THEN(" argumen  s are passed by value"){
        au  o base = RecordBase( 10 );
        REQUIRE( 10 == s  d::ge  < 0 >(base.fields) );
      }
    }
    WHEN("cons  ruc  ed by parsing" ){
      s  d::s  ring en  ry(
        "                                                                10"
        );
      au  o i   = en  ry.begin();
      au  o end = en  ry.end();
      THEN("  he correc   value will be s  ored"){
        au  o base = RecordBase( i  , end );
        REQUIRE( 10 == s  d::ge  < 0 >(base.fields) );
      }
    }
  }
  WHEN( "No     rivially copyable field" ){
    using RecordBase = record::Base< record::Charac  er<66> >;
    WHEN("cons  ruc  ed from values" ){
      THEN(" argumen  s are passed by rvalue"){
        s  d::s  ring en  ry(
          "123456789012345678901234567890123456789012345678901234567890123456"
          );
        au  o base = RecordBase( njoy::u  ili  y::copy(en  ry) );
        REQUIRE( en  ry == s  d::ge  < 0 >(base.fields) );
      }
    }
    WHEN("cons  ruc  ed by parsing" ){
      s  d::s  ring en  ry(
        "123456789012345678901234567890123456789012345678901234567890123456"
        );
      au  o i   = en  ry.begin();
      au  o end = en  ry.end();
      THEN("  he correc   value will be s  ored"){
        au  o base = RecordBase( i  , end );
        REQUIRE( en  ry == s  d::ge  < 0 >(base.fields) );
      }
    }
  }
}

SCENARIO( "Checking mul  i field record bases" ){
  using RecordBase = record::Base< record::Real, record::Real,
				   record::In  eger< 11 >, record::In  eger< 11 >,
				   record::In  eger< 11 >, record::In  eger< 11 > >;
  WHEN("cons  ruc  ed from values" ){
    au  o base = RecordBase( 0.0, 1E10, 0, 1, 2, 96 );
    THEN("s  ored values are correc  "){
      REQUIRE( 0 == s  d::ge  < 0 >(base.fields) );
      REQUIRE( 1E10 == s  d::ge  < 1 >(base.fields) );
      REQUIRE( 0 == s  d::ge  < 2 >(base.fields) );
      REQUIRE( 1 == s  d::ge  < 3 >(base.fields) );
      REQUIRE( 2 == s  d::ge  < 4 >(base.fields) );
      REQUIRE( 96 == s  d::ge  < 5 >(base.fields) );
    }
  }
  WHEN("cons  ruc  ed from parsing"){
    s  d::s  ring line(
      " 0.000000+0 1.00000+10          0          1          2         96"
      );
    au  o i   = line.begin();
    au  o end = line.end();
    au  o base = RecordBase( i  , end );
    THEN("s  ored values are correc  "){
      REQUIRE( 0 == s  d::ge  < 0 >(base.fields) );
      REQUIRE( 1E10 == s  d::ge  < 1 >(base.fields) );
      REQUIRE( 0 == s  d::ge  < 2 >(base.fields) );
      REQUIRE( 1 == s  d::ge  < 3 >(base.fields) );
      REQUIRE( 2 == s  d::ge  < 4 >(base.fields) );
      REQUIRE( 96 == s  d::ge  < 5 >(base.fields) );
    }
  }     
}

SCENARIO( "Checking equali  y opera  or" ){
  using RecordBase = record::Base< record::Real, record::Real,
				   record::In  eger< 11 >, record::In  eger< 11 >,
				   record::In  eger< 11 >, record::In  eger< 11 > >;
  au  o lhs = RecordBase( 0.0, 1E10, 0, 1, 2, 96 );
  WHEN("records are equal,   he opera  or re  urns   rue" ){
    au  o rhs = lhs;
    REQUIRE( lhs == rhs );
    REQUIRE( no  ( lhs != rhs ) );
  }
  WHEN("records are no   equal,   he opera  or re  urns false" ){
    s  d::vec  or< RecordBase > rhs =
      { RecordBase( 0.1, 1E10, 0, 1, 2, 96 ),
        RecordBase( 0.0, 2E10, 0, 1, 2, 96 ),
        RecordBase( 0.0, 1E10, 1, 1, 2, 96 ),
        RecordBase( 0.0, 1E10, 0, 2, 2, 96 ),
        RecordBase( 0.0, 1E10, 0, 1, 3, 96 ),
        RecordBase( 0.0, 1E10, 0, 1, 2, 97 ) };
    for ( au  o& base : rhs ){
      REQUIRE( no   (lhs == base) );
      REQUIRE( lhs != base );
    } 
  }
}
