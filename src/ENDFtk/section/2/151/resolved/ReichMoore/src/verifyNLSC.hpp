static void
verifyNLSC( int NLS, int NLSC ) {

  if ( NLSC < NLS ) {

    Log::error( "Encountered illegal NLSC value" );
    Log::info( "NLSC is required to be greater than or equal to NLS" );
    Log::info( "NLS value: {}", NLS );
    Log::info( "NLSC value: {}", NLSC );
    throw std::exception();
  }
}
