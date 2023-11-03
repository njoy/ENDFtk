/**
 *  @brief Return the number of lines in this MF32 MT151 component
 */
long NC() const {

  long NC = 1;
  for ( const auto& group : this->parameters_ ) { NC += group.NC(); }
  NC += this->covariance_.NC();
  return NC;
};
