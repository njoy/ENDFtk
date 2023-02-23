//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
GeneralRMatrixLimited() = default;
#endif

//! @todo enable this when the scattering radius uncertainty format is ready
// /**
//  *  @brief Constructor with scattering radius uncertainty
//  *
//  *  @param[in] awri      the atomic mass ratio
//  *  @param[in] cshort    the short range covariance blocks
//  */
// GeneralRMatrixLimited( awri,
//                        ReichMooreScatteringRadiusUncertainties&& dap,
//                        std::vector< ShortRangeReichMooreBlock >&& cshort ) :
//   // no need for a try ... catch: nothing can go wrong here
//   GeneralCovarianceBase( awri, 0., 0., std::move( dap ), 0,
//                          std::move( cshort ), {} ) {
//
//     Log::info( "Encountered error while constructing resonance and covariance "
//                "parameters in the R-matrix limited representation for the general "
//                "covariance format (LCOMP = 1)" );
//     throw;
//   }

/**
 *  @brief Constructor without scattering radius uncertainty
 *
 *  @param[in] awri      the atomic mass ratio
 *  @param[in] cshort    the short range covariance blocks
 */
GeneralRMatrixLimited( double awri,
                       std::vector< ShortRangeRMatrixLimitedBlock >&& cshort )
  try : GeneralCovarianceBase( awri, 0., 0., 0, std::move( cshort ), {} ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the R-matrix limited representation for the general "
               "covariance format (LCOMP = 1)" );
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
GeneralRMatrixLimited( Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT )
  try : GeneralCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance and covariance "
               "parameters in the R-matrix limited representation for the general "
               "covariance format (LCOMP = 1)" );
    throw;
  }
