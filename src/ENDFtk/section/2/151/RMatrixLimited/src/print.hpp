/**
 *  @brief Print this MF2 MT151 component
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

  ControlRecord( 0.0, 0.0,
                 this->IFG(), this->KRM(),
                 this->NJS(), this->KRL() ).print( it, MAT, MF, MT );
  this->particle_pairs_.print( it, MAT, MF, MT );
  for ( const auto& spingroup : this->spin_groups_ ) {

    spingroup.print( it, MAT, MF, MT );
  }
}
