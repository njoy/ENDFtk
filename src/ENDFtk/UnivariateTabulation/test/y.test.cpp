#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation yValue",
          "[ENDFtk], [UnivariateTabulation]" ){
  GIVEN( "a reference TAB1 record and it's y-values" ){
    auto tab1 = makeTAB1();
    std::vector< double > yValues{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

    THEN( "the result of y() returns a type with a array-like api" ){
      // indexing, with and without bounds checking
      for ( long index = 0; index < tab1.NP(); ++index ){
        REQUIRE( yValues[ index ] == tab1.y().at( index ) );
        REQUIRE( yValues[ index ] == tab1.y()[ index ] );
      }
  
      REQUIRE_THROWS( tab1.y().at( -1 ) );
      REQUIRE_THROWS( tab1.y().at( tab1.NP() ) );

      // provides random access iterators
      REQUIRE( *(tab1.y().begin()) == 3.0 );
      REQUIRE( tab1.y().begin()[2] == 5.0 );
      REQUIRE( tab1.y().end() - tab1.y().begin() == 6 );

      // is iterable
      int index = 0;
      for ( auto y : tab1.y() ){ REQUIRE( y == tab1.y()[ index++ ] ); }

      // knows size
      REQUIRE( tab1.y().size() == size_t(tab1.NP()) );
    }

    THEN( "the result of y() will be a light-weight reference object" ){
      // ys is a view object, a non-owning "slice" of a container
      auto ys = tab1.y();

      // because they don't own data, views are small and live on the stack
      REQUIRE( sizeof( ys ) == 16 );

      // so we can copy them willy-nilly
      auto ys2 = ys;
      REQUIRE( ranges::equal( ys2, ys ) );
      
      // no more worrying about accidentally copying large vectors!
    }
  }
}
