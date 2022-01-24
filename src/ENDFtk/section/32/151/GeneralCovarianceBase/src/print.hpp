/**
 *  @brief Print this MF32 MT151 component
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 *  @param[in] MT            the MT number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  ControlRecord( this->SPI(), this->AP(),
                 0, this->LCOMP(),
                 this->NLS(), this->ISR() ).print( it, MAT, MF, MT );
  if ( this->ISR() ) {

    Derived::write( this->dap_, it, MAT, MF, MT );
  }
  for ( const auto& cshort : this->short_ ) {

    Derived::write( cshort, it, MAT, MF, MT );
  }
  for ( const auto& clong : this->long_ ) {

    std::visit( [&] ( const auto& v ) -> void
                    { return v.print( it, MAT, MF, MT ); },
                clong );
  }
}
