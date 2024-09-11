void  generateSandT() {

  this->s_.clear();
  this->t_.clear();
  this->s_.push_back( this->principal_.y() );
  this->t_.push_back( this->principal_.C1() );
  for ( auto&& list : this->temperatures_ ) {

    this->s_.push_back( list.list() );
    this->t_.push_back( list.C1() );
  }
}
