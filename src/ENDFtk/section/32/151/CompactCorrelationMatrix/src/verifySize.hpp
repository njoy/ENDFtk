static void
verifySize( unsigned int ni, unsigned int nj, unsigned int nc ) {

  if ( !( ( ni == nj ) && ( ni == nc ) ) ) {

    Log::error( "Encountered inconsistent number of i, j and correlation values" );
    Log::info( "i.size(): {}", ni );
    Log::info( "j.size(): {}", nj );
    Log::info( "correlations.size(): {}", nc );
    throw std::exception();
  }
}
