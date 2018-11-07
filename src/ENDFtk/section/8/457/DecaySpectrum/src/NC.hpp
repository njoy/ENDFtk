/** 
 *  @brief Return the number of lines in this MF8/MT457 section
 */
long NC() const {
  long NC = this->data_.NC();
  if ( this->discrete_ ) { 
      for ( const auto& entry : *this->discrete_ ) NC += entry.NC();
  }
  if ( this->continuous_ ) NC += this->continuous_->NC();
  return NC;
};

