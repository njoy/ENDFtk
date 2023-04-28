long NC() const {

  long NC = 1;
  for ( const auto& entry : this->ranges_ ) { NC += entry.NC(); }
  return NC;
}
