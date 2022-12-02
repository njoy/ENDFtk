std::vector< std::vector< int > > compact() const {

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

    { static_cast< int >( this->i_[0] ),
      static_cast< int >( this->j_[0] ),
      convert( this->correlations_[0] ) }
  };
  unsigned int size = this->i_.size();
  for ( unsigned int i = 1; i < size; ++i ) {

    if ( this->i_[i] == lines.back()[0] ) {

      if ( this->j_[i] < lines.back()[1] + lines.back().size() - 3 + n ) {

        int pad = this->j_[i] - lines.back()[1] - lines.back().size() + 2;
        if ( pad > 0 ) {

          lines.back().insert( lines.back().end(),
                               pad,
                               0 );
        }
        lines.back().emplace_back( convert( this->correlations_[i] ) );
      }
      else {

        lines.emplace_back(
          std::vector< int >{ static_cast< int >( this->i_[i] ),
                              static_cast< int >( this->j_[i] ),
                              convert( this->correlations_[i] ) } );
      }
    }
    else {

      lines.emplace_back(
        std::vector< int >{ static_cast< int >( this->i_[i] ),
                            static_cast< int >( this->j_[i] ),
                            convert( this->correlations_[i] ) } );
    }
  }

  return lines;
}
