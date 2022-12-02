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

  // conversion factor
  double factor = 1;
  switch ( this->NDIGITS() ) {

    case 2: { factor = 100; break; }
    case 3: { factor = 1000; break; }
    case 4: { factor = 10000; break; }
    case 5: { factor = 100000; break; }
    case 6: { factor = 1000000; break; }
    default: { /* unreachable */ break; }
  }

  // conversion function
  auto convert = [factor] ( double value ) -> int {

    value *= factor;
    if ( std::abs( value ) <= 1. ) {

      return 0;
    }
    if ( value > 0. ) {

      return std::floor( value );
    }
    else {

      return -std::floor( value );
    }
  };

  // compact the correlation matrix
  std::vector< std::vector< int > > lines = {

    { static_cast< int >( this->I()[0] ),
      static_cast< int >( this->J()[0] ),
      convert( this->correlations()[0] ) }
  };
  unsigned int size = this->I().size();
  for ( unsigned int i = 1; i < size; ++i ) {

    if ( this->I()[i] == lines.back()[0] ) {

      if ( this->J()[i] < lines.back()[1] + lines.back().size() - 3 + n ) {

        int pad = this->J()[i] - lines.back()[1] - lines.back().size() + 2;
        if ( pad > 0 ) {

          lines.back().insert( lines.back().end(),
                               pad,
                               0 );
        }
        lines.back().emplace_back( convert( this->correlations()[i] ) );
      }
      else {

        lines.emplace_back(
          std::vector< int >{ static_cast< int >( this->I()[i] ),
                              static_cast< int >( this->J()[i] ),
                              convert( this->correlations()[i] ) } );
      }
    }
    else {

      lines.emplace_back(
        std::vector< int >{ static_cast< int >( this->I()[i] ),
                            static_cast< int >( this->J()[i] ),
                            convert( this->correlations()[i] ) } );
    }
  }

  // write the correlation matrix
  ControlRecord( 0., 0.,
                 this->NDIGITS(), this->NNN(),
                 lines.size(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : lines ) {

    std::ostringstream out;
    out << std::setw( 5 ) << entry[0] << std::setw( 5 ) << entry[1];
    if ( this->NDIGITS() != 6 ) { out << ' '; }
    for ( unsigned int i = 2; i < entry.size(); ++i ) {

      out << std::setw( this->NDIGITS() + 1 ) << entry[i];
    }

    std::string line = out.str();
    line.insert( line.size(), 66 - line.size(), ' ');
    TextRecord( std::move( line ) ).print( it, MAT, MF, MT );
  }
}
