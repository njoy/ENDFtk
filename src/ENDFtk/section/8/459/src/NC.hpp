/**
 *  @brief Return the number of lines in this MF7/MT2 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->data_ ) { NC += entry.NC(); }
  return NC;
};
