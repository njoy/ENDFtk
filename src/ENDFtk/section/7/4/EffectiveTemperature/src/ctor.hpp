/** 
 *  @brief Constructor
 *
 *  @param[in] boundaries              the interpolation range boundaries
 *  @param[in] interpolants            the interpolation types for each range
 *  @param[in] moderatorTemperatures   the moderator temperature values
 *  @param[in] effectiveTemperatures   the effective temperature values
 */
EffectiveTemperature( std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& moderatorTemperatures,
                      std::vector< double >&& effectiveTemperatures ) :
  TabulationRecord( 0.0, 0.0, 0, 0,
                    std::move( boundaries ),
                    std::move( interpolants ),
                    std::move( moderatorTemperatures ),
                    std::move( effectiveTemperatures ) ) {}

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
EffectiveTemperature( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT ) :
  TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}

