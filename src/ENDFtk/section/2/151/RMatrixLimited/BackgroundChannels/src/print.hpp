/**
 *  @brief Print this MF2/MT151 component
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

  for ( const auto& channel : this->backgroundRMatrices() ) {

    if ( channel ) {

      std::visit( [&] ( const auto& variant )
                      { return variant.print( it, MAT, MF, MT ); },
                  channel.value() );
    }
  }
}
