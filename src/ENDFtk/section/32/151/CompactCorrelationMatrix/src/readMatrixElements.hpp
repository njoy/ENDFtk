template< typename Iterator >
static
std::tuple< std::vector< unsigned int >,
            std::vector< unsigned int >,
            std::vector< double > >
readMatrixElements( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT,
                    unsigned int ndigit,
                    unsigned int lines ) {

  // this code is not pretty, but the INTG records are just dumb so ...

  std::vector< unsigned int > is;
  std::vector< unsigned int > js;
  std::vector< double > correlations;

  auto process = [&is,&js,&correlations] ( auto&& record, int factor ) -> void {

    for ( unsigned int index = 0; index < record.K().size(); ++index  ) {

      long value = record.K()[index];
      if ( value != 0  ) {

        is.emplace_back( record.I() );
        js.emplace_back( record.J() + index );
        if ( value > 0 ) {

          correlations.emplace_back( ( static_cast< double >( value )
                                       + 0.5 ) / factor );
        }
        else {

          correlations.emplace_back( ( static_cast< double >( value )
                                       - 0.5 ) / factor );
        }
      }
    }
  };

  switch ( ndigit ) {

    case 2: {

      using INTG = record::IntegerBase< 2, 18 >;
      for ( unsigned int line = 0; line < lines; ++line ) {

        process( INTG( begin, end, lineNumber, MAT, MF, MT ), 100 );
      }

      break;
    }
    case 3: {

      using INTG = record::IntegerBase< 3, 13 >;
      for ( unsigned int line = 0; line < lines; ++line ) {

        process( INTG( begin, end, lineNumber, MAT, MF, MT ), 1000 );
      }

      break;
    }
    case 4: {

      using INTG = record::IntegerBase< 4, 11 >;
      for ( unsigned int line = 0; line < lines; ++line ) {

        process( INTG( begin, end, lineNumber, MAT, MF, MT ), 10000 );
      }

      break;
    }
    case 5: {

      using INTG = record::IntegerBase< 5, 9 >;
      for ( unsigned int line = 0; line < lines; ++line ) {

        process( INTG( begin, end, lineNumber, MAT, MF, MT ), 100000 );
      }

      break;
    }
    case 6: {

      using INTG = record::IntegerBase< 6, 8 >;
      for ( unsigned int line = 0; line < lines; ++line ) {

        process( INTG( begin, end, lineNumber, MAT, MF, MT ), 1000000 );
      }

      break;
    }
    default: {

      Log::error( "Encountered illegal NDIGIT value" );
      Log::info( "NDIGIT should be equal to 2, 3, 4, 5 or 6" );
      Log::info( "NDIGIT value: {}", ndigit );
      throw std::exception();
    }
  }

  return std::make_tuple( std::move( is ), std::move( js ),
                          std::move( correlations ) );
}
