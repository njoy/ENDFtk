long NC() const {
  long NC = 0;
  for ( auto& entry : this->photons_ ) { NC += entry.NC(); }
  return NC;
}

