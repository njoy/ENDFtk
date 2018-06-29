/** 
 *  @brief Constructor
 *
 *  @param[in] sequence   the interpolation sequence record
 */
Tabulated( InterpolationSequenceRecord< BetaValue >&& sequence ) :
  data_( std::move( sequence ) ) {}

/** 
 *  @brief Constructor
 *
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] betas          the beta values and associated S(alpha,T)
 *                            functions
 */
Tabulated( std::vector< long >&& boundaries,
           std::vector< long >&& interpolants,
           std::vector< BetaValue >&& betas ) :
  Tabulated( InterpolationSequenceRecord< BetaValue >(
                    InterpolationRecord( 0.0, 0.0, 0, 0,
                                         std::move( boundaries ),
                                         std::move( interpolants ) ),
                    std::move( betas ) ) ) {};

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
Tabulated( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT ) :
  Tabulated( InterpolationSequenceRecord< BetaValue >( begin, end, lineNumber,
                                                       MAT, MF, MT ) ) {}

