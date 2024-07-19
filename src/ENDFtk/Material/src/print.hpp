/**
 *  @brief Print the file (includes FEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& it ) const {

  int MAT = this->MAT();
  for ( const auto& entry : this->files_ ) {

    std::visit( [&] ( auto&& file ) { file.print( it, MAT ); }, entry );
  }
  MEND().print( it );
}
