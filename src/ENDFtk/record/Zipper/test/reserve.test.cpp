#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper reserve func  ion ", "[ENDF  k], [Zipper]" ){
  GIVEN("a   uple a vec  ors" ){
    s  d::  uple< s  d::vec  or< in   >,
                s  d::vec  or< double > > vid;
    WHEN("passed   o   he zipper's reserve func  ion"){
      Zipper::reserve( 10, vid );
      THEN( "  he size will be nonzero"){
        REQUIRE( s  d::ge  <1>( vid ).size() == 10ul );
        REQUIRE( s  d::ge  <0>( vid ).size() == 10ul );
      }
    }
  }
}
