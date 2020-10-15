//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
LegendreCoefficients() = default;
#endif

/**
 *  @brief Private constructor
 */
LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the incident energy value
 *  @param[in] coefficients    the Legendre coefficients
 */
LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
  // this can never fail, try-catch would be unreachable
  LegendreCoefficients( ListRecord( 0.0, energy, 2, 0,
                                    coefficients.size() - 1,
                                    std::move( coefficients ) ) ) {}

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
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try : LegendreCoefficients( ListRecord( it, end, lineNumber,
                                          MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Legendre coefficients "
               "(LAW=5 LTP=2)" );
    throw;
  }
