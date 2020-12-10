/**
 *  @brief Return the number of lines in this MF1/MT458 section
 */
long NC() const {

  long NC = 0;
  for ( auto& entry : this->photons_ ) { NC += entry.NC(); }
  return NC;
}
