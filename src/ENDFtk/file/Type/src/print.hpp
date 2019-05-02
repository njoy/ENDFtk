template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {

  int MF = this->MF();
  for ( auto& entry : this->sectionMap ) entry.second.print( it, MAT, MF );
  FEND( MAT ).print( it );
} 

