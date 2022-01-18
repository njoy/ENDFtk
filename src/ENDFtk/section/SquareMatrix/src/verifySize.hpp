static void
verifySize( int LS, int NE, int NT ) {

  int num_values = NT-NE;

  // symmetric matrix
  if ( LS ) {

    if ( num_values != NE*(NE-1)/2 ) {

      Log::error( "Inconsistent number of values in symetric square matrix" );
      Log::info( "Expected (NE*(NE-1)/2): {}", NE*(NE-1)/2 );
      Log::info( "Observed value: {}", num_values );
      throw std::exception();
    }
  }

  // asymmetric matrix
  else {

    if ( num_values != (NE-1)*(NE-1) ) {

      Log::error( "Inconsistent number of values in symetric square matrix" );
      Log::info( "Expected ((NE-1)^2): {}", (NE-1)*(NE-1) );
      Log::info( "Observed value: {}", num_values );
      throw std::exception();
    }
  }

}
