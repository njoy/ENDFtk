/**
 *  @brief Constructor
 *
 *  @param[in] spin      the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] lssf      the self-shielding only flag
 *  @param[in] lvalues   the l values and the resonance parameters
 */
UnresolvedEnergyIndependent( double spin, double ap, bool lssf,
                             std::vector< LValue >&& lvalues )
    // no need for a try ... catch: nothing can go wrong here
    try: UnresolvedBase( spin, ap, lssf, std::move( lvalues ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing unresolved resonance "
                 "parameters in the Single Level Breit-Wigner representation "
                 "with energy independent widths (without fission)" );
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
UnresolvedEnergyIndependent( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT )
  try : UnresolvedBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing unresolved resonance "
               "parameters in the Single Level Breit-Wigner representation "
               "with energy independent widths (without fission)" );
    throw;
  }
