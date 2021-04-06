//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
AngularDistributions() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] distributions   the sequence of angular distributions
 *  @param[in] C1              the C1 value (default 0.0)
 *  @param[in] C2              the C2 value (default 0.0)
 */
AngularDistributions( std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< Records >&& distributions,
                      double C1 = 0.0, double C2 = 0.0 ) :
  InterpolationSequenceRecord< Records >(
    InterpolationRecord( C1, C2, 0, 0,
                         std::move( interpolants ), std::move( boundaries ) ),
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
AngularDistributions( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
  InterpolationSequenceRecord< Records >(
    readInterpolationSequenceRecord< Records >( begin, end, lineNumber,
                                                MAT, MF, MT ) ) {}
