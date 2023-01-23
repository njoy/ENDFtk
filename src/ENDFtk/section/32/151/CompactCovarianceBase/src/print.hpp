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
                 this->L1(), this->LCOMP(),
                 this->N1(), this->ISR() ).print( it, MAT, MF, MT );
  if ( this->ISR() ) {

    Derived::print( this->dap_.value(), it, MAT, MF, MT );
  }
  this->uncertainties_.print( it, MAT, MF, MT );
  this->matrix_.print( it, MAT, MF, MT );
}
