/**
 *  @brief Print this MF33 component
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
  ControlRecord( this->XMF1(), this->XLFS1(), this->MAT1(), this->MT1(),
                 this->NK(), this->NI() ).print( it, MAT, MF, MT );

  // NC subsubsections
  for ( auto& nc : this->nc_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { v.print( it, MAT, MF, MT ); },
                nc );
  }

  // NI subsubsections
  for ( auto& ni : this->ni_ ) {
    std::visit( [&] ( const auto& v ) -> void
                    { v.print( it, MAT, MF, MT ); },
                ni );
  }

}
