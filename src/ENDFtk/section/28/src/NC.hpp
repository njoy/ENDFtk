/**
 *  @brief Return the number of lines in this MF28 component
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->subshells_ ) {

    NC += entry.NC();
  }
  return NC;
};
