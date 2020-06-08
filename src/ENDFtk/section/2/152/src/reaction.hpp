auto reaction( unsigned int i ) const {

  unsigned int nsigz = this->data_.L2();
  auto chunks = this->data_.list()
                  | ranges::view::drop_exactly( nsigz )
                  | ranges::view::chunk( 1 + nsigz * 5 )
                  | ranges::view::transform(
                      [=] ( const auto& chunk )
                          { return chunk | ranges::view::drop_exactly( 1 )
                                         | ranges::view::chunk( nsigz ); } );

  return chunks | ranges::view::transform( [=] ( const auto& reactions )
                                               { return reactions[i]; } );
}
