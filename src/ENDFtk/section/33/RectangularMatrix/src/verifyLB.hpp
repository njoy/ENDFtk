static void
verifyLB( int LB ) {

  if ( LB != 6 ) {

      Log::error( "Encountered illegal LB value" );
      Log::info( "LB must be 6 for RectangularMatrix" );
      Log::info( "LB value: {}", LB );
      throw std::exception();
  }
}
