template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {
  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), 0,
                 0, this->NK(), 0 ).print( it, MAT, 13, MT );
  for ( auto& entry : this->subsections_ ) { 
    entry.print( it, MAT, MF(), MT );
  }
  SEND( MAT, 13 ).print( it );
} 

