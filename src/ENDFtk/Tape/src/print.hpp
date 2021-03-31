template< typename OutputIterator >
void print( OutputIterator& it ) const {

  this->id_.print( it, 0, 0, 0 );
  for ( const auto& material : this->materials_ ) { material.print( it ); }
  TEND().print( it );
}
