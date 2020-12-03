//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
InterpolationRecord() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] C1             the double in column 1 on line 1
 *  @param[in] C2             the double in column 2 on line 1
 *  @param[in] L1             the integer in column 3 on line 1
 *  @param[in] L2             the integer in column 4 on line 1
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 */
InterpolationRecord ( double C1, double C2, long L1, long L2,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants )
  try : InterpolationBase( C1, C2, L1, L2,
                           std::move( boundaries ),
                           std::move( interpolants ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing TAB2 record" );
    throw e;
  }

/**
 *  @brief Constructor
 *
 *  @param[in] C1         the double in column 1 on line 1
 *  @param[in] C2         the double in column 2 on line 1
 *  @param[in] L1         the integer in column 3 on line 1
 *  @param[in] L2         the integer in column 4 on line 1
 *  @param[in] regions    the interpolation regions
 */
InterpolationRecord ( double C1, double C2, long L1, long L2,
                      std::tuple< std::vector< long >,
                                  std::vector< long > >&& regions ) :
  InterpolationRecord( C1, C2, L1, L2, std::move( std::get< 0 >( regions ) ),
                       std::move( std::get< 1 >( regions ) ) ) {}

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
InterpolationRecord
( Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT )
  try :
    InterpolationBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( IllegalN2& e ) {
    Log::error( "Illegal NZ value encountered" );
    Log::info( "NZ (or number of zones) must be greater than or equal to 1" );
    Log::info( "NZ value: {}", e.n2 );
    Log::info( "Error encountered while parsing TAB2 record" );
    throw std::exception();
  }
  catch ( InconsistentN2& e ) {
    Log::error( "Inconsistent value for NZ" );
    Log::info( "Expected {} as the largest index but found {}", e.n2, e.index );
    Log::info( "Error encountered while parsing TAB2 record" );
    throw std::exception();
  }
  catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing TAB2 record" );
    throw std::exception();
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while parsing TAB2 record" );
    throw e;
  }
