/** 
 *  @brief Constructor
 *
 *  @param[in] sb                  the characteristic bound cross section
 *  @param[in] boundaries          the interpolation range boundaries
 *  @param[in] interpolants        the interpolation types for each range
 *  @param[in] temperatures        the temperature values
 *  @param[in] debyeWallerValues   the values of the Debye-Waller integral
 *                                 divided by the atomic mass (expressed
 *                                 in eV^-1)
 */
IncoherentElastic( double sb,
                   std::vector< long >&& boundaries,
                   std::vector< long >&& interpolants,
                   std::vector< double >&& temperatures,
                   std::vector< double >&& debyeWallerValues ) :
  TabulationRecord( sb, 0.0, 0, 0,
                    std::move( boundaries ),
                    std::move( interpolants ),
                    std::move( temperatures ),
                    std::move( debyeWallerValues ) ) {}

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
IncoherentElastic( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT ) :
  TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}

