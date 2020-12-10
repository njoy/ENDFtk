template< typename Iterator >
static DelayedPhotonData
readPhotonData( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int LO,
                int NG ) {
  switch ( LO ) {
    case 1 : return DiscretePhotons( readDiscretePhotons( begin, end, lineNumber, MAT, NG ) );
    case 2 : return ContinuousPhotons( begin, end, lineNumber, MAT, 1, 460 );
    default : {
      Log::error( "Encountered illegal LO value" );
      Log::info( "LO must be equal to 1 or 2" );
      Log::info( "LO value: {}", LO );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}
