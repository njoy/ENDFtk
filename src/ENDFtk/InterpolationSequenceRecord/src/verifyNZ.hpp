static void
verifyNZ( unsigned int index, unsigned int NZ ) {

  if ( NZ == 0 ) {

    Log::error( "NZ should be larger than 0" );
    throw std::exception();
  }

  const bool inconsistentNZ = ( index != NZ );

  if ( inconsistentNZ ) {

    Log::error( "Inconsistent NZ value between interpolation table and "
                "data points" );
    Log::info( "Last index interpolation table: {}", index );
    Log::info( "Number of points in data: {}", NZ );
    throw std::exception();
  }
}
