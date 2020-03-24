/**
 *  @brief Constructor
 *
 *  @param[in] el                 the lower energy of the resonance region
 *  @param[in] eh                 the upper energy of the resonance region
 *  @param[in] naps               the flag to indicate then on how to calculate
 *                                the scattering radius (0 or 1 if no energy
 *                                dependent scattering radius is given and 0, 1
 *                                or 2 if energy dependent scattering radius is
 *                                given)
 *  @param[in] parameters         the resonance parameters
 *  @param[in] scatteringRadius   An optional energy dependent scattering radius
 */
ResonanceRange( double el, double eh, int naps,
                ResonanceParameters&& parameters,
                std::optional< ScatteringRadius >&& scatteringRadius = std::nullopt )
  try : el_( el ), eh_( eh ), naps_( naps ),
        parameters_( std::move( parameters ) ),
        scattering_radius_( std::move( scatteringRadius ) ) {

    verifyOptions( this->NRO(), this->NAPS(), this->LRU(), this->LRF() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a resonance range" );
    throw;
  }
