/**
 *  @brief Private constructor
 */
LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
};

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the incident energy value
 *  @param[in] coefficients    the coefficients
 */
LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
  // this can never fail, try-catch would be unreachable
  LegendreCoefficients( ListRecord( 0.0, energy, 0, 0,
                                    coefficients.size(),
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
  try : LegendreCoefficients(
          ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Legendre coefficients "
               "(LAW=2 LANG=0)" );
    throw;
  }
