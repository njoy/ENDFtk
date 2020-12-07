static void verify( int LDRV, int IFC ) {

  if ( ( LDRV != 1 ) && ( LDRV != 2 ) ) {

    Log::error( "The value for the primary evaluation flag is not recognised" );
    Log::info( "Expected LDRV equal to 1 or 2" );
    Log::info( "Found {}", LDRV );
    throw std::exception();
  }
  if ( ( IFC < 1 ) || ( IFC > 9 ) ) {

    Log::error( "The index for the energy release component is invalid" );
    Log::info( "Expected IFC between 1 and 9" );
    Log::info( "Found {}", IFC );
    throw std::exception();
  }
}
