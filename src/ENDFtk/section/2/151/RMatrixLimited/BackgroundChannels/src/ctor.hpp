private:

/**
 *  @brief Constructor
 *
 *  @param[in] channels    the background R-matrix values for each channel
 */
BackgroundChannels(
    std::vector< std::optional< BackgroundRMatrix > >&& channels ) :
  channels_( std::move( channels ) ) {}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] nch         the total number of channels in the spin group
 *  @param[in] channels    the background R-matrix values for each channel
 */
BackgroundChannels( unsigned int nch,
                    std::vector< BackgroundRMatrix >&& channels )
  try : BackgroundChannels(
            makeBackgroundMatrices( nch, std::move( channels ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing channel backgrounds" );
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
BackgroundChannels( Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT, int NCH, int KBK )
  try : BackgroundChannels(
            readBackgroundMatrices( it, end, lineNumber,
                                    MAT, MF, MT, NCH, KBK ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing channel backgrounds" );
    throw;
  }
