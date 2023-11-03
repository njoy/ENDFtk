static void
verifyLTY( int LTY ) {

  if ( LTY != 0 ) {

      Log::error( "Encountered illegal LTY value" );
      Log::info( "LTY must be 0 for DerivedRedundant" );
      Log::info( "LTY value: {}", LTY );
      throw std::exception();
  }
}
