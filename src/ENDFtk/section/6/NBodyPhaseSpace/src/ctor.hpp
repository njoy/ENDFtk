/**
 *  @brief Constructor
 *
 *  @param[in] aspx    the particle mass (in neutron mass units)
 *  @param[in] npsx    the number of particles
 */
NBodyPhaseSpace( double apsx, long npsx ) :
  // this can never fail, try-catch would be unreachable
  ControlRecord( apsx, 0.0, 0, 0, 0, npsx ) {}

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
NBodyPhaseSpace( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT )
  try : ControlRecord( begin, end, lineNumber, MAT, MF, MT  ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading n-body phase space "
               "distribution data (LAW=6)" );
    throw;
  }
