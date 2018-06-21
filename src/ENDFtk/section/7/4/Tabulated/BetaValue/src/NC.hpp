long NC() const {
  long NC = this->alphas_.NC();
  for ( const auto& entry : this->temperatures_ ) { NC += entry.NC(); }
  return NC;
};

