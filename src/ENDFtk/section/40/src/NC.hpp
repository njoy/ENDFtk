/**
 *  @brief Return the number of lines in this MF40 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->levelBlocks_ ) { NC += entry.NC(); }
  return NC;
};
