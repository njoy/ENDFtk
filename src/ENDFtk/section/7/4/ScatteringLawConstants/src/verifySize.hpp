static void
verifySize( int NI, int NS ) {

  if ( NS > 3 ) {

    Log::error( "Encountered illegal NS value" );
    Log::info( "NS must be smaller than or equal to 3" );
    Log::info( "NS value: {}", NS );
    throw std::exception();
  }

  if ( NI != 6 * ( NS + 1 ) ) {

    Log::error( "Encountered illegal NI and NS values" );
    Log::info( "NI must be equal to 6*(NS + 1)" );
    Log::info( "NI value: {}", NI );
    Log::info( "NS value: {}", NS );
    throw std::exception();
  }
}
