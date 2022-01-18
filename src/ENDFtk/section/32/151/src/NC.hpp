/**
 *  @brief Return the number of lines in this MF32/MT151 section
 */
long NC() const {

  long NC = 1;
  for ( auto& entry : this->isotopes() ) { NC += entry.NC(); }
  return NC;
}
