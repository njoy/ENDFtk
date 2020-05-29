/**
 *  @brief Return the number of lines in this MF2 MT151 component
 */
long NC() const {

  long NC = this->energies_.NC();
  for ( const auto& lvalue : this->lValues() ) { NC += lvalue.NC(); }
  return NC;
};
