//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DiscretePhotons() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] photons     the discrete photon data
 */
DiscretePhotons( std::vector< DiscretePhotonMultiplicity >&& multiplicities )
  try : photons_( std::move( multiplicities ) ) {

    verifySize( this->NG() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing discrete photon data" );
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
DiscretePhotons( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT,
                 int NG )
  try : DiscretePhotons(
            readSequence< DiscretePhotonMultiplicity >( begin, end, lineNumber,
                                                        MAT, MF, MT, NG ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing discrete photon data" );
    throw;
  }
