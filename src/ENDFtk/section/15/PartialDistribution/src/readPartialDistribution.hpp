template< typename Iterator >
static PartialDistribution
readPartialDistribution( Iterator& begin,
                         const Iterator& end,
                         long& lineNumber,
                         int MAT,
                         int MF,
                         int MT ) {

  Probability probability( begin, end, lineNumber, MAT, MF, MT );
  switch ( probability.LF() ) {
    case 1 :
      return PartialDistribution
             ( std::move( probability ),
               TabulatedSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
    default : {
      Log::error( "Encountered illegal LF value" );
      Log::info( "LF must be equal to 1" );
      Log::info( "LF value: {}", probability.LF() );
      Log::info( "Line number: {}", lineNumber - probability.NC() );
      throw std::exception();
    }
  }
}
