/** 
 *  @brief Print the MF7/MT4 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  int MT = 4;
  ControlRecord( this->ZA(), this->AWR(), 0, this->LAT(),
                 this->LASYM(), 0 ).print( it, MAT, MF, MT );
  this->b_.print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT ); },
              this->law_ );
  this->principal_.print( it, MAT, MF, MT );
  for ( const auto& entry : this->secondary_ ) {
    if ( entry ) entry->print( it, MAT, MF, MT );
  }
  SEND( MAT, MF ).print( it );
} 

