/**
 *  @brief Return the number of lines in this MF7 MT451 component
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->elements_ ) {

    NC += entry.NC();
  }
  return NC;
};
