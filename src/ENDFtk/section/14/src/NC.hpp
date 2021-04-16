/**
 *  @brief Return the number of lines in this MF14 section
 */
long NC() const {

  long NC = 1;
  for ( const auto& entry : this->photons_ ) {

    NC += std::visit( [&] ( const auto& v ) { return v.NC(); }, entry );
  }
  return NC;
};
