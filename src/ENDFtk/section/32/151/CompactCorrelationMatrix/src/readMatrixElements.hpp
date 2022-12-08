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
                    unsigned int ndigits,
                    unsigned int lines ) {

  // this code is not pretty, but the INTG records are just dumb so ...

  std::vector< unsigned int > is;
  std::vector< unsigned int > js;
  std::vector< double > correlations;

  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  int iv;
  int jv;
  std::vector< int > values;
  unsigned int i;
  unsigned int j;

  std::cout << "NM " << lines << " NDIGITS " << ndigits << std::endl;

  switch ( ndigits ) {

    case 2: {

      using Format = disco::Record<
                         disco::Integer< 5 >, disco::Integer< 5 >,
                         disco::ColumnPosition< 1 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::Integer< 3 >, disco::Integer< 3 >,
                         disco::ColumnPosition< 1 > >;

      double factor = 100;
      values.resize( 18 );
      auto iterator = values.begin();

      for ( unsigned int line = 0; line < lines; ++line ) {

        auto pos = begin;
        Format::read( begin, end, i, j,
                      iterator[0], iterator[1], iterator[2],
                      iterator[3], iterator[4], iterator[5],
                      iterator[6], iterator[7], iterator[8],
                      iterator[9], iterator[10], iterator[11],
                      iterator[12], iterator[13], iterator[14],
                      iterator[15], iterator[16], iterator[17] );

std::cout << i << ' ' << j << ' ' << values.front() << ' ' << values.back() << std::endl;
std::cout << *begin << ' ' << (begin - pos) << std::endl;
//        tail( MAT, MF, MT, begin, end, lineNumber );

        i = verifyUnsigned( iv, "I" );
        j = verifyUnsigned( jv, "J" );
        for ( unsigned int index = 0; index < values.size(); ++index  ) {

          if ( values[index] != 0  ) {

            is.emplace_back( i );
            js.emplace_back( j + index );
            if ( values[index] > 0 ) {

              correlations.emplace_back( ( static_cast< double >( values[index] )
                                           + 0.5 ) / factor );
            }
            else {

              correlations.emplace_back( ( static_cast< double >( values[index] )
                                           - 0.5 ) / factor );
            }
          }
        }
      }

      break;
    }
    case 3: {

      unsigned int n = 13;
      break;
    }
    case 4: {

      unsigned int n = 11;
      break;
    }
    case 5: {

      unsigned int n = 9;
      break;
    }
    case 6: {

      unsigned int n = 8;
      break;
    }
    default: { /* unreachable */ break; }
  }

  return std::make_tuple( std::move( is ), std::move( js ),
                          std::move( correlations ) );
}
