template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  using namespace njoy::tools;

  using Format = disco::Record< disco::Character< 66 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::Column< 5 > >;
  Format::write( it, this->text(), MAT, MF, MT );
}
