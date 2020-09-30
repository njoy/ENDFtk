/**
 *  @brief Print the MF1/MT451 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  
  int MT = 451;
  ControlRecord( this->ZA(), this->AWR(), this->LRP(),this->LFI(),
                 this->NLIB(), this->NMOD() ).print( it, MAT, MF, MT );
  for ( auto& entry : this->parameters_ ) entry.print( it, MAT, MF, MT );
  for ( auto& entry : this->description_ ) entry.print( it, MAT, MF, MT );
  for ( auto& entry : this->index_ ) entry.print( it, MAT, MF, MT );
  SEND( MAT, MF ).print( it );
}
