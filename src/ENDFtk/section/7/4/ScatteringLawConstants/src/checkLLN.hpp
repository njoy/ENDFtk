static void
checkLLN( int value ) {

  if ( ( value != 0 ) && ( value != 1 ) ) {

    Log::error( "Encountered illegal LLN value" );
    Log::info( "LLN must be equal to 0 or 1" );
    Log::info( "LLN value: {}", value );
    throw std::exception();
  }
}

