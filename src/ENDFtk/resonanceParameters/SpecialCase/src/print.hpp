template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  using Format = disco::Record< disco::ENDF, disco::ENDF,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::ColumnPosition< 5 > >;
  Format::write( it, this->EL(), this->EH(), 0, 0, 0, 0, MAT, MF, MT );
  Format::write( it, this->SPI(), this->AP(), 0, 0, 0, 0, MAT, MF, MT );
}

