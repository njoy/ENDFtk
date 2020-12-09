/**
 *  @brief Return the number of lines in this MF2/MT151 section
 */
long NC() const {

  long NC = this->values_.NC();
  for ( auto& entry : this->components_ ) {
    if ( entry ) { NC += entry->NC(); }
  }
  return NC;
}
