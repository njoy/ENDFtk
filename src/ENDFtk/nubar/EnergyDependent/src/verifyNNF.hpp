static void
verifyNNF( const std::vector< ListRecord >& lists ) {

  int NPL = lists[0].NPL();
  const bool oddNPL = ( NPL & 1 );
    
  if ( oddNPL ) {
    Log::error( "NPL should be even" );
    Log::info( "list length: {}", lists[0].NPL() );
    throw std::exception();
  }

  for ( auto& entry : lists ) {
    if ( entry.NPL() != NPL ) {
      Log::error( "Inconsistent NPL in lists" );
      Log::info( "Expected: {}, found: {}", NPL, entry.NPL() );
      throw std::exception();
    }
  }
}
