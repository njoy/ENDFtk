/**
 *  @brief Return the number of lines in this MF40 subsection
 */
long NC() const {

  long result = 1;

  for ( const auto& block : this->reactions_ ) {
    result += block.NC();
  }

  return result;

}
