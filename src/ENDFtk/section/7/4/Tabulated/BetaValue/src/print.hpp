template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  this->alphas_.print( it, MAT, MF, MT );
  for ( auto& entry : this->temperatures_ ) { entry.print( it, MAT, MF, MT ); }
} 

