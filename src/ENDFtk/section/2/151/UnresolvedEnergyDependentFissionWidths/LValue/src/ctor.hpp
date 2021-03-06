/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] jvalues    the unresolved resonance parameters for every J value
 *                        (NJS elements)
 */
LValue( double awri, int l, std::vector< JValue >&& jvalues )
  try : UnresolvedLValueBase< JValue >( awri, l, std::move( jvalues ) ) {

    verifySize( this->jValues() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing L value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation using energy dependent fission widths" );
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
LValue( Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try : UnresolvedLValueBase< JValue >( it, end, lineNumber, MAT, MF, MT ) {

    verifySize( this->jValues() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing L value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation using energy dependent fission widths" );
    throw;
  }
