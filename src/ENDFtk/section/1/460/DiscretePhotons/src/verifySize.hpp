static void
verifySize( int NG ) {

  if ( NG == 0 ) {

    Log::error( "Inconsistent data size" );
    Log::info( "Expected NG > 0" );
    Log::info( "NG value: {}", NG );
    throw std::exception();
  }
}
