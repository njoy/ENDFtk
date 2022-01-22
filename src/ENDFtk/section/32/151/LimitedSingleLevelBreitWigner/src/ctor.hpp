//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
LimitedSingleLevelBreitWigner() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] dap       the scattering radius uncertainty
 *  @param[in] lvalues   the l values and the resonance parameters
 */
LimitedSingleLevelBreitWigner( double spi, double ap, double dap,
                               std::vector< BreitWignerLValue >&& lvalues )
  try : LimitedCovarianceBase( spi, ap, dap, std::move( lvalues ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation" );
    throw;
  }

/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lvalues   the l values and the resonance parameters
 */
LimitedSingleLevelBreitWigner( double spi, double ap,
                               std::vector< BreitWignerLValue >&& lvalues )
  try : LimitedCovarianceBase( spi, ap, std::move( lvalues ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation" );
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
LimitedSingleLevelBreitWigner( Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT )
  try : LimitedCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation" );
    throw;
  }
