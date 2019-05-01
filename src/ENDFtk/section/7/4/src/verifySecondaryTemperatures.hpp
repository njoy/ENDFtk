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

    auto verify = ranges::view::zip_with(
                    hana::equal,
                    types | ranges::view::transform( hana::equal.to( 0.0 ) ),
                    temperatures | ranges::view::transform( hana::to<bool> ) );

    auto iter = ranges::find_if_not( verify, hana::equal.to( true ) );

    if ( iter != ranges::end( verify ) ) {

      Log::error( "Available effective temperature data for secondary "
                  "scatterers inconsistent with the thermal scattering "
                  "constants data" );
      Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                 "must be given" );
      Log::info( "Encountered issue for the secondary scatterer with index={}",
                 ranges::distance( ranges::begin( verify ), iter ) );
      throw std::exception();
    }
  }
}

