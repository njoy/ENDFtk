template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  using Format = disco::Record< disco::ENDF, disco::ENDF,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 4 >, disco::Integer< 2>,
                                disco::Integer< 3 >, disco::ColumnPosition<5> >;
  Format::write( it,
                 this->C1(), this->C2(),
                 this->L1(), this->L2(),
                 this->N1(), this->N2(),
                 MAT, MF, MT );
}

