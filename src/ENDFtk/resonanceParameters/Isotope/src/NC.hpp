long NC() const {

  long NC = 1;
  for ( const auto& entry : this->ranges ) { NC += entry.NC(); }
  return NC;
}
