//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ShortRangeRMatrixLimitedBlock() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] parameters     the resonance parameters with covariance data
 *  @param[in] covariances    the covariance matrix
 */
ShortRangeRMatrixLimitedBlock( std::vector< ResonanceParameters >&& parameters,
                               CovarianceMatrix&& covariances ) :
  parameters_( std::move( parameters ) ),
  covariance_( std::move( covariances ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
ShortRangeRMatrixLimitedBlock( std::vector< ResonanceParameters >&& parameters,
                               Iterator& begin,
                               const Iterator& end,
                               long& lineNumber,
                               int MAT, int MF, int MT ) :
  ShortRangeRMatrixLimitedBlock( std::move( parameters ),
                                 CovarianceMatrix( begin, end, lineNumber,
                                                   MAT, MF, MT ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
ShortRangeRMatrixLimitedBlock( ControlRecord&& cont,
                               Iterator& begin,
                               const Iterator& end,
                               long& lineNumber,
                               int MAT, int MF, int MT ) :
  ShortRangeRMatrixLimitedBlock(
      readSequence< ResonanceParameters >( begin, end, lineNumber,
                                           MAT, MF, MT, cont.N2() ),
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
ShortRangeRMatrixLimitedBlock(
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try : ShortRangeRMatrixLimitedBlock( ControlRecord( it, end, lineNumber,
                                                      MAT, MF, MT ),
                                       it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing short range resonance and "
               "covariance parameters in the R-matrix limited representation" );
    throw;
  }
