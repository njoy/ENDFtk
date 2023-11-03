/**
 *  @brief Return the number of lines in this MF2 MT151 component
 */
long NC() const {

  long NC = this->particle_pairs_.NC();
  for ( const auto& spingroup : this->spin_groups_ ) { NC += spingroup.NC(); }
  return NC;
};
