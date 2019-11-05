template< typename Iterator >
static PhotonProduction
readPhotonProduction( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT,
                      int LO,
                      int N ) {

  switch ( LO ) {
    case 1: return Multiplicities( begin, end, lineNumber, MAT, MF, MT, N );
    case 2: return TransitionProbabilities( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LO value" );
      Log::info( "LO is either 1 (multiplicities) or 2 (probabilities)" );
      Log::info( "LO value: {}", LO );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
}
