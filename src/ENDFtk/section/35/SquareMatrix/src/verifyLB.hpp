static void
verifyLB( int LB ) {

  if ( LB != 7 ) {

      Log::error( "Encountered illegal LB value" );
      Log::info( "LB must be 7 for SquareMatrix in MF35" );
      Log::info( "LB value: {}", LB );
      throw std::exception();
  }
}
