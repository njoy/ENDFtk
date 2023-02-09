//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CompactReichMoore() = default;
#endif

/**
 *  @brief Constructor with scattering radius uncertainty
 *
 *  @param[in] spi           the target spin value
 *  @param[in] ap            the scattering radius
 *  @param[in] lad           the angular distribution flag
 *  @param[in] dap           the scattering radius uncertainty data
 *  @param[in] parameters    the resonance parameters and uncertainties
 *  @param[in] matrix        the correlation matrix
 */
CompactReichMoore( double spi, double ap, bool lad,
                   ReichMooreScatteringRadiusUncertainties&& dap,
                   CompactReichMooreUncertainties&& parameters,
                   CompactCorrelationMatrix&& matrix )
  // no need for a try ... catch: nothing can go wrong here
  try : CompactCovarianceBase( spi, ap, std::move( dap ),
                         static_cast< long >( lad ), 0.,
                         std::move( parameters ), std::move( matrix ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Reich-Moore representation for the compact "
               "covariance format (LCOMP = 2)" );
    throw;
  }

/**
 *  @brief Constructor without scattering radius uncertainty
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lad           the angular distribution flag
 *  @param[in] cshort    the short range covariance blocks
 *  @param[in] clong     the long range covariance blocks
 */
CompactReichMoore( double spi, double ap, bool lad,
                   CompactReichMooreUncertainties&& parameters,
                   CompactCorrelationMatrix&& matrix )
  try : CompactCovarianceBase( spi, ap,
                               static_cast< long >( lad ), 0,
                               std::move( parameters ),
                               std::move( matrix ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Reich-Moore representation for the compact "
               "covariance format (LCOMP = 2)" );
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
CompactReichMoore( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT )
  try : CompactCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Reich-Moore representation for the compact "
               "covariance format (LCOMP = 2)" );
    throw;
  }