static void
verifyNDK( int NPL, int NDK ) {

  if ( NDK == 0 ) {
      
    if ( NPL != 6 ) {

      Log::error( "Encountered inconsistent NPL and NDK values" );
      Log::info( "NPL must be equal to 6 if NDK=0" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NDK value: {}", NDK );
      throw std::exception();
    }
  }
  else {

    if ( NPL != 6 * NDK ) {

      Log::error( "Encountered inconsistent NPL and NDK values" );
      Log::info( "NPL must be equal to 6*NDK if NDK>0" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NDK value: {}", NDK );
      throw std::exception();
    }
  }
}
