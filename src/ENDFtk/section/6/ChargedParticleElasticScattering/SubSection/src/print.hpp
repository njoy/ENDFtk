template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT ); },
              *this );
} 
