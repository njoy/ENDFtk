long NC() const {
  long NC = 1;
  for ( auto& entry : this->subsections_ ) { NC += entry.NC(); }
  return NC;
} 

