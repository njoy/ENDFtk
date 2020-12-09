/**
 *  @brief Print the MF1/MT458 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  this->values_.print( it, MAT, MF, MT );
  for ( auto& entry : this->components_ ) {
    if ( entry ) { entry->print( it, MAT, MF, MT ); }
  }
}
