/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the x values
 *  @param[in] transfer        the energy transfer values
 */
EnergyTransfer( std::vector< long >&& boundaries,
                std::vector< long >&& interpolants,
                std::vector< double >&& energies,
                std::vector< double >&& transfer )
  try : TabulationRecord( 0., 0., 0, 0,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( transfer ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing EnergyTransfer" );
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
EnergyTransfer( Iterator& begin, const Iterator& end,
                long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing EnergyTransfer" );
    throw;
  }
