static void
verifySize( unsigned int NE ) {

  if ( NE == 0 ) {

    Log::error( "There appear to be no energy dependent fission widths given" );
    throw std::exception();
  }
}
