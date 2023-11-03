static void
verifyLTY( int LTY ) {

  if ( LTY < 1 || LTY > 3 ) {

      Log::error( "Encountered illegal LTY value" );
      Log::info( "LTY must be 1,2,3 for DerivedRatioToStandard" );
      Log::info( "LTY value: {}", LTY );
      throw std::exception();
  }
}
