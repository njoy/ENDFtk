/** 
 *  @brief Return the number of lines in this MF7/MT4 section
 */
long NC() const {
  long NC = 1;
  NC += this->b_.NC();
  std::visit( [&] ( const auto& v ) -> void
                  { NC += v.NC(); },
              this->law_ );
  NC += principal_.NC();
  for ( const auto& entry : this->secondary_ ) {

    if ( entry ) NC += entry->NC();
  }
  return NC;
};

