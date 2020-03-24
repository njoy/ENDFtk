static void
verifyNIS( int NIS ) {

  if ( NIS == 0 ) {

    Log::error( "No isotopes with resonance parameters were defined" );
    Log::info( "NIS must be non zero" );
    throw std::exception();
  }
}
