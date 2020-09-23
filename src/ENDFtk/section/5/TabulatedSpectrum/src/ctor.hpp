private :
/**
 *  @brief Constructor
 *
 *  @param[in] sequence   the interpolation sequence record
 */
TabulatedSpectrum(
    InterpolationSequenceRecord< OutgoingEnergyDistribution >&& sequence ) :
  data_( std::move( sequence ) ) {}

public :
/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] distributions   the incoming energy values and associated
 *                             outgoing energy distributions
 */
TabulatedSpectrum( std::vector< long >&& boundaries,
                   std::vector< long >&& interpolants,
                   std::vector< OutgoingEnergyDistribution >&& distributions )
  try : TabulatedSpectrum(
            InterpolationSequenceRecord< OutgoingEnergyDistribution >(
                InterpolationRecord( 0.0, 0.0, 0, 0,
                                     std::move( boundaries ),
                                     std::move( interpolants ) ),
                std::move( distributions ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a tabulated energy "
               "distribution (LF=1)" );
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
TabulatedSpectrum( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT )
  try : TabulatedSpectrum(
            readInterpolationSequenceRecord< OutgoingEnergyDistribution >(
                begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while reading a tabulated energy "
               "distribution (LF=1)" );
    throw;
  }
