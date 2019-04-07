/** 
 *  @brief Print the MF8/MT457 section (includes SEND record)
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
  this->data_.print( it, MAT, MF, MT );
  if ( this->discrete_ ) { 
    for ( const auto& entry : *this->discrete_ ) entry.print( it, MAT, MF, MT );
  }
  if ( this->continuous_ ) this->continuous_->print( it, MAT, MF, MT );
} 

