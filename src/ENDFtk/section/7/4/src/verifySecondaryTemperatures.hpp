template< typename TypeArray, typename TemperatureArray >
static void
verifySecondaryTemperatures( const TypeArray& types,
                             const TemperatureArray& temperatures ) {

  if ( types.size() != temperatures.size() ) {

    Log::error( "The data in the scattering constants and the number of "
                "provided secondary effective temperatures are inconsistent" );
    Log::info( "Expected: {} optional temperature functions", types.size() );
    Log::info( "Found: {} optional temperature functions",
               temperatures.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < types.size(); ++i ) {

    if ( ( ( types[i] == 0.0 ) && !( temperatures[i] ) ) ||
         ( ( types[i] != 0.0 ) && ( temperatures[i] ) ) ) {

      Log::error( "Available effective temperature data for secondary "
                  "scatterers inconsistent with the thermal scattering "
                  "constants data" );
      Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                 "must be given" );
      Log::info( "Encountered issue for the secondary scatterer with index={}",
                 i );
      throw std::exception();
    }
  }
}
