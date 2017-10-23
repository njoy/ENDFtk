template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), 0,
                 this->LFC(), 0, 0 ).print( it, MAT, MF, MT() );
  this->components_.print( it, MAT, MF, MT() );
  SEND( MAT, MF ).print( it );
} 

