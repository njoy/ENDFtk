/**
 *  @brief Constructor
 *
 *  @param[in] zap               the ZAID value for the reaction product
 *  @param[in] awp               the atomic weight ratio for the reaction
 *                               product
 *  @param[in] lip               the product modifier flag
 *  @param[in] law               the distribution type
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the x values
 *  @param[in] multiplicities    the function values
 */
Multiplicity( int zap, double awp, long lip, long law,
              std::vector< long >&& boundaries,
              std::vector< long >&& interpolants,
              std::vector< double >&& energies,
              std::vector< double >&& multiplicities )
  try : TabulationRecord( static_cast< double >( zap ), awp, lip, law,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( multiplicities ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Multiplicity" );
    throw;
  }

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] begin        the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 *  @param[in] NK           the number of partials
 */
template< typename Iterator >
Multiplicity( Iterator& begin, const Iterator& end,
              long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Multiplicity" );
    throw;
  }
