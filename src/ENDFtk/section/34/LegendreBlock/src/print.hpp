/**
 *  @brief Print this MF34 component
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
  ControlRecord( 0.0, 0.0, this->L(), this->L1(),
                 this->LCT(), this->NI() ).print( it, MAT, MF, MT );

  // NI subsubsections
  for ( auto& ni : this->ni_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { v.print( it, MAT, MF, MT ); },
                ni );
  }

}
