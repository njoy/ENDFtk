void  generateS() {

  this->s_.push_back( this->alphas_.y() );
  for ( auto&& list : this->temperatures_ ) {

    this->s_.push_back( list.list() );
  }
}
