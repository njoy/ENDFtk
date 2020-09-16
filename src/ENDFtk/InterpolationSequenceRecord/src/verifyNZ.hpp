static void
verifyNZ( unsigned int index, unsigned int NZ ) {

  const bool inconsistentNZ = ( index != NZ );

  if ( inconsistentNZ ) {
    
    Log::error( "Inconsistent NZ value between interpolation table and "
                "data points" );
    Log::info( "Last index interpolation table: {}", index );
    Log::info( "Number of points in data: {}", NZ );
    throw std::exception();
  }
}
