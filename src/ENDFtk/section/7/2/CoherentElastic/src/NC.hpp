/** 
 *  @brief Return the number of lines in this MF7/MT2 component
 */
long NC() const {
  long NC = this->principal_.NC();
  for ( const auto& entry : this->temperatures_ ) { NC += entry.NC(); }
  return NC;
};

