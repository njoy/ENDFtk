template< typename Iterator >
static std::vector< NIType >
readNI( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT, int MF, int MT,
                  int numberNI ) {

  std::vector< NIType > result;

  for (int i=0; i<numberNI; ++i) {

    ListRecord list( begin, end, lineNumber, MAT, MF, MT );

    switch ( list.L2() ) {

      // CovariancePairs
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 8:
      case 9:
        result.push_back( CovariancePairs( std::move( list ) ) );
        break;

      // SquareMatrix
      case 5:
        result.push_back( SquareMatrix( std::move( list ) ) );
        break;

      // RectangularMatrix
      case 6:
        result.push_back( RectangularMatrix( std::move( list ) ) );
        break;

      // Error
      default:
        Log::error( "Encountered illegal LB value" );
        Log::info( "LB can only be 0,1,2,3,4,5,6,8,9" );
        Log::info( "MT value: {}", MT );
        Log::info( "Line number: {}", lineNumber - 1 );
        Log::info( "LB value: {}", list.L2() );
        throw std::exception();

    }

  }

  return result;

}
