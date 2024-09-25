void  generateArrays() {

  this->arrays_.clear();

  using namespace njoy::tools;

  auto chunks = Base::list() | std23::views::chunk( 2 + this->NA() );

  for ( auto&& chunk : chunks ) {

    this->arrays_.emplace_back( chunk.begin() + 2, chunk.end() );
  }
}
