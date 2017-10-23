static void
verifyNPLY( int L2, int N1 ) {

  if ( N1 != 18 * ( L2 + 1 ) ) {
    Log::error( "NPL should be a multiple of 18" );
    Log::info( "Expected: {}, found: {}", 18 * ( L2 + 1 ), N1 );
    throw std::exception();
  }
}
