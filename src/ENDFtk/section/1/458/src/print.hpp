template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), 0,
                 this->LFC(), 0, this->NFC() ).print( it, MAT, MF, MT() );
//! @todo this doesn't compile on gcc
//  std::visit( [] ( const auto& v, OutputIterator& it,
//                   int MAT, int MF, int MT ) -> void
//                 { v.print( it, MAT, MF, MT ); },
//                 this->data_, it, MAT, MF, MT );
// TEMPORARY FIX (really ugly)
if (this->LFC() == 0) {
  if (this->NPLY() == 0) {
    std::experimental::get< ThermalPoint >
      ( this->data_ ).print( it, MAT, MF, MT() );
  }
  else {
    std::experimental::get< Polynomial >
      ( this->data_ ).print( it, MAT, MF, MT() );
  }
}
else {
  std::experimental::get< Tabulated >
    ( this->data_ ).print( it, MAT, MF, MT() );
}

  SEND( MAT, MF ).print( it );
} 

