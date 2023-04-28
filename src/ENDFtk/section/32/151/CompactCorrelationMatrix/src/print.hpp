template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  // this code is not pretty, but the INTG records are just dumb so ...

  // compact the matrix
  auto lines = this->compact();

  // write the correlation matrix
  ControlRecord( 0., 0.,
                 this->NDIGIT(), this->NNN(),
                 lines.size(), 0 ).print( it, MAT, MF, MT );
  for ( auto& line : lines ) {

    switch ( this->NDIGIT() ) {

      case 2: { record::IntegerBase< 2, 18 >(
                    std::get< 0 >( line ),
                    std::get< 1 >( line ),
                    std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                break; }
      case 3: { record::IntegerBase< 2, 13 >(
                    std::get< 0 >( line ),
                    std::get< 1 >( line ),
                    std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                break; }
      case 4: { record::IntegerBase< 4, 11 >(
                    std::get< 0 >( line ),
                    std::get< 1 >( line ),
                    std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                break; }
      case 5: { record::IntegerBase< 5, 9 >(
                    std::get< 0 >( line ),
                    std::get< 1 >( line ),
                    std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                break; }
      case 6: { record::IntegerBase< 6, 8 >(
                    std::get< 0 >( line ),
                    std::get< 1 >( line ),
                    std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                break; }
      default: { /* unreachable */ break; }
    }
  }
}
