/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lad       the angular distributions flag
 *  @param[in] nlsc      the number of l values for convergence
 *  @param[in] lvalues   the l values and the resonance parameters
 */
ReichMoore( double spi, double ap, bool lad, int nlsc,
            std::vector< ReichMooreLValue >&& lvalues )
  try : BreitWignerReichMooreBase( spi, ap, lad, nlsc,
                                   std::move( lvalues ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance "
               "parameters in the Reich-Moore representation" );
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
ReichMoore( Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT )
  try : BreitWignerReichMooreBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance "
               "parameters in the Reich-Moore representation" );
    throw;
  }

