template< typename Iterator >
static std::vector< LongRangeCovarianceBlock >
readSequence( Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT,
              int size ) {

  std::vector< LongRangeCovarianceBlock > sequence;
  sequence.reserve( size );

  while ( size-- ) {

    ListRecord list( begin, end, lineNumber, MAT, MF, MT );

    switch ( list.L2() ) {

      // CovariancePairs
      case -1:
      case 0:
      case 1:
      case 2:
        sequence.emplace_back( section::CovariancePairs( std::move( list ) ) );
        break;

      // SquareMatrix
      case 5:
        sequence.emplace_back( section::SquareMatrix( std::move( list ) ) );
        break;

      // Error
      default:
        Log::error( "Encountered illegal LB value" );
        Log::info( "LB can only be -1,0,1,2,5" );
        Log::info( "LB value: {}", list.L2() );
        Log::info( "Line number: {}", lineNumber - 1 );
        throw std::exception();
    }
  }

  return sequence;
}
