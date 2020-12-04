static void
verifyNNF( const std::vector< DecayConstants >& lists ) {

  int NNF = lists[0].NNF();
  for ( const auto& entry : lists ) {

    if ( entry.NNF() != NNF ) {

      Log::error( "Encountered inconsistent NNF values over all decay constants" );
      Log::info( "Expected NNF = {}", NNF );
      Log::info( "Found NNF = {}", entry.NNF() );
      throw std::exception();
    }
  }
}
