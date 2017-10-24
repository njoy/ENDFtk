template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), 0,
                 this->LFC(), 0, this->NFC() ).print( it, MAT, MF, MT() );
  this->components_.print( it, MAT, MF, MT() );
  for ( auto& entry : this->tables_ ) { entry.print( it, MAT, MF, MT() ); }
  SEND( MAT, MF ).print( it );
} 

