/**
 *  @brief Print this MF40 component
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

  // metadata
  ControlRecord( this->QM(), this->QI(), this->IZAP(), this->LFS(),
                 0, this->NL() ).print( it, MAT, MF, MT );

  for ( const auto& block : this->reactions_ ) {
    block.print( it, MAT, MF, MT );
  }

}
