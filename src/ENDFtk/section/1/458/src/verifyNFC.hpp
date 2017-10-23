static int
verifyNFC( int NFC ) {

  if ( NFC < 0 ){
    Log::error( "Number of tables (NFC) must be greater than or equal to zero" );
    throw std::exception();
  }
  return NFC;
}
