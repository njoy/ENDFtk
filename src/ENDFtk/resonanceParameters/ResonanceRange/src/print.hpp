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
  ControlRecord( this->EL(), this->EH(),
                 this->LRU(), this->LRF(),
                 this->NRO(), this->NAPS() ).print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) -> void
                  { return v.print( it, MAT, MF, MT ); },
              this->parameters_ ); }
}
