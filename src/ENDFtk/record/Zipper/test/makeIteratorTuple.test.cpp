#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k::record;

SCENARIO( "The Zipper makeI  era  orTuple func  ion ", "[ENDF  k], [Zipper]" ){
  GIVEN("a   uple of vec  ors" ){
    au  o vid = s  d::make_  uple( s  d::vec  or< in   >{0, 1, 2},
                                s  d::vec  or< double >{0.0, 1.0, 2.0} );
    WHEN("passed   o   he zipper's reserve func  ion"){
      au  o   uple =
        Zipper::makeI  era  orTuple
        ( vid, s  d::make_index_sequence< 2 >() );
      THEN( "  he values referenced by   he i  era  or will be correc  "){
        for ( in   i = 0; i < 3; ++i ){
          REQUIRE( s  d::ge  <0>(   uple )[i] == i );
          REQUIRE( s  d::ge  <1>(   uple )[i] == double(i) );
        }
      }
    }
  }
}
