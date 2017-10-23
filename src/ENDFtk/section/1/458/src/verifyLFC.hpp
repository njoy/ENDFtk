static int
verifyLFC( int LFC ) {

  if ( ! ( ( LFC == 0 ) || ( LFC == 1 ) ) ) {
    Log::error( "Illegal value detected for the LFC flag (only 0 or 1 are allowed)" );
    Log::info( "Found: {}", LFC );
    throw std::exception();
  }
  return LFC;
}
