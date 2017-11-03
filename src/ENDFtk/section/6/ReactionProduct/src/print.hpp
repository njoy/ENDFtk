template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  this->multiplicity_.print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT ); },
              this->law_ );
  SEND( MAT, MF ).print( it );
} 

