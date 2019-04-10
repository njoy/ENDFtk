static void
verifyDiscreteSize( int size ) {

  if ( size == 0 ) {

    Log::error( "Expected at least one discrete spectrum" );
    throw std::exception();
  }
}
