template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {

  int MF = this->MF();
  for ( const auto& entry : this->sectionMap ) {

    entry.second.print( it, MAT, MF );
  }
  FEND( MAT ).print( it );
}
