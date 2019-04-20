static void
checkLANG( int lang ) {

  if ( ( lang != 1 ) and ( lang != 2 ) and ( lang != 11 ) and
       ( lang != 12 ) and ( lang != 13 ) and ( lang != 14 ) and 
       ( lang != 15 ) ) {

    Log::error( "Encountered illegal LANG value" );
    Log::info( "LANG must be equal to 1, 2, 11, 12, 13, 14 or 15" );
    Log::info( "LANG value: {}", lang );
    throw std::exception();
  }
}

