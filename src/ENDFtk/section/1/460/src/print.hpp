template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), this->LO(),
                 0, this->NG(), 0 ).print( it, MAT, MF, MT() );
//! @todo this doesn't compile on gcc
//  std::visit( [] ( const auto& v, OutputIterator& it,
//                   int MAT, int MF, int MT ) -> void
//                 { v.print( it, MAT, MF, MT ); },
//                 this->data_, it, MAT, MF, MT );
// TEMPORARY FIX (really ugly)
if (this->LO() == 1) {
  std::experimental::get< Discrete >
    ( this->data_ ).print( it, MAT, MF, MT() );
}
else {
  std::experimental::get< Continuous >
    ( this->data_ ).print( it, MAT, MF, MT() );
}

  SEND( MAT, MF ).print( it );
} 

