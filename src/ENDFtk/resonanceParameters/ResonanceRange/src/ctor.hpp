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
                std::optional< ScatteringRadius > scatteringRadius = std::nullopt )
  try : el_( el ), eh_( eh ), naps_( naps ),
        parameters_( std::move( parameters ) ),
        scattering_radius_( std::move( scatteringRadius ) ) {

    verifyOptions( this->NRO(), this->NAPS(), this->LRU(), this->LRF() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a resonance range" );
    throw;
  }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
ResonanceRange( double el, double eh, int LRU, int LRF, int naps,
                std::optional< ScatteringRadius >&& scatteringRadius,
                Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) :
  ResonanceRange( el, eh, naps,
                  readParameters( begin, end, lineNumber,
                                  MAT, MF, MT, LRU, LRF ),
                  std::move( scatteringRadius ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
ResonanceRange( ControlRecord&& cont,
                Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) :
  ResonanceRange( cont.C1(), cont.C2(), cont.L1(), cont.L2(), cont.N1(),
                  readScatteringRadius( begin, end, lineNumber,
                                        MAT, MF, MT, cont.N1(), cont.N2() ),
                  begin, end, lineNumber, MAT, MF, MT ) {}

public:
/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 */
template< typename Iterator >
ResonanceRange( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) :
  ResonanceRange( ControlRecord( begin, end, lineNumber,
                                 MAT, MF, MT ),
                  begin, end, lineNumber, MAT, MF, MT ) {}
