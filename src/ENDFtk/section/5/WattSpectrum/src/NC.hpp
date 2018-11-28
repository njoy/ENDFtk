/** 
 *  @brief Return the number of lines in this MF5 component
 */
long NC() const {
  long NC = 0;
  for ( const auto& entry : this->parameters_ ) { NC += entry.NC(); }
  return NC;
};
