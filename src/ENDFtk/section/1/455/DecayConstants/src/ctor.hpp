/**
 *  @brief Constructor
 *
 *  @param[in] energy        the incident neutron energy
 *  @param[in] constants     the precursor families decay constants
 *  @param[in] abundances    the precursor families decay abundancies
 */
DecayConstants( double energy, std::vector< double >&& constants,
                std::vector< double >&& abundances )
  try : ListRecord( 0.0, energy, 0, 0, 0,
                    generateList( std::move( constants ),
                                  std::move( abundances ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while decay constant data" );
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
DecayConstants( Iterator& begin, const Iterator& end,
                long& lineNumber, int MAT, int MF, int MT )
  try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {

    verifySize( this->NPL() );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while decay constant data" );
    throw;
  }
