/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] tmod            the moderator temperature values
 *  @param[in] teff            the effective temperature values
 */
EffectiveTemperature( std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& tmod,
                      std::vector< double >&& teff )
  try : TabulationRecord( 0.0, 0.0, 0, 0,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( tmod ),
                          std::move( teff ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing effective temperature "
               "data" );
    throw;
  }

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
EffectiveTemperature( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading effective temperature "
               "data" );
    throw;
  }
