static void
checkValue( int value, const std::string& name ) {

  if ( ( value != 0 ) && ( value != 1 ) ) {

    Log::error( "Encountered illegal {} value", name );
    Log::info( "{} must be equal to 0 or 1", name );
    Log::info( "{} value: {}", name, value );
    throw std::exception();
  }
}

