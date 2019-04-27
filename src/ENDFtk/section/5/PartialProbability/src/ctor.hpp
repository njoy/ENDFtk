/**
 *  @brief Constructor
 *
 *  @param[in] lf              the type of the underlying distribution
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] probabilities   the probability values
 *  @param[in] constant        the energy limit constant U (default = 0.0)
 */
PartialProbability( long lf,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& energies,
                    std::vector< double >&& probabilities,
                    double u = 0.0 )
  try : TabulationRecord( u, 0.0, 0, lf,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( probabilities ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a partial probability" );
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
PartialProbability( Iterator& begin, const Iterator& end,
                    long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a partial probability" );
    throw;
  }

