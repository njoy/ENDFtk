private:

/**
 *  @brief Constructor
 *
 *  The number of values in the list should be 2 * 3 or 2 * 17, this is checked.
 *
 *  @param[in] list   the ListRecord to be moved into the object
 */
DecayModes( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifyNDK( ListRecord::NPL(), this->NDK() );
}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DecayModes() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] spin       the spin of the nuclide
 *  @param[in] parity     the parity (used if spin is zero)
 *  @param[in] modes      the decay decay modes
 */
DecayModes( double spin, double parity,
            std::vector< DecayMode >&& modes ) :
  // this can never fail, try-catch would be unreachable
  DecayModes( ListRecord( spin, parity, 0, 0, modes.size(),
                          generateList( std::move( modes ) ) ) ) {}

/**
 *  @brief Constructor
 *
 *  This constructor is used for stable nuclides without decay modes and adheres
 *  strictly to ENDF rules (the list contains 6 values, all zero).
 *
 *  @param[in] spin       the spin of the nuclide
 *  @param[in] parity     the parity (used if spin is zero)
 */
DecayModes( double spin, double parity ) :
  DecayModes( ListRecord( spin, parity, 0, 0, 0,
                          { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ) ) {}

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
DecayModes( Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT )
  try : DecayModes( readListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading decay mode data" );
    throw;
  }
