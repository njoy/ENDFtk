/**
 *  @brief Return the number of lines in this MF33 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->reactions_ ) { NC += entry.NC(); }
  return NC;
};
