//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DistributionFunction() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] x               the x values
 *  @param[in] g               the function values
 */
DistributionFunction( std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& x,
                      std::vector< double >&& g )
  try : TabulationRecord( 0.0, 0.0, 0, 0,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( x ),
                          std::move( g ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a distribution function" );
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
DistributionFunction( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a distribution function" );
    throw;
  }
