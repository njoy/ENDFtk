static void
verify( int KBK1, int KBK2, int NCH1, int NCH2 ) {

  if ( KBK1 != KBK2 ) {

    Log::error( "KBK is not consistent with the number of channels with a "
                "background R-matrix value" );
    Log::info( "KBK value: {}", KBK1 );
    Log::info( "Channels with a background R-matrix value: {}", KBK2 );
    throw std::exception();
  }

  if ( NCH1 != NCH2 ) {

    Log::error( "NCH is not consistent with the background R-matrix data" );
    Log::info( "NCH value: {}", NCH1 );
    Log::info( "Number of channels from background R-matrices: {}", NCH2 );
    throw std::exception();
  }
}
