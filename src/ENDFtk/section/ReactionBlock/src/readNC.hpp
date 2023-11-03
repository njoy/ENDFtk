template< typename Iterator >
static std::vector< DerivedCovariance >
readNC( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT, int MF, int MT,
                  int numberNC ) {

  std::vector< DerivedCovariance > result;

  for (int i=0; i<numberNC; ++i) {

    ControlRecord cont( begin, end, lineNumber, MAT, MF, MT );

    switch ( cont.L2() ) {

      // DerivedRedundant
      case 0:
        result.push_back(
          DerivedRedundant( cont.L2(),
                            begin, end, lineNumber, MAT, MF, MT ) );
        break;

      // DerivedRatioToStandard
      case 1:
      case 2:
      case 3:
        result.push_back(
          DerivedRatioToStandard( cont.L2(),
                                  begin, end, lineNumber, MAT, MF, MT ) );
        break;

      // Error
      default:
        Log::error( "Encountered illegal LTY value" );
        Log::info( "LTY can only be 0,1,2,3" );
        Log::info( "LTY value: {}", cont.L2() );
        Log::info( "Line number: {}", lineNumber - 1 );
        throw std::exception();

    }

  }

  return result;

}
