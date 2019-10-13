static void
verifySize( int NPL, int NCH ) {

  if ( NPL / 6. != NCH ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NCH" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NCH value: {}", NCH );
    throw std::exception();
  }
}
