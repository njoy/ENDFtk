template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  for ( auto& entry : this->photons_ ) { entry.print( it, MAT, MF, MT ); }
} 

