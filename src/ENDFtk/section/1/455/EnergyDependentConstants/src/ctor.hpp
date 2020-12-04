/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] constants       the decay constants
 */
EnergyDependentConstants( std::vector< long >&& boundaries,
                          std::vector< long >&& interpolants,
                          std::vector< DecayConstants >&& constants )
  try : InterpolationSequenceRecord(
          InterpolationRecord( 0.0, 0.0, 0, 0,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( constants ) ) {

    // verifyNNF( this->lists_ );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing energy dependent decay "
               "constants" );
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
EnergyDependentConstants( Iterator& it, const Iterator& end,
                          long& lineNumber, int MAT, int MF, int MT )
  try : InterpolationSequenceRecord(
          readInterpolationSequenceRecord< DecayConstants >(
            it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading energy dependent decay "
               "constants" );
    throw;
  }
