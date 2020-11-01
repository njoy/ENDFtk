/**
 *  @brief Print this MF6 component
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
  this->multiplicity_.print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT ); },
              this->law_ );
}
