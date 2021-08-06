static void
verifyLB( int LB, int LT ) {

  switch( LB ) {

    case 0:
    case 1:
    case 2:
    case 8:
    case 9:
      if ( LT != 0 ) {
        Log::error( "Encountered illegal LT value" );
        Log::info( "LT must be equal to 0 for LB=0,1,2,8,9" );
        Log::info( "LT value: {}", LT );
        throw std::exception();
      }
      break;

    case 3:
    case 4:
      if ( LT <= 0 ) {
        Log::error( "Encountered illegal LT value" );
        Log::info( "LT must be positive for LB=3,4" );
        Log::info( "LT value: {}", LT );
        throw std::exception();
      }
      break;

    default:
      Log::error( "Encountered illegal LB value" );
      Log::info( "LB must be 0,1,2,3,4,8,9 for CovariancePairs" );
      Log::info( "LB value: {}", LB );
      throw std::exception();

  }

}
