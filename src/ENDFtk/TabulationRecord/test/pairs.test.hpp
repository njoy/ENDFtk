SCENARIO( "TabulationRecord pairs",
          "[ENDFtk], [TabulationRecord]" ){
  GIVEN( "a reference TAB1 record and it's x- and y-values" ){
    auto tab1 = makeTAB1();
    std::vector< double > xValues{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    std::vector< double > yValues{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

    THEN( "the result of pairs() returns a type mimicing an array of pairs" ){
      int index = 0;

      // indexing, with and without bounds checking
      for ( long index = 0; index < tab1.NP(); ++index ){
        REQUIRE( xValues[ index ] == tab1.pairs().at( index ).first );
        REQUIRE( yValues[ index ] == tab1.pairs().at( index ).second );
        REQUIRE( xValues[ index ] == tab1.pairs()[ index ].first );
        REQUIRE( yValues[ index ] == tab1.pairs()[ index ].second );
      }

      REQUIRE_THROWS( tab1.pairs().at( -1 ) );
      REQUIRE_THROWS( tab1.pairs().at( tab1.NP() ) );

      // the result is iterable
      for( auto pair : tab1.pairs() ){
        REQUIRE( pair.first == xValues[index] );
        REQUIRE( pair.second == yValues[index++] );
      }

      // knows size
      REQUIRE( tab1.pairs().size() == size_t(tab1.NP()) );
    }

    THEN( "the result of pairs() will be a light-weight reference object" ){
      // ys is a view object, a non-owning "slice" of a container
      auto pairs = tab1.pairs();

      // this zipped view is a bit expensive (5 doubles), but lives on the stack
      REQUIRE( sizeof( pairs ) == 40 );

      // so copying them isn't the end of the world
      auto pairs2 = pairs;
      REQUIRE( ranges::equal( pairs2, pairs ) );
    }
  }
}
