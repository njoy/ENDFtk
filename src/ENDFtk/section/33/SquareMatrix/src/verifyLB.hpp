static void
verifyLB( int LB ) {

  if ( LB != 5 ) {

      Log::error( "Encountered illegal LB value" );
      Log::info( "LB must be 5 for SquareMatrix" );
      Log::info( "LB value: {}", LB );
      throw std::exception();
  }
}
