static void
verifySize( int NI, int NS ) {

  if ( NI != 6 * ( NS + 1 ) ) {

    Log::error( "Encountered illegal NI and NS values" );
    Log::info( "NI must be equal to 6*(NS + 1)" );
    Log::info( "NI value: {}", NI );
    Log::info( "NS value: {}", NS );
    throw std::exception();
  }
}
