void  generateArrays() {

  this->reactions_.clear();

  using namespace njoy::tools;

  unsigned int nreac = this->data_.L1();
  unsigned int nsigz = this->data_.L2();
  this->reactions_ = std::vector< std::vector< Array > >( nreac );
  auto chunks = this->data_.list()
                  | std20::views::drop( nsigz )
                  | std23::views::chunk( 1 + nsigz * nreac );

  for ( auto&& chunk : chunks ) {

    auto begin = chunk.begin();
    for ( std::size_t i = 0; i < nreac; ++i ) {

      this->reactions_[i].emplace_back( begin + 1 + i * nsigz,
                                        begin + 1 + ( i + 1 ) * nsigz );
    }
  }
}
