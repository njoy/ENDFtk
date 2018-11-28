/** 
 *  @brief Constructor
 *
 *  @param[in] parameters   the parameters for the Watt spectrum
 */
WattSpectrum( std::array< Parameter, 2 >&& parameters ) :
  parameters_( std::move( parameters ) ) {}

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
WattSpectrum( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT ) :
  WattSpectrum( readParameters( begin, end, lineNumber,
                                MAT, MF, MT ) ) {}
