/**
 *  @brief Return the number of lines in this MF35 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->energyBlocks_ ) { NC += entry.NC(); }
  return NC;
};
