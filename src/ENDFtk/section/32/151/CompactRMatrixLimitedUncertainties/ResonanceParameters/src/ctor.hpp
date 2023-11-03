private:
/**
 *  @brief Private intermediate constructor
 */
ResonanceParameters( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energies      the resonance energies (NRS values)
 *  @param[in] parameters    the resonance parameters (NRS times NCH values)
 *  @param[in] denergies     the resonance energy uncertainties (NRS values)
 *  @param[in] dparameters   the resonance parameter uncertainties (NRS times
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
