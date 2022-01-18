/**
 *  @brief Print the MF32/MT151 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = 151;
  ControlRecord( this->ZA(), this->AWR(),
                 0, 0, this->NIS(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->isotopes() ) {

    entry.print( it, MAT, MF, MT );
  }
  SEND( MAT, MF ).print( it );
}
