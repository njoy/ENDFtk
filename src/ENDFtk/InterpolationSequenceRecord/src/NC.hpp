/**
 *  @brief Return the number of lines in this ENDF component
 */
auto NC() const {

  auto NC = this->interpolation_.NC();
  for ( const auto& entry : this->sequence_ ) { NC += ENDFtk::NC( entry ); }
  return NC;
};
