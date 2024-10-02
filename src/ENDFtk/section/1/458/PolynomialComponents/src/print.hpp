/**
 *  @brief Print the MF1/MT458 component
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

  std::vector< double > values;
  values.reserve( 18 * ( this->order() + 1 ) );
  for ( std::size_t i = 0; i < this->order() + 1; ++i ) {

    for ( std::size_t j = 0; j < 9; ++j ) {

      values.push_back( this->energyRelease()[j][i][0] );
      values.push_back( this->energyRelease()[j][i][1] );
    }
  }

  ListRecord( 0., 0., 0, this->order(), ( this->order() + 1 ) * 9,
              std::move( values ) ).print( it, MAT, MF, MT );
}
