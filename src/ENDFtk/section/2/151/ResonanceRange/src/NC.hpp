/**
 *  @brief Return the number of lines in this MF2/MT151 component
 */
long NC() const {

  long NC = 1 + std::visit( [] ( const auto& v ) -> long
                               { return v.NC(); },
                            this->parameters_ );
  if ( this->NRO() ) { NC += this->scattering_radius_->NC(); }
  return NC;
}
