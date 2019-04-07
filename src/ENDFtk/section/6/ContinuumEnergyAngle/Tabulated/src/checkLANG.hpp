static void
checkLANG( int lang ) {

  if ( ( lang != 11 ) && ( lang != 12 ) && ( lang != 13 ) && ( lang != 14 ) &&
       ( lang != 15 ) ) {

    Log::error( "Encountered illegal LANG value for a tabulated LAW=1" );
    Log::info( "LANG must be equal to 11, 12, 13, 14 or 15" );
    Log::info( "LANG value: {}", lang );
    throw std::exception();
  }
}

