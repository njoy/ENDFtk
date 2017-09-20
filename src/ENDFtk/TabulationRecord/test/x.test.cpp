#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< TabulationRecord() > makeTAB1;

SCENARIO( "TabulationRecord x command",
          "[ENDFtk], [TabulationRecord]" ){
  GIVEN( "a reference TAB1 record and it's x-values" ){

    auto tab1 = makeTAB1();
    std::vector< double > xValues{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    THEN( "the result of x() returns a type with a array-like api" ){
      // indexing, with and without bounds checking
      for ( long index = 0; index < tab1.NP(); ++index ){
        REQUIRE( xValues[ index ] == tab1.x().at( index ) );
        REQUIRE( xValues[ index ] == tab1.x()[ index ] );
      }
  
      REQUIRE_THROWS( tab1.x().at( -1 ) );
      REQUIRE_THROWS( tab1.x().at( tab1.NP() ) );

      // provides random access iterators
      REQUIRE( *(tab1.x().begin()) == 1.0 );
      REQUIRE( tab1.x().begin()[2] == 3.0 );
      REQUIRE( tab1.x().end() - tab1.x().begin() == 6 );

      // is iterable
      int index = 0;
      for ( auto x : tab1.x() ){ REQUIRE( x == tab1.x()[ index++ ] ); }

      // knows size
      REQUIRE( tab1.x().size() == size_t(tab1.NP()) );
    }

    THEN( "the result of x() will be a light-weight reference object" ){
      // xs is a view object, a non-owning "slice" of a container
      auto xs = tab1.x();

      // because they don't own data, views are small and live on the stack
      REQUIRE( sizeof( xs ) == 16 );

      // so we can copy them willy-nilly
      auto xs2 = xs;
      REQUIRE( ranges::equal( xs2, xs ) );
      
      // no more worrying about accidentally copying large vectors!
    }
  }
}
