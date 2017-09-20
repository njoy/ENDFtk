template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  BreitWigner::print< LRF() >( it, MAT, MF, MT );
}



