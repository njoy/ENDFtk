void  generateSandT() {

  this->s_.push_back( this->alphas_.y() );
  this->t_.push_back( this->alphas_.C1() );
  for ( auto&& list : this->temperatures_ ) {

    this->s_.push_back( list.list() );
    this->t_.push_back( list.C1() );
  }
}
