template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {  
  using Format = disco::Record< disco::ENDF, disco::ENDF,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::ColumnPosition< 5 > >;

  Format::write( it, this->AWRI(), 0.0, this->L(), 0, this->NJS(), 0, MAT, MF, MT );
    
  for( const auto& list : this->lists ){ list.print( it, MAT, MF, MT ); }
}
