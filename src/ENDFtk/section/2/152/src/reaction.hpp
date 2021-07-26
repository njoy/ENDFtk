auto reaction( unsigned int i ) const {

  unsigned int nreac = this->data_.L1();
  unsigned int nsigz = this->data_.L2();
  auto chunks = this->data_.list()
                  | ranges::views::drop_exactly( nsigz )
                  | ranges::views::chunk( 1 + nsigz * nreac )
                  | ranges::cpp20::views::transform(
                      [=] ( const auto& chunk )
                          { return chunk | ranges::views::drop_exactly( 1 )
                                         | ranges::views::chunk( nsigz ); } );

  return chunks | ranges::cpp20::views::transform(
                      [=] ( const auto& reactions )
                          { return reactions[i]; } );
}
