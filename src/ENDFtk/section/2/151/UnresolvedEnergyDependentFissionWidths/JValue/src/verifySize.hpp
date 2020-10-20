static void
verifySize( unsigned int NE ) {

  if ( NE < 1 ) {

    Log::error( "There appear to be no energy dependent fission widths given" );
    throw std::exception();
  }
}
