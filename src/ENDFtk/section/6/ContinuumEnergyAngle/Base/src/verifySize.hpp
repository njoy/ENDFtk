static void
verifySize( int NW, int NA, int NEP ) {

  if ( NW != NEP * ( NA + 2 ) ) {

    Log::error( "Encountered illegal NA, NW and NEP values " );
    Log::info( "NW must be equal to NEP*(NA+2) for continuum energy-angle "
               "distributions" );
    Log::info( "NW value: {}", NW );
    Log::info( "NA value: {}", NA );
    Log::info( "NEP value: {}", NEP );
    throw std::exception();
  }
}
