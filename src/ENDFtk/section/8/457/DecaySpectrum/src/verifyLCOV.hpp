static void
verifyLCOV( int LCOV ) {

  if ( LCOV != 0 ) {

    Log::error( "Encountered unsupported LCOV value: {}", LCOV );
    throw std::exception();
  }
}
