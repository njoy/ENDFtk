static void
verifySize( int NLS ) {

  if ( NLS < 1 ) {

    Log::error( "Encountered illegal NLS value" );
    Log::info( "NLS should be larger than zero" );
    Log::info( "NLS value: {}", NLS );
    throw std::exception();
  }
}
