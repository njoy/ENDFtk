/** 
 *  @brief Return the number of lines in this MF7/MT4 section
 */
long NC() const {
  long NC = 1 + this->b_.NC()
          + std::visit( [&] ( const auto& v ) { return v.NC(); }, this->law_ )
          + principal_.NC();
  for ( const auto& entry : this->secondary_ ) {

    if ( entry ) NC += entry->NC();
  }
  return NC;
};

