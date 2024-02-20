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
