/**
 *  @brief Print the MF14 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), this->LI(), this->LTT(),
                 this->NK(), this->NI() ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->photons_ ) {

    std::visit( [&] ( const auto& v )
                    { return v.print( it, MAT, MF, MT ); },
                entry );
  }
  SEND( MAT, MF ).print( it );
}
