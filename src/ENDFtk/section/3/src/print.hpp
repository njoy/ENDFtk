template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  const int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), 0, 0, 0, 0 ).print( it, MAT, MF, MT );
  this->table.print( it, MAT, MF, MT );
  SEND( MAT, MF ).print( it );
} 

