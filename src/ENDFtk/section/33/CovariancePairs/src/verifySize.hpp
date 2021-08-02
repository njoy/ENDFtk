static void
verifySize( int NT, int NP ) {

  if ( NT != 2*NP ) {
    Log::error( "Number of pairs inconsistent with vector size" );
    Log::info( "NT value: {}", NT );
    Log::info( "NP value: {}", NP );
    throw std::exception();
  }

}
