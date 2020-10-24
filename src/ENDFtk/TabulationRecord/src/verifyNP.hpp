static void
verifyNP( unsigned int index, unsigned int NP ) {
  const bool inconsistentNP =
    ( index != NP );

  if ( inconsistentNP ) {
    Log::error( "Inconsistent NP value between interpolation table and "
                "data table" );
    Log::info( "Last index interpolation table: {}", index );
    Log::info( "Number of points in data table: {}", NP );
    throw std::exception();
  }
}
