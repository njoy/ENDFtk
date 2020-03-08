static void
verifySize( unsigned int NPL, unsigned int NE ) {

  if ( NE == 0 ) {

    Log::error( "There must be at least one set of resonance parameters" );
    Log::info( "Expected NE > 0 but found {}", NE );
    throw std::exception();
  }

  if ( NPL != 6 + NE * 6 ) {

    Log::error( "The resonance parameters must be given as multiples of 6" );
    Log::info( "Expected NPL=(NE+1)*6, found NPL={} for NE={}", NPL, NE );
    throw std::exception();
  }
}
