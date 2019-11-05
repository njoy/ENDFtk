/** 
 *  @brief Print the MF4 section (includes SEND record)
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
  ControlRecord( this->ZA(), this->AWR(), 0, this->LTT(),
                 0, 0 ).print( it, MAT, MF, MT );
  ControlRecord( 0, this->AWR(), this->LI(), this->LCT(),
                 0, 0 ).print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) { return v.print( it, MAT, MF, MT ); },
              this->distributions_ );
  SEND( MAT, MF ).print( it );
} 
