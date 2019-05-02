/** 
 *  @brief Print the MF8/MT457 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), this->lis_, this->liso_,
                 this->nst_, this->NSP() ).print( it, MAT, MF, MT );
  this->energies_.print( it, MAT, MF, MT );
  this->modes_.print( it, MAT, MF, MT );
  for ( const auto& entry : this->spectra_ ) { entry.print( it, MAT, MF, MT ); }
  SEND( MAT, MF ).print( it );
} 
