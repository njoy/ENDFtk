/**
 *  @brief Print this MF9 component
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
  ControlRecord( this->ZA(), this->AWR(),
                 this->LIS(), 0,
                 this->products_.size(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->products_ ) {

    entry.print( it, MAT, MF, MT );
  }
  SEND( MAT, MF ).print( it );
}
