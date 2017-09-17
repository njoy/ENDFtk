template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  using Format = disco::Record< disco::Character< 66 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::ColumnPosition< 5 > >;
  Format::write( it, this->text(), MAT, MF, MT );
}
