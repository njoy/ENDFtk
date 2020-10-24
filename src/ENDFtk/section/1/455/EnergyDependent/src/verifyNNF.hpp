static void
verifyNNF( const DecayConstant& list, long lineNumber ) {

  const bool oddNPL = ( list.NPL() & 1 );
  if ( oddNPL ) {
    Log::error( "Encountered bad NPL value" );
    Log::info( "NPL must be equal to 2 times NNF" );
    Log::info( "NPL value: {}", list.NPL() );
    Log::info( "Line number: {}", lineNumber - list.NC() );
    throw std::exception();
  }
}

static void
verifyNNF( const std::vector< DecayConstant >& lists ) {

  int NPL = lists[0].NPL();
  for ( auto& entry : lists ) {
    if ( entry.NPL() != NPL ) {
      Log::error( "Encountered inconsistent NPL values over all lists" );
      Log::info( "NPL must be equal to 2 times NNF" );
      Log::info( "NNF value: {}", NPL / 2 );
      Log::info( "NPL value: {}", entry.NPL() );
      throw std::exception();
    }
  }
}
