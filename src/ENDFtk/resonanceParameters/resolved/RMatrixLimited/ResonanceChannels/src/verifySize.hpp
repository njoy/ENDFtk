static void
verifySize( int NPL, int NCH ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 6 * NCH" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NCH value: {}", NCH );
    throw std::exception();
  }

  if ( NCH < 1 ) {

    Log::error( "Encountered illegal NCH value" );
    Log::info( "NCH should be larger than zero" );
    Log::info( "NCH value: {}", NCH );
    throw std::exception();
  }

  if ( NPL / 6. != NCH ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NCH" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NCH value: {}", NCH );
    throw std::exception();
  }
}
