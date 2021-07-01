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

  if ( types.size() > 0 ) {

    auto needTemperature =
      types | ranges::cpp20::views::transform( [] ( double value )
                                                  { return value == 0.0; } );

    auto haveTemperature =
      temperatures | ranges::cpp20::views::transform( hana::to<bool> );

    auto verify =
      ranges::views::zip_with( std::equal_to<>{},
                               needTemperature, haveTemperature );

    auto iter = ranges::cpp20::find( verify, false );

    if ( iter != ranges::cpp20::end( verify ) ) {

      Log::error( "Available effective temperature data for secondary "
                  "scatterers inconsistent with the thermal scattering "
                  "constants data" );
      Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                 "must be given" );
      Log::info( "Encountered issue for the secondary scatterer with index={}",
                 ranges::cpp20::distance( ranges::cpp20::begin( verify ), iter ) );
      throw std::exception();
    }
  }
}
