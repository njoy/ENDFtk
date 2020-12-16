/**
 *  @brief Constructor
 *
 *  @param[in] energy            the discrete photon energy
 *  @param[in] lph               the index of the discrete photon
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] time              the time values
 *  @param[in] multiplicities    the multiplicity values
 */
DiscretePhotonMultiplicity( double energy, int lph,
                            std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< double >&& time,
                            std::vector< double >&& multiplicities )
  try : TabulationRecord( energy, 0.0, lph, 0,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( time ),
                          std::move( multiplicities ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a discrete photon "
               "multiplicity" );
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
DiscretePhotonMultiplicity( Iterator& begin, const Iterator& end,
                            long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a discrete photon "
               "multiplicity" );
    throw;
  }
