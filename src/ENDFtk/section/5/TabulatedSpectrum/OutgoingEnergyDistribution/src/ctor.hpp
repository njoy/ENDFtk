/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy value
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the outgoing energy values
 *  @param[in] probabilities   the probability values
 */
OutgoingEnergyDistribution( double incident,
                            std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< double >&& energies,
                            std::vector< double >&& probabilities )
  try : TabulationRecord( 0.0, incident, 0, 0,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( probabilities ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing an outgoing energy "
               "distribution (LF=1)" );
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
OutgoingEnergyDistribution( Iterator& begin, const Iterator& end,
                            long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading an outgoing energy "
               "distribution (LF=1)" );
    throw;
  }
