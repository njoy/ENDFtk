std::vector< std::tuple< unsigned int, unsigned int,
                         std::vector< int > > > compact() const {

  // this code is not pretty, but the INTG records are just dumb so ...

  std::vector< std::tuple< unsigned int, unsigned int,
                           std::vector< int > > > lines;
  if ( this->correlations_.size() != 0 ) {

    // the maximum number of values per line
    unsigned int n = 0;
    switch ( this->NDIGIT() ) {

      case 2: { n = 18; break; }
      case 3: { n = 13; break; }
      case 4: { n = 11; break; }
      case 5: { n =  9; break; }
      case 6: { n =  8; break; }
      default: { /* unreachable */ break; }
    }

    // conversion factor
    double factor = 1;
    switch ( this->NDIGIT() ) {

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

        return -std::floor( std::abs( value ) );
      }
    };

    // compact the correlation matrix
    lines.push_back( { this->i_[0], this->j_[0], { convert( this->correlations_[0] ) } } );
    unsigned int size = this->i_.size();
    for ( unsigned int i = 1; i < size; ++i ) {

      if ( ( this->i_[i] == std::get< 0 >( lines.back() ) ) &&
           ( std::get< 2 >( lines.back() ) ).size() < n ) {

        if ( this->j_[i] < std::get< 1 >( lines.back() ) + n ) {

          int pad = this->j_[i] - std::get< 1 >( lines.back() ) - std::get< 2 >( lines.back() ).size();
          if ( pad > 0 ) {

            std::get< 2 >( lines.back() ).insert( std::get< 2 >( lines.back() ).end(),
                                                  pad,
                                                  0 );
          }
          std::get< 2 >( lines.back() ).emplace_back( convert( this->correlations_[i] ) );
        }
        else {

          lines.emplace_back( std::make_tuple (
                                this->i_[i],
                                this->j_[i],
                                std::vector< int >{ convert( this->correlations_[i] ) } ) );
        }
      }
      else {

        lines.emplace_back( std::make_tuple (
                              this->i_[i],
                              this->j_[i],
                              std::vector< int >{ convert( this->correlations_[i] ) } ) );
      }
    }
  }

  return lines;
}
