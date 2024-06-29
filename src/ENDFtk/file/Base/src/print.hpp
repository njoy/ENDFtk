/**
 *  @brief Print the file (includes FEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {

  int MF = this->MF();
  for ( const auto& entry : this->sections_ ) {

    Derived::printSection( entry, it, MAT, MF );
  }
  FEND( MAT ).print( it );
}
