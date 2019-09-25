template< typename Iterator >
static Distributions
readDistributions( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT,
                   long LTT) {

  switch ( LTT ) {
    case 0 : return Isotropic();
    case 1 : return LegendreDistributions( begin, end, lineNumber,
                                           MAT, MF, MT );
    case 2 : return TabulatedDistributions( begin, end, lineNumber, MAT, MF, MT );
    case 3 : return MixedDistributions( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LTT value" );
      Log::info( "LTT must be equal to 0, 1, 2 or 3" );
      Log::info( "LTT value: {}", LTT );
      Log::info( "Line number: {}", lineNumber - 2 );
      throw std::exception();
    }
  }
}
