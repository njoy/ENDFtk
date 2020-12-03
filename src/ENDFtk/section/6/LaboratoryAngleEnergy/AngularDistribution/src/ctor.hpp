/**
 *  @brief Constructor
 *
 *  @param[in] energy           the incident energy
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the secondary energy distributions
 */
AngularDistribution(
    double energy,
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< EnergyDistribution >&& distributions )
  try : InterpolationSequenceRecord(
          InterpolationRecord( 0.0, energy, 0, 0,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( distributions ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing angular distribution data "
               "(LAW=7)" );
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
AngularDistribution( Iterator& it, const Iterator& end,
                                  long& lineNumber, int MAT, int MF, int MT )
  try : InterpolationSequenceRecord(
          readInterpolationSequenceRecord< EnergyDistribution >(
            it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading angular distribution data "
               "(LAW=7)" );
    throw;
  }
