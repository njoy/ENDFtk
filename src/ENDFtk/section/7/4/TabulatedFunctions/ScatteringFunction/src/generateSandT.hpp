void  generateSandT() {

  this->s_.clear();
  this->t_.clear();

  this->s_.reserve( this->numberTemperatures() );
  this->t_.reserve( this->numberTemperatures() );

  this->s_.emplace_back( this->alphas_.y() );
  this->t_.push_back( this->alphas_.C1() );
  for ( auto&& list : this->temperatures_ ) {

    this->s_.emplace_back( list.list() );
    this->t_.push_back( list.C1() );
  }
}
