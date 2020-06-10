static void
verifySize( int NREAC, int NSIGZ, int NUNR, int NW ) {

  if ( NW != ( NREAC * NSIGZ + 1 ) * NUNR + NSIGZ )  {

    Log::error( "Inconsistent data size" );
    Log::info( "Expected NW = ( NREAC * NSIGZ + 1 ) * NUNR + NSIGZ" );
    Log::info( "NW value: {}", NW );
    Log::info( "NREAC value: {}", NREAC );
    Log::info( "NSIGZ value: {}", NSIGZ );
    Log::info( "NUNR value: {}", NUNR );
    throw std::exception();
  }
}
