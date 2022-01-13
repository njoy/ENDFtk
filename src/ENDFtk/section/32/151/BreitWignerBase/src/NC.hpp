/**
 *  @brief Return the number of lines in this MF2 MT151 component
 */
long NC() const {

  long NC = this->ISR() ? 2 : 1;
  for ( const auto& lvalue : this->lvalues_ ) { NC += lvalue.NC(); }
  return NC;
};
