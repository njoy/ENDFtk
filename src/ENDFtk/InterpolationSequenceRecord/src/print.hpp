/**
 *  @brief Print the interpolation sequence record
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

  this->interpolation_.print( it, MAT, MF, MT );
  for ( const auto& entry : this->sequence_ ) {

    ENDFtk::print( entry, it, MAT, MF, MT );
  }
}
