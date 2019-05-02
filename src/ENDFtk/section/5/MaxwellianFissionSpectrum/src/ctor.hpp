/**
 *  @brief Constructor
 *
 *  You can construct a MaxwellianFissionSpectrum using any constructor for
 *  EffectiveTemperature (including copy, move, etc. constructors).
 */
template< typename... Args,
          std::enable_if_t
          < std::is_constructible
            < EffectiveTemperature, Args... >::value, 
            bool > = false >
MaxwellianFissionSpectrum( Args&&... args )
  try : EffectiveTemperature( std::forward< Args >( args )... ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a Maxwellian fission "
               "spectrum" );
    throw;
  }

