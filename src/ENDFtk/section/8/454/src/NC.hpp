/**
 *  @brief Return the number of lines in this MF87/MT454 or MF8/MT459 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->data_ ) { NC += entry.NC(); }
  return NC;
};
