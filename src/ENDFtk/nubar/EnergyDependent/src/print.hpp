template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  this->interpolation_.print( it, MAT, MF, MT );
  for ( auto& entry : this->lists_ ) { entry.print( it, MAT, MF, MT ); }
} 

