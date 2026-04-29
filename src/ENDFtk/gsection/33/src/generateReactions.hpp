void generateReactions() {

  this->reactions_.clear();
  this->reactions_.resize( this->covariances_.size() );
  std::transform( this->covariances_.begin(), this->covariances_.end(),
                  this->reactions_.begin(),
                  [] ( auto&& pair ) { return pair.first; } );
}
