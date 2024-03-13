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
