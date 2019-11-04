/**
 *  @brief Return the number of lines in this MF12 component
 */
long NC() const {
  long NC = 0;
  if ( this->total_ ) { NC += this->total_->NC(); }
  for ( const auto& entry : this->partials_ ) {

    NC += entry.NC();
  }
  return NC;
};
