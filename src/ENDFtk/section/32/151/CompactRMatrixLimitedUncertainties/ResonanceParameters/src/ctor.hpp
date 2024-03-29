private:
/**
 *  @brief Private intermediate constructor
 */
ResonanceParameters( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
}

public:
//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ResonanceParameters() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] energies      the resonance energies (NRSA values)
 *  @param[in] parameters    the resonance parameters (NRSA times NCH values)
 *  @param[in] denergies     the resonance energy uncertainties (NRSA values)
 *  @param[in] dparameters   the resonance parameter uncertainties (NRSA times
 *                           NCH values)
 */
ResonanceParameters( std::vector< double >&& energies,
                     std::vector< std::vector< double > >&& parameters,
                     std::vector< double >&& denergies,
                     std::vector< std::vector< double > >&& dparameters )
  try : ResonanceParameters( generateList( std::move( energies ),
                                           std::move( parameters ),
                                           std::move( denergies ),
                                           std::move( dparameters ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance parameters" );
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
ResonanceParameters( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
  try : ResonanceParameters( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing resonance channels" );
    throw;
  }
