/**
 *  @brief Print the MF33 section (includes SEND record)
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
  ControlRecord( this->ZA(), this->AWR(), 0,this->MTL(),
                 0, this->NL() ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->reactions_ ) { entry.print( it, MAT, MF, MT ); }
  SEND( MAT, MF ).print( it );
}
