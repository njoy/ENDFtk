static void
checkLANG( int lang ) {

  if ( ( lang != 1 ) && ( lang != 2 ) && ( lang != 11 ) &&
       ( lang != 12 ) && ( lang != 13 ) && ( lang != 14 ) && 
       ( lang != 15 ) ) {

    Log::error( "Encountered illegal LANG value" );
    Log::info( "LANG must be equal to 1, 2, 11, 12, 13, 14 or 15" );
    Log::info( "LANG value: {}", lang );
    throw std::exception();
  }
}

