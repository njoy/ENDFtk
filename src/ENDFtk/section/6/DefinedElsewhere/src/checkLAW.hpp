static void
checkLAW( int law ) {

  if ( ( law != -4 ) and ( law != -5 ) and
       ( law != -14 ) and ( law != -15 ) ) {

    Log::error( "Encountered illegal negative LAW value" );
    Log::info( "LANG must be equal to -4, -5, -14 or -15" );
    Log::info( "LANG value: {}", law );
    throw std::exception();
  }
}

