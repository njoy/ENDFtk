/**
 *  @brief Return the number of lines in this MF32 MT151 component
 */
long NC() const {

  long NC = 1;
  if ( this->ISR() ) { NC += Derived::NC( this->dap_.value() ); }
  NC += this->uncertainties_.NC();
  NC += this->matrix_.NC();
  return NC;
};
