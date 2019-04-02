long NC() const {
  long NC = 1;
  for ( const auto& entry : this->products_ ) { NC += entry.NC(); }
  return NC;
};

