static void
verifyDiscreteSize( int LCON, int size ) {

  if ( LCON != 1 and size ==0 ) {

    Log::error( "Expected at least one discrete spectrum" );
    throw std::exception();
  }
}
