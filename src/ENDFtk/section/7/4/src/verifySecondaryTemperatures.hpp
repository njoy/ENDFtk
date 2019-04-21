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

    // lambdas for verifying
    auto needTemperature = [] ( double value ) -> bool
                              { return value == 0.0; };
    auto haveTemperature = [] ( const auto& value ) -> bool
                              { return value != std::nullopt; };
    auto equal = [] ( bool left, bool right ) -> bool
                    { return left == right; };
    auto sum = [] ( bool left, bool right ) -> bool
                  { return left and right; };

    if ( ranges::accumulate(
           ranges::view::zip_with(
                   equal,
                   types | ranges::view::transform( needTemperature ),
                   temperatures | ranges::view::transform( haveTemperature ) ),
           true,
           sum ) == false ) {

      Log::error( "Available effective temperature data for secondary "
                  "scatterers inconsistent with the thermal scattering "
                  "constants data" );
      Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                 "must be given" );
      throw std::exception();
    }
  }
}






