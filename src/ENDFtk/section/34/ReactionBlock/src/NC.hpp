/**
 *  @brief Return the number of lines in this MF34 subsection
 */
long NC() const {

  long result = 1;

  for ( auto& block : this->lblocks_ ) {
    result += block.NC();
  }

  return result;

}
