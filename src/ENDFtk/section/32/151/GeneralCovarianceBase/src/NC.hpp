/**
 *  @brief Return the number of lines in this MF2 MT151 component
 */
long NC() const {

  long NC = 1;
  if ( this->ISR() ) { NC += Derived::NC( this->dap_.value() ); }
  for ( const auto& cshort : this->short_ ) {

    NC += Derived::NC( cshort );
  }
  for ( const auto& clong : this->long_ ) {

    NC += std::visit( [] ( const auto& value ) { return value.NC(); }, clong );
  }
  return NC;
};
