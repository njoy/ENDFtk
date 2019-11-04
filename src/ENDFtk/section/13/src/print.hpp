/**
 *  @brief Print the MF13 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), 0, 0,
                 this->NK(), 0 ).print( it, MAT, MF, MT );
  if ( this->total_ ) { this->total_->print( it, MAT, MF, MT ); }
  for ( const auto& entry : this->partials_ ) {

    entry.print( it, MAT, MF, MT );
  }
  SEND( MAT, MF ).print( it );
}
