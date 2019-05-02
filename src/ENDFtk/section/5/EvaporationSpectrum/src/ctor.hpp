/**
 *  @brief Constructor
 *
 *  You can construct a EvaporationSpectrum using any constructor for
 *  EffectiveTemperature (including copy, move, etc. constructors).
 */
template< typename... Args,
          std::enable_if_t
          < std::is_constructible
            < EffectiveTemperature, Args... >::value, 
            bool > = false >
EvaporationSpectrum( Args&&... args )
  try : EffectiveTemperature( std::forward<Args>(args)... ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing an evaporation spectrum" );
    throw;
  }

