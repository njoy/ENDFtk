template< typename Iterator >
static ScatteringLaw
readScatteringLaw( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT,
                   int LTHR ) {

  switch ( LTHR ) {
    case 1: return CoherentElastic( begin, end, lineNumber, MAT, MF, MT );
    case 2: return IncoherentElastic( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LTHR value" );
      Log::info( "LTHR is either 1 (coherent) or 2 (incoherent)" );
      Log::info( "LTHR value: {}", LTHR );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
}
