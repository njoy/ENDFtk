static void
verifySize( int NPL ) {

  if ( ( NPL == 0 ) || ( NPL%2 != 0 ) ) {

    Log::error( "Inconsistent data size" );
    Log::info( "Expected NPL = 2 NNF with NNF > 0" );
    Log::info( "NPL value: {}", NPL );
    throw std::exception();
  }
}
