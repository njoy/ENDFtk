//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ContinuousPhotons() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] energy        the incident neutron energy
 *  @param[in] constants     the precursor families decay constants
 */
ContinuousPhotons( std::vector< double >&& constants )
  try : ListRecord( 0.0, 0.0, 0, 0, 0, std::move( constants ) ) {

    verifySize( this->NNF() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing continuous delayed photon "
               "data" );
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
ContinuousPhotons( Iterator& begin, const Iterator& end,
                   long& lineNumber, int MAT, int MF, int MT )
  try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {

    verifySize( this->NNF() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing continuous delayed photon "
               "data" );
    throw;
  }
