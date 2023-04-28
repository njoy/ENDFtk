/**
 *  @brief Print the DerivedRedundant component
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

  ControlRecord( 0.0, 0.0, 0, 0, 0, 0).print( it, MAT, MF, MT );
  this->list_.print( it, MAT, MF, MT );
}
