static void
verifyNIS( int NIS ) {

  if ( NIS < 1 ) {

    Log::error( "No isotopes with resonance parameters were defined" );
    Log::info( "NIS must be greater than zero" );
    throw std::exception();
  }
}
