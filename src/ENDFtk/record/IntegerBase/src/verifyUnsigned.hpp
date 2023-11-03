template < typename String >
static unsigned int verifyUnsigned( long value, const String& name ) {

  if ( value <= 0 ) {

    Log::error( "Encountered negative or zero integer for {}, "
                "expected an unsigned integer", name );
    Log::info( "{}: {}", name, value );
  }

  return static_cast< unsigned int >( value );
}
