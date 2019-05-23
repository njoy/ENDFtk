/** 
 *  @brief Print this MF4 component
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

  this->legendre_.print( it, MAT, MF, MT );
  this->tabulated_.print( it, MAT, MF, MT );
} 

