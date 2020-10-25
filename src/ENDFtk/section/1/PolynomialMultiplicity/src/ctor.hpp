/**
 *  @brief Constructor
 *
 *  @param[in] coefficients    the polynomial coefficients
 */
PolynomialMultiplicity( std::vector< double >&& coefficients )
  try : ListRecord( 0.0, 0.0, 0, 0, 0, std::move( coefficients ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing polynomial fission "
    	         "multiplicities" );
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
PolynomialMultiplicity( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
  try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing polynomial fission "
    	         "multiplicities" );
    throw;
  }
