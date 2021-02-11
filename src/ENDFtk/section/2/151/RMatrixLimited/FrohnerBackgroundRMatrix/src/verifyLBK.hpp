static void
verifyLBK( int LBK ) {

  if ( LBK != 3 ) {

    Log::error( "Encountered the wrong LBK value" );
    Log::info( "Expected LBK to be equal to 3" );
    Log::info( "LBK value: {}", LBK );
    throw std::exception();
  }
}
