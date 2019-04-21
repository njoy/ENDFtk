long NC() const {

  long NC = 1;
  for ( auto& entry : this->isotopes ) { NC += entry.NC(); }
  return NC;
} 

