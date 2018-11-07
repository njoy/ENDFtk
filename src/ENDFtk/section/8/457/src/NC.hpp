long NC() const {
  long NC = 1;
  NC += this->energies_.NC();
  NC += this->modes_.NC();
  for ( const auto& entry : this->spectra_ ) { NC += entry.NC(); }
  return NC;
};
