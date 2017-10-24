template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  this->values_.print( it, MAT, MF, MT );
  for ( auto& entry : this->components_ ) {
    if ( entry ) { entry->print( it, MAT, MF, MT ); }
  }
} 

