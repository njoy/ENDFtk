template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {
  int MF = this->MF();
  for ( auto& entry : this->sectionVector ) entry.print( it, MAT, MF );
  FEND( MAT ).print( it );
} 

