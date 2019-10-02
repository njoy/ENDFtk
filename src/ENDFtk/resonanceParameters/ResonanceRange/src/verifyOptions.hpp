static void
verifyOptions( bool NRO, int NAPS, int LRU, int LRF ) {

  if ( not NRO and ( ( NAPS < 0 ) or ( NAPS > 1 ) ) {

    Log::error( "Encountered illegal NAPS value" );
    Log::info( "NAPS is either 0 or 1 when no energy dependent scattering "
               "radius is given (NRO = 0)" );
    Log::info( "NRO value: {}", int( NRO ) );
    Log::info( "NAPS value: {}", NAPS );
    throw std::exception();
  }

  if ( NRO and ( ( NAPS < 0 ) or ( NAPS > 2 ) ) {

    Log::error( "Encountered illegal NAPS value" );
    Log::info( "NAPS is either 0, 1 or 2 when an energy dependent scattering "
               "radius is given (NRO = 1)" );
    Log::info( "NRO value: {}", int( NRO ) );
    Log::info( "NAPS value: {}", NAPS );
    throw std::exception();
  }

  if ( NRO and ( LRU = 1 ) and ( LRF = 7 ) ) {

    Log::error( "An energy dependent scattering radius is not allowed for "
                "a Limited R-matrix resonance range (LRU = 1, LRF = 7)" );
    Log::info( "NRO value: {}", int( NRO ) );
    throw std::exception();
  }
}
