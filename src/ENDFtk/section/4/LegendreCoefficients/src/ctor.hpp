private:

/** 
 *  @brief Private intermediate constructor
 */
LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energy         the incident energy
 *  @param[in] coefficients   the Legendre coefficients
 */
LegendreCoefficients( double energy, std::vector< double >&& list ) :
  // no try-catch because it would be unreachable
  LegendreCoefficients( ListRecord( 0.0, energy, 0, 0, 0,
                                    std::move( list ) ) ) {}

/** 
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
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

    Log::info( "Encountered error while parsing Legendre coefficients" );
    throw;
  }
