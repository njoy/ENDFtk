template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  // this code is not pretty, but the INTG records are just dumb so ...

  // the maximum number of values per line
  unsigned int n = 0;
  switch ( this->NDIGITS() ) {

    case 2: { n = 18; break; }
    case 3: { n = 13; break; }
    case 4: { n = 11; break; }
    case 5: { n =  9; break; }
    case 6: { n =  8; break; }
    default: { /* unreachable */ break; }
  }

  // compact the matrix
  std::vector< std::vector< int > > lines = this->compact();

  // write the correlation matrix
  ControlRecord( 0., 0.,
                 this->NDIGITS(), this->NNN(),
                 lines.size(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : lines ) {

    disco::Integer< 5 >::write( entry[0], it );
    disco::Integer< 5 >::write( entry[1], it );
    if ( this->NDIGITS() != 6 ) {

      disco::ColumnPosition< 1 >::write( it );
    }
    for ( unsigned int i = 2; i < entry.size(); ++i ) {

      switch ( this->NDIGITS() ) {

        case 2: { disco::Integer< 3 >::write( entry[i], it ); break; }
        case 3: { disco::Integer< 4 >::write( entry[i], it ); break; }
        case 4: { disco::Integer< 5 >::write( entry[i], it ); break; }
        case 5: { disco::Integer< 6 >::write( entry[i], it ); break; }
        case 6: { disco::Integer< 7 >::write( entry[i], it ); break; }
        default: { /* unreachable */ break; }
      }
    }
    for ( unsigned int i = entry.size() - 2; i < n; ++i ) {

      switch ( this->NDIGITS() ) {

        case 2: { disco::ColumnPosition< 3 >::write( it ); break; }
        case 3: { disco::ColumnPosition< 4 >::write( it ); break; }
        case 4: { disco::ColumnPosition< 5 >::write( it ); break; }
        case 5: { disco::ColumnPosition< 6 >::write( it ); break; }
        case 6: { disco::ColumnPosition< 7 >::write( it ); break; }
        default: { /* unreachable */ break; }
      }
    }
    switch ( this->NDIGITS() ) {

      case 2: { disco::ColumnPosition< 1 >::write( it ); break; }
      case 3: { disco::ColumnPosition< 3 >::write( it ); break; }
      case 5: { disco::ColumnPosition< 1 >::write( it ); break; }
      default: { /* unreachable */ break; }
    }

    using Format =
      disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                     disco::Integer< 3 >, disco::ColumnPosition< 5 > >;

    Format::write( it, MAT, MF, MT );
  }
}
