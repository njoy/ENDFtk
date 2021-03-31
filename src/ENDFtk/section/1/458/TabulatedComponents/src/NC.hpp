/**
 *  @brief Return the number of lines in this MF1/MT458 section
 */
long NC() const {

  long NC = this->values_.NC();
  for ( auto& entry : this->components_ ) {
    if ( entry ) { NC += entry->NC(); }
  }
  return NC;
}
