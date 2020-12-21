static void
verifySize( int NPL ) {

  if ( NPL <= 0 ) {

    Log::error( "Inconsistent data size" );
    Log::info( "Expected NNF > 0" );
    Log::info( "NNF value: {}", NPL );
    throw std::exception();
  }
}
