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

    using namespace njoy::tools;
    auto needTemperature = types | std20::views::transform( [] ( double value )
                                                               { return value == 0.0; } );

    auto haveTemperature = temperatures | std20::views::transform( [] ( auto&& value )
                                                                      { return bool( value ); } );

    std::vector< bool > verify;
    std::transform( needTemperature.begin(), needTemperature.end(), haveTemperature.begin(),
                    std::back_inserter( verify ), std::equal_to<>{} );

    auto iter = std20::find( verify, false );

    if ( iter != verify.end() ) {

      Log::error( "Available effective temperature data for secondary "
                  "scatterers inconsistent with the thermal scattering "
                  "constants data" );
      Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                 "must be given" );
      Log::info( "Encountered issue for the secondary scatterer with index={}",
                 std20::distance( std20::begin( verify ), iter ) );
      throw std::exception();
    }
  }
}
