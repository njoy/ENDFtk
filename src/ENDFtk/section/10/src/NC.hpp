/**
 *  @brief Return the number of lines in this MF10 component
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->products_ ) {

    NC += entry.NC();
  }
  return NC;
};
