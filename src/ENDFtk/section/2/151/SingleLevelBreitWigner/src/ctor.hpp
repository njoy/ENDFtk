//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
SingleLevelBreitWigner() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lvalues   the l values and the resonance parameters
 */
SingleLevelBreitWigner( double spi, double ap,
                        std::vector< BreitWignerLValue >&& lvalues )
  try : BreitWignerReichMooreBase( spi, ap, false, 0,
                                   std::move( lvalues ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance "
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
SingleLevelBreitWigner( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try : BreitWignerReichMooreBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance "
               "parameters in the Single Level Breit-Wigner representation" );
    throw;
  }
