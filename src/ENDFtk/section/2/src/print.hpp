template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(),
                 0, 0, this->isotopes.size(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->isotopes ) { entry.print( it, MAT, MF, MT ); }
  SEND( MAT, MF ).print( it );
} 

