long NC() const {
  long NC = this->interpolation_.NC();
  for ( auto& entry : this->lists_ ) { NC += entry.NC(); }
  return NC;
}

