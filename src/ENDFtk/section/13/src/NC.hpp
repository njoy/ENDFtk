/**
 *  @brief Return the number of lines in this MF13 section
 */
long NC() const {
  
  long NC = 1;
  if ( this->total_ ) { NC += this->total_->NC(); }
  for ( const auto& entry : this->partials_ ) {

    NC += entry.NC();
  }
  return NC;
};
