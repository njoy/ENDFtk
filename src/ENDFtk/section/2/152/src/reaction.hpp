auto reaction( unsigned int i ) const {

  using namespace njoy::tools;
  unsigned int nreac = this->data_.L1();
  unsigned int nsigz = this->data_.L2();
  auto chunks = this->data_.list()
                  | std20::views::drop( nsigz )
                  | std23::views::chunk( 1 + nsigz * nreac )
                  | std20::views::transform(
                      [=] ( const auto& chunk )
                          { return chunk | std20::views::drop( 1 )
                                         | std23::views::chunk( nsigz ); } );

  return chunks | std20::views::transform(
                      [=] ( const auto& reactions )
                          { return reactions[i]; } );
}
