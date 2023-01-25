//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CompactSingleLevelBreitWigner() = default;
#endif

/**
 *  @brief Constructor with scattering radius uncertainty
 *
 *  @param[in] spi           the target spin value
 *  @param[in] ap            the scattering radius
 *  @param[in] dap           the scattering radius uncertainty data
 *  @param[in] parameters    the resonance parameters and uncertainties
 *  @param[in] matrix        the correlation matrix
 */
CompactSingleLevelBreitWigner( double spi, double ap, double dap,
                               CompactBreitWignerUncertainties&& parameters,
                               CompactCorrelationMatrix&& matrix ) :
  // no need for a try ... catch: nothing can go wrong here
  CompactCovarianceBase( spi, ap, std::move( dap ), 0., 0.,
                         std::move( parameters ), std::move( matrix ) ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation for "
               "the compact covariance format (LCOMP = 2)" );
    throw;
  }

/**
 *  @brief Constructor without scattering radius uncertainty
 *
 *  @param[in] spi           the target spin value
 *  @param[in] ap            the scattering radius
 *  @param[in] parameters    the short range covariance blocks
 *  @param[in] matrix        the long range covariance blocks
 */
CompactSingleLevelBreitWigner( double spi, double ap, 
                               CompactBreitWignerUncertainties&& parameters,
                               CompactCorrelationMatrix&& matrix ) :
  // no need for a try ... catch: nothing can go wrong here
  CompactCovarianceBase( spi, ap, 0, 0, std::move( parameters ),
                         std::move( matrix ) ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation for "
               "the compact covariance format (LCOMP = 2)" );
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
CompactSingleLevelBreitWigner( Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT ) :
  // no try ... catch: exceptions will be handled in the derived class
  CompactCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the Single Level Breit-Wigner representation for "
               "the compact covariance format (LCOMP = 2)" );
    throw;
  }
