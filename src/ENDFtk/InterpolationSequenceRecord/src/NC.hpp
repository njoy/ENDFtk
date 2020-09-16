/**
 *  @brief Return the number of lines in this MF7/MT2 component
 */
auto NC() const {

  auto NC = this->interpolation_.NC();
  for ( const auto& entry : this->sequence_ ) { NC += ENDFtk::NC( entry ); }
  return NC;
};
