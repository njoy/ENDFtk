template < typename String >
static unsigned int verifyUnsigned( int value, const String& name ) {

  if ( value < 0 ) {

    Log::error( "Encountered negative integer for {}, expected an unsigned integer",
                name );
    Log::info( "{}: {}", name, value );
  }

  return static_cast< unsigned int >( value );
}
