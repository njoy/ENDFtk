/**
 *  @brief Print the MF1/MT458 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  ControlRecord( this->ZA(), this->AWR(), this->LO(),
                 0, this->NG(), 0 ).print( it, MAT, MF, MT() );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT() ); },
              this->data_ );
  SEND( MAT, MF ).print( it );
}
