static void
verifyDiscreteSize( int LCON, int size ) {

  if ( LCON == 2 and size ==0 ) {

    Log::error( "Expected at least one discrete spectrum for LCON 2" );
    throw std::exception();
  }
}
