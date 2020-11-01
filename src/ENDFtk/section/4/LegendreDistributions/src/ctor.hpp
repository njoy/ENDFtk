/** 
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] distributions   the sequence of angular distributions
 */
LegendreDistributions( std::vector< long >&& boundaries,
                       std::vector< long >&& interpolants,
                       std::vector< LegendreCoefficients >&& distributions ) :
  AngularDistributions( std::move( interpolants ), std::move( boundaries ),
                        std::move( distributions ) ) {}

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
LegendreDistributions( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT ) :
  AngularDistributions( begin, end, lineNumber, MAT, MF, MT  ) {}
