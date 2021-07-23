template< typename Iterator >
static std::vector< NCType >
readNC( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT, int MF, int MT,
                  int numberNC ) {

  std::vector< NCType > result;

  for (int i=0; i<numberNC; ++i) {

    ControlRecord cont( begin, end, lineNumber, MAT, MF, MT );

    switch ( cont.L2() ) {

      // DerivedRedundant
      case 0:
        result.push_back(
          DerivedRedundant( std::move( cont ),
                            begin, end, lineNumber, MAT, MF, MT ) );
        break;

      // DerivedRatioToStandard
      case 1:
      case 2:
      case 3:
        result.push_back(
          DerivedRatioToStandard( std::move( cont ),
                                  begin, end, lineNumber, MAT, MF, MT ) );
        break;

      // Error
      default:
        Log::error( "Encountered illegal LTY value" );
        Log::info( "LTY can only be 0,1,2,3" );
        Log::info( "MT value: {}", MT );
        Log::info( "Line number: {}", lineNumber - 1 );
        Log::info( "LTY value: {}", cont.L2() );
        throw std::exception();

    }

  }

  return result;

}
